var Draw = function () {

   var ctx = document.getElementById("myChart");
   return {
      launchFile(data) {

         var best = [];
         var average = [];
         var labels = [];
         for (var i = 0; i < data.length; ++i){
            best.push(data[i].best);
            average.push(data[i].average);
            labels.push("Iteration n°" + i);
         }

         var myChart = new Chart(ctx, {
           type: 'line',
           data: {
            labels: labels,
            datasets: [{
               label: "Best by Iteration",
               backgroundColor: [
               'rgba(255, 99, 132, 0.2)'],
               data: best
            },{

               label: "Average by Iteration",
               backgroundColor: [
               'rgba(0, 99, 132, 0.2)'],
               data: average
            }]
         },
         options: {
          scales: {
            yAxes: [{
              ticks: {
                beginAtZero:true
             }
          }]
       }
    }
 });

      },
      launchWS() {

      }
   }
}