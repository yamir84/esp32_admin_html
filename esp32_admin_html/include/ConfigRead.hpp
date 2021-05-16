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
