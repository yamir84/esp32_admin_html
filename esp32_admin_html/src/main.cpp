/***************************************************
 * CUBAELECTRONICA
 * Configuración con JSON e SPIFFS
 * Plataforma ESP32
 * Proyecto Admin Panel for ESP32
 * 05/2021 - Ing. Yamir Hidalgo Peña
 * admin@cubaelectronica.com
 * https://cubaelectronica.com
 * Licencia: MIT

 ___           _             ___    _                  _                                       
(  _`\        ( )           (  _`\ (_ )               ( )_                     _               
| ( (_) _   _ | |_      _ _ | (_(_) | |    __     ___ | ,_) _ __   _     ___  (_)   ___    _ _ 
| |  _ ( ) ( )| '_`\  /'_` )|  _)_  | |  /'__`\ /'___)| |  ( '__)/'_`\ /' _ `\| | /'___) /'_` )
| (_( )| (_) || |_) )( (_| || (_( ) | | (  ___/( (___ | |_ | |  ( (_) )| ( ) || |( (___ ( (_| |
(____/'`\___/'(_,__/'`\__,_)(____/'(___)`\____)`\____)`\__)(_)  `\___/'(_) (_)(_)`\____)`\__,_)

**************** Librerias *************************/

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <SPIFFS.h>
#include "esp32-hal-cpu.h"
#include <DNSServer.h>

/************** Archivos de Apoyo ******************/
#include "header.hpp"
#include "functions.hpp"
#include "ESP32_MQTT.hpp"
#include "ConfigReset.hpp"
#include "ConfigRead.hpp"
#include "ConfigSave.hpp"
#include "ESP32_WIFI.hpp"
// nuevo codico
#include "ESP32_API.hpp"         
#include "Websocket.hpp"
#include "Server.hpp"
#include "ESP32_WS.hpp"

/************** Setup ******************/
void setup() {
  /* SERIAL BAUDRATE */
  Serial.begin(115200);
  /* CPU FREQU */
  setCpuFrequencyMhz(240);
  log("\nInfo: Iniciando Setup");
  /* Configurar los Pines */
  configPines();
  /* Parpadeo LEDs */
  led();
  lastSendWS = 0;
  /* SPIFFS */                  
  if (!SPIFFS.begin()){
    log(F("\nError: Fallo la inicialización del SPIFFS ERROR"));
    while (true);
  }
  /* Lee la Configuración */
  configRead();
  /* Guarda la Configuración */
  configSave();
  /* Configuracion WIFI */
  WiFi.disconnect(true);
  delay(1000);
  WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
  configWiFi();
  // Lee la Configuración MQTT
  configReadMQTT();
  // Guarda la Configuración MQTT
  configSaveMQTT();
  /* MQTT */
  if(MQTT){
    client.setServer(mqttserver, 1883);
    client.setCallback(callback);
    log("\nInfo: Cliente MQTT Habilitado");
  }else{
    log("\nInfo: Cliente MQTT Deshabilitado");
  }
  /* Iniciamos el WebSocket */
  InitWebSockets();
  /* Iniciamos el Server */
  InitServer();
  /* Listo */
  log("\nInfo: Setup completado");

}

/************** Bucle Infinito ******************/
void loop() {
  /*** Usar si va a tardar mucho tiempo el Loop */
  //yield();
  /************* Portal Captivo en el ESP32 *****/
  dnsServer.processNextRequest();
  /************ Enviar JSON por WS cada segundo */
  if (millis() - lastSendWS > 1000){
      lastSendWS  = millis();
      WsMessage(GetJson(), "");
  }
  /************ Leer la temp del CPU *************/
  TempCPU = (temprature_sens_read() - 32) / 1.8;
  /************ MQTT envio de Datos  *************/
  if(MQTT){

    if (!client.connected() && WiFi.status() == WL_CONNECTED){
      //para parpadear un led cuando esta conectandose al wifi no bloqueante
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval){
        // * Guarda la última vez que parpadeó el LED.
        previousMillis = currentMillis;
        // * Si el LED está apagado, enciéndalo y viceversa:
        ledState = not(ledState);
        // * configurar el LED con el ledState de la variable:
        digitalWrite(MQTTLED, ledState);
      }
      long now = millis();
      //intenta conectarse a cada un minuto.
      if (now - lastReconnectAttempt > 1000){
        lastReconnectAttempt = now;
        // Attempt to reconnect
        if (reconnect()){
          lastReconnectAttempt = 0;
        }
      }
    }else{
      // Client connected
      client.loop();
      digitalWrite(MQTTLED, LOW);
    }

    //Publicar segun el Tiempo MQTT el mensaje
    if (client.connected()){
      if (millis() - lastMsg > timeMQTT){

        lastMsg = millis();
        // Usuario MQTT Para Armar el Topico
        const String userMQTT = mqttuser;

        String payload_to_send = MQTTJson();  
        payload_to_send.toCharArray(payload, 300);
        String topic_aux_to_send = userMQTT+"/"+device_id+"/valores";
        topic_aux_to_send.toCharArray(topico, 150);   

        if (client.publish(topico, payload)){
          log("\nInfo: Mansaje enviado por MQTT");
        }else{
          log("\nError: Mansaje no enviado por MQTT");
        } 

      }
    }

  } 

}