#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SDA_PIN 10  // Pin SS untuk RFID
#define RST_PIN 9   // Pin RST untuk RFID

LiquidCrystal_I2C lcd(0x26, 16, 2); // Sesuaikan alamat I2C jika perlu
MFRC522 rfid(SDA_PIN, RST_PIN);

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    lcd.init();
    lcd.backlight();

    // **Animasi Loading**
    lcd.setCursor(4, 0);
    lcd.print("Loading");
    for (int i = 0; i < 3; i++) {
        lcd.print(".");
        delay(500);
    }
    delay(500);
    lcd.clear();
    lcd.print("Tempelkan Kartu");
}

void loop() {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        Serial.print("UID Kartu: ");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UID: ");

        String uidString = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
            uidString += String(rfid.uid.uidByte[i], HEX);
            Serial.print(rfid.uid.uidByte[i], HEX);
            Serial.print(" ");
        }

        Serial.println();
        lcd.setCursor(0, 1);
        lcd.print(uidString);

        delay(2000);
        lcd.clear();
        lcd.print("Tempelkan Kartu");

        rfid.PICC_HaltA();  // Hentikan komunikasi dengan kartu
    }
}
