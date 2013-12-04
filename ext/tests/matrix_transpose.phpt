--TEST--
matrix_transpose() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
$mem1 = 0;
$mem2 = 0;
matrix_dump(matrix_transpose(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q',),
    )
));
$mem1 = memory_get_usage();
var_dump(matrix_transpose(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q', 5,),
    )
));
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);
$mem1 = memory_get_usage();
matrix_transpose(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q',),
    )
);
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);
?>
=== DONE ===
--EXPECTF--
matrix[3x2]:
|%w1%w<undef>%w|
|%w2%w5.500%w|
|%w3%w"q"%w|
NULL
int(0)
int(0)
=== DONE ===
