/* Service to communicate with the node server by HTTP */
var Service = function(url) {
  var server_url = url;
  return ({
    /* Get request to directly receive a data file */
    /* Without inputed id, get the list of data files */
    get: function(id = "") {
      return $.ajax({
       method: "GET",
       url: server_url + "/save/" + id
     });
    },
    /* Post request to send the inputed simulation parameters to the server */
    post: function(data) {
      return $.ajax({
       method: "POST",
       url: server_url + "/params",
       data: data,
     })
    }
  })
}