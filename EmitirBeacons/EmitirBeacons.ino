//----------------------------------------------------
// Código para emitir beacons desde SparkFun Pro nRF52840 Mini
//----------------------------------------------------

#include <bluefruit.h>


// ----------------------------------------------------
//                    SETUP()
// ----------------------------------------------------
void setup(){

  Serial.begin(115200);
  while(!Serial) delay(10);

  Serial.println("-----------------------\n");
  Serial.println(" PRUEBAS iBeacon  ");
  Serial.println("-----------------------\n");

  //Se inicializa el módulo Bluefruit:
  Serial.println("Inicializando el módulo nRF52 Bluefruit");

  Bluefruit.begin();

  //Cambio de nombre del dispositivo:
  Serial.println("Cambiando el nombre del dispositivo a GTI-Elena");

  Bluefruit.setName("GTI-Elena");
  Bluefruit.ScanResponse.addName();

  Bluefruit.Advertising.start();

  Serial.println("\nAdvertising");

} //setup()

void loop(){

}



