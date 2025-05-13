#ifndef SHIP_JVM_ATTR_INFO_H
#define SHIP_JVM_ATTR_INFO_H

#include <stdint.h>

#include "util.h"

// All attributes

struct ConstantValue_attribute;
struct Code_attribute;
struct StackMapTable_attribute;
struct BootstrapMethods_attribute;
struct NestHost_attribute;
struct NestMembers_attribute;
struct PermittedSubclasses_attribute;
struct Exceptions_attribute;
struct InnerClasses_attribute;
struct EnclosingMethod_attribute;
struct Synthetic_attribute;
struct Signature_attribute;
struct Record_attribute;
struct SourceFile_attribute;
struct LineNumberTable_attribute;
struct LocalVariableTable_attribute;
struct LocalVariableTypeTable_attribute;
struct SourceDebugExtension_attribute;
struct Deprecated_attribute;
struct RuntimeVisibleAnnotations_attribute;
struct RuntimeInvisibleAnnotations_attribute;
struct RuntimeVisibleParameterAnnotations_attribute;
struct RuntimeInvisibleParameterAnnotations_attribute;
struct RuntimeVisibleTypeAnnotations_attribute;
struct RuntimeInvisibleTypeAnnotations_attribute;
struct AnnotationDefault_attribute;
struct MethodParameters_attribute;
struct Module_attribute;
struct ModulePackages_attribute;
struct ModuleMainClass_attribute;

struct attribute_info
{
  uint16_t attribute_name_index;
  uint32_t attribute_length;
};

struct ConstantValue_attribute
{
  struct attribute_info info;
  uint16_t constant_value_index;
};

struct exception_table
{
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;
  uint16_t catch_type;
};

struct Code_attribute
{
  struct attribute_info info;
  uint16_t max_stack;
  uint16_t max_locals;
  uint32_t code_length;
  uint8_t *code; /* size = code_length */
  uint16_t exception_table_length;
  struct exception_table *table; /* size = exception_table_length */
  uint16_t attributes_count;
  struct attribute_info **attributes; /* size = attributes_count */
};

/**
 * Union representing verification type info in StackMapTable
 * Uses tag byte to determine which type is actually stored
 */
union verification_type_info
{
  uint8_t tag;
  struct
  {
    uint8_t tag; // = ITEM_Top (0)
  } Top_variable_info;

  struct
  {
    uint8_t tag; // = ITEM_Integer (1)
  } Integer_variable_info;

  struct
  {
    uint8_t tag; // = ITEM_Float (2)
  } Float_variable_info;

  struct
  {
    uint8_t tag; // = ITEM_Long (4)
  } Long_variable_info;

  struct
  {
    uint8_t tag; // = ITEM_Double (3)
  } Double_variable_info;

  struct
  {
    uint8_t tag; // = ITEM_Null (5)
  } Null_variable_info;

  struct
  {
    uint8_t tag; // = ITEM_UninitializedThis (6)
  } UninitializedThis_variable_info;

  struct
  {
    uint8_t tag;          // = ITEM_Object (7)
    uint16_t cpool_index; // Constant pool index
  } Object_variable_info;

  struct
  {
    uint8_t tag;     // = ITEM_Uninitialized (8)
    uint16_t offset; // Bytecode offset
  } Uninitialized_variable_info;
};

/**
 * Union representing different stack map frame types
 */
union stack_map_frame
{
  uint8_t frame_type;
  /**
   * Frame type where the frame has exactly the same locals as the previous
   * frame and the operand stack is empty (frame_type = 0-63)
   */
  struct
  {
    uint8_t frame_type; /* SAME (0-63) */
  } same_frame;

  /**
   * Frame type where the frame has exactly the same locals as the previous
   * frame and the operand stack has one entry (frame_type = 64-127)
   */
  struct
  {
    uint8_t frame_type; /* SAME_LOCALS_1_STACK_ITEM (64-127) */
    union verification_type_info *stack; // size = 1
  } same_locals_1_stack_item_frame;

  /**
   * Frame type where the frame has exactly the same locals as the previous
   * frame except one additional verification type on the stack, with explicit
   * offset delta
   */
  struct
  {
    uint8_t frame_type; /* SAME_LOCALS_1_STACK_ITEM_EXTENDED (247) */
    uint16_t offset_delta;
    union verification_type_info *stack; // size = 1
  } same_locals_1_stack_item_frame_extended;

  /**
   * Frame type where the frame has the same locals as the previous frame
   * except that the last k locals are absent (frame_type = 248-250)
   */
  struct
  {
    uint8_t frame_type; /* CHOP (248-250) */
    uint16_t offset_delta;
  } chop_frame;

  /**
   * Frame type that has exactly the same locals as the previous frame and
   * the operand stack is empty, with explicit offset delta
   */
  struct
  {
    uint8_t frame_type; /* SAME_FRAME_EXTENDED (251) */
    uint16_t offset_delta;
  } same_frame_extended;

  /**
   * Frame type where the frame has the same locals as the previous frame
   * except that k additional locals are defined (frame_type = 252-254)
   */
  struct
  {
    uint8_t frame_type; /* APPEND (252-254) */
    uint16_t offset_delta;
    union verification_type_info *locals; /* size = frame_type - 251 */
  } append_frame;

  /**
   * Complete frame data with explicit locals and stack info
   */
  struct
  {
    uint8_t frame_type; /* FULL_FRAME (255) */
    uint16_t offset_delta;
    uint16_t number_of_locals;
    union verification_type_info *locals; /* size = number_of_locals */
    uint16_t number_of_stack_items;
    union verification_type_info *stack; /* size = number_of_stack_items */
  } full_frame;
};

/**
 * StackMapTable attribute structure as defined in JVM specification
 */
struct StackMapTable_attribute
{
  struct attribute_info info;

  /**
   * Number of stack map frame entries in this attribute
   */
  uint16_t number_of_entries;

  /**
   * Array of stack map frames describing the state of
   * the local variables and operand stack at specific
   * bytecode offsets
   */
  union stack_map_frame *entries; /* array of size number_of_entries */
};

struct bootstrap_methods
{
  /**
   * Index into the constant pool of a CONSTANT_MethodHandle
   * representing the bootstrap method
   */
  uint16_t bootstrap_method_ref;

  /**
   * Number of arguments for this bootstrap method
   */
  uint16_t num_bootstrap_arguments;

  /**
   * Array of constant pool indices (each a CONSTANT_* entry)
   * representing the bootstrap arguments
   */
  uint16_t *bootstrap_arguments; /* array of size num_bootstrap_arguments */
};

/**
 * BootstrapMethods attribute structure
 * Used for invokedynamic instruction support
 */
struct BootstrapMethods_attribute
{
  struct attribute_info info;

  /**
   * Number of bootstrap methods in this attribute
   */
  uint16_t num_bootstrap_methods;

  /**
   * Array of bootstrap method entries
   */
  struct bootstrap_methods
      *bootstrap_methods; /* array of size num_bootstrap_methods */
};

/**
 * NestHost attribute structure (Java 11+)
 * Indicates which class is the host of the nest to which the current class
 * belongs
 */
struct NestHost_attribute
{
  struct attribute_info info;

  /**
   * Index into the constant pool of a CONSTANT_Class_info
   * representing the nest host class
   */
  uint16_t host_class_index;
};

/**
 * NestMembers attribute structure (Java 11+)
 * Lists all classes that are members of the nest hosted by the current class
 */
struct NestMembers_attribute
{
  struct attribute_info info;

  /**
   * Number of classes in the nest
   */
  uint16_t number_of_classes;

  /**
   * Array of constant pool indices (each a CONSTANT_Class_info)
   * representing the nest member classes
   */
  uint16_t *classes; /* array of size number_of_classes */
};

/**
 * PermittedSubclasses attribute structure (Java 17+)
 * Specifies the allowed direct subclasses of a sealed class
 */
struct PermittedSubclasses_attribute
{
  struct attribute_info info;

  /**
   * Number of permitted subclasses
   */
  uint16_t number_of_classes;

  /**
   * Array of constant pool indices (each a CONSTANT_Class_info)
   * representing the permitted subclasses
   */
  uint16_t *classes; /* array of size number_of_classes */
};

/**
 * Exceptions attribute structure
 * Lists checked exceptions that may be thrown by a method
 */
struct Exceptions_attribute
{
  struct attribute_info info;

  /**
   * Number of exceptions in the exception table
   */
  uint16_t number_of_exceptions;

  /**
   * Array of constant pool indices (each a CONSTANT_Class_info)
   * representing the exception classes
   */
  uint16_t *exception_index_table; /* array of size number_of_exceptions */
};

/**
 * Array of inner class entries
 */
struct inner_class_entries
{
  /**
   * Index into the constant pool of a CONSTANT_Class_info
   * representing the inner class
   */
  uint16_t inner_class_info_index;

  /**
   * Index into the constant pool of a CONSTANT_Class_info
   * representing the outer class (0 if not member)
   */
  uint16_t outer_class_info_index;

  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the original name of the inner class (0 if anonymous)
   */
  uint16_t inner_name_index;

  /**
   * Access flags of the inner class (ACC_PUBLIC, ACC_PRIVATE, etc.)
   */
  uint16_t inner_class_access_flags;
};

/**
 * InnerClasses attribute structure
 * Contains information about inner classes of a class
 */
struct InnerClasses_attribute
{
  struct attribute_info info;

  /**
   * Number of entries in the classes table
   */
  uint16_t number_of_classes;

  struct inner_class_entries *classes; /* array of size number_of_classes */
};

/**
 * EnclosingMethod attribute structure
 * Indicates the immediately enclosing method of a nested class
 */
struct EnclosingMethod_attribute
{
  struct attribute_info info;

  /**
   * Index into the constant pool of a CONSTANT_Class_info
   * representing the enclosing class
   */
  uint16_t class_index;

  /**
   * Index into the constant pool of a CONSTANT_NameAndType_info
   * representing the enclosing method (0 if class is not enclosed by a method)
   */
  uint16_t method_index;
};

/**
 * Synthetic attribute structure
 * Marks synthetic elements generated by the compiler
 */
struct Synthetic_attribute
{
  struct attribute_info info;
};

/**
 * Signature attribute structure
 * Stores generic type information for classes, methods, and fields
 */
struct Signature_attribute
{
  struct attribute_info info;

  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * containing the generic signature string
   */
  uint16_t signature_index;
};

/**
 * Record component information structure
 * Represents a single component in a record declaration
 */
struct record_component_info
{
  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the component name
   */
  uint16_t name_index;

  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the component descriptor
   */
  uint16_t descriptor_index;

  /**
   * Number of attributes for this component
   */
  uint16_t attributes_count;

  /**
   * Array of attributes associated with this component
   */
  struct attribute_info **attributes; /* array of size attributes_count */
};

/**
 * Record attribute structure (Java 14+)
 * Contains metadata about record class components
 */
struct Record_attribute
{
  struct attribute_info info;

  /**
   * Number of components in this record
   */
  uint16_t components_count;

  /**
   * Array of record component information structures
   */
  struct record_component_info
      *components; /* array of size components_count */
};

/**
 * SourceFile attribute structure
 * Records the source file from which this class was compiled
 */
struct SourceFile_attribute
{
  struct attribute_info info;

  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the source file name
   */
  uint16_t sourcefile_index;
};

/**
 * Array of line number entries
 */
struct line_number_table
{
  /**
   * Bytecode offset (program counter) where this line starts
   */
  uint16_t start_pc;

  /**
   * Corresponding source file line number
   */
  uint16_t line_number;
};

/**
 * LineNumberTable attribute structure
 * Maps bytecode offsets to source code line numbers
 */
struct LineNumberTable_attribute
{
  struct attribute_info info;

  /**
   * Number of entries in the line number table
   */
  uint16_t line_number_table_length;

  /**
   * Array of line number entries
   */
  struct line_number_table *table; /* array of size line_number_table_length */
};

/**
 * Array of local variable entries
 */
struct local_variable_table
{
  /**
   * Bytecode offset where variable scope begins
   */
  uint16_t start_pc;

  /**
   * Length of variable scope (in bytes)
   */
  uint16_t length;

  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the variable name
   */
  uint16_t name_index;

  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the variable descriptor
   */
  uint16_t descriptor_index;

  /**
   * Index in the local variable array of this variable
   */
  uint16_t index;
};

/**
 * LocalVariableTable attribute structure
 * Stores debug information about local variables
 */
struct LocalVariableTable_attribute
{
  struct attribute_info info;

  /**
   * Number of entries in the local variable table
   */
  uint16_t local_variable_table_length;

  /**
   * Array of local variable entries
   */
  struct local_variable_table
      *table; /* array of size local_variable_table_length */
};

/**
 * Array of local variable type entries
 */
struct local_variable_type_table
{
  /**
   * Bytecode offset where variable scope begins
   */
  uint16_t start_pc;

  /**
   * Length of variable scope (in bytes)
   */
  uint16_t length;

  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the variable name
   */
  uint16_t name_index;

  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the generic signature
   */
  uint16_t signature_index;

  /**
   * Index in the local variable array of this variable
   */
  uint16_t index;
};

/**
 * Stores generic type information for local variables
 */
struct LocalVariableTypeTable_attribute
{
  struct attribute_info info;

  /**
   * Number of entries in the local variable type table
   */
  uint16_t local_variable_type_table_length;

  /**
   * Array of local variable type entries
   */
  struct local_variable_type_table *table; /* array of size
                                   local_variable_type_table_length */
};

/**
 * SourceDebugExtension attribute structure
 * Contains extended debugging information in implementation-defined format
 */
struct SourceDebugExtension_attribute
{
  struct attribute_info info;

  /**
   * Array of bytes containing implementation-specific debug information
   * (typically SMAP data for JSR-045)
   */
  uint8_t *debug_extension; /* array of size attribute_length */
};

/**
 * Marks deprecated class, field, or method
 */
struct Deprecated_attribute
{
  struct attribute_info info;
};

struct element_value_pairs;
/**
 * Annotation structure
 * Represents a single annotation
 */
struct annotation
{
  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the annotation type descriptor
   */
  uint16_t type_index;

  /**
   * Number of element-value pairs
   */
  uint16_t num_element_value_pairs;

  /**
   * Array of annotation element-value pairs
   */
  struct element_value_pairs
      *element_value_pairs; /* array of size num_element_value_pairs */
};

/**
 * Element_value structure
 * Represents the value of an annotation element
 */
struct element_value
{
  /**
   * Tag indicating the type of this element value
   * Possible values:
   *   'B', 'C', 'D', 'F', 'I', 'J', 'S', 'Z' - primitive
   *   's' - String
   *   'e' - enum constant
   *   'c' - Class
   *   '@' - Annotation
   *   '[' - Array
   */
  uint8_t tag;

  /**
   * Union of possible value types
   */
  union
  {
    /**
     * For primitive and String values (tags
     * 'B','C','D','F','I','J','S','Z','s') Index into the constant pool of
     * appropriate type
     */
    uint16_t const_value_index;

    /**
     * For enum constants (tag 'e')
     */
    struct
    {
      uint16_t type_name_index;  /* Index of enum type descriptor */
      uint16_t const_name_index; /* Index of enum constant name */
    } enum_const_value;

    /**
     * For Class values (tag 'c')
     * Index into the constant pool of class descriptor
     */
    uint16_t class_info_index;

    /**
     * For nested annotations (tag '@')
     */
    struct annotation annotation_value;

    /**
     * For arrays (tag '[')
     */
    struct
    {
      uint16_t num_values;          /* Number of elements */
      struct element_value *values; /* Array of element values */
    } array_value;
  } value;
};

struct element_value_pairs
{
  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the element name
   */
  uint16_t element_name_index;

  /**
   * The element value
   */
  struct element_value value;
};

/**
 * RuntimeVisibleAnnotations attribute structure
 * Stores annotations that should be visible at runtime
 */
struct RuntimeVisibleAnnotations_attribute
{
  struct attribute_info info;

  /**
   * Number of annotations
   */
  uint16_t num_annotations;

  /**
   * Array of annotation structures
   */
  struct annotation *annotations; /* array of size num_annotations */
};

/**
 * RuntimeInvisibleAnnotations attribute structure
 * Stores annotations that should not be visible at runtime
 */
struct RuntimeInvisibleAnnotations_attribute
{
  struct attribute_info info;

  /**
   * Number of annotations
   */
  uint16_t num_annotations;

  /**
   * Array of annotation structures
   */
  struct annotation *annotations; /* array of size num_annotations */
};

/**
 * Array of parameter annotation collections
 */
struct parameter_annotations
{
  /**
   * Number of annotations on this parameter
   */
  uint16_t num_annotations;

  /**
   * Array of annotations for this parameter
   */
  struct annotation *annotations; /* array of size num_annotations */
};

/**
 * RuntimeVisibleParameterAnnotations attribute structure
 * Stores parameter annotations visible at runtime
 */
struct RuntimeVisibleParameterAnnotations_attribute
{
  struct attribute_info info;

  /**
   * Number of method parameters
   */
  uint8_t num_parameters;

  struct parameter_annotations
      *parameter_annotations; /* array of size num_parameters */
};

/**
 * Type parameter target (for class/method type parameters)
 */
struct type_parameter_target
{
  uint8_t type_parameter_index; /* 0-based type parameter index */
};

/**
 * Supertype target (for extends/implements clauses)
 */
struct supertype_target
{
  uint16_t supertype_index; /* Index in interfaces/superclass list */
};

/**
 * Type parameter bound target
 */
struct type_parameter_bound_target
{
  uint8_t type_parameter_index; /* 0-based type parameter index */
  uint8_t bound_index;          /* 0-based bound index */
};

/**
 * Empty target (for field declarations, method return types, etc.)
 */
struct empty_target
{
  /* No additional data */
};

/**
 * Formal parameter target
 */
struct formal_parameter_target
{
  uint8_t formal_parameter_index; /* 0-based parameter index */
};

/**
 * Throws target
 */
struct throws_target
{
  uint16_t throws_type_index; /* Index in exception table */
};

/**
 * Local variable target
 */
struct localvar_target
{
  uint16_t table_length; /* Number of scope entries */
  struct
  {
    uint16_t start_pc; /* Start of scope (bytecode offset) */
    uint16_t length;   /* Scope length */
    uint16_t index;    /* Local variable index */
  } *table;            /* Array of scope entries */
};

/**
 * Catch target (exception handler)
 */
struct catch_target
{
  uint16_t exception_table_index; /* Index in exception table */
};

/**
 * Offset target (various bytecode offsets)
 */
struct offset_target
{
  uint16_t offset; /* Bytecode offset */
};

/**
 * Type argument target (generic type arguments)
 */
struct type_argument_target
{
  uint16_t offset;             /* Bytecode offset */
  uint8_t type_argument_index; /* 0-based type argument index */
};

/**
 * Type path (path to nested type)
 */
struct type_path
{
  uint8_t path_length; /* Number of path entries */
  struct
  {
    uint8_t type_path_kind;      /* Path step kind (0=array,1=inner,etc) */
    uint8_t type_argument_index; /* For parameterized types */
  } *path;                       /* Array of path steps */
};

/**
 * RuntimeInvisibleParameterAnnotations attribute structure
 * Stores parameter annotations that should not be visible at runtime
 */
struct RuntimeInvisibleParameterAnnotations_attribute
{
  struct attribute_info info;

  /**
   * Number of method parameters
   */
  uint8_t num_parameters;

  /**
   * Array of parameter annotation collections
   */
  struct parameter_annotations
      *parameter_annotations; /* array of size num_parameters */
};

/**
 * Type annotation structure
 * Extended annotation format for Java type annotations
 */
struct type_annotation
{
  /**
   * Type of target being annotated (item 17.1 in JVMS)
   * Possible values:
   * 0x00-0x01: Type parameter declarations
   * 0x10: Class extends/implements
   * 0x11-0x12: Type parameter bounds
   * 0x13: Field declaration
   * 0x14-0x16: Method return/receiver/parameters
   * 0x17: Throws clause
   * etc.
   */
  uint8_t target_type;

  /**
   * Target-specific information
   */
  union
  {
    struct type_parameter_target type_parameter;
    struct supertype_target supertype;
    struct type_parameter_bound_target type_parameter_bound;
    struct empty_target empty;
    struct formal_parameter_target formal_parameter;
    struct throws_target throws;
    struct localvar_target localvar;
    struct catch_target catch;
    struct offset_target offset;
    struct type_argument_target type_argument;
  } target_info;

  /**
   * Path to the exact annotated type in a compound type
   */
  struct type_path target_path;

  /**
   * Index into the constant pool of the annotation type
   */
  uint16_t type_index;

  /**
   * Number of element-value pairs
   */
  uint16_t num_element_value_pairs;

  /**
   * Array of annotation element-value pairs
   */
  struct
  {
    /**
     * Index into the constant pool of element name
     */
    uint16_t element_name_index;

    /**
     * The element value
     */
    struct element_value value;
  } *element_value_pairs; /* array of size num_element_value_pairs */
};

/**
 * Stores type annotations that should be visible at runtime
 */
struct RuntimeVisibleTypeAnnotations_attribute
{
  struct attribute_info info;

  /**
   * Number of type annotations
   */
  uint16_t num_annotations;

  /**
   * Array of type annotation structures
   */
  struct type_annotation *type_annotation; /* array of size num_annotations */
};

/**
 * RuntimeInvisibleTypeAnnotations attribute structure
 * Stores type annotations that should not be visible at runtime
 */
struct RuntimeInvisibleTypeAnnotations_attribute
{
  struct attribute_info info;

  /**
   * Number of type annotations
   */
  uint16_t num_annotations;

  /**
   * Array of type annotation structures
   */
  struct type_annotation *annotations; /* array of size num_annotations */
};

/**
 * AnnotationDefault attribute structure
 * Specifies default value for an annotation type element
 */
struct AnnotationDefault_attribute
{
  struct attribute_info info;

  /**
   * The default value for this annotation element
   */
  struct element_value default_value;
};

struct method_params
{
  /**
   * Index into the constant pool of a CONSTANT_Utf8_info
   * representing the parameter name (0 if unnamed)
   */
  uint16_t name_index;

  /**
   * Parameter access flags (e.g., ACC_FINAL, ACC_SYNTHETIC, ACC_MANDATED)
   */
  uint16_t access_flags;
};

/**
 * MethodParameters attribute structure
 * Contains metadata about method parameters
 */
struct MethodParameters_attribute
{
  struct attribute_info info;

  /**
   * Number of parameter entries
   */
  uint8_t parameters_count;

  /**
   * Array of parameter entries
   */
  struct method_params *parameters; /* array of size parameters_count */
};

struct requires
{
  uint16_t requires_index;         /* CONSTANT_Module_info index */
  uint16_t requires_flags;         /* ACC_TRANSITIVE, etc. */
  uint16_t requires_version_index; /* CONSTANT_Utf8_info (0 if none) */
};

struct exports
{
  uint16_t exports_index; /* CONSTANT_Package_info index */
  uint16_t exports_flags; /* ACC_SYNTHETIC, etc. */
  uint16_t exports_to_count;
  uint16_t *exports_to_index; /* CONSTANT_Module_info indices */
};

struct opens
{
  uint16_t opens_index; /* CONSTANT_Package_info index */
  uint16_t opens_flags; /* ACC_SYNTHETIC */
  uint16_t opens_to_count;
  uint16_t *opens_to_index; /* CONSTANT_Module_info indices */
};

struct provides
{
  uint16_t provides_index; /* CONSTANT_Class_info index */
  uint16_t provides_with_count;
  uint16_t *provides_with_index; /* CONSTANT_Class_info indices */
};

/**
 * Module attribute structure (Java 9+)
 * Contains module definition metadata
 */
struct Module_attribute
{
  struct attribute_info info;

  /* Module basic info */
  uint16_t module_name_index;    /* CONSTANT_Module_info index */
  uint16_t module_flags;         /* ACC_OPEN, ACC_SYNTHETIC, etc. */
  uint16_t module_version_index; /* CONSTANT_Utf8_info index (0 if none) */

  /* Requires section */
  uint16_t requires_count;
  struct requires *requires; /* array of size requires_count */

  /* Exports section */
  uint16_t exports_count;
  struct exports *exports; /* array of size exports_count */

  /* Opens section */
  uint16_t opens_count;
  struct opens *opens; /* array of size opens_count */

  /* Uses section */
  uint16_t uses_count;
  uint16_t *uses_index; /* CONSTANT_Class_info indices */

  /* Provides section */
  uint16_t provides_count;
  struct provides *provides; /* array of size provides_count */
};

/**
 * ModulePackages attribute structure (Java 9+)
 * Lists all packages owned by this module
 */
struct ModulePackages_attribute
{
  struct attribute_info info;

  /**
   * Number of packages in this module
   */
  uint16_t package_count;

  /**
   * Array of constant pool indices (each a CONSTANT_Package_info)
   * representing the packages in this module
   */
  uint16_t *package_index; /* array of size package_count */
};

/**
 * ModuleMainClass attribute structure (Java 9+)
 * Specifies the main class for executable modules
 */
struct ModuleMainClass_attribute
{
  struct attribute_info info;

  /**
   * Index into the constant pool of a CONSTANT_Class_info
   * representing the main class
   */
  uint16_t main_class_index;
};

#endif
