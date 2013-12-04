--TEST--
matrix_version() function basic test
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
var_dump(matrix_version());
?>
=== DONE ===
--EXPECT--
string(3) "1.0"
=== DONE ===
