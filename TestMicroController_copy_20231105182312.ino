#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 1000000UL);

const char* ssid = "Wifi"; // put your own wifi SSID / Name here
const char* password = "Broodje"; // Put your wifi password here 
const char* server = "irc.chat.twitch.tv";
const int port = 6667;
const char* oauth = "awda212rw3fg132t123123"; // put your Twitch Oauth token here
const char* channel = "#GAMINGHOUND"; // example put your channel name in here

WiFiClient client;

String messages[3];
int messageCount = 0;
bool connectedToTwitch = false;
unsigned long previousDisplayTime = 0;

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Onionconsumee");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();

  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  display.clearDisplay();
  display.display();

  if (!client.connect(server, port)) {
    Serial.println("The connection to Twitch IRC, failed.");
    display.println("The connection to Twitch IRC, failed.");
    display.display();
    return;
  }

  Serial.println("Connected to Twitch IRC server");
  display.println("Connected to Twitch IRC server");
  display.display();
  connectedToTwitch = true;

  client.println("PASS " + String(oauth));
  client.println("NICK justinfan1234");
  client.println("JOIN " + String(channel));

  Wire.begin(12, 14);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    display.println(F("SSD1306 allocation failed"));
    display.display();
    for (;;)
      ;
  }

  display.clearDisplay();
  display.display();
  Serial.println("OLED display initialized.");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost");
    display.println("WiFi connection lost");
    display.display();
    delay(5000);
    clearDisplay();
    return;
  }

  if (!client.connected()) {
    Serial.println("Connection to Twitch IRC server lost");
    display.println("Connection to Twitch IRC server lost");
    display.display();
    connectedToTwitch = false;
    delay(5000);
    clearDisplay();
    return;
  }

  if (connectedToTwitch) {
    while (client.available()) {
      String message = client.readStringUntil('\n');

      if (message.startsWith("PING")) {
        client.println("PONG :tmi.twitch.tv");
      } else if (!isUnwantedMessage(message)) {
        String username = parseUsername(message);
        if (username != "justinfan1234") {
          String privilege = checkPrivilege(username);
          if (privilege.equals("mod")) {
            addMessage("Mod " + username + ": " + parseChatMessage(message));
          } else {
            addMessage("Viewer " + username + ": " + parseChatMessage(message));
          }
        }
      }
    }

    displayMessages();
  }

  delay(1000);
}

bool isUnwantedMessage(String message) {
  if (message.startsWith(":") && !message.startsWith(":justinfan") && !message.endsWith("/NAMES list")) {
    return false;
  }
  return true;
}

String parseUsername(String message) {
  int exclamationIndex = message.indexOf("!");
  if (exclamationIndex != -1) {
    return message.substring(1, exclamationIndex);
  }
  return "UnknownUser";
}

//put your own twitch name where GamingHound is, this says owner/mod if not viewer on the display.
String checkPrivilege(String username) {
  if (username.equals("GAMINGHOUDn")) {
    return "mod";
  } else {
    return "viewer";
  }
}

String parseChatMessage(String message) {
  int firstColonIndex = message.indexOf(":", 1);
  if (firstColonIndex != -1) {
    return message.substring(firstColonIndex + 1);
  }
  return "No message found";
}

void addMessage(String text) {
  if (messageCount < 3) {
    messages[messageCount] = text;
    messageCount++;
  } else {
    for (int i = 0; i < 2; i++) {
      messages[i] = messages[i + 1];
    }
    messages[2] = text;
  }
}

void displayMessages() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  for (int i = 0; i < 3; i++) {
    if (messages[i] != "") {
      display.println(messages[i]);
    }
  }

  display.display();
}

void clearDisplay() {
  display.clearDisplay();
  display.display();
}
