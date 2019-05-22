 #include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
int led=9;

void setup(){
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  pinMode(led, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop(){
  int chk;
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:
                Serial.print("OK,\t");
                break;
    case DHTLIB_ERROR_CHECKSUM:
                Serial.print("Checksum error,\t");
                break;
    case DHTLIB_ERROR_TIMEOUT:
                Serial.print("Time out error,\t");
                break;
    default:
                Serial.print("Unknown error,\t");
                break;
  }
 // DISPLAT DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);

  if(DHT.humidity < 35){
 digitalWrite(led, HIGH);  
 }
  if (DHT.humidity > 50){
  digitalWrite(led, LOW);   
  }

  if(DHT.temperature >= 30){
 digitalWrite(LED_BUILTIN, HIGH);  
 }
  else{
  digitalWrite(LED_BUILTIN, LOW);   
  }
  

  delay(2000);
}
