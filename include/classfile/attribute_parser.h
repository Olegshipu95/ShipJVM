#ifndef SHIP_JVM_ATTR_PARSER_H
#define SHIP_JVM_ATTR_PARSER_H

#include <stdlib.h>

#include "attribute_info.h"
#include "classfile_parser.h"
#include "classfile_stream.h"
#include "constant_pool.h"
#include "util.h"

struct attribute_info *parse_attribute (Loader *loader,
                                        struct class_file *class);
int read_attributes (Loader *loader, struct class_file *class,
                     struct attribute_info ***info, uint16_t count);

int parse_ConstantValue_at (Loader *loader, struct ConstantValue_attribute *);
int parse_Code_attribute (Loader *loader, struct class_file *class,
                          struct Code_attribute *attr);
int parse_StackMapTable_at (Loader *loader, struct StackMapTable_attribute *);
int parse_BootstrapMethods_at (Loader *loader,
                               struct BootstrapMethods_attribute *);
int parse_NestHost_at (Loader *loader, struct NestHost_attribute *);
int parse_NestMembers_at (Loader *loader, struct NestMembers_attribute *);
int parse_PermittedSubclasses_at (Loader *loader,
                                  struct PermittedSubclasses_attribute *);
int parse_Exceptions_at (Loader *loader, struct Exceptions_attribute *);
int parse_InnerClasses_at (Loader *loader, struct InnerClasses_attribute *);
int parse_EnclosingMethod_at (Loader *loader,
                              struct EnclosingMethod_attribute *);
int parse_Synthetic_at (Loader *loader, struct Synthetic_attribute *);
int parse_Signature_at (Loader *loader, struct Signature_attribute *);
int parse_Record_at (Loader *loader, struct class_file *class,
                     struct Record_attribute *);
int parse_SourceFile_at (Loader *loader, struct SourceFile_attribute *);
int parse_LineNumberTable_at (Loader *loader,
                              struct LineNumberTable_attribute *);
int parse_LocalVariableTable_at (Loader *loader,
                                 struct LocalVariableTable_attribute *);
int
parse_LocalVariableTypeTable_at (Loader *loader,
                                 struct LocalVariableTypeTable_attribute *);
int parse_SourceDebugExtension_at (Loader *loader,
                                   struct SourceDebugExtension_attribute *);
int parse_Deprecated_at (Loader *loader, struct Deprecated_attribute *);
int parse_RuntimeVisibleAnnotations_at (
    Loader *loader, struct RuntimeVisibleAnnotations_attribute *);
int parse_RuntimeInvisibleAnnotations_at (
    Loader *loader, struct RuntimeInvisibleAnnotations_attribute *);
int parse_RuntimeVisibleParameterAnnotations_at (
    Loader *loader, struct RuntimeVisibleParameterAnnotations_attribute *);
int parse_RuntimeInvisibleParameterAnnotations_at (
    Loader *loader, struct RuntimeInvisibleParameterAnnotations_attribute *);
int parse_RuntimeVisibleTypeAnnotations_at (
    Loader *loader, struct RuntimeVisibleTypeAnnotations_attribute *);
int parse_RuntimeInvisibleTypeAnnotations_at (
    Loader *loader, struct RuntimeInvisibleTypeAnnotations_attribute *);
int parse_AnnotationDefault_at (Loader *loader,
                                struct AnnotationDefault_attribute *);
int parse_MethodParameters_at (Loader *loader,
                               struct MethodParameters_attribute *);
int parse_Module_at (Loader *loader, struct Module_attribute *);
int parse_ModulePackages_at (Loader *loader,
                             struct ModulePackages_attribute *);
int parse_ModuleMainClass_at (Loader *loader,
                              struct ModuleMainClass_attribute *);

#endif