/**********************************************/
void configWiFi(){
    /************ AP ************************/
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(nameap, passwordap);
    log("\nInfo: WiFi AP " + deviceID() + " - IP " + ipStr(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", WiFi.softAPIP());
    
    /************ CLIENTE *******************/
    WiFi.begin(ssid, pw);
    log("\nInfo: Conectando WiFi " + String(ssid));
    byte b = 0;
    while (WiFi.status() != WL_CONNECTED && b < 60){
        b++;
        delay(500);
        //para parpadear led WIFI cuando esta conectandose al wifi no bloqueante
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval){
            // * Guarda la última vez que parpadeó el LED.
            previousMillis = currentMillis;
            // * Si el LED está apagado, enciéndalo y viceversa:
            ledState = not(ledState);
            // * configurar el LED con el ledState de la variable:
            digitalWrite(WIFILED, ledState);
        }
    }

    if (WiFi.status() == WL_CONNECTED){
        // WiFi Station conectado
        log("\nInfo: WiFi conectado (" + String(WiFi.RSSI()) + ") IP " + ipStr(WiFi.localIP()));
        digitalWrite(WIFILED, HIGH);
    }else{
        log(F("\nError: WiFi no conectado"));
        digitalWrite(MQTTLED, LOW);
    }
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  log("\nInfo: WiFI Desconectado Motivo");
  log("\nError: " + info.disconnected.reason);
  log("\nInfo: Intentando conectar al WiFi");
  WiFi.disconnect();
  WiFi.begin(ssid, pw);
}