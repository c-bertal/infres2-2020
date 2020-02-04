<?php define("_BBC_PAGE_NAME", "Index");
define("_BBCLONE_DIR", "bbclone/");
define("COUNTER", _BBCLONE_DIR."mark_page.php");
if (is_readable(COUNTER)) include_once(COUNTER);
include 'var.php';
?>
<!DOCTYPE html>
<?php echo makeHeader("Connexion", "Connexion", "") ?>
<body>
<!-- Navbar -->
<!-- Masthead -->
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.1.0/css/all.css" integrity="sha384-lKuwvrZot6UHsBSfcMvOkWwlCMgc0TaWr+30HWe3a4ltaBwTZhyTEggF5tJv8tbt" crossorigin="anonymous">
<link href="css/contact.css" rel="stylesheet">

<script>
Swal.fire({
  html: '<div class="row justify-content-around"><div class="col-sm-6"><img src="http://dummyimage.com/200x200/f0f/fff" /></div>'+'<div class="col-sm-6">'+        '<h3 class="post-title">Post title</h3>'+        '<p>st desc post desc post desc post desc post desc post desc t '+'</div>',
  animation: false
})
</script>

<div class="container">
    <br><br>
	<div class="row justify-content-center">
		<div class="col-12 col-md-8 col-lg-6 pb-5">


                    <!--Form with header-->

                    <form action="messageSend.php" method="post" id="contact">
                        <div class="card border-primary rounded-0">
                            <div class="card-header p-0">
                                <div class="bg-info text-white text-center py-2">
                                    <h3>Connexion</h3>

                                </div>
                            </div>
                            <div class="card-body p-3">

                                <!--Body-->

                                <div class="form-group">
                                    <div class="input-group mb-2">
                                        <div class="input-group-prepend">
                                          <div class="input-group-text"><i class="fa fa-user text-info"></i></div>
                                        </div>
                                        <input type="text" class="form-control" id="name" name="name" placeholder="Nom" required>
                                    </div>
                                </div>




                                <div class="form-group">
                                    <div class="input-group mb-2">
                                        <div class="input-group-prepend">
                                            <div class="input-group-text"><i class="fa fa-key text-info"></i></div>
                                        </div>
                                          <input type="password" class="form-control" id="subject" name="passwordUser" placeholder="Sujet du message" required>

                                        </div>
                                      </div>


                                <?php
                                require_once 'securimage/securimage.php';
                                echo Securimage::getCaptchaHtml();
                                ?>
                                <img style="float: left; padding-right: 5px; padding-bottom: 50px" id="captcha_one" src="/securimage/securimage_show.php" alt=" ">
                                <div class="text-center">
                                    <input type="submit" value="Se connecter" class="btn btn-info btn-block rounded-0 py-2">
                                </div>
                            </div>

                        </div>

                    </form>

                    <!--Form with header-->


                </div>
	</div>
</div>




<script src="js/contact.js?<?php echo uniqid();?>"></script> <!--?<?php /*echo uniqid();*/ ?>-->

</body>
</html>
