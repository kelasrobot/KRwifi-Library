#include "WiFiEsp.h"
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3);
#endif
int status = WL_IDLE_STATUS;
WiFiEspClient client;
String getHttpStatus;
String getData;
bool statusKirim;
char* SSID;
char* PASS;

void printWifiStatus()
{
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

void statusPengiriman()
{
  if (statusKirim)
  {
    if (!client.connected())
    {
      Serial.println();
      Serial.println("Memutuskan hubungan dengan server...");
      delay(10);
      client.stop();
      statusKirim = false;
    }
  }
}

void httpGet(char *kriot_server, String kriot_path, int kriot_port)
{
  client.stop();
  if (client.connect(kriot_server, kriot_port))
  {
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
  else
  {
    getHttpStatus = "Koneksi Gagal";
  }
}

void httpGet2(char *kriot_server, String kriot_path, int kriot_port)
{
  client.stop();
  if (client.connect(kriot_server, kriot_port))
  {
    client.print("GET ");
    client.print(kriot_path);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(kriot_server);
    client.println("Connection: close");
    client.println();
    char endOfHeaders[] = "\r\n\r\n";
    client.find(endOfHeaders);
    client.find(endOfHeaders);
    getData = client.readString();
    getData.trim();
    getData.trim();
    getHttpStatus = "Koneksi Berhasil";
  }
  else
  {
    getHttpStatus = "Koneksi Gagal";
  }
}

void httpsGet(char *kriot_server, String kriot_path, int kriot_port)
{
  client.stop();
  if (client.connectSSL(kriot_server, kriot_port))
  {
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
  else
  {
    getHttpStatus = "Koneksi Gagal";
  }
}

void httpPOST(char* SERVER, char* APIKEY, String KONTEN, int JUMLAHKONTENT, int PORT) {
  //Jika WiFi Tidak Terhubung
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Menghubungkan ke jaringan SSID: ");
    Serial.println(SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(SSID, PASS);
      Serial.print(".");
      delay(500);
    }
    printWifiStatus();
    Serial.println("Berhasil terhubung ke jaringan");
  }

  //Jika WiFi Terhubung
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("Menghubungkan dengan server...");
    if (client.connect(SERVER, PORT)) {
      Serial.println();
      Serial.println("Terhubung dengan server.");

      char content2[JUMLAHKONTENT];
      KONTEN.toCharArray(content2, JUMLAHKONTENT);

      client.println("POST /update HTTP/1.1");
      client.print("Host: ");
      client.println(SERVER);
      client.println("User-Agent: tslib-arduino/1.5.0");
      client.print("X-THINGSPEAKAPIKEY: ");
      client.println(APIKEY);
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(strlen(content2));
      client.println("Connection: close");
      client.println();

      client.print(KONTEN);

      char endOfHeaders[] = "\r\n\r\n";
      client.find(endOfHeaders);
      getData = client.readString();
      getData.trim();

      //      statusKirim = true;
    }
  }

}

void setWifi(char *kriot_ssid, char *kriot_pass)
{
  SSID = kriot_ssid;
  PASS = kriot_pass;
  Serial1.begin(115200);
  Serial1.println("AT+UART_DEF=9600,8,1,0,0");
  delay(500);
  Serial1.begin(9600);
  WiFi.init(&Serial1);
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("[WIFI]: KelasRobot WiFi Shield Tidak Terdeteksi");
    while (true)
      ;
  }
  while (status != WL_CONNECTED)
  {
    Serial.print("[WIFI]: Mencoba Terhubung ke SSID: ");
    Serial.println(kriot_ssid);
    status = WiFi.begin(kriot_ssid, kriot_pass);
  }
  Serial.print("[WIFI]: Kamu Berhasil Terhubung ke ");
  Serial.println(kriot_ssid);

  printWifiStatus();
}
