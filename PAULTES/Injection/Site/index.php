<?php
session_start();
?>

<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<link rel="stylesheet" media="all" type="text/css" href="style.css" />
		<title>En cour de création</title>
	</head>
	<body>
		<div class="site">
			<div class="header">
				<center>Se connecter</center>
			</div>
			<div class="clean"></div>
        <div class="menu_h">
            <ul class="menu_h_list">
                <li><a href="index.php">Accueil</a></li>
				<?php if((array_key_exists('NameCompte',$_SESSION) && !empty($_SESSION['NameCompte']))&&(array_key_exists('PassCompte',$_SESSION) && !empty($_SESSION['PassCompte']))) { 
				?>
				<li><a href="deco.php">Deconnexion</a></li>
				<?php
} ?>

            </ul>
        </div><div class="clean"></div>
			
			<div class="corp">
				<div class="corp_top"></div>
				<div class="corp_ctn">
				<?php if((array_key_exists('NameCompte',$_SESSION) && !empty($_SESSION['NameCompte']))&&(array_key_exists('PassCompte',$_SESSION) && !empty($_SESSION['PassCompte']))) { 
				?>
				<center>Bonjour <?php echo $_SESSION['NameCompte']; ?></center>
				<p>Votre role est : <?php if($_SESSION['AdminOrNot'] == 1){ echo 'Administrateur'; } else { echo 'Utilisateur'; } ?></p>
				<?php
} else {
?>
					<center><h1>Connexion</h1></center>
					<div class="paragraphe">
						<center><h2>Se connecter</h2></center>
						<div class="paragraphe">
							<center>
								<form action="connect.php" method="POST">
								Pseudo :</br>
								<input type="text" style="text-align:center;" value="pseudo" name="pseudo" size="20" onFocus="javascript:this.value=''" /></br></br>
								Mots de passe :</br>
								<input type="password" style="text-align:center;" value="password" name="mdp" size="20" onFocus="javascript:this.value=''" /></br></br>
								<input type="submit" name="connecte" value=" Connexion "> 
								</form>
							</center>
						</div>
					</div>
					<?php 
} ?> 
				</div>
				<div class="corp_bottom"></div>
			</div>
		</div>
	</body>
</html>
