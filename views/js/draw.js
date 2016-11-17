var Draw = function () {
   //Initialize the graph with empty data
   var ctx = $("#myChart");
   var defaults = {};
   Chart.defaults.global.defaultFontSize = 19;
   var options = {
      maintainAspectRatio: false,
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero:true,
                }
            }]
        }
     };
   var startingdata = {
            labels: [],
            datasets: [
               {
                  label: "Best",
                  strokeColor: "rgba(220,220,220,1)",
                  pointColor: "rgba(220,220,220,1)",
                  borderColor: "red",
                  pointStrokeColor: "#fff",
                  data: []
               },
               {
                  label: "Average",
                  strokeColor: "rgba(151,187,205,1)",
                  pointColor: "rgba(151,187,205,1)",
                  borderColor: "yellow",
                  pointStrokeColor: "#fff",
                  data: []
               },
               {
                  label: "Worst",
                  strokeColor: "rgba(220,220,220,1)",
                  pointColor: "rgba(220,220,220,1)",
                  borderColor: "white",
                  pointStrokeColor: "#fff",
                  data: []
               }
            ]
         };

   return {
      launchWS(socket) {
         var myChart = null;
         var ready = false;

         socket.on('set y axle', function(data) {
            options.scales.yAxes[0].ticks = {beginAtZero: true, min: 0, max: data.theoreticalMaxScore};
            myChart = new Chart(ctx, {type: 'line', data: startingdata, options: options});
            ready = true;
         });

         socket.on('new_iteration', function (data) {
            if (!ready) return;
            myChart.data.datasets[0].data.push(data.maxScore);
            myChart.data.datasets[1].data.push(data.averageScore);
            myChart.data.datasets[2].data.push(data.worstScore);
            myChart.config.data.labels.push("Iteration n°" + (data.iteration + 1));
            myChart.update();
         });
      },

      launchFile(data) {
        options.scales.yAxes[0].ticks = {beginAtZero: true, min: 0, max: data.theoreticalMaxScore};
         /* Read the inputed file line by line to populate the data */
         for (var i = 0; i < data.results.length; ++i) {
            startingdata.datasets[0].data.push(data.results[i].maxScore);
            startingdata.datasets[1].data.push(data.results[i].averageScore);
            startingdata.datasets[2].data.push(data.results[i].worstScore);
            startingdata.labels.push("Iteration n°" + (data.results[i].iteration + 1));
         }
         var myChart = new Chart(ctx, {type: 'line', data: startingdata, options: options});

      }
   }
}
