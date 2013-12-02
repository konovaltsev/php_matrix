#include "php.h"

#include "src/matrix.h"

/**/
PHP_FUNCTION(matrix_add_int)
{
    zval *arg_matrix1, *arg_matrix2;

    zval **data1_1, **data1_2;
    zval **data2_1, **data2_2;

    HashTable *j1_hash, *i1_hash;
    HashTable *j2_hash, *i2_hash;
    HashPosition pointer1_1, pointer1_2;
    HashPosition pointer2_1, pointer2_2;
    int i, j, m, n;
    int x1, x2;

    zval *row;
    zval temp;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }

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

            temp = **data1_2;
            zval_copy_ctor(&temp);
            convert_to_long(&temp);
            x1 = Z_LVAL(temp);
            zval_dtor(&temp);

            temp = **data2_2;
            zval_copy_ctor(&temp);
            convert_to_long(&temp);
            x2 = Z_LVAL(temp);
            zval_dtor(&temp);

            add_next_index_long(row, x1 + x2);
        }
        add_next_index_zval(return_value, row);
    }
}
/*/
PHP_FUNCTION(matrix_add_int)
{
    zval *arg_matrix1, *arg_matrix2;
    IMatrix m1, m2, res;
    int idx, cnt;
    zval *r;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }

    if(php_matrix_init_matrix_int(&m1, arg_matrix1) == FAILURE)
    {
        RETURN_NULL();
    }

    if(php_matrix_init_matrix_int(&m2, arg_matrix2) == FAILURE)
    {
        php_matrix_free_int(m1);
        RETURN_NULL();
    }

    if(m1.m != m2.m || m1.n != m2.n)
    {
        php_matrix_free_int(m1);
        php_matrix_free_int(m2);
        RETURN_NULL();
    }

    res.m = m1.m;
    res.n = m1.n;
    res.matrix = emalloc(sizeof(*res.matrix) * res.m * res.n);

    cnt = res.m * res.n;
    for(idx = 0; idx < cnt; ++idx)
    {
        res.matrix[idx] = m1.matrix[idx] + m2.matrix[idx];
    }

    php_imatrix_to_pzval(res, return_value);

    php_matrix_free_int(m1);
    php_matrix_free_int(m2);
    php_matrix_free_int(res);
}
/**/


PHP_FUNCTION(matrix_add_float)
{
    zval *arg_matrix1, *arg_matrix2;

    zval **data1_1, **data1_2;
    zval **data2_1, **data2_2;

    HashTable *j1_hash, *i1_hash;
    HashTable *j2_hash, *i2_hash;
    HashPosition pointer1_1, pointer1_2;
    HashPosition pointer2_1, pointer2_2;
    int i, j, m, n;
    double x1, x2;

    zval *row;
    zval temp;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &arg_matrix1, &arg_matrix2) == FAILURE)
    {
        RETURN_NULL();
    }

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

            temp = **data1_2;
            zval_copy_ctor(&temp);
            convert_to_double(&temp);
            x1 = Z_DVAL(temp);
            zval_dtor(&temp);

            temp = **data2_2;
            zval_copy_ctor(&temp);
            convert_to_double(&temp);
            x2 = Z_DVAL(temp);
            zval_dtor(&temp);

            add_next_index_double(row, x1 + x2);
        }
        add_next_index_zval(return_value, row);
    }
}
