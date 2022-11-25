#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <IRremote.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

// Numéro du pin sortie du récepteur 
long int res_val;
const int receiver = 9; 

// Déclaration d'un objet IRrecv
IRrecv irrecv(receiver);           
decode_results results; 

void setup() {
  Serial.begin(9600);
  dht.begin();
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  delay(1000);
  read_dht11();
  read_remote();
}
void read_dht11(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("temp: ");
  Serial.println(t);
  Serial.print("hum: ");
  Serial.println(h);
  Serial.println("");
}
 void read_remote(){
  if (irrecv.decode())
  {
    // Récupération du code   
    //res_val = irrecv.decodedIRData.decodedRawData;
    IrReceiver.printIRResultShort(&Serial);
    // Transfert à l'interface série 
    //Serial.println(res_val, HEX);
    
    // Réception de la nouvelle valeur
    irrecv.resume();

    // Temporisateur de la boucle 
  }
 }

