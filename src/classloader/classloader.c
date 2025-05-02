#include "classloader.h"

#include <stdio.h>

#include "classfile_parser.h"
#include "util.h"


struct classloader_trie
{

  // next node in current level
  struct classloader_trie *next;

  // node name (package or class name)
  const char *name;

  // children trie nodes
  struct classloader_trie *children;

  // associated value
  // since we may have class named same as a package,
  // both "children" and "value" makes sense to be presented simultaneously
  // because of this, we may always hold only zero or one node with the same name on a same level
  struct class_file *value;
};

// TODO: обработка ошибок выделения памяти (в ядре malloc может кинуть NULL при нехватке)

// initialize trie node with the first path of classname
// returns length of the first path
size_t
classloader_trie_init(struct classloader_trie *node, const char *classname)
{
  node->next = NULL;
  node->children = NULL;
  node->value = NULL;

  size_t len = 0;
  while (classname[len] && classname[len] != '.') ++len;

  char *name = my_alloc_array(char, len + 1);
  memcpy(name, classname, len);
  name[len] = 0;

  node->name = name;
  return len;
}

// find node in trie and create it if needed
struct class_file **
classloader_trie_find(struct classloader_trie **root, const char *classname, int create)
{
  struct classloader_trie **node = root;
  while (*node)
  {
    // check is the current prefix of classname matches with current node name

    size_t len = 0;
    for (const char *it = (*node)->name; *it; ++it, ++len)
      if (classname[len] != *it) goto next;

    // are we fully matching the name?
    if (classname[len] && classname[len] != '.')
    {
next:
      node = &(*node)->next;
      continue;
    }

    // if classname ended, we are reached the searching value
    if (!classname[len]) return &(*node)->value;

    classname = classname + (len + 1);
    node = &(*node)->children;
  }

  if (!create) return NULL;

  while (1)
  {
    *node = my_alloc(struct classloader_trie);
    classname += classloader_trie_init(*node, classname);

    if (!*classname) return &(*node)->value;
    ++classname;

    node = &(*node)->children;
  }
}

struct classloader
{

  // NULL-terminated array of directory paths
  const char **dir_paths;

  // trie is built by package names
  struct classloader_trie *classes;
};

struct classloader *
classloader_new(void)
{
  struct classloader *classloader = my_alloc(struct classloader);
  if (!classloader) return NULL;

  classloader->dir_paths = NULL;
  classloader->classes = NULL;
  return classloader;
}

void
classloader_init_dir_paths(struct classloader *classloader, const char *paths)
{
  size_t values = 0, started = 0;
  for (const char *it = paths; *it; ++it)
  {
    if (*it == ':')
    {
      values += started;
      started = 0;
      continue;
    }

    started = 1;
  }

  values += started;
  started = 0;

  classloader->dir_paths = my_alloc_array(const char *, values + 1);

  values = 0;
  const char *prev = paths;
  const char *it = paths;
  for (; *it; ++it)
  {
    if (*it == ':')
    {
      if (started)
      {
        const size_t len = it - prev;
        char *const val = my_alloc_array(char, len + 1);
        memcpy(val, prev, len);
        val[len] = 0;

        classloader->dir_paths[values] = val;
      }

      prev = it + 1;

      values += started;
      started = 0;
      continue;
    }

    started = 1;
  }

  if (started)
  {
    const size_t len = it - prev;
    char *const val = my_alloc_array(char, len + 1);
    memcpy(val, prev, len);

    classloader->dir_paths[values] = val;
    ++values;
  }

  classloader->dir_paths[values] = NULL;
}

char *
classloader_build_path(const char *path, const char *classname)
{
  const size_t path_len = strlen(path);
  const size_t classname_len = strlen(classname);

  char * const res = my_alloc_array(char, path_len + 1 + classname_len + 6 + 1);
  memcpy(res, path, path_len);
  res[path_len] = '/';

  for (size_t i = 0; i < classname_len; ++i)
  {
    res[path_len + 1 + i] = classname[i] == '.' ? '/' : classname[i];
  }

  memcpy(res + path_len + 1 + classname_len, ".class", 6);
  res[path_len + 1 + classname_len + 6] = 0;

  return res;
}

int
_classloader_load_class(
  struct classloader *classloader,
  const char *path,
  const char *classname,
  struct class_file ** result
)
{
  (void) classloader;
  char *class_path = classloader_build_path(path, classname);

  printf("Built path to class: %s\n", class_path);

  struct class_file class;
  const int err = parse_class_file(&class, class_path);
  if (err) return err;

  struct class_file *entry = my_alloc(struct class_file);
  *entry = class;

  *classloader_trie_find(&classloader->classes, classname, 1) = entry;
  *result = entry;
  return 0;
}

int
classloader_load_class(
  struct classloader *classloader,
  const char *classname,
  struct class_file ** result
)
{
  struct class_file **const found = classloader_trie_find(&classloader->classes, classname, 0);
  if (found)
  {
    *result = *found;
    return 0;
  }

  for (const char **it = classloader->dir_paths; *it; ++it)
  {
    const int err = _classloader_load_class(classloader, *it, classname, result);
    if (err != ENOENT) return err;
  }

  return ENOENT;
}
