#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TCS34725.h>
#include <LiquidCrystal_I2C.h>

// Inicializar o sensor de cor TCS34725
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1);

// Inicializar o LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // O endereço I2C pode variar (use um scanner I2C para encontrar o endereço correto)

void setup() {
  Serial.begin(9600);
  
  // Inicializar o sensor de cor
  if (!tcs.begin()) {
    Serial.println("Não foi possível encontrar o sensor. Verifique as conexões!");
    while (1);
  }

  // Inicializar o LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cor: ");
}

void loop() {
  // Ler os valores de cor
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Enviar valores para o Serial Monitor
  Serial.print("Vermelho: "); Serial.print(r); 
  Serial.print(" Verde: "); Serial.print(g); 
  Serial.print(" Azul: "); Serial.print(b); 
  Serial.println();

  // Atualizar o LCD com a cor identificada
  atualizarLCD(r, g, b);

  delay(500); // Ajuste o atraso conforme necessário
}

void atualizarLCD(uint16_t r, uint16_t g, uint16_t b) {
  // Limpar a linha do LCD
  lcd.setCursor(6, 1);
  lcd.print("    "); 

  // Determinar a cor dominante
  if (r > g && r > b) {
    lcd.setCursor(6, 1);
    lcd.print("Vermelho");
  } else if (g > r && g > b) {
    lcd.setCursor(6, 1);
    lcd.print("Verde");
  } else {
    lcd.setCursor(6, 1);
    lcd.print("Azul");
  }
}
