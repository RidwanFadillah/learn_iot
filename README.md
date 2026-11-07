# Belajar IoT dengan Arduino dan ESP32

Repositori ini berisi beberapa contoh sederhana untuk belajar dasar Internet of Things (IoT) menggunakan Arduino IDE dan ESP32. Contoh-contohnya dibuat untuk latihan, mulai dari menyalakan LED sampai membaca sensor dan menghubungkan ESP32 ke Wi-Fi.

## Isi repositori

| Folder | Yang dipelajari |
| --- | --- |
| `firstBlink` | Menyalakan dan mematikan LED, serta melihat pesan di Serial Monitor |
| `buzzertest` | Mencoba buzzer |
| `wifiscaning` | Mencari jaringan Wi-Fi di sekitar |
| `wificonnect` | Menghubungkan ESP32 ke Wi-Fi |
| `gasSensor` | Membaca sensor gas dan menampilkan hasilnya di LCD serta Blynk |
| `gasSensor2` | Latihan sensor gas dengan LED dan buzzer |

## Peralatan dan aplikasi

- Board ESP32
- Arduino IDE
- Kabel USB untuk menghubungkan ESP32 ke komputer
- Komponen sesuai contoh yang ingin dicoba, misalnya LED, buzzer, sensor gas, atau LCD I2C
- Koneksi Wi-Fi untuk contoh yang menggunakannya

Beberapa contoh menggunakan library `LiquidCrystal_I2C` dan Blynk. Library yang tersedia di folder `libraries` bisa dipasang melalui Arduino IDE jika belum tersedia.

## Cara mulai

1. Buka folder contoh yang ingin dicoba.
2. Buka file `.ino` di dalam folder tersebut menggunakan Arduino IDE.
3. Pilih board ESP32 dan port yang sesuai.
4. Pasang komponen mengikuti pin yang tertulis di dalam program.
5. Untuk contoh Wi-Fi atau Blynk, isi nama jaringan, kata sandi, dan pengaturan Blynk milik sendiri.
6. Unggah program ke ESP32, lalu buka Serial Monitor bila contoh menggunakannya.

Urutan belajar yang disarankan: `firstBlink`, `buzzertest`, `wifiscaning`, `wificonnect`, lalu contoh `gasSensor`.

## Catatan

- Contoh-contoh ini dibuat untuk belajar dan bereksperimen, bukan untuk digunakan sebagai sistem keselamatan.
- Hasil pembacaan sensor gas pada proyek latihan ini tidak menggantikan alat deteksi gas yang bersertifikat.
- Jangan membagikan kata sandi Wi-Fi atau token Blynk. Gunakan kredensial milik sendiri dan jaga kerahasiaannya.
