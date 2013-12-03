
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

typedef struct LMatrix{
    int m; //i, rows
    int n; //j, columns
    long *matrix;
} LMatrix;

int php_lmatrix_to_pzval(LMatrix, zval*);

int php_matrix_init_matrix(ZMatrix*, zval*);
void php_matrix_free(ZMatrix);
void php_matrix_free_matrix(ZMatrix);

int php_matrix_init_matrix_double(DMatrix*, zval*);
void php_matrix_free_double(DMatrix);

int php_matrix_init_matrix_long(LMatrix*, zval*);
void php_matrix_free_long(LMatrix);

void php_matrix_elementwise_function(zval*, zval*, zval*, void (*f)(zval*, zval*, zval*));
void php_matrix_scalar_matrix_function(zval*, double, zval*, double (*f)(double, double));
void php_matrix_scalar_matrix_function_long(zval*, long, zval*, long (*f)(long, long));

void php_array_add_sum_long(zval*, zval*, zval*);
void php_array_add_sum_double(zval*, zval*, zval*);
void php_array_add_mul_zvals_to_long(zval*, zval*, zval*);
void php_array_add_mul_zvals_to_double(zval*, zval*, zval*);
double php_matrix_mul_double(double, double);
long php_matrix_mul_long(long, long);
