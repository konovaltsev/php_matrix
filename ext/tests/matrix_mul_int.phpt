--TEST--
matrix_mul_int() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
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

matrix_dump(matrix_mul_int($m1, $m2));

$mem1 = 0;
$mem2 = 0;

$mem1 = memory_get_usage();
matrix_mul_int($m1, $m2);
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);

$m1 = array(
    array(1, 2, 3),
    array(4, 5, 6),
);
$m2 = array(
    array(2, 1.5, 4, 5,),
    array(3, 1, 4, 3,),
    array(3, 1, 4, 3,),
    array(3, 1, 4, 3,),
    array(3, 1, 4, 3,),
);

$mem1 = memory_get_usage();
var_dump(matrix_mul_int($m1, $m2));
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);


$m1 = array(
    array(1, 2, 3),
    array(4, 5, 6),
);
$m2 = array(
    array(2, 1.5, 4),
    array(3, 1),
);

$mem1 = memory_get_usage();
var_dump(matrix_mul_int($m1, $m2));
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);
?>
=== DONE ===
--EXPECTF--
matrix[2x4]:
|%w10%w7%w21%w22%w|
|%w20%w18%w37%w44%w|
int(0)
NULL
int(0)
NULL
int(0)
=== DONE ===