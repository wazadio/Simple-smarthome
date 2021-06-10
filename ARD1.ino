#include <Arduino_FreeRTOS.h>

void ReadPIR( void *pvParameters );
//void Blink( void *pvParameters );

void setup() {
  // put your setup code here, to run once:
  xTaskCreate(ReadPIR,"Task1",128,NULL,1,NULL);
  //xTaskCreate(Blink,"Task2 ",128,NULL,2,NULL);   
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void ReadPIR( void *pvParameters ){
  pinMode(9, INPUT);
  pinMode(2, OUTPUT);
  pinMode(10, OUTPUT);
  while(1){
    if(digitalRead(9)){
      digitalWrite(2, HIGH);
      digitalWrite(10, HIGH);
    }
    else{
      digitalWrite(2, LOW);
      digitalWrite(10, LOW);
    }
  }  
}

/*
void Blink(void *pvParameters) 
{
  pinMode(8, OUTPUT);
  while(1)
  {
    digitalWrite(8, HIGH);   
    vTaskDelay( 200 / portTICK_PERIOD_MS ); 
    digitalWrite(8, LOW);    
    vTaskDelay( 200 / portTICK_PERIOD_MS ); 
  }
}
*/
