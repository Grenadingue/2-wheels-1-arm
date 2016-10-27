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
                  fillColor: "rgba(220,220,220,0.2)",
                  strokeColor: "rgba(220,220,220,1)",
                  pointColor: "rgba(220,220,220,1)",
                  pointStrokeColor: "#fff",
                  data: []
               },
               {
                  label: "Average",
                  fillColor: "rgba(151,187,205,0.2)",
                  strokeColor: "rgba(151,187,205,1)",
                  pointColor: "rgba(151,187,205,1)",
                  pointStrokeColor: "#fff",
                  data: []
               }
            ]
         };

   return {
      launchWS() {
         var myChart = new Chart(ctx, {type: 'line', data: startingdata, options: options});
         /* Simulation of real time rendering */
         var i = 1;
         var cptr = 1;
         var update = function() {
            myChart.data.datasets[0].data.push(i*2);
            myChart.data.datasets[1].data.push(i);
            myChart.config.data.labels.push("Iteration n°" + cptr);
            i = i * 2;
            cptr = cptr + 1;
            myChart.update();
         }
         setInterval(function() {update(); console.log("ntm");}, 1000);
      },
      launchFile(data) {

         /* Read the inputed file line by line to populate the data */
         for (var i = 0; i < data.length; ++i) {
            startingdata.datasets[0].data.push(data[i].best);
            startingdata.datasets[1].data.push(data[i].average);
            startingdata.labels.push("Iteration n°" + i);
         }
         var myChart = new Chart(ctx, {type: 'line', data: startingdata, options: options});

      }
   }
}