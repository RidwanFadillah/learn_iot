#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "WiFi.h"

// Set alamat I2C LCD (Biasanya 0x27, kalau gagal coba ganti 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight(); // Nyalakan lampu latar
  
  // Tampilan Awal
  lcd.setCursor(0,0);
  lcd.print("ESP32 Starting..");
  lcd.setCursor(0,1);
  lcd.print("Siap Scan WiFi!");
  delay(2000);

  // Setup WiFi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}

void loop() {
  Serial.println("Sedang scan...");
  
  // Info di LCD kalau lagi scanning
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scanning WiFi...");
  
  int n = WiFi.scanNetworks();
  
  lcd.clear();
  if (n == 0) {
    lcd.setCursor(0,0);
    lcd.print("No Networks");
    lcd.setCursor(0,1);
    lcd.print("Found :(");
  } else {
    // Tampilkan jumlah WiFi yang ditemukan
    lcd.setCursor(0,0);
    lcd.print("Ketemu: ");
    lcd.print(n);
    lcd.print(" WiFi");
    
    // Tampilkan nama WiFi terkuat di baris kedua
    lcd.setCursor(0,1);
    lcd.print(WiFi.SSID(0)); 
  }
  
  // Tunggu 5 detik sebelum scan lagi
  delay(5000);
}