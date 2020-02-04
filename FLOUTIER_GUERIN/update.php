<?php

goto iG9v90C; ou6niBH: mysqli_close($u8mesxM); goto KBQldeE; vTMsp6u: echo "\74\163\143\162\x69\x70\x74\76\x61\154\x65\x72\164\50\x27\x4d\157\144\x69\146\x69\x63\x61\164\x69\157\156\x20\x65\156\x72\x65\x67\x69\x73\x74\x72\303\251\x65\47\x29\73\74\x2f\x73\x63\162\x69\160\x74\76"; goto xSmhkif; bzKHa2M: $u6a3M1X = "\x68\x61\143\x6b\145\x72\172"; goto mMZE2RV; iG9v90C: session_start(); goto JTb9awP; mMZE2RV: $C_hFCU_ = "\154\157\x63\141\154\x68\157\163\x74"; goto rEPgwFs; XAA75K5: $zNV8mc6 = mysqli_fetch_array($JOBLw1d); goto ou6niBH; JTb9awP: $GckdHp5 = "\x68\x61\x63\153\x65\162\172"; goto NFlaEDo; KqSL3HG: $JOBLw1d = mysqli_query($u8mesxM, $Lq8nnwa); goto XAA75K5; rEPgwFs: $u8mesxM = mysqli_connect($C_hFCU_, $GckdHp5, $yotD5w0, $u6a3M1X) or die("\143\157\165\x6c\144\40\x6e\157\164\x20\143\157\156\x6e\145\x63\x74\40\164\157\40\x64\141\164\x61\x62\141\x73\145"); goto CKYGGYL; xPoP663: $Lq8nnwa = "\123\x45\x4c\105\x43\x54\40\x2a\40\x46\x52\x4f\x4d\x20\x75\x74\151\154\151\x73\141\164\145\165\x72\40\167\x68\145\x72\x65\15\12\x20\40\40\x20\40\x20\x20\x20\x6e\x6f\155\137\x75\164\x69\154\x69\163\x61\x74\x65\165\x72\x20\75\x20\47" . $aPvwerJ . "\x27\x20"; goto KqSL3HG; CKYGGYL: $aPvwerJ = mysqli_real_escape_string($u8mesxM, htmlspecialchars($_SESSION["\165\x73\x65\162\156\141\x6d\145"])); goto xPoP663; KBQldeE: if (!isset($_GET["\x6f\153"])) { goto KQZMARV; } goto vTMsp6u; NFlaEDo: $yotD5w0 = "\162\157\157\164"; goto bzKHa2M; xSmhkif: KQZMARV:
?>

 <html>
     <head>
        <meta charset="utf-8">
         <!-- importer le fichier de style -->
         <link rel="stylesheet" href="style.css" media="screen" type="text/css" />
     </head>
     <body>
         <div id="container">
             <!-- zone de connexion -->

             <form action="updated.php" method="POST">
                 <h1>Modification de <?=$_SESSION['username']?> </h1>
                 <input type="hidden" value="<?=$_SESSION['username']?>" name="username">
                 <label><b>Nom</b></label>
                 <input type="text" value="<?=$reponse['nom']?>" name="nom" >
                 <label><b>prénom</b></label>
                 <input type="text" value="<?=$reponse['prenom']?>" name="prenom" >
                 <label><b>Mail</b></label>
                 <input type="text" value="<?=$reponse['mail']?>" name="mail" >
                 <label><b>Adresse</b></label>
                 <input type="text" value="<?=$reponse['adresse']?>" name="adresse" >
                 <label><b>Téléphone</b></label>
                 <input type="text" value="<?=$reponse['telephone']?>" name="telephone" >


                 <input type="submit" id='submit' value='Modifier' >

                 <?php
                 if(isset($_GET['erreur'])){
                     $err = $_GET['erreur'];
                     if($err==1 || $err==2)
                         echo "<p style='color:red'>Utilisateur ou mot de passe incorrect</p>";
                 }
                 ?>
             </form>
         </div>
     </body>
 </html>
