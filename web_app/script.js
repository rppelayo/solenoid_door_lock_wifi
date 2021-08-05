$(function(){

    var msg;
    var init = "ABC";
  
   var client = mqtt.connect('wss://iotfishfeeder:mhh3T7yPApq2XrGE@iotfishfeeder.cloud.shiftr.io', { // insert your MQTT Instance here
     clientId: 'browser-client'
   });
   
   client.on('connect', function(){
     console.log('client has connected!');
   });
   
   client.on('message', function(topic, message) {
    $('#data').text(message.toString());
   });
     client.subscribe('solenoid');  //Insert your MQTT topic here
        
     document.querySelector('#open-lock').addEventListener('click', function() {
      var p = confirm("Unlock the door?");
  
      if (p != false) {
        alert("Door Unlocked!")
      }else{
        return;
      }
      var user = "MQTT CLIENT ID"; //Insert MQTT CLIENT ID here
     
      msg = user.concat(">","ON");
      client.publish("solenoid", msg);
  
    });
  })