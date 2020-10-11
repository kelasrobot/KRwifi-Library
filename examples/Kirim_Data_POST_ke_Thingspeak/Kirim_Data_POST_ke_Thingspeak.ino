#include<KRwifi.h>
char* ssid         = "xxxx";
char* pass         = "xxxx";
char* server       = "api.thingspeak.com";
char* APIKey       = "xxxx";

//Millis
uint32_t periodeKirim   = 20000;
uint32_t millisKirim;

int count;

void setup() {
  Serial.begin(9600);
  setWifi(ssid, pass);
  millisKirim = millis();
}

void loop() {
  if (millisKirim < millis()) {
    millisKirim = millis() + periodeKirim;
    count++;
    String konten;
    konten = String() + "field1=" + count +  "&field2=" + count;
    httpPOST(server, APIKey, konten, 50, 80);
    Serial.print("Respon: ");
    Serial.println(getData);
  }
  statusPengiriman();
}
