
    $(function(){
        $("#contact").submit(function(event){
            var nom        = $("#name").val();
            var sujet      = $("#subject").val();
            var email      = $("#nombre").val();
            var message    = $("#textInput").val();
            var dataString = nom + sujet + email + message;
            var msg_all    = "Merci de remplir tous les champs";
            var msg_alert  = "Merci de remplir ce champs";

                $.ajax({
                    type : "POST",
                    url: $(this).attr("action"),
                    data: $(this).serialize(),
                    success : function(data) {


                        if (!(data.includes("Erreur"))){

                            // $("h4").html("<p style=\"color:green\">Formulaire bien envoyé</p>");

                            swal("Connexion réussie", data, "success")
                        }
                        else{
                              window.location = "./erreurConnexion.html";
                        }
                    },
                    error: function(e) {
                        // $("h4").html("<p style=\"color:red\">Erreur, merci de réessayer ultérieurement</p>");
                        swal("Erreur !", "Merci de réessayer ultérieurement", "error")
                    }
                });
            //}

            return false;
        });
    });
