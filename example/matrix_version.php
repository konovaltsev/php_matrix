<?php
var_dump(matrix_version());
$c = 1000000;
$i = $t1 = $t2 = 0;

$t1 = microtime(true);
var_dump(xdebug_memory_usage() . '|' . memory_get_usage() . '|' . memory_get_usage(true));
for($i = 0; $i < $c; ++$i)
{
    matrix_version();
}
var_dump(xdebug_memory_usage() . '|' . memory_get_usage() . '|' . memory_get_usage(true));
$t2 = microtime(true);
echo 'c: ' . sprintf('%.3f', $t2 - $t1) . PHP_EOL . PHP_EOL;
