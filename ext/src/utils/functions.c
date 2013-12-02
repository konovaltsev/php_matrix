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

int php_matrix_init_matrix_int(IMatrix* out, zval* php_matrix)
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

int php_imatrix_to_pzval(IMatrix matrix, zval* ret)
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

void php_matrix_free_int(IMatrix matrix)
{
    efree(matrix.matrix);
}
