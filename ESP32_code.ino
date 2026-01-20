#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL2AIRyy5Mq"
#define BLYNK_TEMPLATE_NAME "Solar Energy Monitor"
#define BLYNK_AUTH_TOKEN "TPte0eP2u52a_bvLnoyxurwL3bfgIXX8"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Free WIFI";
char pass[] = "@dean2646EE";

const int systemLed = 14;     // GPIO pin for turning on the solar generator
const int statusLed = 12;     // GPIO pin for simulating Mains charging status
const int solarPower = 34;    // Analog pin for solar power input
const int batteryLevel = 35;  // Analog pin for battery voltage level

int battery;
int systemStatus;
double solar;

BlynkTimer timer;

void setup() {
  pinMode(systemLed, OUTPUT);
  pinMode(statusLed, OUTPUT);

  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendFeedBackToBlynk);
  delay(1000);

  disableCore0WDT();
} // end setup

void loop() {
  Blynk.run();
  timer.run();
  battery = analogRead(batteryLevel) * 100 / 4096;
  solar = analogRead(solarPower) * 1000 / 4096;
} // end main loop

BLYNK_WRITE(V0) {
  systemStatus = param.asInt();
  digitalWrite(systemLed, systemStatus);
  digitalWrite(statusLed, systemStatus);
}// end BLYNK_WRITEz

void sendFeedBackToBlynk() {
  Blynk.virtualWrite(V1, solar);
  Blynk.virtualWrite(V2, battery);
  Blynk.virtualWrite(V4, systemStatus);
}// end sendFeedbackToBlynk
