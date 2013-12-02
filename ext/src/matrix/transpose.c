#include "php.h"

#include "src/matrix.h"

PHP_FUNCTION(matrix_transpose)
{
    zval *arg_matrix;
    ZMatrix m;
    int i, j;
    zval *row;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arg_matrix) == FAILURE)
    {
        RETURN_NULL();
    }

    if(php_matrix_init_matrix(&m, arg_matrix) == FAILURE)
    {
        RETURN_NULL();
    }

    array_init(return_value);
    for(j = 0; j < m.n; ++j)
    {
        MAKE_STD_ZVAL(row);
        array_init(row);
        for(i = 0; i < m.m; ++i)
        {
            add_next_index_zval(row, m.matrix[i*m.n + j]);
        }
        add_next_index_zval(return_value, row);
    }
    php_matrix_free_matrix(m);
}
