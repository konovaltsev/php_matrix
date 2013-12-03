--TEST--
Check for matrix presence
--CREDITS--
Roman Konovaltsev rkonovaltsev@gmail.com
--SKIPIF--
<?php if (!extension_loaded("matrix")) die("Skipped: matrix extension required."); ?>
--FILE--
<?php
echo "matrix extension is available";
?>
--EXPECT--
matrix extension is available
