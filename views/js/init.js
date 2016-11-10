$( document ).ready(function() {

   var serve = Service("http://localhost:8080");
   var drawer = Draw();

   // Populate the saved data choice
   serve.get().then(function(success) {
      var location = $("#saved_file");
      for (var i = 0; i < success.length; ++i) {
         location.append("<option>" + success[i] + "</option>");
      };
   });

   // Do the live simulation using the inputed value
   $("#launch_simulation").on("click", function() {
     var file_name = $(".select_perso option:selected").text();
     if ($("#launch_simulation").text() == "Display backup") {
       serve.get(file_name).then(function(success) {
          $("#myForm").hide();
          $("canvas").show();
          drawer.launchFile(success);
       });
     } else {
       var socket = io.connect('http://localhost:8081');
       socket.emit('launchSimulation',
        {
         serverPort: "8081",
         backupFile: '/home/foo/bar.csv',
         populationSize: parseInt($("#popsize").val(), 10),
         mutationRate: parseInt($("#mutationrate").val(),10)
        }
       );
       $("#myForm").hide();
       $("canvas").show();
       drawer.launchWS(socket);
     }
   });

   $("#show_form_param").on("click", function() {
     $("#form_select").hide();
     $("#form_param").show();
     $("#launch_simulation").text("Launch simulation");
   });

   $("#show_form_select").on("click", function() {
     $("#form_param").hide();
     $("#form_select").show();
     $("#launch_simulation").text("Display backup");
   });
});
