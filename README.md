# 🏠 Smart Home Security Monitoring System

Proyek ini adalah sistem keamanan rumah sederhana berbasis mikrokontroler Arduino yang memanfaatkan sensor PIR (Passive Infrared) dan sensor ultrasonik HC-SR04 untuk mendeteksi keberadaan manusia serta mengukur jarak objek di sekitar area pemantauan. Sistem dilengkapi dengan LCD I2C sebagai media tampilan informasi secara real-time dan buzzer sebagai alarm peringatan ketika terdeteksi gerakan sekaligus objek berada dalam jarak yang dianggap mencurigakan. Sistem ini cocok digunakan sebagai prototipe keamanan rumah pintar (Smart Home Security System) yang mampu memberikan informasi kondisi lingkungan secara langsung.

## 📋 Fitur Utama

* **Deteksi Gerakan (Motion Detection)** menggunakan sensor PIR.
* **Pengukuran Jarak Objek** menggunakan sensor ultrasonik HC-SR04.
* **Tampilan Real-Time** pada LCD I2C 16x2.
* **Alarm Otomatis** menggunakan buzzer saat kondisi mencurigakan terdeteksi.
* **Monitoring Serial** melalui Serial Monitor Arduino IDE.
* **Indikator Status Sistem** berupa kondisi Aman, Gerakan Terdeteksi, dan Alarm.

---

## 🛠️ Komponen yang Dibutuhkan

| Komponen                  | Jumlah     |
| ------------------------- | ---------- |
| Arduino Uno R3 / Nano     | 1x         |
| Sensor PIR HC-SR501       | 1x         |
| Sensor Ultrasonik HC-SR04 | 1x         |
| LCD I2C 16x2              | 1x         |
| Buzzer Aktif 5V           | 1x         |
| Breadboard                | 1x         |
| Kabel Jumper              | Secukupnya |

---

## 🔌 Skema Wiring (Sambungan Kabel)

Berikut adalah koneksi pin yang digunakan berdasarkan source code:

| Nama Komponen  | Pin Komponen | Pin Arduino | Keterangan                   |
| -------------- | ------------ | ----------- | ---------------------------- |
| Sensor PIR     | VCC          | 5V          | Daya Sensor                  |
|                | GND          | GND         | Ground                       |
|                | OUT          | D2          | Input Deteksi Gerakan        |
| Sensor HC-SR04 | VCC          | 5V          | Daya Sensor                  |
|                | GND          | GND         | Ground                       |
|                | TRIG         | D9          | Trigger Ultrasonik           |
|                | ECHO         | D10         | Pembacaan Pantulan Gelombang |
| LCD I2C 16x2   | VCC          | 5V          | Daya LCD                     |
|                | GND          | GND         | Ground                       |
|                | SDA          | A4          | Jalur Data I2C               |
|                | SCL          | A5          | Jalur Clock I2C              |
| Buzzer Aktif   | Positif (+)  | D8          | Kontrol Alarm                |
|                | Negatif (-)  | GND         | Ground                       |

### Important

* Pastikan alamat I2C LCD sesuai dengan kode program yaitu **0x27**.
* Sensor PIR membutuhkan waktu kalibrasi beberapa detik saat pertama kali dinyalakan.
* Sensor HC-SR04 bekerja optimal pada jarak sekitar 2 cm hingga 400 cm.
* Gunakan sumber daya 5V yang stabil agar pembacaan sensor tetap akurat.

---

## ⚙️ Logika Kerja Program

Program bekerja dengan memanfaatkan kombinasi sensor PIR dan sensor ultrasonik untuk menentukan kondisi keamanan.

### Kondisi 1: ALARM

Jika:

* PIR mendeteksi gerakan (`PIR = HIGH`)
* DAN jarak objek ≤ 50 cm

Maka:

* LCD menampilkan:

```
PIR:1 ALARM!
```

* Buzzer berbunyi pada frekuensi 1000 Hz.
* Sistem menganggap terdapat objek yang bergerak sangat dekat dengan area pemantauan.

---

### Kondisi 2: GERAKAN TERDETEKSI

Jika:

* PIR mendeteksi gerakan (`PIR = HIGH`)
* Tetapi jarak objek > 50 cm

Maka:

* LCD menampilkan:

```
PIR:1 GERAK
```

* Buzzer tidak berbunyi.
* Sistem hanya memberikan informasi bahwa ada aktivitas gerakan.

---

### Kondisi 3: AMAN

Jika:

* PIR tidak mendeteksi gerakan (`PIR = LOW`)

Maka:

* LCD menampilkan:

```
PIR:0 AMAN
```

* Buzzer mati.
* Sistem berada dalam kondisi normal.

---

## 🔄 Alur Kerja Sistem

1. Arduino melakukan inisialisasi LCD, sensor PIR, sensor HC-SR04, dan buzzer.
2. LCD menampilkan pesan:

```
SMART HOME
READY
```

3. Sensor PIR membaca keberadaan gerakan manusia.
4. Sensor HC-SR04 mengukur jarak objek di depan sensor.
5. Arduino menghitung jarak berdasarkan waktu pantulan gelombang ultrasonik.
6. Sistem membandingkan status gerakan dan nilai jarak.
7. Jika gerakan terdeteksi dan jarak ≤ 50 cm maka alarm aktif.
8. Jika hanya ada gerakan maka status GERAK ditampilkan.
9. Jika tidak ada gerakan maka status AMAN ditampilkan.
10. Data status dan jarak dikirim ke Serial Monitor setiap 200 ms.
11. Proses berulang terus menerus selama sistem menyala.

---

## 💻 Panduan Pemrograman & Upload

### 1. Kebutuhan Library

Pastikan library berikut telah terinstal:

* Wire.h
* LiquidCrystal_I2C.h

Library LiquidCrystal_I2C dapat diinstal melalui:

```
Arduino IDE
→ Library Manager
→ Cari "LiquidCrystal I2C"
→ Install
```

---

### 2. Langkah Upload Program

1. Hubungkan Arduino ke komputer menggunakan kabel USB.
2. Buka Arduino IDE.
3. Salin source code ke editor Arduino IDE.
4. Pilih Board:

```
Tools → Board → Arduino Uno
```

5. Pilih Port yang sesuai:


Tools → Port


6. Klik tombol Upload.
7. Buka Serial Monitor dengan baudrate:

9600


📊 Contoh Output Serial Monitor

Saat kondisi aman:

text
PIR=0 | Jarak=181 cm
PIR=0 | Jarak=180 cm
PIR=0 | Jarak=182 cm


Saat terdeteksi gerakan:

text
PIR=1 | Jarak=120 cm
PIR=1 | Jarak=118 cm


Saat kondisi alarm:

text
PIR=1 | Jarak=45 cm
PIR=1 | Jarak=42 cm
PIR=1 | Jarak=39 cm




 🎯 Kesimpulan

Sistem Smart Home Security Monitoring ini mampu mendeteksi keberadaan gerakan manusia menggunakan sensor PIR dan mengukur kedekatan objek menggunakan sensor ultrasonik HC-SR04. Dengan kombinasi kedua sensor tersebut, sistem dapat membedakan kondisi aman, gerakan biasa, dan kondisi alarm sehingga dapat digunakan sebagai dasar pengembangan sistem keamanan rumah pintar yang lebih kompleks berbasis IoT maupun notifikasi jarak jauh.
