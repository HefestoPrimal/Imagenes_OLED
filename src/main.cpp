#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "imagenes.h"

#define PIN_SCL 10
#define PIN_SDA 11

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64
#define OLED_RESET -1
#define ADDRESS_SCREEN 0x3c

struct Imagen {
  char ID[4];
  int Alto;
  int Ancho;
  const unsigned char* BitMap;
};

const Imagen IMAGENES[] = {
  {"AXL", Ajolote_Height, Ajolote_Width, Ajolote},
  {"PNK", SpiderPunk_Height, SpiderPunk_Width, SpiderPunk},
  {"RBL", Rebelion_Height, Rebelion_Width, Rebelion},
  {"TRZ", Trazo_Height, Trazo_Width, Trazo},
};

const size_t NUM_IMAGENES = sizeof(IMAGENES)/sizeof(IMAGENES[0]);

#define LED 48

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, OLED_RESET);

const Imagen* BuscarImagenID(const char id[4]) {
  if(!id)
    return nullptr;
  for (size_t i = 0; i < NUM_IMAGENES; ++i) {
    if(strncmp(IMAGENES[i].ID, id, 3) == 0) {
      return &IMAGENES[i];
    }
  }
  return nullptr;
}

void MostrarImagenID(const char id[4], int tiempoSeg) {
  const Imagen* img = BuscarImagenID(id);
  if (!img) {
    Serial.println("Imagen no encontrada");
    digitalWrite(LED, HIGH);
    delay(3000);
    digitalWrite(LED, LOW);
    return;
  }
  display.clearDisplay();
  display.display();
  display.drawBitmap((display.width() - img->Ancho) / 2, (display.height() - img->Alto) / 2, img->BitMap, img->Ancho, img->Alto, SSD1306_WHITE);
  display.display();
  delay(tiempoSeg * 1000);
  display.clearDisplay();
  display.display();
}

void setup() {
  Serial.begin(9600);
  Wire.begin(PIN_SDA, PIN_SCL);
  delay(100);

  pinMode(LED, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, ADDRESS_SCREEN)) {
    Serial.println("Error inicializando la pantalla OLED");
    digitalWrite(LED, HIGH);
    //while(1);
  }

  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Sistema Iniciado");
  display.display();
  delay(200);

  Serial.println("Sistema Iniciado");
  delay(5000);
  display.clearDisplay();
  display.display();
}

int scanI2C() {
  byte error, address;
  int nDevices = 0;
  Serial.println("Escaneando puerto I2C...\n");

  for (address = 1; address < 127; address++) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0) {
          String mensaje = "I2C encontrado en la direccion 0x";
          if (address < 16)
              mensaje += "0";
          mensaje += String(address, HEX);
          mensaje += " !";
          Serial.println(mensaje);
          nDevices++;
      } else if (error == 4) {
          String mensaje = "Error desconocido en la direccion 0x";
          if (address < 16)
              mensaje += "0";
          mensaje += String(address, HEX);
          Serial.println(mensaje);
      }
      delay(5);
  }

  if (nDevices == 0) {
      Serial.println("Ningun dispositivo I2C encontrado");
  } else {
      Serial.println("\nEscaneo completado!");
  }
  return nDevices;
}

void ProcesarComando(String cmd) {
  if (cmd != "") {
    for (int i = 0; i < 2; i++) {
      digitalWrite(LED, HIGH);
      delay(250);
      digitalWrite(LED, LOW);
      delay(250);
    }

    if (cmd.startsWith("SCAN")) {
      Serial.println("Se encontraron " + String(scanI2C()) + " dispositivos I2C");

    } else if (cmd.startsWith("IMG")) {
      //* Ejemplo IMG>AXL10
      String IDImg = cmd.substring(4, 7);
      int tiempo = cmd.substring(7, 9).toInt();
      MostrarImagenID(IDImg.c_str(), tiempo);

    } else {
      Serial.println("Comando Desconocido");
    }
  }
}

void loop() {
  String comando = Serial.readStringUntil('\n');
  ProcesarComando(comando);
  delay(100);
}
