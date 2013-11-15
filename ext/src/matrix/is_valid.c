#include "php.h"

#include "src/matrix.h"

PHP_FUNCTION(matrix_is_valid)
{
    zval *arg_matrix;
    ZMatrix m;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arg_matrix) == FAILURE)
    {
        RETURN_FALSE;
    }

    if(php_matrix_init_matrix(&m, arg_matrix) == FAILURE)
    {
        RETURN_FALSE;
    }

    php_matrix_free(m);
    RETURN_TRUE;
}
