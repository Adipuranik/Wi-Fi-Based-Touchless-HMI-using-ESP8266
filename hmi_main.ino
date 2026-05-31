/*
 * Wi-Fi Based Touchless HMI using ESP8266 NodeMCU
 * Author: Aditi S Puranik
 * Description: Smartphone-controlled wireless HMI with onboard web server,
 *              LCD menu navigation, and buzzer feedback over Wi-Fi.
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ─── Wi-Fi Credentials ───────────────────────────────────────────────────────
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ─── Hardware Pin Definitions ─────────────────────────────────────────────────
#define BUZZER_PIN  D5   // GPIO14

// ─── LCD: I2C address 0x27, 16 cols, 2 rows ──────────────────────────────────
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ─── Web Server on port 80 ───────────────────────────────────────────────────
ESP8266WebServer server(80);

// ─── Menu State ──────────────────────────────────────────────────────────────
const String menuItems[] = {"1. LED Control", "2. Sensor Data", "3. Settings", "4. About"};
const int MENU_SIZE = 4;
int currentMenu = 0;

// ─── Function Prototypes ─────────────────────────────────────────────────────
void handleRoot();
void handleUp();
void handleDown();
void handleSelect();
void beep(int duration_ms);
void updateLCD();
String buildWebPage();

// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(100);

  // GPIO init
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Touchless HMI");
  lcd.setCursor(0, 1);
  lcd.print("  Connecting...");

  // Wi-Fi connect
  Serial.println("\nConnecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Show IP on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());
  lcd.setCursor(0, 1);
  lcd.print("Open in browser");
  beep(200);
  delay(2000);

  // Register web server routes
  server.on("/",        handleRoot);
  server.on("/up",      handleUp);
  server.on("/down",    handleDown);
  server.on("/select",  handleSelect);
  server.begin();
  Serial.println("Web server started.");

  // Show initial menu
  updateLCD();
}

// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  server.handleClient();   // Non-blocking: handle incoming HTTP requests
}

// ─── Web Server Handlers ──────────────────────────────────────────────────────

void handleRoot() {
  server.send(200, "text/html", buildWebPage());
}

void handleUp() {
  currentMenu = (currentMenu - 1 + MENU_SIZE) % MENU_SIZE;
  beep(50);
  updateLCD();
  server.send(200, "text/html", buildWebPage());
}

void handleDown() {
  currentMenu = (currentMenu + 1) % MENU_SIZE;
  beep(50);
  updateLCD();
  server.send(200, "text/html", buildWebPage());
}

void handleSelect() {
  beep(300);
  lcd.setCursor(0, 1);
  lcd.print("  >> Selected   ");
  delay(800);
  updateLCD();
  server.send(200, "text/html", buildWebPage());
}

// ─── LCD Update ───────────────────────────────────────────────────────────────

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("> " + menuItems[currentMenu]);
  // Show next item as preview
  int nextItem = (currentMenu + 1) % MENU_SIZE;
  lcd.setCursor(0, 1);
  lcd.print("  " + menuItems[nextItem]);
}

// ─── Buzzer ───────────────────────────────────────────────────────────────────

void beep(int duration_ms) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration_ms);
  digitalWrite(BUZZER_PIN, LOW);
}

// ─── Web Page Builder ─────────────────────────────────────────────────────────

String buildWebPage() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Touchless HMI</title>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#1a1a2e;color:#eee;padding:20px;}";
  html += "h2{color:#e94560;}";
  html += ".menu-box{background:#16213e;border:2px solid #0f3460;border-radius:12px;padding:20px;margin:20px auto;max-width:300px;}";
  html += ".menu-item{padding:8px;font-size:16px;}";
  html += ".active{color:#e94560;font-weight:bold;font-size:18px;}";
  html += "a{display:inline-block;margin:10px;padding:14px 28px;background:#e94560;color:white;";
  html += "border-radius:8px;text-decoration:none;font-size:18px;font-weight:bold;}";
  html += "a:hover{background:#c73652;}";
  html += "</style></head><body>";
  html += "<h2>&#128225; Touchless HMI</h2>";
  html += "<div class='menu-box'>";
  for (int i = 0; i < MENU_SIZE; i++) {
    if (i == currentMenu) {
      html += "<div class='menu-item active'>&#9654; " + menuItems[i] + "</div>";
    } else {
      html += "<div class='menu-item'>&nbsp;&nbsp; " + menuItems[i] + "</div>";
    }
  }
  html += "</div>";
  html += "<a href='/up'>&#9650; Up</a>";
  html += "<a href='/select'>&#9654; Select</a>";
  html += "<a href='/down'>&#9660; Down</a>";
  html += "<p style='color:#888;font-size:12px;'>Connected via Wi-Fi &bull; No app needed</p>";
  html += "</body></html>";
  return html;
}
