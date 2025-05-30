#ifndef SHIP_JVM_PARSER_H
#define SHIP_JVM_PARSER_H

#ifdef DEBUG
#include <assert.h>
#endif

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "attribute_info.h"
#include "attribute_parser.h"
#include "classfile.h"
#include "classfile_stream.h"
#include "constant_pool.h"
#include "util.h"

int parse_class_file (struct class_file *class, const char *filename);

#endif
