#include <DHT.h>
#include <DHT_U.h>
#include <BlynkSimpleStream.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//local server
//char auth[]="37gWQC8oqFaM4yePF07QCpcfj22bTGuX";

//blynk-server
char auth[]="tpyU8q-BtPxPSpjNR6V2GFC3tIo6O3SC";

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
/*  if (isnan(h) || isnan(t)) {
    Blynk.virtualWrite(V1, "Failed to read from DHT sensor!");
    return;
  }
*/
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
  //digitalWrite(8, HIGH);
  //digitalWrite(9, HIGH);
  //digitalWrite(10, HIGH);
}
