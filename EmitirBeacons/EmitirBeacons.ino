//----------------------------------------------------
// Código para medir datos y enviarlos mediante beacons
//----------------------------------------------------

#define PinVGas 5
#define PinVRef 28
#define PinVTemp 29

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

  startAdvertising(0,0);

  Serial.println("\nAdvertising");

} //setup()


// ----------------------------------------------------
//            Función startAdvertising()
// ----------------------------------------------------
void startAdvertising(float medicionGas, float medicionTemperatura){
  
  Serial.println("startAdvertising()");

  Serial.println("Bluefruit.Advertising.stop()");
  Bluefruit.Advertising.stop();

  //Paquete de advertising:
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  //Incluir nombre:
  Serial.println("Bluefruit.Advertising.addName()");
  Bluefruit.Advertising.addName();

  Serial.println("Bluefruit.Advertising.setBeacon( elBeacon )");
  
  uint8_t beaconUUID[16] = {
    'E', 'P', 'S', 'G', '-', 'G', 'T', 'I',
    '-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
  };

  BLEBeacon elBeacon (beaconUUID, medicionGas, medicionTemperatura, 73 );
  elBeacon.setManufacturer(0x004c); //id de Apple
  Bluefruit.Advertising.setBeacon(elBeacon);

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); //en unidades de 0.625ms
  Bluefruit.Advertising.setFastTimeout(30); //número de segundos en modo rápido
  Bluefruit.Advertising.start(0); // 0 = no pares el advertising después de n segundos.

  Serial.println("Bluefruit.Advertising.start(0)");

}//startAdvertising()



// ----------------------------------------------------
//                        LOOP()
// ----------------------------------------------------

namespace Loop {
   int cont = 0;
};

void loop() {

   using namespace Loop;

   cont++;

   Serial.print( " ** loop cont=" );
   Serial.println( cont );

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

  startAdvertising(medicionEnPpm *10, analogTemp);

  delay(10000);
} // loop()



