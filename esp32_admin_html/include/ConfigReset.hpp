/**********************************************/
void configReset(){
    /* ------------------- CLIENTE -------------------- */
    strlcpy(id, "ESP32_ADMIN", sizeof(id));
    strlcpy(ssid, "casa ciruelo", sizeof(ssid));
    strlcpy(pw, "casaplum265", sizeof(pw));
    /* ------------------- AP -------------------- */
    strlcpy(nameap, deviceID().c_str(), sizeof(nameap));
    strlcpy(passwordap, "iotcubaelectronica", sizeof(passwordap));
}
/**********************************************/
