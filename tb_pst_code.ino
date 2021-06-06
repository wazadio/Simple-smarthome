#include <DHT.h>
#include <DHT_U.h>
#include <BlynkSimpleStream.h>
#include <Arduino_FreeRTOS.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//local server
//char auth[]="37gWQC8oqFaM4yePF07QCpcfj22bTGuX";

//blynk-server
char auth[]="tpyU8q-BtPxPSpjNR6V2GFC3tIo6O3SC";

void lampuhandler( void *pvParameters );
void suhukelembapan( void *pvParameters );
void pirdetect ( void *pvParameters );
void blynkinit ( void *pvParameters );

/*
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
/*  if (isnan(h) || isnan(t)) {
    Blynk.virtualWrite(V1, "Failed to read from DHT sensor!");
    return;
  }

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
*/

void setup() {
  xTaskCreate(
    blynkinit
    ,  (const portCHAR *)"PIR"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  4  // priority
    ,  NULL );

  xTaskCreate(
    pirdetect
    ,  (const portCHAR *)"PIR"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  1  // priority
    ,  NULL );

  xTaskCreate(
    lampuhandler
    ,  (const portCHAR *)"Lampu"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  NULL );

  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"DHT11"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  3  // priority
    ,  NULL );

  //Serial.begin(9600);
  Blynk.begin(auth, Serial);
  dht.begin();
  //timer.setInterval(1000L, sendSensor);
}

void loop() {
  
  //timer.run();
  //digitalWrite(8, HIGH);
  //digitalWrite(9, HIGH);
  //digitalWrite(10, HIGH);
}

void pirdetect ( void *pvParameters ){
  (void) pvParameters;
  pinMode(5, OUTPUT);
  if(digitalRead(13)){
      for(int i=1; i<=120; i++){
        digitalWrite(5, HIGH);
        vTaskDelay( 500 / portTICK_PERIOD_MS );
      }
    }
  }

void suhukelembapan( void *pvParameters );{
  (void) pvParameters;
  for(;;){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    Blynk.virtualWrite(V5, h);
    Blynk.virtualWrite(V6, t);
    vTaskDelay(1);
  }
 }

void lampuhandler( void *pvParameters ){
    (void) pvParameters;
    for(;;){
      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      pinMode(10, OUTPUT);
    }
  }

void blynkinit ( void *pvParameters ){
    (void) pvParameters;
    for(;;){
        Blynk.run();
      }
  }
