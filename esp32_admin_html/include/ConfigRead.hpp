/**********************************************/
boolean configRead(){
    // Lee la configuración
    StaticJsonDocument<JSON_CONFIG> jsonConfig;
    File file = SPIFFS.open("/Config.json", "r");
    if (deserializeJson(jsonConfig, file)){
        // Si falla la lectura inicia valores por defecto
        configReset();
        log("\nError: Falló la lectura de la configuración, iniciando valores por defecto");
        return false;
    }else{
        /* ------------------- CLIENTE -------------------- */
        strlcpy(id, jsonConfig["id"] | "", sizeof(id));
        strlcpy(ssid, jsonConfig["ssid"] | "", sizeof(ssid));
        strlcpy(pw, jsonConfig["pw"] | "", sizeof(pw));
        /* ------------------- AP -------------------- */
        strlcpy(nameap, jsonConfig["nameap"] | "", sizeof(nameap));
        strlcpy(passwordap, jsonConfig["passwordap"] | "", sizeof(passwordap));
        file.close();
        log("\nInfo: Lectura correcta configuración general");
        return true;
    }
}
/**********************************************/
boolean configReadMQTT(){
    // Lee la configuración MQTT
    StaticJsonDocument<JSONMQTT_SIZE> jsonConfig;

    File file = SPIFFS.open(F("/ConfigMQTT.json"), "r");
    if (deserializeJson(jsonConfig, file))
    {
        // Si falla la lectura asume valores padrones
        configResetMQTT();
        log(F("\nError: Falló la lectura del MQTT, asumiendo valores por defecto"));
        return false;
    }
    else
    {
        // Si lee el archivo
        strlcpy(mqttuser, jsonConfig["mqttuser"] | "", sizeof(mqttuser));
        strlcpy(mqttpass, jsonConfig["mqttpass"] | "", sizeof(mqttpass));
        strlcpy(mqttserver, jsonConfig["mqttserver"] | "", sizeof(mqttserver));
        strlcpy(idMqtt, jsonConfig["idMqtt"] | "", sizeof(idMqtt));
        timeMQTT = jsonConfig["timeMQTT"] | 60000;
        MQTT = jsonConfig["MQTT"] | true;
        file.close();
        log(F("\nInfo: Lectura de configuración MQTT correcta"));
        return true;
    }
}
/**********************************************/

