--TEST--
matrix_mul_elementwise() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
$m1 = array(
    array(1, 2, 3),
    array(4, 5, 6),
);
$m2 = array(
    array(2, 1.2, 4),
    array(NULL, 'qq', 1),
);

matrix_dump(matrix_mul_elementwise($m1, $m2));

$mem1 = 0;
$mem2 = 0;

$mem1 = memory_get_usage();
matrix_mul_elementwise($m1, $m2);
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
var_dump(matrix_mul_elementwise($m1, $m2));
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);
?>
=== DONE ===
--EXPECTF--
matrix[2x3]:
|%w2.000%w2.400%w12.000%w|
|%w0.000%w0.000%w6.000%w|
int(0)
NULL
int(0)
=== DONE ===