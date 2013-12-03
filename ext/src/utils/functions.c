#include "php.h"

#include "src/matrix.h"

int php_matrix_init_matrix(ZMatrix* out, zval* php_matrix)
{
    zval **data, **data2;
    int n, m, i, j, idx, i_mem;
    HashTable *j_hash, *i_hash;
    HashPosition pointer, pointer2;
    zval **matrix;

    out->n = 0;
    out->m = 0;
    out->matrix = NULL;

    if (Z_TYPE_P(php_matrix) != IS_ARRAY)
    {
        return FAILURE;
    }

    i_hash = Z_ARRVAL_P(php_matrix);
    zend_hash_internal_pointer_reset_ex(i_hash, &pointer);
    m = zend_hash_num_elements(i_hash);
    if(zend_hash_get_current_data_ex(i_hash, (void**) &data, &pointer) == SUCCESS)
    {
        j_hash = Z_ARRVAL_PP(data);
        n = zend_hash_num_elements(j_hash);
    }
    else
    {
        return FAILURE;
    }
    matrix = emalloc(sizeof(zval*) * m * n);

    idx = 0;
    for(
        i = 0, zend_hash_internal_pointer_reset_ex(i_hash, &pointer);
        i < m;
        ++i, zend_hash_move_forward_ex(i_hash, &pointer)
    )
    {
        if
        (
            zend_hash_get_current_data_ex(i_hash, (void**) &data, &pointer) != SUCCESS
            ||
            Z_TYPE_PP(data) != IS_ARRAY
        )
        {
            for(i_mem = 0; i_mem < idx; ++i_mem)
            {
                zval_ptr_dtor(&matrix[i_mem]);
            }
            efree(matrix);
            return FAILURE;
        }

        j_hash = Z_ARRVAL_PP(data);
        if(zend_hash_num_elements(j_hash) != n)
        {
            for(i_mem = 0; i_mem < idx; ++i_mem)
            {
                zval_ptr_dtor(&matrix[i_mem]);
            }
            efree(matrix);
            return FAILURE;
        }

        for(
            j = 0, zend_hash_internal_pointer_reset_ex(j_hash, &pointer2);
            j < n;
            ++j, zend_hash_move_forward_ex(j_hash, &pointer2)
        )
        {
            if(zend_hash_get_current_data_ex(j_hash, (void**) &data2, &pointer2) != SUCCESS)
            {
                for(i_mem = 0; i_mem < idx; ++i_mem)
                {
                    zval_ptr_dtor(&matrix[i_mem]);
                }
                efree(matrix);
                return FAILURE;
            }
            MAKE_STD_ZVAL(matrix[idx]);
            ZVAL_COPY_VALUE(matrix[idx], *data2);

            ++idx;
        }
    }

    out->n = n;
    out->m = m;
    out->matrix = matrix;

    return SUCCESS;
}

int php_matrix_init_matrix_long(LMatrix* out, zval* php_matrix)
{
    zval **data, **data2;
    int n, m, i, j, idx, i_mem;
    HashTable *j_hash, *i_hash;
    HashPosition pointer, pointer2;
    long *matrix;

    zval temp;

    out->n = 0;
    out->m = 0;
    out->matrix = NULL;

    if (Z_TYPE_P(php_matrix) != IS_ARRAY)
    {
        return FAILURE;
    }

    i_hash = Z_ARRVAL_P(php_matrix);
    zend_hash_internal_pointer_reset_ex(i_hash, &pointer);
    m = zend_hash_num_elements(i_hash);
    if(zend_hash_get_current_data_ex(i_hash, (void**) &data, &pointer) == SUCCESS)
    {
        j_hash = Z_ARRVAL_PP(data);
        n = zend_hash_num_elements(j_hash);
    }
    else
    {
        return FAILURE;
    }
    matrix = emalloc(sizeof(*matrix) * m * n);

    idx = 0;
    for(
        i = 0, zend_hash_internal_pointer_reset_ex(i_hash, &pointer);
        i < m;
        ++i, zend_hash_move_forward_ex(i_hash, &pointer)
    )
    {
        if
        (
            zend_hash_get_current_data_ex(i_hash, (void**) &data, &pointer) != SUCCESS
            ||
            Z_TYPE_PP(data) != IS_ARRAY
        )
        {
            efree(matrix);
            return FAILURE;
        }

        j_hash = Z_ARRVAL_PP(data);
        if(zend_hash_num_elements(j_hash) != n)
        {
            efree(matrix);
            return FAILURE;
        }

        for(
            j = 0, zend_hash_internal_pointer_reset_ex(j_hash, &pointer2);
            j < n;
            ++j, zend_hash_move_forward_ex(j_hash, &pointer2)
        )
        {
            if(zend_hash_get_current_data_ex(j_hash, (void**) &data2, &pointer2) != SUCCESS)
            {
                efree(matrix);
                return FAILURE;
            }

            temp = **data2;
            zval_copy_ctor(&temp);
            convert_to_long(&temp);
            matrix[idx] = Z_LVAL(temp);
            zval_dtor(&temp);

            ++idx;
        }
    }

    out->n = n;
    out->m = m;
    out->matrix = matrix;

    return SUCCESS;
}

int php_lmatrix_to_pzval(LMatrix matrix, zval* ret)
{
    int i, j, idx = 0;
    zval *row;

    array_init(ret);
    for(i = 0; i < matrix.m; ++i)
    {
        MAKE_STD_ZVAL(row);
        array_init(row);
        for(j = 0; j < matrix.n; ++j)
        {
            add_next_index_long(row, matrix.matrix[idx]);
            ++idx;
        }
        add_next_index_zval(ret, row);
    }
}

void php_matrix_free(ZMatrix matrix)
{
    int eCnt, idx;
    eCnt = matrix.m * matrix.n;
    for(idx = 0; idx < eCnt; ++idx)
    {
        zval_ptr_dtor(&matrix.matrix[idx]);
    }
    efree(matrix.matrix);
}

void php_matrix_free_matrix(ZMatrix matrix)
{
    efree(matrix.matrix);
}

void php_matrix_free_double(DMatrix matrix)
{
    efree(matrix.matrix);
}

void php_matrix_free_long(LMatrix matrix)
{
    efree(matrix.matrix);
}

void php_matrix_elementwise_function(zval *return_value, zval *arg_matrix1, zval *arg_matrix2, void (*f)(zval*, zval*, zval*))
{
    zval **data1_1, **data1_2;
    zval **data2_1, **data2_2;

    HashTable *j1_hash, *i1_hash;
    HashTable *j2_hash, *i2_hash;
    HashPosition pointer1_1, pointer1_2;
    HashPosition pointer2_1, pointer2_2;
    int i, j, m, n;

    zval *row;

    i1_hash = Z_ARRVAL_P(arg_matrix1);
    i2_hash = Z_ARRVAL_P(arg_matrix2);
    m = zend_hash_num_elements(i1_hash);
    if(zend_hash_num_elements(i2_hash) != m)
    {
        RETURN_NULL();
    }

    zend_hash_internal_pointer_reset_ex(i1_hash, &pointer1_1);
    if(zend_hash_get_current_data_ex(i1_hash, (void**) &data1_1, &pointer1_1) == SUCCESS)
    {
        j1_hash = Z_ARRVAL_PP(data1_1);
        n = zend_hash_num_elements(j1_hash);
    }
    else
    {
        RETURN_NULL();
    }

    array_init(return_value);
    for(
        i = 0, zend_hash_internal_pointer_reset_ex(i1_hash, &pointer1_1), zend_hash_internal_pointer_reset_ex(i2_hash, &pointer2_1);
        i < m;
        ++i, zend_hash_move_forward_ex(i1_hash, &pointer1_1), zend_hash_move_forward_ex(i2_hash, &pointer2_1)
    )
    {
        if
        (
            zend_hash_get_current_data_ex(i1_hash, (void**) &data1_1, &pointer1_1) != SUCCESS
            ||
            Z_TYPE_PP(data1_1) != IS_ARRAY
            ||
            zend_hash_get_current_data_ex(i2_hash, (void**) &data2_1, &pointer2_1) != SUCCESS
            ||
            Z_TYPE_PP(data2_1) != IS_ARRAY
        )
        {
            zval_ptr_dtor(&return_value);
            RETURN_NULL();
        }

        j1_hash = Z_ARRVAL_PP(data1_1);
        j2_hash = Z_ARRVAL_PP(data2_1);
        if(zend_hash_num_elements(j1_hash) != n || zend_hash_num_elements(j2_hash) != n)
        {
            zval_ptr_dtor(&return_value);
            RETURN_NULL();
        }

        MAKE_STD_ZVAL(row);
        array_init(row);
        for(
            j = 0, zend_hash_internal_pointer_reset_ex(j1_hash, &pointer1_2), zend_hash_internal_pointer_reset_ex(j2_hash, &pointer2_2);
            j < n;
            ++j, zend_hash_move_forward_ex(j1_hash, &pointer1_2), zend_hash_move_forward_ex(j2_hash, &pointer2_2)
        )
        {
            if(zend_hash_get_current_data_ex(j1_hash, (void**) &data1_2, &pointer1_2) != SUCCESS)
            {
                zval_ptr_dtor(&row);
                zval_ptr_dtor(&return_value);
                RETURN_NULL();
            }
            if(zend_hash_get_current_data_ex(j2_hash, (void**) &data2_2, &pointer2_2) != SUCCESS)
            {
                zval_ptr_dtor(&row);
                zval_ptr_dtor(&return_value);
                RETURN_NULL();
            }

            f(row, *data1_2, *data2_2);
        }
        add_next_index_zval(return_value, row);
    }
}

void php_matrix_scalar_matrix_function(zval *return_value, double arg_scalar, zval *arg_matrix, double (*f)(double, double))
{
    zval **data1_1, **data1_2;

    HashTable *j1_hash, *i1_hash;
    HashPosition pointer1_1, pointer1_2;
    int i, j, m, n;

    double a;

    zval *row;

    zval temp;

    i1_hash = Z_ARRVAL_P(arg_matrix);
    m = zend_hash_num_elements(i1_hash);

    zend_hash_internal_pointer_reset_ex(i1_hash, &pointer1_1);
    if(zend_hash_get_current_data_ex(i1_hash, (void**) &data1_1, &pointer1_1) == SUCCESS)
    {
        j1_hash = Z_ARRVAL_PP(data1_1);
        n = zend_hash_num_elements(j1_hash);
    }
    else
    {
        RETURN_NULL();
    }

    array_init(return_value);
    for(
        i = 0, zend_hash_internal_pointer_reset_ex(i1_hash, &pointer1_1);
        i < m;
        ++i, zend_hash_move_forward_ex(i1_hash, &pointer1_1)
    )
    {
        if
        (
            zend_hash_get_current_data_ex(i1_hash, (void**) &data1_1, &pointer1_1) != SUCCESS
            ||
            Z_TYPE_PP(data1_1) != IS_ARRAY
        )
        {
            zval_ptr_dtor(&return_value);
            RETURN_NULL();
        }

        j1_hash = Z_ARRVAL_PP(data1_1);
        if(zend_hash_num_elements(j1_hash) != n)
        {
            zval_ptr_dtor(&return_value);
            RETURN_NULL();
        }

        MAKE_STD_ZVAL(row);
        array_init(row);
        for(
            j = 0, zend_hash_internal_pointer_reset_ex(j1_hash, &pointer1_2);
            j < n;
            ++j, zend_hash_move_forward_ex(j1_hash, &pointer1_2)
        )
        {
            if(zend_hash_get_current_data_ex(j1_hash, (void**) &data1_2, &pointer1_2) != SUCCESS)
            {
                zval_ptr_dtor(&row);
                zval_ptr_dtor(&return_value);
                RETURN_NULL();
            }

            temp = **data1_2;
            zval_copy_ctor(&temp);
            convert_to_double(&temp);
            a = Z_DVAL(temp);
            zval_dtor(&temp);

            add_next_index_double(row, f(arg_scalar, a));
        }
        add_next_index_zval(return_value, row);
    }
}

void php_matrix_scalar_matrix_function_long(zval *return_value, long arg_scalar, zval *arg_matrix, long (*f)(long, long))
{
    zval **data1_1, **data1_2;

    HashTable *j1_hash, *i1_hash;
    HashPosition pointer1_1, pointer1_2;
    int i, j, m, n;

    long a;

    zval *row;

    zval temp;

    i1_hash = Z_ARRVAL_P(arg_matrix);
    m = zend_hash_num_elements(i1_hash);

    zend_hash_internal_pointer_reset_ex(i1_hash, &pointer1_1);
    if(zend_hash_get_current_data_ex(i1_hash, (void**) &data1_1, &pointer1_1) == SUCCESS)
    {
        j1_hash = Z_ARRVAL_PP(data1_1);
        n = zend_hash_num_elements(j1_hash);
    }
    else
    {
        RETURN_NULL();
    }

    array_init(return_value);
    for(
        i = 0, zend_hash_internal_pointer_reset_ex(i1_hash, &pointer1_1);
        i < m;
        ++i, zend_hash_move_forward_ex(i1_hash, &pointer1_1)
    )
    {
        if
        (
            zend_hash_get_current_data_ex(i1_hash, (void**) &data1_1, &pointer1_1) != SUCCESS
            ||
            Z_TYPE_PP(data1_1) != IS_ARRAY
        )
        {
            zval_ptr_dtor(&return_value);
            RETURN_NULL();
        }

        j1_hash = Z_ARRVAL_PP(data1_1);
        if(zend_hash_num_elements(j1_hash) != n)
        {
            zval_ptr_dtor(&return_value);
            RETURN_NULL();
        }

        MAKE_STD_ZVAL(row);
        array_init(row);
        for(
            j = 0, zend_hash_internal_pointer_reset_ex(j1_hash, &pointer1_2);
            j < n;
            ++j, zend_hash_move_forward_ex(j1_hash, &pointer1_2)
        )
        {
            if(zend_hash_get_current_data_ex(j1_hash, (void**) &data1_2, &pointer1_2) != SUCCESS)
            {
                zval_ptr_dtor(&row);
                zval_ptr_dtor(&return_value);
                RETURN_NULL();
            }

            temp = **data1_2;
            zval_copy_ctor(&temp);
            convert_to_long(&temp);
            a = Z_LVAL(temp);
            zval_dtor(&temp);

            add_next_index_long(row, f(arg_scalar, a));
        }
        add_next_index_zval(return_value, row);
    }
}

double php_matrix_mul_double(double x1, double x2)
{
    return x1 * x2;
}

long php_matrix_mul_long(long x1, long x2)
{
    return x1 * x2;
}
