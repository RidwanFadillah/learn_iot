#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* ssid     = "your_wifi_name_here";      // Nama WiFi (Case Sensitive!)
const char* password = "your_wifi_password_here";  // Password WiFi
// ------------------------------

// Setting LCD (Alamat 0x27, sesuaikan kalau beda)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Tampilan awal saat mencoba konek
  lcd.setCursor(0, 0);
  lcd.print("Connecting to:");
  lcd.setCursor(0, 1);
  lcd.print(ssid); // Nampilin nama WiFi yang mau dituju

  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);

  // Perintah sakti buat konek WiFi
  WiFi.begin(ssid, password);

  // Loop 'menunggu' (polling) sampai statusnya CONNECTED
  // Selama belum konek, dia bakal muter di sini terus
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // Titik-titik di Serial Monitor biar tau lagi proses
  }

  // --- SUKSES KONEK ---
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print IP di Serial Monitor juga

  // Tampilkan Status & IP Address di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!");
  
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP()); // <--- INI DIA! Alamat IP ESP32 kamu
}

void loop() {
  // Gak perlu ngapa-ngapain di loop, biarin IP-nya nampang terus
}