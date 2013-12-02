#include "php.h"

#include "src/matrix.h"

int php_matrix_init_matrix(ZMatrix* out, zval* php_matrix)
{
    zval **data, **data2;
    int n, m, i, j, idx;
    HashTable *j_hash, *i_hash;
    HashPosition pointer, pointer2;
    zval **matrix;

    zval tmp;

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
