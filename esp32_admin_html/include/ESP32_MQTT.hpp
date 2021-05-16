/**********************************************/
void callback(char *topic, byte *payload, unsigned int length){

}
  
/**********************************************/
boolean reconnect(){
      log("\nInfo: Intentando conexión al Broker MQTT...");
      // Conexion al Servidor MQTT , ClienteID, Usuario, Password.
      // Ver documentación => https://pubsubclient.knolleary.net/api.html
      if (client.connect(idMqtt, mqttuser, mqttpass)){
          log("\nInfo: Conectado al Broker MQTT");

      }
      return client.connected();
}
/**********************************************/

