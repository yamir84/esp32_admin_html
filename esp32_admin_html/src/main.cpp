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
#include "Server.hpp"

/************** Setup ******************/
void setup() {
  /* SERIAL BAUDRATE */
  Serial.begin(115200);
  /* CPU FREQU */
  setCpuFrequencyMhz(240);
  log("\nInfo: Iniciando Setup");
  /* MQTT */
  if(MQTT){
    client.setServer(mqttserver, 1883);
    client.setCallback(callback);
    log("\nInfo: Cliente MQTT Habilitado");
  }else{
    log("\nInfo: Cliente MQTT Deshabilitado");
  }
  /* Configurar los Pines */
  configPines();
  /* Parpadeo LEDs */
  led();
  lastReconnectAttempt = 0;
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
  /* Server */
  InitServer();
  /* Listo */
  log("\nInfo: Setup completado");

}

/************** Bucle Infinito ******************/
void loop() {
  TempCPU = (temprature_sens_read() - 32) / 1.8;
}