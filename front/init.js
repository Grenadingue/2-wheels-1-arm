$( document ).ready(function() {

   var serve = Service("http://localhost:8080");
   var drawer = Draw();

   // Populate the saved data choice
   serve.get().then(function(success) {
      var location = $("#saved_file");
      for (var i = 0; i < success.length; ++i) {
         location.append("<li class='saved_file'>" + success[i] + "</li>");
      };
   });

   // Do the live simulation using the inputed value
   $("#launch_simulation").on("click", function() {
      var data = {};
      serve.post(data).then(function() {
         drawer.launchWS();
      });
   });

   // Get the corresponding data file and launch the draw
   $("#saved_file").on("click", function(e) {
      var file_name = $(this).text();
      serve.get(file_name).then(function(success) {
         drawer.launchFile(success.data);
      });
   });
});