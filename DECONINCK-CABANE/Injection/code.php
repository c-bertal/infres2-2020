<?php

function transformation($entry)
{
    $entries = explode(' ', $entry);

    $exit = null;
    foreach ($entries as $entry) {
        $exit .= pack('H*', dechex(bindec($entry)));
    }

    return $exit;
}

