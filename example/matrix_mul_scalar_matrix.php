<?php
matrix_dump(matrix_mul_scalar_matrix(
    2.9,
    array(
        array(2, 1.5, 4),
        array(null, 'qq', 1),
    )
));

matrix_dump(matrix_mul_scalar_matrix_int(
    2.9,
    array(
        array(2, 1.5, 4),
        array(null, 'qq', 1),
    )
));

var_dump(matrix_mul_scalar_matrix(
    2.9,
    array(
        array(2, 1.5, 4),
        array(3, 1),
    )
));
