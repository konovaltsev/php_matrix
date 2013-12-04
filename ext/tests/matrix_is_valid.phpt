--TEST--
matrix_is_valid() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
$mem1 = 0;
$mem2 = 0;
var_dump(matrix_is_valid(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q',),
    )
));

$mem1 = memory_get_usage();
matrix_is_valid(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q',),
    )
);
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);

var_dump(matrix_is_valid(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q', 5,),
    )
));

$mem1 = memory_get_usage();
matrix_is_valid(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q', 5,),
    )
);
$mem2 = memory_get_usage();
var_dump($mem2 - $mem1);

?>
=== DONE ===
--EXPECTF--
bool(true)
int(0)
bool(false)
int(0)
=== DONE ===
