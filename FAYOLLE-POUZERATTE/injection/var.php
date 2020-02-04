<?php
$jsSearcher=
"<script src=\"https://code.jquery.com/jquery-latest.min.js\"></script>
<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\"></script>
";
function makeHeader($titre,$description,$css){

$headerSearcher="<html lang=\"fr\">
<head>
<meta name=\"msapplication-TileColor\" content=\"#da532c\">
<meta name=\"msapplication-config\" content=\"img/browserconfig.xml\">
<meta name=\"theme-color\" content=\"#ffffff\">
<meta charset=\"utf-8\">
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">
<meta name=\"description\" content=\"".$description."\">
<title>".$titre."</title>
<script src=\"https://code.jquery.com/jquery-latest.min.js\"></script>
<script src=\" https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.15.0/umd/popper.min.js\"></script>
<link href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\" rel=\"stylesheet\">
<!--
<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js\"></script>
-->
<link href=\"https://cdnjs.cloudflare.com/ajax/libs/flag-icon-css/0.8.2/css/flag-icon.min.css\" rel=\"stylesheet\">

<script src=\"./js/bootbox.all.min.js\"></script>
<link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.4.2/css/all.css\" integrity=\"sha384-/rXc/GQVaYpyDdyxK+ecHPVYJSN9bmVFBvjA/9eOB+pb3F2w2N6fc5qB9Ew5yIns\" crossorigin=\"anonymous\">
<script src=\"https://unpkg.com/sweetalert/dist/sweetalert.min.js\"></script>
<link href=\"css/landing-page.min.css\" rel=\"stylesheet\">
<link href=\"css/animate.css\" rel=\"stylesheet\">


<link rel=\"apple-touch-icon\" sizes=\"57x57\" href=\"./img/ico/apple-icon-57x57.png\">
<link rel=\"apple-touch-icon\" sizes=\"60x60\" href=\"./img/ico/apple-icon-60x60.png\">
<link rel=\"apple-touch-icon\" sizes=\"72x72\" href=\"./img/ico/apple-icon-72x72.png\">
<link rel=\"apple-touch-icon\" sizes=\"76x76\" href=\"./img/ico/apple-icon-76x76.png\">
<link rel=\"apple-touch-icon\" sizes=\"114x114\" href=\"./img/ico/apple-icon-114x114.png\">
<link rel=\"apple-touch-icon\" sizes=\"120x120\" href=\"./img/ico/apple-icon-120x120.png\">
<link rel=\"apple-touch-icon\" sizes=\"144x144\" href=\"./img/ico/apple-icon-144x144.png\">
<link rel=\"apple-touch-icon\" sizes=\"152x152\" href=\"./img/ico/apple-icon-152x152.png\">
<link rel=\"apple-touch-icon\" sizes=\"180x180\" href=\"./img/ico/apple-icon-180x180.png\">
<link rel=\"icon\" type=\"image/png\" sizes=\"192x192\"  href=\"./img/ico/android-icon-192x192.png\">
<link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"./img/ico/favicon-32x32.png\">
<link rel=\"icon\" type=\"image/png\" sizes=\"96x96\" href=\"./img/ico/favicon-96x96.png\">
<link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"./img/ico/favicon-16x16.png\">
<link rel=\"manifest\" href=\"/manifest.json\">
<meta name=\"msapplication-TileColor\" content=\"#ffffff\">
<meta name=\"msapplication-TileImage\" content=\"./img/ico/ms-icon-144x144.png\">
<meta name=\"theme-color\" content=\"#ffffff\">

";
if ($css!=""){
  $headerSearcher=$headerSearcher."<link href=\"".$css."\" rel=\"stylesheet\" type=\"text/css\">";
}
$headerSearcher=$headerSearcher."</head>";
return $headerSearcher;
}




$footerSearcher="<footer class=\"footer bg-light\">
<div class=\"container\">
<div class=\"row\">
<div class=\"col-lg-6 h-100 text-center text-lg-left my-auto\">
<ul class=\"list-inline mb-2\">
<li class=\"list-inline-item\">
<a href=\"remerciements.php\">Remerciements</a>
</li>
<li class=\"list-inline-item\">&sdot;</li>
<li class=\"list-inline-item\">
<a href=\"disclaimer.php\">Disclaimer</a>
<li class=\"list-inline-item\">&sdot;</li>
<li class=\"list-inline-item\">
<a href=\"mentions-legales.php\">Mentions légales</a>
<li class=\"list-inline-item\">&sdot;</li>
<li class=\"list-inline-item\">
<a href=\"faq.php\">FAQ</a>
</li>
</ul>
<br>

<p class=\"text-muted small mb-4 mb-lg-0\">&copy; Qwanturank 2020. All Rights Reserved.</p>
</div>
<div class=\"col-lg-6 h-100 text-center text-lg-right my-auto\">
<ul class=\"list-inline mb-0\">
<li class=\"list-inline-item mr-3\">
<a href=\"https://fb.me/qwanturank.click\">
<i class=\"fab fa-facebook fa-2x fa-fw\"></i>
</a>
</li>
<li class=\"list-inline-item mr-3\">
<a href=\"https://twitter.com/ClickQwanturank\">
<i class=\"fab fa-twitter fa-2x fa-fw\"></i>
</a>
</li>
</ul>

</div>
</div>
</div>
 </footer>";
// <li class=\"list-inline-item\">&sdot;</li>
// <li class=\"list-inline-item\">
// <a href=\"confidentialite.php\">Politique de confidentialité</a>
//<link href=\"vendor/fontawesome-free/css/all.min.css\" rel=\"stylesheet\">
//<link href=\"vendor/simple-line-icons/css/simple-line-icons.css\" rel=\"stylesheet\" type=\"text/css\">
