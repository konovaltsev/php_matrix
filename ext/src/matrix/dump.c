#include "php.h"

#include "src/matrix.h"

PHP_FUNCTION(matrix_dump)
{
    zval *arg_matrix;
    ZMatrix m;
    int i, j;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arg_matrix) == FAILURE)
    {
        php_printf("matrix[not valid]\n");
        return;
    }

    if(php_matrix_init_matrix(&m, arg_matrix) == FAILURE)
    {
        php_printf("matrix[not valid]\n");
        return;
    }

      php_printf("matrix[%dx%d]:\n", m.m, m.n);

    for(i = 0; i < m.m; ++i)
    {
        php_printf("|\t");

        for(j = 0; j < m.n; ++j)
        {
            switch(Z_TYPE_P(m.matrix[i][j]))
            {
                case IS_LONG:
                    php_printf("%ld\t", Z_LVAL_P(m.matrix[i][j]));
                    break;
                case IS_DOUBLE:
                    php_printf("%.3f\t", Z_DVAL_P(m.matrix[i][j]));
                    break;
                default:
                    php_printf("<undef>\t");
            }
        }

        php_printf("|\n");
    }

    php_matrix_free(m);
}
