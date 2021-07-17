/**********************************************/
void callback(char *topic, byte *payload, unsigned int length){

    String mensaje  = "";
    String str_topic(topic);
 
    for (uint16_t i = 0; i < length; i++){
        mensaje += (char)payload[i];
    }

    mensaje.trim();
    
    DynamicJsonDocument doc(1024);

    deserializeJson(doc, mensaje);

    if (doc["RELAY1"] == "on"){
        digitalWrite(RELAY1, HIGH);
    }else if(doc["RELAY1"] == "off"){
        digitalWrite(RELAY1, LOW);
    }
    
    log("\nInfo: Topico -->" + str_topic);
    log("\nInfo: Mensaje -->" + mensaje);
    serializeJsonPretty(doc, Serial);
    log("\n");  


}
  
/**********************************************/
boolean reconnect(){

    log("\nInfo: Intentando conexión al Broker MQTT...");
    // Conexion al Servidor MQTT , ClienteID, Usuario, Password.
    // Ver documentación => https://pubsubclient.knolleary.net/api.html
    if (client.connect(idMqtt, mqttuser, mqttpass)){
    
    log("\nInfo: Conectado al Broker MQTT");
    // Usuario MQTT Para Armar el Topico
    const String userMQTT = mqttuser;
    // Nos suscribimos a comandos  usuario/dispositivo/comando
    String topico_subscribe = userMQTT+"/"+device_id+"/command";
    topico_subscribe.toCharArray(topico, 150);
    client.subscribe(topico);

    }
    return client.connected();

}
/**********************************************/

