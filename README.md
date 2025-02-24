# 📌 **Pembaca UID Kartu RFID RC522 dengan LCD & Serial Monitor**

Proyek ini memungkinkan pengguna untuk membaca UID kartu RFID menggunakan **RFID RC522** dan menampilkan hasilnya pada **LCD 16x2 I2C** serta **Serial Monitor Arduino**.

---

## 🚀 **Fitur**
- **Menampilkan UID kartu RFID** di **Serial Monitor** dan **LCD 16x2 I2C**.
- **Kompatibel dengan Arduino Uno R3**.
- **Mudah dipasang dan digunakan**.

---

## 🛠 **Hardware yang Dibutuhkan**
| Komponen       | Jumlah |
|---------------|--------|
| Arduino Uno R3 | 1 |
| RFID RC522    | 1 |
| LCD 16x2 I2C  | 1 |
| Kabel Jumper  | Secukupnya |

---

## 🔌 **Wiring Diagram**
### **RFID RC522 ke Arduino**
| Pin RFID | Pin Arduino |
|----------|------------|
| SDA      | 10 |
| SCK      | 13 |
| MOSI     | 11 |
| MISO     | 12 |
| RST      | 9 |
| GND      | GND |
| 3.3V     | 3.3V |

### **LCD I2C ke Arduino**
| Pin LCD | Pin Arduino |
|---------|------------|
| SDA     | A4 |
| SCL     | A5 |
| VCC     | 5V |
| GND     | GND |

---

## 📥 **Instalasi Library yang Diperlukan**
1. Buka **Arduino IDE**.
2. Masuk ke **Sketch** → **Include Library** → **Manage Libraries...**.
3. **Cari dan install** library berikut:
   - **MFRC522** *(oleh GithubCommunity)* → Untuk RFID RC522.
   - **LiquidCrystal_I2C** *(oleh Frank de Brabander)* → Untuk LCD 16x2 I2C.
   - **Wire** *(bawaan Arduino IDE)* → Untuk komunikasi I2C.
   - **SPI** *(bawaan Arduino IDE)* → Untuk komunikasi SPI.
4. Pastikan semua library sudah terinstall sebelum mengunggah kode.

---

## 📝 **Kode Arduino**
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>

// Konfigurasi Pin
#define SDA_PIN 10
#define RST_PIN 9
LiquidCrystal_I2C lcd(0x26, 16, 2);
MFRC522 rfid(SDA_PIN, RST_PIN);

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Tempelkan Kartu");
}

void loop() {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UID:");

        Serial.print("UID Kartu: ");
        for (byte i = 0; i < rfid.uid.size; i++) {
            Serial.print(rfid.uid.uidByte[i], HEX);
            Serial.print(" ");
            lcd.print(rfid.uid.uidByte[i], HEX);
            lcd.print(" ");
        }
        Serial.println();
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tempelkan Kartu");
        rfid.PICC_HaltA();
    }
}
```

---

## 🎥 **Demo**
📷 **Screenshot hasil di Serial Monitor:**  
![Hasil di Serial Monitor](https://raw.githubusercontent.com/rickaux/pembaca-kartu-rfid-rc522/refs/heads/main/salah%20satu%20contoh%20uid%20di%20serial%20monitor.png)

🎬 **Video Demonstrasi:**  
[![Tonton Video](https://github.com/rickaux/pembaca-kartu-rfid-rc522/blob/main/demo%20pembaca%20uid%20rfid-rc522.mp4)

---

## 📤 **Cara Upload ke Arduino**
1. Hubungkan Arduino ke PC menggunakan kabel USB.
2. Buka **Arduino IDE**.
3. Salin dan tempel kode di atas ke dalam **Arduino IDE**.
4. Pilih **Board: Arduino Uno** → **Port yang sesuai**.
5. Klik **Upload** (ikon panah ke kanan).
6. Setelah berhasil diunggah, buka **Serial Monitor** (*Tools → Serial Monitor*).
7. Tempelkan kartu RFID ke sensor untuk melihat UID.

---

## 📌 **Kesimpulan**
Proyek ini memungkinkan pengguna untuk membaca UID kartu RFID dan menampilkannya pada LCD serta Serial Monitor. Fitur ini berguna untuk sistem akses kontrol berbasis RFID.

📢 **Silakan laporkan masalah atau kontribusi di GitHub repository ini!** 🚀

