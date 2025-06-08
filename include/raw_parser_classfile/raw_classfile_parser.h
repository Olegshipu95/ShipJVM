#ifndef SHIP_JVM_RAW_PARSER_H
#define SHIP_JVM_RAW_PARSER_H

#ifdef DEBUG
#include <assert.h>
#endif

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raw_attribute_info.h"
#include "raw_attribute_parser.h"
#include "raw_classfile.h"
#include "raw_classfile_stream.h"
#include "raw_constant_pool.h"
#include "util.h"

int parse_class_file (struct class_file *class, const char *filename);

#endif
