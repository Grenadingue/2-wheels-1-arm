$( document ).ready(function() {

   var serve = Service("http://localhost:8080");
   var drawer = Draw();

   // Populate the saved data choice
   serve.get().then(function(success) {
      var location = $("#saved_file");
      for (var i = 0; i < success.length; ++i) {
         location.append("<li class='saved_file'><a href='#'>" + success[i] + "</a></li>");
      };
   });

   // Do the live simulation using the inputed value
   $("#launch_simulation").on("click", function() {
      var socket = io.connect('http://localhost:8081');

      socket.emit('launchSimulation',
       {
        serverPort: "8081",
        backupFile: '/home/foo/bar.csv',
        populationSize: parseInt($("#popsize").val(), 10),
        mutationRate: parseInt($("#mutationrate").val(),10)
       }
      );
      $(".cover-container").hide();
      $("canvas").show();
      drawer.launchWS(socket);
   });

   // Get the corresponding data file and launch the draw
   $("#saved_file").delegate("a", "click", function(e) {
      var file_name = $(this).text();
      serve.get(file_name).then(function(success) {
         $(".cover-container").hide();
         $("canvas").show();
         drawer.launchFile(success);
      });
   });
});