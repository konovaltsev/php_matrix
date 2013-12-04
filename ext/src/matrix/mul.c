#include "php.h"

#include "src/matrix.h"

PHP_FUNCTION(matrix_mul)
{
    zval *arg_matrix1, *arg_matrix2;
    DMatrix a, b;
    double elem;

    zval *row;
    int m, n, p, i, j, r;
    int a_idx, a_idx_start, b_idx;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }

    if(
        php_matrix_init_matrix_double(&a, arg_matrix1) != SUCCESS
    )
    {
        RETURN_NULL();
    }

    if(
        php_matrix_init_matrix_double(&b, arg_matrix2) != SUCCESS
    )
    {
        php_matrix_free_double(a);
        RETURN_NULL();
    }

    if(a.n != b.m)
    {
        php_matrix_free_double(a);
        php_matrix_free_double(b);
        RETURN_NULL();
    }

    /*** all correct now ***/
    m = a.m;
    n = a.n;
    p = b.n;

    array_init(return_value);
    for(
        i = a_idx_start = 0;
        i < m;
        ++i, a_idx_start += n
    )
    {
        MAKE_STD_ZVAL(row);
        array_init(row);
        for(j = 0; j < p; ++j)
        {
            for(
                r = 0, elem = 0, a_idx = a_idx_start, b_idx = j;
                r < n;
                ++r, ++a_idx, b_idx += p
            )
            {
                elem = elem + a.matrix[a_idx] * b.matrix[b_idx];
            }
            add_next_index_double(row, elem);
        }
        add_next_index_zval(return_value, row);
    }

    php_matrix_free_double(a);
    php_matrix_free_double(b);
}

PHP_FUNCTION(matrix_mul_int)
{
    zval *arg_matrix1, *arg_matrix2;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }
}
