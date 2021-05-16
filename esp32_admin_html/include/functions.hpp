/* Funciones Personalizadas YHP */

/**********************************************/
/*  Genera un log en el puerto Serial */
void log(String s){
    Serial.println(s);
}
/**********************************************/
/*  Retorna IPAddress en formato "n.n.n.n" de IP a String */
String ipStr(const IPAddress &ip){    
    String sFn = "";
    for (byte bFn = 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3)) & 0xFF);
    return sFn;
}
/**********************************************/
/*  De HEX a String */
String hexStr(const unsigned long &h, const byte &l = 8){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}
/**********************************************/
/*  Create a Unique ID from MAC address */
String idUnique(){
    // Retorna los ultimos 4 Bytes del MAC rotados
    char idunique[15]; 
    uint64_t chipid = ESP.getEfuseMac();           
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}
/**********************************************/
/*  ESP32 utiliza funcion getEfuseMac() */
String deviceID(){
    return "ESP32" + hexStr(ESP.getEfuseMac()) + String(idUnique());
}
/**********************************************/
/*  Configurar los Pines de Salida */
void configPines(){
    pinMode(RELAY1, OUTPUT);              
    pinMode(WIFILED, OUTPUT);                  
    pinMode(MQTTLED, OUTPUT);                  
    digitalWrite(MQTTLED, LOW);
    digitalWrite(WIFILED, LOW);
    digitalWrite(RELAY1, LOW);
}
/**********************************************/
/*  Parpadeo de los LEDs */
void led(){
    for(int i=0; i < 4; i++) {
        digitalWrite(MQTTLED, HIGH);
        digitalWrite(WIFILED, HIGH);
        delay(100);
        digitalWrite(MQTTLED, LOW);
        digitalWrite(WIFILED, LOW);
        delay(100);
    }
}
/**********************************************/