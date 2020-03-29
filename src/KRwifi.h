#include "WiFiEsp.h"
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3);
#endif
int status = WL_IDLE_STATUS;
WiFiEspClient client;
String getHttpStatus;
String getData;

void httpGet(char* kriot_server, String kriot_path, int kriot_port) {
  client.stop();
  if (client.connect(kriot_server, kriot_port)) {
    client.print("GET ");
    client.print(kriot_path);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(kriot_server);
    client.println("Connection: close");
    client.println();
    char endOfHeaders[] = "\r\n\r\n";
    client.find(endOfHeaders);
    getData = client.readString();
    getData.trim();
    getHttpStatus = "Koneksi Berhasil";
  }
  else {
    getHttpStatus = "Koneksi Gagal";
  }
}

void httpsGet(char* kriot_server, String kriot_path, int kriot_port) {
  client.stop();
  if (client.connectSSL(kriot_server, kriot_port)) {
    client.print("GET ");
    client.print(kriot_path);
    client.println(" HTTP/1.0");
    client.print("Host: ");
    client.println(kriot_server);
    client.println("Connection: close");
    client.println();
    char endOfHeaders[] = "\r\n\r\n";
    client.find(endOfHeaders);
    getData = client.readString();
    getData.trim();
    getHttpStatus = "Koneksi Berhasil";
  }
  else {
    getHttpStatus = "Koneksi Gagal";
  }
}


void setWifi(char* kriot_ssid, char* kriot_pass) {
  Serial1.begin(115200);
  Serial1.println("AT+UART_DEF=9600,8,1,0,0");
  delay(500);
  Serial1.begin(9600);
  WiFi.init(&Serial1);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("[WIFI]: KelasRobot WiFi Shield Tidak Terdeteksi");
    while (true);
  }
  while ( status != WL_CONNECTED) {
    Serial.print("[WIFI]: Mencoba Terhubung ke SSID: ");
    Serial.println(kriot_ssid);
    status = WiFi.begin(kriot_ssid, kriot_pass);
  }
  Serial.print("[WIFI]: Kamu Berhasil Terhubung ke ");
  Serial.println(kriot_ssid);

  Serial.print("[WIFI]: SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("[WIFI]: IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("[WIFI]: Kekuatan Sinyal (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}