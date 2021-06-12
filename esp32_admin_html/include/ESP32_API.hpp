/* Websocket */
AsyncWebSocket ws("/ws");

/* Función enviar JSON al Websocket */
void WsMessage(String status, String descriptor )
{
  if(descriptor != ""){
    String response;
    StaticJsonDocument<300> doc;
    doc["status"] = status;
    doc["descriptor"] = descriptor;
    serializeJson(doc, response);
    ws.textAll(response);
  }else{
    ws.textAll(status);
  }
}
