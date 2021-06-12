/* Defines */

//GPIO13 para salida de Relay 1
#define RELAY1 13
//GPIO14 LED INDICADOR WIFI 
#define WIFILED 14
//GPIO32 LED INDICADOR MQTT
#define MQTTLED 32  

/* Variables Globales */
// Variable para no bloquear la reconexion del MQTT
long lastSendWS = 0; 
// Tamaño del Objeto JSON
const size_t JSON_CONFIG = JSON_OBJECT_SIZE(5) + 500; 
// ID del dispositivo           
char id[30];
// Red WiFi
char ssid[30];
// Contraseña da Red WiFi                  
char pw[30];
// Para ssid AP
char nameap[31]; 
// Para ssid AP Password       
char passwordap[63];  
// Habilitar MQTT Broker
boolean MQTT = true;
// Usuario MQTT Broker
char mqttuser[30];  
// ID MQTT Broker  
char idMqtt[30]; 
// Password Usuario MQTT Broker       
char mqttpass[30]; 
// Para Guardar el servidor del MQTT Broker
char mqttserver[30];
// Guardará la última vez que se actualizó el LED  
unsigned long previousMillis = 0; 
// Intervalo en el cual parpadear (milisegundos)             
const long interval = 300;
// Utiliza ledState para configurar el LED                       
bool ledState = LOW;   
// Nuevas Variables declaradas
// Variable para Temperatura de CPU
float TempCPU; 

/****************************************
 * Sensor Temp Interno CPU
 ****************************************/
//Para ESP32 temperatura del CPU
#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();


/* Instancias */

/****************************************
 * Init MQTT
 ****************************************/
WiFiClient espClient;
PubSubClient client(espClient);
/****************************************
 * Init DNS
 ****************************************/
const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;

