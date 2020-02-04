<?php
    include "SHA-1.php";

    if (isset($_POST['id']) && isset($_POST['mdp'])) {
        if (azerty($_POST['id'] ,$_POST['mdp'])) {
            echo "<h1>Vous etes connecte</h1>";
            echo '<b>Identifiant : </b>'.$_POST['id'];
            echo '<b>Mot de passe : </b>'.$_POST['mdp'];
        }
        else {
            sleep(1);
            header("Location: index.php");
            exit();
        }
    }
    else {
        echo "<h1>Erreur</h1>";
    }
