
typedef struct ZMatrix{
    int m; //i, rows
    int n; //j, columns
    zval **matrix;
} ZMatrix;

typedef struct DMatrix{
    int m; //i, rows
    int n; //j, columns
    double *matrix;
} DMatrix;

typedef struct IMatrix{
    int m; //i, rows
    int n; //j, columns
    long *matrix;
} IMatrix;

int php_imatrix_to_pzval(IMatrix, zval*);

int php_matrix_init_matrix(ZMatrix*, zval*);
void php_matrix_free(ZMatrix);
void php_matrix_free_matrix(ZMatrix);

int php_matrix_init_matrix_double(DMatrix*, zval*);
void php_matrix_free_double(DMatrix);

int php_matrix_init_matrix_int(IMatrix*, zval*);
void php_matrix_free_int(IMatrix);
