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