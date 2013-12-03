<?php
$matrix = [
    [1, 2, 3,],
    [4, 5.1, 6,],
//    ['a', 'b', 'cc',],
//    ['d', 'e', 'ff',],
];
$scalar = 2.1;

$c = 100000;
matrix_dump($matrix);

var_dump(memory_get_usage());
$t1 = microtime(true);
for($i = 0; $i < $c; ++$i)
{
    matrix_mul_scalar_matrix_int($scalar, $matrix);
//	ob_start(); matrix_dump($matrix); ob_end_clean();
//    matrix_is_valid($matrix);
}
$t2 = microtime(true);
var_dump(memory_get_usage());
matrix_dump(matrix_mul_scalar_matrix_int($scalar, $matrix));
echo 'c: ' . ($t2 - $t1) . PHP_EOL;

$t1 = microtime(true);
for($i = 0; $i < $c; ++$i)
{
    p_mul($scalar, $matrix);
}
$t2 = microtime(true);
matrix_dump(p_mul($scalar, $matrix));
echo 'php: ' . ($t2 - $t1) . PHP_EOL;

function p_mul($scalar, $matrix)
{
    $m = count($matrix);
    $n = count($matrix[0]);
    $ret    = array();
    for($i = 0; $i < $m; $i++)
    {
        for($j = 0; $j < $n; $j++)
        {
            $ret[$i][$j] = /*intval*/($scalar) * /*intval*/($matrix[$i][$j]);
        }
    }
    return $ret;
}