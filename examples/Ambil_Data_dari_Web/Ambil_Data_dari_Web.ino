/*
 * KRwifi adalah Library Arduino yang digunakan untuk WiFi Module & WiFi Shield Kelas Robot
 * Untuk bisa menggunakan Library ini kamu harus add dulu Library WiFiEsp.h
 * Yang mana Library nya bisa di dapatkan di https://github.com/bportaluri/WiFiEsp
 * 
 * Dan Program contoh bisa digunakan untuk Arduino Uno, Nano, Mega, dkk.
 * Untuk Arduino Mega silakan pasang TX ke RX1, RX ke TX1. 
 * Untuk Arduino Uno / Nano silakan pasang TX ke Pin 2, dan RX ke Pin 3.
 * 
 * Jika pake WiFi Shield tinggal Colok aja.
 * Btw WiFi Modulenya bisa di dapatkan di https://www.tokopedia.com/kelasrobot
 * Thanks
 * 
 * Selamat Mencoba
 */

#include<KRwifi.h>
char* ssid = "xxx";   //Ganti xxx dengan nama WiFi / Hotspot
char* pass = "xxx";   //Ganti xxx dengan password WiFi / Hotspot

char* server = "test.kelasrobot.com";

void setup() {
  Serial.begin(9600);
  setWifi(ssid, pass);
}

void loop() {
  httpGet(server, "/index.php", 80);
  Serial.print("Respon: ");
  Serial.println(getData);
  delay(5000);
}
