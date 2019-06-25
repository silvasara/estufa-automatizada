 #include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
#define pino_sinal_analogico A0
#define ventilador 5
#define pino_led_amarelo 6
#define pino_led_verde 7
#define ledF 9
#define led2 10
int valor_analogico;
int i = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  pinMode(ledF, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pino_sinal_analogico, INPUT);
  pinMode(ventilador, OUTPUT);
  pinMode(pino_led_amarelo, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);

}

void loop(){
  int chk;
  
  controleT();
  
   valor_analogico = analogRead(pino_sinal_analogico);
 
  //Mostra o valor da porta analogica no serial monitor
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);
  Serial.print("\n");

  
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

//  if(DHT.humidity < 35){
// digitalWrite(ledF, HIGH);  
// }
//  if (DHT.humidity > 50){
//  digitalWrite(ledF, LOW);   
//  }

  if(DHT.temperature >= 20){
 digitalWrite(ventilador, HIGH);  
 }
  if (DHT.temperature <= 10){
  digitalWrite(led2, LOW);
   digitalWrite(ventilador, LOW);  
   
  }
  
 //Solo umido, acende o led verde
  if (valor_analogico < 500)
  {
    Serial.println(" Status: Solo umido");
    apagaleds();
    digitalWrite(pino_led_verde, HIGH);
  }
 
  //Solo com umidade moderada, acende led amarelo
  if (valor_analogico >= 500 && valor_analogico < 800)
  {
    Serial.println(" Status: Umidade moderada");
    apagaleds();
    digitalWrite(pino_led_amarelo, HIGH);
  }
 
  //Solo seco, acende led vermelho
//  if ( valor_analogico > 800)
//  {
//    Serial.println(" Status: Solo seco");
//    apagaleds();
//    digitalWrite(led, HIGH);
//  }

  Serial.println(i);
  delay(1000);
}

void controleT(){
  i++;
  if(i >= 50){
    digitalWrite(ledF, HIGH);
  }
  if(i > 100){
    i = 1;
    digitalWrite(ledF, LOW);
  }
}

void apagaleds()
{
//  digitalWrite(ventilador, LOW);
  digitalWrite(pino_led_amarelo, LOW);
  digitalWrite(pino_led_verde, LOW);
}
