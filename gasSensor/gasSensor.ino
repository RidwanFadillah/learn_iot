#define BLYNK_TEMPLATE_ID "your_template_id_here"
#define BLYNK_TEMPLATE_NAME "Gas level monitoring system"
#define BLYNK_AUTH_TOKEN "your_auth_token_here"

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define sensor 34
#define buzzer 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

char ssid[] = "aqua";
char pass[] = "Ciandong";

// Variabel untuk status Mute
bool isMuted = false;

unsigned long lastNotifyTime = 0;  
const unsigned long notifyInterval = 5000; 

// --- FUNGSI TOMBOL MUTE (V2) ---
BLYNK_WRITE(V2) {
  int pinValue = param.asInt(); 
  if (pinValue == 1) {
    isMuted = true;
    digitalWrite(buzzer, LOW); // Langsung diamkan buzzer
    Serial.println("Alarm Muted by User");
  } else {
    isMuted = false;
    Serial.println("Alarm Unmuted by User");
  }
}

bool alarmActive = false; // Penanda apakah alarm sedang aktif

void GASLevel() {
  int sum = 0;
  const int samples = 64; 
  for(int i = 0; i < samples; i++) {
    sum += analogRead(sensor);
    delayMicroseconds(150);
  }
  int raw = sum / samples;
  int value = map(raw, 0, 4095, 0, 100);

  // LCD & Gauge V0
  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(value);
  lcd.print("%  ");
  Blynk.virtualWrite(V0, value);

  // --- LOGIKA UTAMA ---
  if (value < 50) {
    // === 1. KONDISI AMAN (HIJAU) ===
    
    // [LOGIKA ANTI SPAM] Reset alarm supaya siap notif lagi kalau nanti bocor baru
    alarmActive = false; 

    digitalWrite(buzzer, LOW);
    if (isMuted) {
       isMuted = false;
       Blynk.virtualWrite(V2, 0);
    }
    Blynk.setProperty(V0, "color", "#23C48E"); 
    Blynk.virtualWrite(V1, "AMAN");
    Blynk.setProperty(V1, "color", "#23C48E");
    lcd.setCursor(0, 1);
    lcd.print("Status: NORMAL  ");

  } else {
    // === KONDISI BAHAYA (>= 50%) ===

    // [LOGIKA ANTI SPAM] 
    // Notifikasi hanya dikirim jika:
    // 1. Alarm belum aktif (Kejadian baru)
    // 2. ATAU sudah lewat 1 menit (Reminder kalau bocornya awet banget)
    
    if (!alarmActive || (millis() - lastNotifyTime > 60000)) { // Set 60000 (1 menit) buat reminder
      Blynk.logEvent("gas_warning", String("PERINGATAN! Gas Level: ") + value + "%"); 
      lastNotifyTime = millis();
      alarmActive = true; // Kunci alarm biar gak spam pas turun
    }

    // --- Logic Warna & Suara Tetap Jalan Terus (Realtime) ---
    if (value >= 50 && value < 75) {
      // ZONA WASPADA
      if (!isMuted) {
        static bool beepState = false;
        beepState = !beepState;
        digitalWrite(buzzer, beepState ? HIGH : LOW);
      } else { digitalWrite(buzzer, LOW); }
      
      Blynk.setProperty(V0, "color", "#EDB305");
      Blynk.virtualWrite(V1, "WASPADA ⚠️");
      Blynk.setProperty(V1, "color", "#EDB305");
      lcd.setCursor(0, 1);
      lcd.print("Status: WASPADA ");

    } else {
      // ZONA BAHAYA
      if (!isMuted) {
        digitalWrite(buzzer, HIGH);
      } else { digitalWrite(buzzer, LOW); }

      Blynk.setProperty(V0, "color", "#D3435C");
      Blynk.virtualWrite(V1, "BAHAYA ☠️");
      Blynk.setProperty(V1, "color", "#D3435C");
      lcd.setCursor(0, 1);
      lcd.print("Status: BAHAYA! ");
    }
  }
  Serial.println(value);
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Loading");
  delay(1500);
  lcd.clear();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Sinkronisasi status tombol V2
  Blynk.syncVirtual(V2); 
  
  timer.setInterval(500L, GASLevel);
}

void loop() {
  Blynk.run();
  timer.run();
}