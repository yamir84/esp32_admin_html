String GetJson(){
   String response;
   StaticJsonDocument<3000> jsonDoc;
   jsonDoc["WFEstatus"] = WiFi.status() == WL_CONNECTED ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-important'>DESCONECTADO</span>");
   jsonDoc["WFDBM"] = WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0");
   jsonDoc["WFPRC"] = WiFi.status() == WL_CONNECTED ? String(round(1.88 * (WiFi.RSSI() + 100)), 0) : F("0"); 
   jsonDoc["cpu"] = String(TempCPU); 
   jsonDoc["ram"] = String(ESP.getFreeHeap() * 100 / ESP.getHeapSize()); 
   jsonDoc["PMEM"] = String(round(SPIFFS.usedBytes() * 100 / SPIFFS.totalBytes()), 0); 
   jsonDoc["MQTTStatus"] = client.connected() ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-important'>DESCONECTADO</span>");
   jsonDoc["MQTTBroker"] = client.connected() ? F(mqttserver) : F("--");
   
   serializeJson(jsonDoc, response);   
   return response;
}

void ProcessRequest(AsyncWebSocketClient * client, String request){

   String command = request;

   if(command == "1"){
        
   }else{    
    
   }

}
