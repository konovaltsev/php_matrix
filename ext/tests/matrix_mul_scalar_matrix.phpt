--TEST--
matrix_mul_scalar_matrix() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
$s = 1.9;
$m = array(
    array(2, 1.2, 4),
    array(NULL, 'qq', 1),
);

matrix_dump(matrix_mul_scalar_matrix($s, $m));

$mem1 = 0;
$mem2 = 0;

$mem1 = memory_get_usage();
matrix_mul_scalar_matrix($s, $m);
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);

$m = array(
    array(2, 1.5, 4),
    array(3, 1),
);

$mem1 = memory_get_usage();
var_dump(matrix_mul_scalar_matrix($s, $m));
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);
?>
=== DONE ===
--EXPECTF--
matrix[2x3]:
|%w3.800%w2.280%w7.600%w|
|%w0.000%w0.000%w1.900%w|
int(0)
NULL
int(0)
=== DONE ===