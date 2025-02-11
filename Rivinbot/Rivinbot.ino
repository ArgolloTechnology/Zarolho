//***********************************************************************************************
//  This example shows how to use the basic methods of the FluxGarage Robo Eyes library. 
//
//  Hardware: You'll need a breadboard, an arduino nano r3, an I2C oled display with 1306   
//  or 1309 chip and some jumper wires.
//  
//  Published in September 2024 by Dennis Hoelscher, FluxGarage
//  www.youtube.com/@FluxGarage
//  www.fluxgarage.com
//
//***********************************************************************************************

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <FluxGarage_RoboEyes.h>
roboEyes roboEyes; // create RoboEyes instance

const uint8_t lightSensorPin = A3;  // Pino analógico para o sensor de luz
const uint8_t buzzerPin = 8;

// Sons
const uint16_t startupSound[][2] = {
  {1000, 200}, {1200, 200}, {1500, 300}
}; // {frequência, duração}
const uint16_t wakeupSound[][2] = {
  {800, 150}, {1000, 200}, {1200, 300}
};
const uint16_t annoyedSound[][2] = {
  {2000, 100}, {1800, 100}, {2000, 100}, {1800, 100}, {2000, 100}
}; 

// Controle de som
bool playingSound = false;
uint32_t soundStartTime = 0;
uint8_t currentToneIndex = 0;

const uint16_t *currentSound = nullptr;
uint8_t soundLength = 0;

// Definindo os valores iniciais dos olhos
uint8_t leftEye = 25;
uint8_t rightEye = 40;
bool bright = false, sleeping = false;

// Variáveis para controlar o tempo de atraso
uint32_t eventTimer = 0;
uint32_t previousMillis = 0;

uint8_t mood = DEFAULT;

void setup() {
  Serial.begin(9600);

  // Startup OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C or 0x3D
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Startup robo eyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);

  // Define some automated eyes behaviour
  roboEyes.setAutoblinker(ON, 3, 2);
  roboEyes.setIdleMode(ON, 2, 2);

  // Define eye shapes, all values in pixels
  roboEyes.setWidth(40, 40);
  roboEyes.setHeight(25, 40);
  roboEyes.setBorderradius(5, 25);
  roboEyes.setSpacebetween(15);

  // Define mood, curiosity and position
  roboEyes.setMood(mood);
  roboEyes.setCuriosity(ON);

  roboEyes.close();
  playSound(startupSound, sizeof(startupSound) / sizeof(startupSound[0]));
}

void loop() {
  lightInteraction();
  roboEyes.update(); // update eyes drawings
  updateSound();
}

void lightInteraction() {
  // Lê o valor da luminosidade do sensor
  uint16_t lightLevel = analogRead(lightSensorPin);

  // Normaliza o valor da luz (0 a 1023) para um intervalo mais fácil de trabalhar (0 a 100)
  uint8_t lightPercentage = map(lightLevel, 0, 1023, 0, 100);

  // Alteração dos valores dos olhos dependendo da luminosidade
  if (millis() >= eventTimer + 500 && lightPercentage < 5) {
    roboEyes.setCuriosity(OFF);
    if (leftEye <= 1 || rightEye <= 1) {
      roboEyes.setIdleMode(false);
      roboEyes.close();
      roboEyes.setMood(mood);
      roboEyes.setPosition(DEFAULT);
      sleeping = true;
    } else {
      eventTimer = millis(); // Reinicia o timer
      roboEyes.setAutoblinker(ON, 6, 2);
      roboEyes.setIdleMode(ON, 4, 2);
      roboEyes.setMood(TIRED);
      leftEye = max(leftEye - (leftEye * 0.2), 0);
      rightEye = max(rightEye - (rightEye * 0.2), 0);
      roboEyes.setHeight(leftEye, rightEye);
    }
  } else if (lightPercentage > 65 && !bright) {
    bright = true;
    playSound(annoyedSound, sizeof(annoyedSound) / sizeof(annoyedSound[0]));
    leftEye = max((leftEye * 0.2), 0);
    rightEye = max((rightEye * 0.2), 0);
    roboEyes.setHeight(leftEye, rightEye);
  } else if (lightPercentage < 65 && lightPercentage > 10) {
    roboEyes.setCuriosity(ON);
    if (sleeping) {
      sleeping = false;
      roboEyes.anim_confused();
      playSound(wakeupSound, sizeof(wakeupSound) / sizeof(wakeupSound[0]));
    }
    roboEyes.setMood(mood);
    roboEyes.setAutoblinker(ON, 3, 2);
    roboEyes.setIdleMode(ON, 2, 2);
    bright = false;
    leftEye = 25;
    rightEye = 40;
    leftEye = max(leftEye, 0);
    rightEye = max(rightEye, 0);
    roboEyes.setHeight(leftEye, rightEye);
  }

  // Mostra os valores dos olhos e a luminosidade no monitor serial
  Serial.print("Luminosidade: ");
  Serial.print(lightPercentage);
  Serial.print("% | Left Eye: ");
  Serial.print(leftEye);
  Serial.print(" | Right Eye: ");
  Serial.println(rightEye);
}

void playSound(const uint16_t sound[][2], uint8_t length) {
  currentSound = &sound[0][0];
  soundLength = length;
  currentToneIndex = 0;
  playingSound = true;
  soundStartTime = millis();
  tone(buzzerPin, currentSound[currentToneIndex * 2], currentSound[currentToneIndex * 2 + 1]);
}

void updateSound() {
  if (playingSound && (millis() - soundStartTime >= currentSound[currentToneIndex * 2 + 1])) {
    currentToneIndex++;
    if (currentToneIndex >= soundLength) {
      noTone(buzzerPin);
      playingSound = false;
    } else {
      soundStartTime = millis();
      tone(buzzerPin, currentSound[currentToneIndex * 2], currentSound[currentToneIndex * 2 + 1]);
    }
  }
}
