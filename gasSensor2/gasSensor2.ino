#define BLYNK_TEMPLATE_ID "your_template_id_here"
#define BLYNK_TEMPLATE_NAME "Gas level monitoring system"
#define BLYNK_AUTH_TOKEN "your_auth_token_here"

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define sensor 34
#define buzzer 2
#define ledMerah 26   // LED MERAH untuk WARNING
#define ledHijau 27   // LED HIJAU untuk NORMAL

LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

char ssid[] = "Sopia";
char pass[] = "190405rf";

WidgetLED widgetLed(V1);  // LED virtual di Blynk

// Variabel manual override dari Blynk
bool manualMerah = false;
bool manualHijau = false;

// Tombol Blynk untuk kontrol manual
BLYNK_WRITE(V2) {  // Tombol untuk LED Merah
  manualMerah = param.asInt();
}

BLYNK_WRITE(V3) {  // Tombol untuk LED Hijau
  manualHijau = param.asInt();
}

void GASLevel() {
  int sum = 0;
  const int samples = 64;  // averaging untuk stabil
  for(int i = 0; i < samples; i++) {
    sum += analogRead(sensor);
    delayMicroseconds(150);
  }
  int raw = sum / samples;
  int value = map(raw, 0, 4095, 0, 100);

  lcd.setCursor(0, 0);
  lcd.print("Gas Level:     ");
  lcd.setCursor(11, 0);
  lcd.print(value);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  
  bool warning = (value >= 50);
  
  if (warning) {
    digitalWrite(buzzer, HIGH);
    lcd.print("Status: WARNING ");
    widgetLed.on();
    
    digitalWrite(ledMerah, HIGH);   // Merah nyala
    digitalWrite(ledHijau, LOW);    // Hijau mati
  } else {
    digitalWrite(buzzer, LOW);
    lcd.print("Status: NORMAL  ");
    widgetLed.off();
    
    digitalWrite(ledMerah, LOW);    // Merah mati
    digitalWrite(ledHijau, HIGH);   // Hijau nyala
  }

  // Override manual dari app Blynk (prioritas lebih tinggi)
  if (manualMerah) digitalWrite(ledMerah, HIGH);
  if (manualHijau) digitalWrite(ledHijau, HIGH);

  Blynk.virtualWrite(V0, value);
  Serial.printf("Raw: %d → %d%% | Warning: %d\n", raw, value, warning);
}

void setup() {
  Serial.begin(115200);

  pinMode(buzzer, OUTPUT);
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  digitalWrite(ledMerah, LOW);
  digitalWrite(ledHijau, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Loading");
  delay(1500);
  lcd.clear();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(500L, GASLevel);
}

void loop() {
  Blynk.run();
  timer.run();
}