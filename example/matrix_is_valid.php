<?php
var_dump(matrix_is_valid(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q',),
    )
));

var_dump(matrix_is_valid(
    array(
        array(1, 2, 3,),
        array(null, 5.5, 'q', 5,),
    )
));
