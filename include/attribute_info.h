#ifndef SHIP_JVM_ATTR_INFO_H
#define SHIP_JVM_ATTR_INFO_H

#include <stdint.h>
#include "classfile.h"


#define ITEM_Top 0
#define ITEM_Integer 1
#define ITEM_Float 2
#define ITEM_Double 3
#define ITEM_Long 4
#define ITEM_Null 5
#define ITEM_UninitializedThis 6
#define ITEM_Object 7
#define ITEM_Uninitialized 8

#define ATTRIBUTE_ConstantValue 0
#define ATTRIBUTE_Code 1
#define ATTRIBUTE_StackMapTable 2
#define ATTRIBUTE_Exceptions 3
#define ATTRIBUTE_InnerClasses 4
#define ATTRIBUTE_EnclosingMethod 5
#define ATTRIBUTE_Synthetic 6
#define ATTRIBUTE_Signature 7
#define ATTRIBUTE_SourceFile 8
#define ATTRIBUTE_SourceDebugExtension 9
#define ATTRIBUTE_LineNumberTable 10
#define ATTRIBUTE_LocalVariableTable 11
#define ATTRIBUTE_LocalVariableTypeTable 12
#define ATTRIBUTE_Deprecated 13
#define ATTRIBUTE_RuntimeVisibleAnnotations 14
#define ATTRIBUTE_RuntimeInvisibleAnnotations 15
#define ATTRIBUTE_RuntimeVisibleParameterAnnotations 16
#define ATTRIBUTE_RuntimeInvisibleParameterAnnotations 17
#define ATTRIBUTE_RuntimeVisibleTypeAnnotations 18
#define ATTRIBUTE_RuntimeInvisibleTypeAnnotations 19
#define ATTRIBUTE_AnnotationDefault 20
#define ATTRIBUTE_BootstrapMethods 21
#define ATTRIBUTE_MethodParameters 22

#define ATTRIBUTE_INVALID 99

struct attribute_info {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t *info;  // size = attribute_length
};

struct exception_table_entry {
  uint16_t start_pc;  // Начальная инструкция (offset в code[])
  uint16_t end_pc;  // Конечная инструкция (не включительно)
  uint16_t handler_pc;  // Инструкция обработчика
  uint16_t
      catch_type;  // Тип исключения (индекс в пуле констант, 0 = catch all)
};

struct code_attribute {
  uint16_t max_stack;    // Макс. глубина стека
  uint16_t max_locals;   // Число локальных переменных
  uint32_t code_length;  // Длина байт-кода
  uint8_t *code;         // Байт-код (массив инструкций)
  uint16_t exception_table_length;
  struct exception_table_entry *exception_table;  // Таблица исключений
  uint16_t attributes_count;
  struct attribute_info *attributes;  // Вложенные атрибуты (например, LineNumberTable)
};

 struct line_number_table_entry{
  uint16_t start_pc;        // Смещение в байт-коде
  uint16_t line_number;     // Номер строки в исходном файле
} ;

struct LineNumberTable_attribute{
  uint16_t line_number_table_length;
  struct line_number_table_entry *entries;
};

typedef struct {
  uint16_t sourcefile_index; // Индекс в пуле констант (имя файла, например "Hello.java")
} SourceFile_attribute;

typedef struct {
  uint16_t number_of_exceptions;
  uint16_t *exception_index_table; // Индексы в пуле констант (CONSTANT_Class)
} exceptions_attribute;

enum ATTRIBUTE_TYPE {
  CODE_AT,
  BOOTSTRAP_METHODS_AT,
  LocalVariableTable_AT,
  METHOD_PARAMETERS_AT,
  RUNTIME_VISIBLE_ANNOTATIONS_AT,
  // todo delete when implemnt all
  UNKNOWN_AT
};



#endif