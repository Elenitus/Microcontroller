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

  startAdvertising();

  Serial.println("\nAdvertising");

} //setup()


// ----------------------------------------------------
//            Función startAdvertising()
// ----------------------------------------------------
void startAdvertising(){
  
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

  BLEBeacon elBeacon (beaconUUID, 12, 34, 73 );
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

   delay(1000);

   Serial.print( " ** loop cont=" );
   Serial.println( cont );
} // ()
