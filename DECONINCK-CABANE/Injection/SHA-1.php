<?php

include "code.php";

function azerty($arg1, $arg2)
{
    if ($arg1 == transformation("01000001 01100100 00110010 00110000 00110100 00111001 01101101 01111100 01101110 00101110") && $arg2 == transformation("00101110 01101110 01111100 01101101 00111001 00110100 00110000 00110010 01000001 01100100"))
        return true;
    else
        return false;
}




