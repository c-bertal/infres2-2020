<?php

session_start();
require 'vendor/autoload.php';
include_once './securimage/securimage.php';
use App\SQLiteConnection;
$securimage = new Securimage();
$correctLogin=false;

/*if ($securimage->check($_POST['captcha_code']) == false) {
    echo    json_encode("Erreur");
}
else {*/
    $pdo = (new SQLiteConnection())->connect();
    //$sql = 'SELECT userName FROM bdUsers where bdUsers.userName="' . $_POST['name'] . '"';
    $sql = 'SELECT bdUsers.userName
FROM bdUsers, bdMdp 
WHERE bdUsers.userId == bdmDP.mdpUserId
AND bdUsers.userName=="'.$_POST["name"].'" and bdmDP.mdpUser=="'.$_POST['passwordUser'].'"';
    foreach ($pdo->query($sql) as $row) {
        $correctLogin = true;

/*        $sqlId = 'SELECT userId FROM bdUsers where bdUsers.userName="' . $_POST['name'] . '"';
        foreach ($pdo->query($sqlId) as $rowId) {
            $sqlPwd = 'SELECT mdpUser FROM bdMdp where bdMdp.mdpUserId="' . $rowId[0] . '"';
            foreach ($pdo->query($sqlPwd) as $rowMdp) {
                if ($_POST['passwordUser'] === $rowMdp[0]) {
                    $correctLogin = true;
                }
            }
        }*/
    }
    if ($correctLogin) {
        echo json_encode("T'es trop fort !");
    } else {
        echo json_encode("Erreur");
    }
//}

 ?>
