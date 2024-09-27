// Definicion de los pines UART
#define PinVGas 5
#define PinVRef 28
#define PinVTemp 29

#include <bluefruit.h>

void setup() {

  Serial.begin(115200);
  while(!Serial) delay(10);

  //Se inicializa el módulo Bluefruit:
  Serial.println("Inicializando el módulo nRF52 Bluefruit");

  Bluefruit.begin();

}

void loop() {

  //Leemos datos analógicos del sensor:
  float analogGas = analogRead(PinVGas);
  float analogRef = analogRead(PinVRef);
  float analogTemp = analogRead(PinVTemp);

  //Pasamos los datos analógicos a voltios:
  //Nuestro ADC es de 10 bits

  //((analogGas - analogRef) / 2^10) * 3.3

  float voltios = ((analogGas - analogRef) / 1024) * 3.3;

  //Obtenemos las ppm a partir de los datos analógicos:
  float medicionEnPpm = (voltios * pow(10,6)) / ((-35.35) * 499);

  Serial.println(analogGas);
  Serial.println(analogRef);
  Serial.println(analogTemp);
  Serial.println(voltios);
  Serial.println(medicionEnPpm);
  Serial.println("--------------------------");

  delay(10000);
}
