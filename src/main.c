#include <stdint.h>

#include "classfile_parser.h"

// Пример использования
int main(int argc, char* argv[]) { 
    printf("Argc: %d, pointer for argv: %p\n", argc, argv); // for analyzers
    return parse_class_file(); 
}
