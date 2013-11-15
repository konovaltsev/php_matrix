
typedef struct ZMatrix{
    int iCount;
    int jCount;
    zval ***array;
} ZMatrix;

int php_matrix_init_matrix(ZMatrix*, zval*);
void php_matrix_free(ZMatrix);
void php_matrix_free_array(ZMatrix);
