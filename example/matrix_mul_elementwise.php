<?php
matrix_dump(matrix_mul_elementwise(
    array(
        array(1, 2.9, 3),
        array(4, 5, 6),
    ),
    array(
        array(2, 1.5, 4),
        array(null, 'qq', 1),
    )
));

matrix_dump(matrix_mul_elementwise_int(
    array(
        array(1, 2, 3),
        array(4, 5, 6),
    ),
    array(
        array(2, 1.5, 4),
        array(null, 'qq', 1),
    )
));

var_dump(matrix_mul_elementwise(
    array(
        array(1, 2, 3),
        array(4, 5, 6),
    ),
    array(
        array(2, 1.5, 4),
        array(3, 1),
    )
));
