#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_matrix.h"
#include "matrix.h"

const zend_function_entry matrix_functions[] = {
    PHP_FE(matrix_is_valid, NULL)
    PHP_FE(matrix_dump, NULL)
    PHP_FE(matrix_transpose, NULL)
    PHP_FE(matrix_add_int, NULL)
    PHP_FE(matrix_add_float, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry matrix_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_MATRIX_EXTNAME,
    matrix_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MATRIX_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MATRIX
    ZEND_GET_MODULE(matrix)
#endif
