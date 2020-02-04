<?php
session_start();
$user = 'root';
$password = '';
$database = 'bdd_site';
$port = 3306; 
$mysqli = new mysqli('127.0.0.1', $user, $password, $database, $port);

if ($mysqli->connect_error) {
    die('Connect Error (' . $mysqli->connect_errno . ') '
            . $mysqli->connect_error);
} else {
	if (isset($_POST['pseudo']) && isset($_POST['mdp'])){
		$username = stripslashes($_POST['pseudo']);
		$password = stripslashes($_POST['mdp']);
		$query = "SELECT * FROM user WHERE name='$username' and pass='$password'"; 
		$result = mysqli_query($mysqli,$query);
		$rows = mysqli_num_rows($result);
		if($rows==1){
			while($val = mysqli_fetch_array($result)){
				$champ = $val["role"];	
			}
			$_SESSION['AdminOrNot'] = $champ;
			$_SESSION['NameCompte'] = $username;
			$_SESSION['PassCompte'] = $password;
		}
	}
}

$mysqli->close();
header("Location: index.php");
?>