#pragma once

#include "classfile.h"

struct classloader;

struct classloader *classloader_new (void);

void classloader_init_dir_paths (struct classloader *classloader,
                                 const char *paths);

int classloader_load_class (struct classloader *classloader,
                            const char *classname, struct class_file **result);
