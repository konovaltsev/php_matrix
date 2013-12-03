--TEST--
matrix_add() function fail test
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
    array(2, 1.5, 4),
    array(3, 1),
);
$mem1 = 0;
$mem2 = 0;

var_dump(matrix_add($m1, $m2));
$mem1 = memory_get_usage();
matrix_add($m1, $m2);
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);
?>
=== DONE ===
--EXPECTF--
NULL
int(0)
=== DONE ===