<?php
$m1 = array(
    array(1.2, 3, 4),
    array(4, 5, 6),
);
$m2 = array(
    array(2.9, 3, 2, 4),
    array(NULL, 'qq', 1, 2),
    array(2, 1, 4, 3.1),
);

matrix_dump(matrix_mul($m1, $m2));
matrix_dump(matrix_mul_int($m1, $m2));
