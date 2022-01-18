#!/usr/bin/php

<?php
$uploaddir = $_SERVER['DOCUMENT_ROOT'] . "/" . getenv('UPLOAD_DIR');
$uploadfile = $uploaddir . basename($_FILES['file']['name']);

if (!is_dir($uploaddir))
    mkdir($uploaddir, 0775);

print("uploaddir   : $uploaddir</br>\n");
print("uploadfile  : $uploadfile</br>\n</br>\n");

echo '<pre>';
if (move_uploaded_file($_FILES['file']['tmp_name'], $uploadfile)) {
    echo "Le fichier est valide, et a été téléchargé
           avec succès. Voici plus d'informations :\n";
} else {
    echo "Attaque potentielle par téléchargement de fichiers.
          Voici plus d'informations :\n";
}

echo 'Voici quelques informations de débugage :';
print_r($_FILES);

echo '</pre>';
?>
