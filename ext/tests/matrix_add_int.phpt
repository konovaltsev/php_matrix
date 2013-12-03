--TEST--
matrix_add() function basic test
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
?>
=== DONE ===
--EXPECTF--
matrix[2x3]:
|%w3%w3%w7%w|
|%w7%w5%w7%w|
=== DONE ===