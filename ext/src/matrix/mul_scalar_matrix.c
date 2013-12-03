#include "php.h"

#include "src/matrix.h"

PHP_FUNCTION(matrix_mul_scalar_matrix)
{
    double arg_scalar;
    zval *arg_matrix;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "da", &arg_scalar, &arg_matrix) == FAILURE)
    {
        RETURN_NULL();
    }

    php_matrix_scalar_matrix_function(return_value, arg_scalar, arg_matrix, &php_matrix_mul);
}

PHP_FUNCTION(matrix_mul_scalar_matrix_int)
{
    long arg_scalar;
    zval *arg_matrix;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "la", &arg_scalar, &arg_matrix) == FAILURE)
    {
        RETURN_NULL();
    }

    php_matrix_scalar_matrix_function_int(return_value, arg_scalar, arg_matrix, &php_matrix_mul_int);
}
