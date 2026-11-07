const int buzzerPin = 5; // Pin D5

void setup() {
  // Setup saluran PWM untuk buzzer (Khusus ESP32)
  ledcAttach(buzzerPin, 2000, 8); // pin, freq, resolution
}

void loop() {
  // Bunyi Nada 1 (2000 Hz)
  ledcWriteTone(buzzerPin, 2000); 
  delay(500);

  // Bunyi Nada 2 (3000 Hz)
  ledcWriteTone(buzzerPin, 3000);
  delay(500);
  
  // Matikan
  ledcWriteTone(buzzerPin, 0);
  delay(1000);
}