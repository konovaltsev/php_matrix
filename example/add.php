<?php

$m1 = [
    [1, 2, 3,],
    [4, 4.6, 5,],
];

$m2 = [
    [2, 3, 4,],
    [5, 6, 7,],
];

//$m1 = array_fill(0, 1000, array_fill(0, 3690, 42));
//$m2 = array_fill(0, 1000, array_fill(0, 3690, 666));

$c = 100000;

var_dump(memory_get_usage());
$t1 = microtime(true);
for($i = 0; $i < $c; ++$i)
{
    matrix_add($m1, $m2);
}
$t2 = microtime(true);
var_dump(memory_get_usage());
matrix_dump(matrix_add($m1, $m2));
echo 'c: ' . ($t2 - $t1) . PHP_EOL;

$t1 = microtime(true);
for($i = 0; $i < $c; ++$i)
{
    m_add($m1, $m2);
}
$t2 = microtime(true);
matrix_dump(m_add($m1, $m2));
echo 'p: ' . ($t2 - $t1) . PHP_EOL;


function m_add($m1, $m2)
{
    $m = count($m1);
    $n = count($m1[0]);
    $ret = array();
    for($i = 0; $i < $m; $i++)
    {
        for($j = 0; $j < $n; $j++)
        {
            $ret[$i][$j] = /*intval*/($m1[$i][$j]) + /*intval*/($m2[$i][$j]);
        }
    }
    return $ret;
}
