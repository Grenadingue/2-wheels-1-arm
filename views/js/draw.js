var Draw = function () {
   //Initialize the graph with empty data
   var ctx = $("#myChart");
   var options = {
      responsive: true,
      maintainAspectRatio: false,
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero:true
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
                  borderColor: "blue",
                  pointStrokeColor: "#fff",
                  data: []
               }
            ]
         };

   return {
      launchWS(socket) {
         var myChart = new Chart(ctx, {type: 'line', data: startingdata, options: options});


         /* Simulation of real time rendering */
         var cptr = 1;

         socket.on('new_iteration', function (data) {
            myChart.data.datasets[0].data.push(data.best);
            myChart.data.datasets[1].data.push(data.mid);
            myChart.config.data.labels.push("Iteration n°" + cptr);
            cptr++;
            myChart.update();
         });
      },
      launchFile(data) {

         /* Read the inputed file line by line to populate the data */
         for (var i = 0; i < data.length; ++i) {
            startingdata.datasets[0].data.push(data[i].best);
            startingdata.datasets[1].data.push(data[i].mid);
            startingdata.labels.push("Iteration n°" + i);
         }
         var myChart = new Chart(ctx, {type: 'line', data: startingdata, options: options});

      }
   }
}