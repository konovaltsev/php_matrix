--TEST--
matrix_add_int() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
matrix_dump(matrix_add_int(
    array(
        array(1, 2, 3),
        array(4, 5, 6),
    ),
    array(
        array(2, 1.5, 4),
        array(3, 'qq', 1),
    )
));
$m1 = array(
    array(1, 2, 3),
    array(4, 5, 6),
);
$m2 = array(
    array(2, 1.5, 4),
    array(3, 1),
);
$mem1 = 0;
$mem2 = 0;

$mem1 = memory_get_usage();
matrix_add(
    array(
        array(1, 2, 3),
        array(4, 5, 6),
    ),
    array(
        array(2, 1.5, 4),
        array(3, 'qq', 1),
    )
);
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);

$mem1 = memory_get_usage();
var_dump(matrix_add_int($m1, $m2));
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);

?>
=== DONE ===
--EXPECTF--
matrix[2x3]:
|%w3%w3%w7%w|
|%w7%w5%w7%w|
int(0)
NULL
int(0)
=== DONE ===