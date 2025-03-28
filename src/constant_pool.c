#include "constant_pool.h"

int read_utf8_info(Loader* loader, struct UTF8_info* utf8){
    uint16_t i;

    utf8->lenght = loader_u2(loader);
    utf8->string = malloc(utf8->lenght);
    if(utf8->string != NULL){
        put("ERROR: Can't allocate memory for string\n");
        return EINVAL;
    }

    for (i = 0; i < utf8->lenght; i++)
    {
        utf8->string[i] = loader_u1(loader);
    }
    return 0;
}

int read_integer_info(Loader* loader, struct integer_info* int_info){
    int_info->bytes = loader_u4(loader);
    return 0;
}

int read_float_info(Loader* loader, struct float_info* float_info){
    float_info->bytes = loader_u4(loader);
    return 0;
}

int read_long_info(Loader* loader, struct long_info* long_info){
    long_info->high_bytes = loader_u4;
    long_info->low_bytes = loader_u4;
    return 0;
}

int read_double_info(Loader* loader, struct double_info* double_info){
    double_info->high_bytes = loader_u4;
    double_info->low_bytes = loader_u4;
    return 0;
}

int read_class_info(Loader* loader, struct class_info* class_info){

}

int read_string_info(Loader* loader, struct string_info* string_info){

}

int read_fieldref_info(Loader* loader, struct fieldref_info* fieldref_info){

}

int read_methodref_info(Loader* loader, struct methodref_info* methodref_info){

}

int read_interface_meth_ref_info(Loader* loader, struct interface_meth_ref_info* interf){
    
}

int read_name_and_type_info(Loader* loader, struct string_info* string_info){
    
}

int read_method_handle_info(Loader* loader, struct string_info* string_info){
    
}

int read_method_type_info(Loader* loader, struct string_info* string_info){
    
}

int read_dynamic_info(Loader* loader, struct string_info* string_info){
    
}

int read_invoke_dynamic_info(Loader* loader, struct string_info* string_info){
    
}

int read_module_info(Loader* loader, struct string_info* string_info){
    
}

int read_package_info(Loader* loader, struct string_info* string_info){
    
}