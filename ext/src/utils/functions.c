#include "php.h"

#include "src/matrix.h"

int php_matrix_init_matrix(ZMatrix* out, zval* php_matrix)
{
    zval **data, **data2;
    int i_count, i_prev, j_count, i, j;
    HashTable *i_hash, *j_hash;
    HashPosition pointer, pointer2;
    zval ***array;

    zval tmp;

    out->iCount = 0;
    out->jCount = 0;
    out->array = NULL;

    if (Z_TYPE_P(php_matrix) != IS_ARRAY)
    {
        return FAILURE;
    }

    j_hash = Z_ARRVAL_P(php_matrix);
    j_count = zend_hash_num_elements(j_hash);
    array = emalloc(sizeof(zval*) * j_count);

    i_prev = -1;

    for(
        j = 0, zend_hash_internal_pointer_reset_ex(j_hash, &pointer);
        zend_hash_get_current_data_ex(j_hash, (void**) &data, &pointer) == SUCCESS;
        ++j, zend_hash_move_forward_ex(j_hash, &pointer)
    )
    {
        if (Z_TYPE_PP(data) != IS_ARRAY)
        {
          return FAILURE;
        }
        i_hash = Z_ARRVAL_PP(data);
        i_count = zend_hash_num_elements(i_hash);
        if(i_count < 1 || (i_prev > 0 && i_prev != i_count))
        {
          return FAILURE;
        }

        array[j] = emalloc(sizeof(zval*) * i_count);

        for(
            i = 0, zend_hash_internal_pointer_reset_ex(i_hash, &pointer2);
            zend_hash_get_current_data_ex(i_hash, (void**) &data2, &pointer2) == SUCCESS;
            ++i, zend_hash_move_forward_ex(i_hash, &pointer2)
        )
        {
            ALLOC_ZVAL(array[j][i]);
            INIT_PZVAL_COPY(array[j][i], *data2);
        }

        i_prev = i_count;
    }

    out->iCount = i_count;
    out->jCount = j_count;
    out->array = array;

    return SUCCESS;
}

void php_matrix_free(ZMatrix matrix)
{
    int i, j;
    for(j = 0; j < matrix.jCount; ++j)
    {
        for(i = 0; i < matrix.iCount; ++i)
        {
            zval_ptr_dtor(&matrix.array[j][i]);
        }
        efree(matrix.array[j]);
    }
    efree(matrix.array);
}

void php_matrix_free_array(ZMatrix matrix)
{
    int i, j;
    for(j = 0; j < matrix.jCount; ++j)
    {
        efree(matrix.array[j]);
    }
    efree(matrix.array);
}
