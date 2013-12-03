#include "php.h"

#include "src/matrix.h"

PHP_FUNCTION(matrix_add_int)
{
    zval *arg_matrix1, *arg_matrix2;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }

    php_matrix_elementwise_function(return_value, arg_matrix1, arg_matrix2, &php_array_add_sum_long);
}

PHP_FUNCTION(matrix_add)
{
    zval *arg_matrix1, *arg_matrix2;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }

    php_matrix_elementwise_function(return_value, arg_matrix1, arg_matrix2, &php_array_add_sum_double);
}

void php_array_add_sum_long(zval *row, zval *data1, zval *data2)
{
    long x1, x2;
    zval temp;

    temp = *data1;
    zval_copy_ctor(&temp);
    convert_to_long(&temp);
    x1 = Z_LVAL(temp);
    zval_dtor(&temp);

    temp = *data2;
    zval_copy_ctor(&temp);
    convert_to_long(&temp);
    x2 = Z_LVAL(temp);
    zval_dtor(&temp);

    add_next_index_long(row, x1 + x2);
}

void php_array_add_sum_double(zval *row, zval *data1, zval *data2)
{
    double x1, x2;
    zval temp;

    temp = *data1;
    zval_copy_ctor(&temp);
    convert_to_double(&temp);
    x1 = Z_DVAL(temp);
    zval_dtor(&temp);

    temp = *data2;
    zval_copy_ctor(&temp);
    convert_to_double(&temp);
    x2 = Z_DVAL(temp);
    zval_dtor(&temp);

    add_next_index_double(row, x1 + x2);
}
