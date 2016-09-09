SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
    pinMode(D6,OUTPUT); //set the led pin as output
    pinMode(WKP,INPUT);  //set the wakeup pin as input
    blink(2);
    
    Particle.connect();
    Particle.publish("Button","1",60,PRIVATE); //send the command to ifttt
    
    delay(500);                       //wait ½ second
    System.sleep(SLEEP_MODE_DEEP);    // put the system into deep sleep
}

void loop() {
      //do nothing
}

void blink(int num)
{
   for(int i=0;i<num;i++)             //repeat for i number of times
   {
       digitalWrite(D6,HIGH);         //turn on led
       delay(500);                    //wait ½ second
       digitalWrite(D6,LOW);          //turn off the led
       delay(500);                    //wait ½ second
   }
}
