#include <DHT.h>
#include <DHT_U.h>
#include <BlynkSimpleStream.h>


#define DHTPIN1 10
#define DHTPIN2 11

#define DHTTYPE DHT11

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
BlynkTimer timer;
WidgetLED led(V0);

//local server
//char auth[]="37gWQC8oqFaM4yePF07QCpcfj22bTGuX";

//blynk-server
char auth[]="tpyU8q-BtPxPSpjNR6V2GFC3tIo6O3SC";

void sendSensor()
{
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  //float h2 = dht2.readHumidity();
  //float t2 = dht2.readTemperature();
  
/*  if (isnan(h) || isnan(t)) {
    Blynk.virtualWrite(V1, "Failed to read from DHT sensor!");
    return;
  }
*/
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t1);
  //Blynk.virtualWrite(V6, t2);
  Blynk.virtualWrite(V7, h1);
  //Blynk.virtualWrite(V8, h2);
}

void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, INPUT);
  //pinMode(8, INPUT);
  //Serial.begin(9600);
  Blynk.begin(auth, Serial);
  dht1.begin();
  //dht2.begin();
  timer.setInterval(1000L, sendSensor);
}


void loop() {
  Blynk.run();
  if(digitalRead(9)){
    led.on();
  }
  else led.off();
  timer.run();
}
