// Biasanya LED bawaan ESP32 terhubung ke GPIO 2
#define INTERNAL_LED 2

void setup() {
  // Mengatur pin LED sebagai Output
  pinMode(INTERNAL_LED, OUTPUT);
  
  // Bonus: Tes Serial Monitor (biar bisa 'ngobrol' sama laptop)
  Serial.begin(115200);
  Serial.println("Tes ESP32 dimulai!");
}

void loop() {
  digitalWrite(INTERNAL_LED, HIGH);  // Nyalakan lampu
  Serial.println("Lampu Nyala");     // Kirim pesan ke laptop
  delay(1000);                       // Tunggu 1000ms (1 detik)
  
  digitalWrite(INTERNAL_LED, LOW);   // Matikan lampu
  Serial.println("Lampu Mati");      // Kirim pesan ke laptop
  delay(1000);                       // Tunggu 1 detik
}