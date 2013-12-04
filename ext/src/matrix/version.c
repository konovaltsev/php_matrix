#include "php.h"

#include "src/matrix.h"
#include "src/php_matrix.h"

PHP_FUNCTION(matrix_version)
{
    RETURN_STRING(PHP_MATRIX_VERSION, strlen(PHP_MATRIX_VERSION));
}
