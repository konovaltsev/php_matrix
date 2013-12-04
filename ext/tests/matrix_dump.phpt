--TEST--
matrix_dump() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
$mem1 = 0;
$mem2 = 0;
matrix_dump(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q',),
    )
);
$mem1 = memory_get_usage();
matrix_dump(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q', 5,),
    )
);
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);
matrix_dump(array(1, 2, 3));
?>
=== DONE ===
--EXPECTF--
matrix[2x3]:
|%w1%w2%w3%w|
|%w<undef>%w5.500%w"q"%w|
matrix[not valid]
int(0)
matrix[not valid]
=== DONE ===
