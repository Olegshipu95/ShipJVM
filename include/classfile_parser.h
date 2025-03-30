#ifndef SHIP_JVM_PARSER_H
#define SHIP_JVM_PARSER_H

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "classfile.h"
#include "classfile_stream.h"
#include "constant_pool.h"

int parse_class_file();

#endif