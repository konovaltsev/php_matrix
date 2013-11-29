
typedef struct ZMatrix{
    int m; //i, rows
    int n; //j, columns
    zval ***matrix;
} ZMatrix;

int php_matrix_init_matrix(ZMatrix*, zval*);
void php_matrix_free(ZMatrix);
void php_matrix_free_matrix(ZMatrix);
