/* Instancia de AsyncWebServer */
AsyncWebServer server(80);

// Cargar Información de las paginas al Servidor --------------------------------------
void InitServer(){
    /**********************************************/
    server.serveStatic("/bootstrap-responsive.min.css", SPIFFS, "/bootstrap-responsive.min.css").setDefaultFile("bootstrap-responsive.min.css");
    server.serveStatic("/bootstrap.min.css", SPIFFS, "/bootstrap.min.css").setDefaultFile("bootstrap.min.css");
    server.serveStatic("/styles.css", SPIFFS, "/styles.css").setDefaultFile("styles.css");
    server.serveStatic("/jquery.easy-pie-chart.css", SPIFFS, "/jquery.easy-pie-chart.css").setDefaultFile("jquery.easy-pie-chart.css");
    server.serveStatic("/bootstrap.min.js", SPIFFS, "/bootstrap.min.js").setDefaultFile("bootstrap.min.js");
    server.serveStatic("/jquery-1.9.1.min.js", SPIFFS, "/jquery-1.9.1.min.js").setDefaultFile("jquery-1.9.1.min.js");
    server.serveStatic("/jquery.easy-pie-chart.js", SPIFFS, "/jquery.easy-pie-chart.js").setDefaultFile("jquery.easy-pie-chart.js");
    server.serveStatic("/modernizr.min.js", SPIFFS, "/modernizr.min.js").setDefaultFile("modernizr.min.js");
    server.serveStatic("/scripts.js", SPIFFS, "/scripts.js").setDefaultFile("scripts.js");
    server.serveStatic("/glyphicons-halflings.png", SPIFFS, "/glyphicons-halflings.png").setDefaultFile("glyphicons-halflings.png");
    server.serveStatic("/glyphicons-halflings-white.png", SPIFFS, "/glyphicons-halflings-white.png").setDefaultFile("glyphicons-halflings-white.png");
    server.serveStatic("/logo.png", SPIFFS, "/logo.png").setDefaultFile("logo.png");
    /**********************************************/
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      // Index.html
      File file = SPIFFS.open(F("/index.html"), "r");
      if (file){
        file.setTimeout(100);
        String s = file.readString();
        file.close();
        // Actualiza contenido dinamico del html
        s.replace(F("#id#"), id);
        /* Bloque WIFI */
        s.replace(F("#WFEstatus#"), WiFi.status() == WL_CONNECTED ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-important'>DESCONECTADO</span>"));
        s.replace(F("#WFSSID#"), WiFi.status() == WL_CONNECTED ? F(ssid) : F("--"));
        s.replace(F("#sysIP#"), ipStr(WiFi.status() == WL_CONNECTED ? WiFi.localIP() : WiFi.softAPIP()));
        s.replace(F("#WFDBM#"), WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0"));
        s.replace(F("#WFPRC#"), WiFi.status() == WL_CONNECTED ? String(round(1.88 * (WiFi.RSSI() + 100)), 0) : F("0"));
        /* Bloque MQTT */
        s.replace(F("#MQTTStatus#"), client.connected() ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-important'>DESCONECTADO</span>"));
        s.replace(F("#MQTTBroker#"), client.connected() ? F(mqttserver) : F("--"));
        s.replace(F("#MQTTUser#"), F(mqttuser));
        s.replace(F("#MQTTID#"), F(idMqtt));
        /* Bloque pie chart */
        s.replace(F("#SWFI#"), WiFi.status() == WL_CONNECTED ? String(round(1.88 * (WiFi.RSSI() + 100)), 0) : F("0"));
        s.replace(F("#PMEM#"), String(round(SPIFFS.usedBytes() * 100 / SPIFFS.totalBytes()), 0));
        s.replace(F("#ram#"), String(ESP.getFreeHeap() * 100 / ESP.getHeapSize()));
        s.replace(F("#cpu#"), String(TempCPU));
        // Envia dados al navegador
        request->send(200, "text/html", s);  
      }else{
        request->send(500, "text/html", "<sript>alert('fallo la lectura del index.html');</script>");
        log(F("\nError: Home - ERROR leyendo archivo"));
      }
    });

    /**********************************************/
	  server.begin();
    log("\nInfo: HTTP server iniciado");
    /**********************************************/
    

 }