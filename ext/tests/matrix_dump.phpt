--TEST--
matrix_dump() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
matrix_dump(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q',),
    )
);
matrix_dump(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q', 5,),
    )
);
?>
=== DONE ===
--EXPECTF--
matrix[2x3]:
|%w1%w2%w3%w|
|%w<undef>%w5.500%w"q"%w|
matrix[not valid]
=== DONE ===
