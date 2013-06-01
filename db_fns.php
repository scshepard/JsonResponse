<?php

error_reporting('E_ALL');
ini_set ( 'display_errors', 'On' );

function db_connect()
{

	$result = mysqli_connect("path", "act", "pwd", "table");

     return $result;
}
