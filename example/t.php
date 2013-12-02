<?php
$matrix = [
    [1, 2, 3,],
    [4, 5.1, 6,],
    ['a', 'b', 'cc',],
    ['d', 'e', 'ff',],
];

$c = 100000;
matrix_dump($matrix);

var_dump(memory_get_usage());
$t1 = microtime(true);
for($i = 0; $i < $c; ++$i)
{
    matrix_transpose($matrix);
//	ob_start(); matrix_dump($matrix); ob_end_clean();
//    matrix_is_valid($matrix);
}
$t2 = microtime(true);
var_dump(memory_get_usage());
matrix_dump(matrix_transpose($matrix));
echo 'c: ' . ($t2 - $t1) . PHP_EOL;

$t1 = microtime(true);
for($i = 0; $i < $c; ++$i)
{
    p_transpose($matrix);
}
$t2 = microtime(true);
matrix_dump(p_transpose($matrix));
echo 'php: ' . ($t2 - $t1) . PHP_EOL;


function p_transpose($matrix)
{
    $m = count($matrix);
    $n = count($matrix[0]);
    $ret    = array();
    for($j = 0; $j < $m; ++$j)
    {
        for($i = 0; $i < $n; ++$i)
        {
            $ret[$i][$j] = $matrix[$j][$i];
        }
    }
    return $ret;
}
