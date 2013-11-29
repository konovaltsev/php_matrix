#include "php.h"

#include "src/matrix.h"

int php_matrix_init_matrix(ZMatrix* out, zval* php_matrix)
{
    zval **data, **data2;
    int n, j_prev, m, i, j;
    HashTable *ij_hash, *i_hash;
    HashPosition pointer, pointer2;
    zval ***matrix;

    zval tmp;

    out->n = 0;
    out->m = 0;
    out->matrix = NULL;

    if (Z_TYPE_P(php_matrix) != IS_ARRAY)
    {
        return FAILURE;
    }

    i_hash = Z_ARRVAL_P(php_matrix);
    m = zend_hash_num_elements(i_hash);
    matrix = emalloc(sizeof(zval*) * m);

    j_prev = -1;

    for(
        i = 0, zend_hash_internal_pointer_reset_ex(i_hash, &pointer);
        zend_hash_get_current_data_ex(i_hash, (void**) &data, &pointer) == SUCCESS;
        ++i, zend_hash_move_forward_ex(i_hash, &pointer)
    )
    {
        if (Z_TYPE_PP(data) != IS_ARRAY)
        {
          return FAILURE;
        }
        j_hash = Z_ARRVAL_PP(data);
        n = zend_hash_num_elements(j_hash);
        if(n < 1 || (j_prev > 0 && j_prev != n))
        {
          return FAILURE;
        }

        matrix[i] = emalloc(sizeof(zval*) * n);

        for(
            j = 0, zend_hash_internal_pointer_reset_ex(j_hash, &pointer2);
            zend_hash_get_current_data_ex(j_hash, (void**) &data2, &pointer2) == SUCCESS;
            ++j, zend_hash_move_forward_ex(j_hash, &pointer2)
        )
        {
            ALLOC_ZVAL(matrix[i][j]);
            INIT_PZVAL_COPY(matrix[i][j], *data2);
        }

        j_prev = n;
    }

    out->n = n;
    out->m = m;
    out->matrix = matrix;

    return SUCCESS;
}

void php_matrix_free(ZMatrix matrix)
{
    int i, j;
    for(i = 0; i < matrix.m; ++i)
    {
        for(j = 0; j < matrix.n; ++j)
        {
            zval_ptr_dtor(&matrix.matrix[i][j]);
        }
        efree(matrix.matrix[i]);
    }
    efree(matrix.matrix);
}

void php_matrix_free_matrix(ZMatrix matrix)
{
    int i;
    for(i = 0; i < matrix.m; ++i)
    {
        efree(matrix.matrix[i]);
    }
    efree(matrix.matrix);
}
