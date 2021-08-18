#!/usr/bin/php

<?php
$my_str = 'The quick brown fox jumps over the lazy dog.';
echo strtoupper($my_str);
echo "\n";

$uploaddir = $_SERVER['DOCUMENT_ROOT'] . "/" . getenv('UPLOAD_DIR');
$querystr = getenv('QUERY_STRING');
// $uploadfile = $uploaddir . basename($_FILES['file']['name']);

print("uploaddir   : $uploaddir\n");
print("querystr   (before): $querystr\n");
print("querystr   (after) :");
echo 'Bonjour ' . htmlspecialchars($_GET[0]) . '!';
$_SERVER['QUERY_STRING'] = strtoupper($_SERVER['QUERY_STRING']);
print("\n");
print(strtoupper($_SERVER['QUERY_STRING']));
print("querystr   : $querystr\n");
// print_r($_SERVER);
print_r($_GET);

echo '</pre>';

?>