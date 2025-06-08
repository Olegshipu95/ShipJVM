#ifndef SHIP_JVM_CLASSLOADER_H
#define SHIP_JVM_CLASSLOADER_H

#include "runtime_class.h"

struct heap;
/**
 * Creates and initializes a new class loader instance.
 *
 * @return A pointer to the newly allocated class loader structure,
 *         or NULL if memory allocation fails.
 *
 * @note The returned class loader has no search paths initialized.
 *       Use `classloader_init_dir_paths()` to set up class search paths.
 */
struct classloader *classloader_new (void);

/**
 * Initializes the class search paths for the class loader from a
 * colon-separated string.
 *
 * @param classloader The class loader instance to configure
 * @param paths       Colon-separated list of directories to search for class
 * files (e.g., "/usr/lib/jvm:/home/user/classes")
 *
 * @note This function performs memory allocation to store individual path
 * copies. The input string is not modified or retained.
 * @note Paths are searched in the order they appear in the string.
 * @note Subsequent calls will overwrite previously set paths.
 */
void classloader_init_dir_paths (struct classloader *classloader,
                                 const char *paths);

/**
 * Loads a Java class file by its fully qualified name.
 *
 * @param classloader The class loader instance to use
 * @param classname   Fully qualified class name (e.g., "java.lang.Object")
 * @param result      Output parameter for the loaded class structure
 *
 * @return 0 on success, or an error code if:
 *         - ENOENT: Class not found in any search path
 *         - Other system errors (e.g., file access errors, memory allocation
 * failures)
 *
 * @note The loaded class structure is cached in the class loader's trie
 * structure.
 * @note Subsequent calls for the same class will return the cached version.
 * @note The caller does not own the returned class_file structure - it's
 * managed by the class loader's lifetime.
 */
int classloader_load_class (struct classloader *classloader, struct heap *heap,
                            const char *classname, struct jclass **result);

#endif
