#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

const char* ssid = "ASUS";
const char* password = "1135432906";

WebServer server(80);

const char webpage[] PROGMEM = R"====(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>ESP32 Universal OTA Lite</title>
<style>
body{
font-family:Arial;
background:#f0f0f0;
text-align:center;
margin-top:40px;
}
div{
background:white;
display:inline-block;
padding:20px;
border-radius:10px;
box-shadow:0 0 10px #999;
}
input{
margin:10px;
}
button{
padding:10px 25px;
font-size:18px;
}
</style>
</head>
<body>

<div>

<h2>ESP32 Universal OTA Lite</h2>

<form method='POST'
action='/update'
enctype='multipart/form-data'>

<input type='file' name='update'><br>

<button>Upload BIN</button>

</form>

</div>

</body>
</html>
)====";void handleRoot() {
  server.send(200, "text/html", webpage);
}

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("mDNS started");
  }

  server.on("/", HTTP_GET, handleRoot);

  server.on("/update", HTTP_POST, []() {

    server.send(
      200,
      "text/plain",
      Update.hasError() ? "Update Failed!" : "Update Success! Rebooting..."
    );

    delay(1000);
    ESP.restart();

  }, []() {

    HTTPUpload &upload = server.upload();

    if (upload.status == UPLOAD_FILE_START) {

      Update.begin(UPDATE_SIZE_UNKNOWN);

    } else if (upload.status == UPLOAD_FILE_WRITE) {

      Update.write(upload.buf, upload.currentSize);

    } else if (upload.status == UPLOAD_FILE_END) {

      Update.end(true);

    }

  });

  server.begin();

  Serial.println("OTA Server Ready");
}void loop() {
  server.handleClient();

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint > 30000) {
    lastPrint = millis();

    Serial.println();
    Serial.println("==========");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Free Heap: ");
    Serial.println(ESP.getFreeHeap());
    Serial.println("OTA Ready");
    Serial.println("Open:");
    Serial.println("http://esp32.local");
    Serial.println("==========");
  }
}#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

const char* ssid = "ASUS";
const char* password = "1135432906";

WebServer server(80);

const char webpage[] PROGMEM = R"====(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>ESP32 Universal OTA Lite</title>
<style>
body{
font-family:Arial;
background:#f0f0f0;
text-align:center;
margin-top:40px;
}
div{
background:white;
display:inline-block;
padding:20px;
border-radius:10px;
box-shadow:0 0 10px #999;
}
input{
margin:10px;
}
button{
padding:10px 25px;
font-size:18px;
}
</style>
</head>
<body>

<div>

<h2>ESP32 Universal OTA Lite</h2>

<form method='POST'
action='/update'
enctype='multipart/form-data'>

<input type='file' name='update'><br>

<button>Upload BIN</button>

</form>

</div>

</body>
</html>
)====";void handleRoot() {
  server.send(200, "text/html", webpage);
}

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("mDNS started");
  }

  server.on("/", HTTP_GET, handleRoot);

  server.on("/update", HTTP_POST, []() {

    server.send(
      200,
      "text/plain",
      Update.hasError() ? "Update Failed!" : "Update Success! Rebooting..."
    );

    delay(1000);
    ESP.restart();

  }, []() {

    HTTPUpload &upload = server.upload();

    if (upload.status == UPLOAD_FILE_START) {

      Update.begin(UPDATE_SIZE_UNKNOWN);

    } else if (upload.status == UPLOAD_FILE_WRITE) {

      Update.write(upload.buf, upload.currentSize);

    } else if (upload.status == UPLOAD_FILE_END) {

      Update.end(true);

    }

  });

  server.begin();

  Serial.println("OTA Server Ready");
}void loop() {
  server.handleClient();

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint > 30000) {
    lastPrint = millis();

    Serial.println();
    Serial.println("==========");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Free Heap: ");
    Serial.println(ESP.getFreeHeap());
    Serial.println("OTA Ready");
    Serial.println("Open:");
    Serial.println("http://esp32.local");
    Serial.println("==========");
  }
}
