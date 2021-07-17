/**********************************************/
void configReset(){
    /* ------------------- CLIENTE -------------------- */
    strlcpy(id, "ESP32_ADMIN", sizeof(id));
    strlcpy(ssid, "casa ciruelo", sizeof(ssid));
    strlcpy(pw, "casaplum265", sizeof(pw));
    /* ------------------- AP -------------------- */
    strlcpy(nameap, deviceID().c_str(), sizeof(nameap));
    strlcpy(passwordap, "iotcubaelectronica", sizeof(passwordap));
}
/**********************************************/
void configResetMQTT(){
    // Define configuración por defecto del equipo conexión MQTT
    strlcpy(mqttuser, "curso_iot", sizeof(mqttuser));
    strlcpy(mqttpass, "cubaelectronica", sizeof(mqttpass));
    strlcpy(mqttserver, "cubaelectronica.com", sizeof(mqttserver));
    strlcpy(idMqtt, deviceID().c_str(), sizeof(idMqtt));
    timeMQTT = 60000;
    MQTT = true;
}
/**********************************************/