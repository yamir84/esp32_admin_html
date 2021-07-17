/**********************************************/
boolean configSave(){
    // Graba configuración
    StaticJsonDocument<JSON_CONFIG> jsonConfig;
    File file = SPIFFS.open("/Config.json", "w+");
    if (file){
        /* ------------------- CLIENTE -------------------- */
        jsonConfig["id"] = id;
        jsonConfig["ssid"] = ssid;
        jsonConfig["pw"] = pw;
        /* ------------------- AP -------------------- */
        jsonConfig["nameap"] = nameap;
        jsonConfig["passwordap"] = passwordap;
        serializeJsonPretty(jsonConfig, file);
        file.close();
        log("\nInfo: Grabando configuración general");
        //serializeJsonPretty(jsonConfig, Serial);
        return true;
    }else{
      log("\nError: Falló el grabado de la configuración general");
      return false;
    }    
}
/**********************************************/
boolean configSaveMQTT(){
    // Guarda configuración MQTT
    StaticJsonDocument<JSONMQTT_SIZE> jsonConfig;
    File file = SPIFFS.open(F("/ConfigMQTT.json"), "w+");
    if (file)
    {
        // Atribulle valores al JSON y graba
        jsonConfig["mqttuser"] = mqttuser;
        jsonConfig["mqttpass"] = mqttpass;
        jsonConfig["mqttserver"] = mqttserver;
        jsonConfig["idMqtt"] = idMqtt;
        jsonConfig["timeMQTT"] = timeMQTT;
        jsonConfig["MQTT"] = MQTT;
        serializeJsonPretty(jsonConfig, file);
        file.close();
        log(F("\nInfo: Guardando la configuración del MQTT"));
        //serializeJsonPretty(jsonConfig, Serial);
        return true;
    }else{
      log(F("\nError: Falló el guardado de la configuración del MQTT"));
      return false;
    }    
}
/**********************************************/