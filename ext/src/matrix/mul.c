#include "php.h"

#include "src/matrix.h"

PHP_FUNCTION(matrix_mul)
{
    zval *arg_matrix1, *arg_matrix2;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }
}

PHP_FUNCTION(matrix_mul_int)
{
    zval *arg_matrix1, *arg_matrix2;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }
}
