#ifndef PHP_MATRIX_H
#define PHP_MATRIX_H 1

#define PHP_MATRIX_VERSION "1.0"
#define PHP_MATRIX_EXTNAME "matrix"

PHP_FUNCTION(matrix_is_valid);
PHP_FUNCTION(matrix_dump);
PHP_FUNCTION(matrix_transpose);
PHP_FUNCTION(matrix_add_int);
PHP_FUNCTION(matrix_add);
PHP_FUNCTION(matrix_mul_elementwise_int);
PHP_FUNCTION(matrix_mul_elementwise);
PHP_FUNCTION(matrix_mul_scalar_matrix);
PHP_FUNCTION(matrix_mul_scalar_matrix_int);

extern zend_module_entry matrix_module_entry;
#define phpext_matrix_ptr &matrix_module_entry

#endif
