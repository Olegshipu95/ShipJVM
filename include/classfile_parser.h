#ifndef SHIP_JVM_PARSER_H
#define SHIP_JVM_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include "classfile_stream.h"
#include "constant_pool.h"
#include "classfile.h"

int parse_class_file();

#endif