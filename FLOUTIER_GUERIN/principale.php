<html>
    <head>
        <meta charset="utf-8">
        <!-- importer le fichier de style -->
        <link rel="stylesheet" href="style.css" media="screen" type="text/css" />
    </head>
    <body style='background:#fff;'>
        <div id="content">

            <a href='principale.php?deconnexion=true'><span>Déconnexion</span></a>

            <!-- tester si l'utilisateur est connecté -->
            <?php
                session_start();
                if(isset($_GET['deconnexion']))
                {
                   if($_GET['deconnexion']==true)
                   {
                      session_unset();
                      header("location:index.php");
                   }
                }
                else if($_SESSION['username'] !== ""){
                    $user = $_SESSION['username'];

                    // afficher un message
                    require_once('update.php');
                }
            ?>

        </div>
    </body>
</html>
