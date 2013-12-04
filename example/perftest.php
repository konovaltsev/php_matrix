<?php

$m1 = [
    [1, 2, 3,],
    [4, 5, 6,],
];

$m2 = [
    [7,   8,  9, 10,],
    [11, 12, 13, 14,],
    [15, 16, 17, 18,],
];

$c = 1;

$i = $t1 = $t2 = 0;

$m1 = array_fill(0, 200, array_fill(0, 300, 42));
$m2 = array_fill(0, 300, array_fill(0, 400, 1));

matrix_mul($m1, $m2);
//matrix_dump(matrix_mul($m1, $m2));
//matrix_dump(p_matrix_mul($m1, $m2));
//echo PHP_EOL;

var_dump(xdebug_memory_usage() . '|' . memory_get_usage() . '|' . memory_get_usage(true));
$t1 = microtime(true);
for($i = 0; $i < $c; ++$i)
{
    matrix_mul($m1, $m2);
}
$t2 = microtime(true);
var_dump(xdebug_memory_usage() . '|' . memory_get_usage() . '|' . memory_get_usage(true));
echo 'c: ' . sprintf('%.3f', $t2 - $t1) . PHP_EOL . PHP_EOL;

var_dump(xdebug_memory_usage() . '|' . memory_get_usage() . '|' . memory_get_usage(true));
$t1 = microtime(true);
for($i = 0; $i < $c; ++$i)
{
    p_matrix_mul($m1, $m2);
}
$t2 = microtime(true);
var_dump(xdebug_memory_usage() . '|' . memory_get_usage() . '|' . memory_get_usage(true));
echo 'php: ' . sprintf('%.3f', $t2 - $t1) . PHP_EOL . PHP_EOL;

function p_matrix_mul($a, $b)
{
    $m = count($a);
    $n = count($a[0]);
    $p = count($b[0]);

    $return_value = array();

    for($i = 0; $i < $m; ++$i)
    {
        $row = array();
        for($j = 0; $j < $p; ++$j)
        {
            for($r = 0, $elem = 0; $r < $n; ++$r)
            {
                $elem = $elem + $a[$i][$r] * $b[$r][$j];
            }
            $row[] = $elem;
        }
        $return_value[] = $row;
    }
    return $return_value;
}