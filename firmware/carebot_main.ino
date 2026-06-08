// Name: Avni Trivedi
// Roll Number: 2510110134

#define BLYNK_TEMPLATE_ID "your_id"
#define BLYNK_TEMPLATE_NAME "project_name"
#define BLYNK_AUTH_TOKEN "project_token"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <TFT_eSPI.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

// ---------------- WIFI ----------------
char ssid[] = "device_name";
char pass[] = "device_password";

// ---------------- DHT ----------------
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ---------------- TFT ----------------
TFT_eSPI tft = TFT_eSPI();

// ---------------- TIMER ----------------
BlynkTimer timer;

// ---------------- RTC FROM BLYNK ----------------
WidgetRTC rtc;

// ---------------- BUZZER ----------------
#define BUZZER 23

// ---------------- ALARM ----------------
int alarmHour = 0;
int alarmMinute = 0;

// ---------------- ALARM CONTROL ----------------
bool buzzerOn = false;
bool triggered = false;
unsigned long buzzerStart = 0;

// ─────────────────────────────────────────
// DRAW HEART
// ─────────────────────────────────────────
void drawHeart(int cx, int cy, int r, uint16_t color) {

  tft.fillCircle(cx - r/2, cy - r/2, r, color);

  tft.fillCircle(cx + r/2, cy - r/2, r, color);

  tft.fillTriangle(
    cx - r - r/2, cy - r/2,
    cx + r + r/2, cy - r/2,
    cx, cy + r + r/2,
    color
  );
}

// ─────────────────────────────────────────
// HOME PAGE
// ─────────────────────────────────────────
void home_page() {

  tft.setRotation(1);

  tft.fillScreen(tft.color565(244,194,194));

  // Title
  tft.setTextSize(3);
  tft.setTextColor(TFT_RED);

  tft.setCursor(20,20);
  tft.print("Welcome,", user);

  // Labels
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);

  tft.setCursor(20,70);
  tft.print("Temperature:");

  tft.setCursor(20,105);
  tft.print("Humidity:");

  tft.setCursor(20,140);
  tft.print("WiFi:");

  tft.setCursor(20,175);
  tft.print("Blynk:");

  tft.setCursor(20,210);
  tft.print("Alarm:");

  // Heart
  drawHeart(302, 222, 8, tft.color565(200, 50, 50));
}

// ─────────────────────────────────────────
// UPDATE TFT
// ─────────────────────────────────────────
void updateDisplay(float temp, float hum) {

  // Clear previous values area
  tft.fillRect(170, 65, 140, 160, tft.color565(244,194,194));

  // Temperature
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(2);

  tft.setCursor(170,70);
  tft.print(temp);
  tft.print(" C");

  // Humidity
  tft.setCursor(170,105);
  tft.print(hum);
  tft.print(" %");

  // WiFi Status
  tft.setCursor(170,140);

  if (WiFi.status() == WL_CONNECTED) {

    tft.setTextColor(TFT_GREEN);
    tft.print("ON");

  } else {

    tft.setTextColor(TFT_RED);
    tft.print("OFF");
  }

  // Blynk Status
  tft.setCursor(170,175);

  if (Blynk.connected()) {

    tft.setTextColor(TFT_GREEN);
    tft.print("CONNECTED");

  } else {

    tft.setTextColor(TFT_RED);
    tft.print("OFFLINE");
  }

  // Alarm Time
  tft.setCursor(170,210);

  tft.setTextColor(TFT_MAGENTA);

  char alarmStr[6];

  sprintf(alarmStr, "%02d:%02d", alarmHour, alarmMinute);

  tft.print(alarmStr);
}

// ─────────────────────────────────────────
// BLYNK SLIDERS
// ─────────────────────────────────────────
BLYNK_WRITE(V3) {

  alarmHour = param.asInt();

  Serial.print("Alarm Hour: ");
  Serial.println(alarmHour);
}

BLYNK_WRITE(V5) {

  alarmMinute = param.asInt();

  Serial.print("Alarm Minute: ");
  Serial.println(alarmMinute);
}

// ─────────────────────────────────────────
// SEND SENSOR DATA
// ─────────────────────────────────────────
void sendSensorData() {

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {

    Serial.println("DHT ERROR");

    tft.setTextColor(TFT_RED);

    tft.setCursor(20,235);

    tft.print("DHT SENSOR ERROR");

    return;
  }

  // Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // Send to Blynk
  if (Blynk.connected()) {

    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, hum);
  }

  // Update TFT
  updateDisplay(temp, hum);

  // ───── GET CURRENT TIME FROM BLYNK ─────
  int currentHour = hour();
  int currentMinute = minute();

  Serial.print("Current Time: ");
  Serial.print(currentHour);
  Serial.print(":");
  Serial.println(currentMinute);

  // ───── ALARM CHECK ─────
  if (currentHour == alarmHour &&
      currentMinute == alarmMinute &&
      !triggered) {

    Serial.println("MEDICINE ALERT!");

    tone(BUZZER, 262);

    buzzerOn = true;

    buzzerStart = millis();

    triggered = true;
  }

  // ───── STOP BUZZER AFTER 5 SEC ─────
  if (buzzerOn &&
      millis() - buzzerStart >= 5000) {

    noTone(BUZZER);

    buzzerOn = false;

    Serial.println("Alarm Ended");
  }

  // ───── RESET TRIGGER ─────
  if (currentHour != alarmHour ||
      currentMinute != alarmMinute) {

    triggered = false;
  }
}

// ─────────────────────────────────────────
// SETUP
// ─────────────────────────────────────────
void setup() {

  Serial.begin(115200);

  // TFT
  tft.init();

  // DHT
  dht.begin();

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  // Home page
  home_page();

  // WiFi
  Serial.print("Connecting WiFi");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  // Blynk
  Blynk.config(BLYNK_AUTH_TOKEN);

  Serial.println("Connecting Blynk...");

  Blynk.connect();

  // Sync Blynk time
  rtc.begin();

  // Timer
  timer.setInterval(2000L, sendSensorData);
}

// ─────────────────────────────────────────
// LOOP
// ─────────────────────────────────────────
void loop() {

  if (!Blynk.connected()) {

    Blynk.connect();
  }

  Blynk.run();

  timer.run();
}
