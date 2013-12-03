
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

void php_matrix_elementwise_function(zval*, zval*, zval*, void (*f)(zval*, zval*, zval*));
void php_matrix_scalar_matrix_function(zval*, double, zval*, double (*f)(double, double));
void php_matrix_scalar_matrix_function_int(zval*, long, zval*, long (*f)(long, long));

void php_array_add_sum_int(zval*, zval*, zval*);
void php_array_add_sum_double(zval*, zval*, zval*);
void php_array_add_mul_zvals_to_int(zval*, zval*, zval*);
void php_array_add_mul_zvals_to_double(zval*, zval*, zval*);
double php_matrix_mul(double, double);
long php_matrix_mul_int(long, long);
