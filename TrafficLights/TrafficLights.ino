
//These are the boolean variables for the inputs of the circuit
bool bA = false;
bool bB = false;
bool bC = false;
bool bD = false;

//These are the pin addresses for the switch inputs
int iA = 7;
int iB = 2;
int iC = 3;
int iD = 4;

//These are the pin addresses for the LEDS
int iEWGreen = 5;
int iEWRed = 6;
int iNSGreen = 10;
int iNSRed = 11;

// iCount is the variable which checks how many times the led has been off in a row
int iCount = 0;

//The final output boolean, If bNS is false then EW is true.
bool bNS = true;

//Set up the Light Dependent Resistor
//This is the LDR pin address
int iSensor = A1;
//This is the value the sensor is reading.
int iSensorRead = 0;

//The initial setup phase, only ran once at the start of the program
void setup() {
  //This is for debugging the LDR
  Serial.begin(9600);
  
  // Set up the LED pins
  pinMode(iEWGreen, OUTPUT);
  pinMode(iEWRed, OUTPUT);
  pinMode(iNSGreen, OUTPUT);
  pinMode(iNSRed, OUTPUT);

  // Set up the input pins
    pinMode(iA, INPUT);
    pinMode(iB, INPUT);
    pinMode(iC, INPUT);
    pinMode(iD, INPUT);

}

//This is the loop, it will keep looping forever.
void loop() {
  
  // read the value from the sensor
  iSensorRead = analogRead(iSensor); 

  //This is for debugging the LDR
  //This prints the LDR resistance value, ie the light level
  Serial.println(iSensorRead);
    
  // Loop of all the stuff
  // All booleans are set to false at the start of each loop
  bA = false;
  bB = false;
  bC = false;
  bD = false;

  // Take in the current inputs and set them to booleans
  // If any switches are pressed, their matching boolean is set to true
  if(digitalRead(iA) == 1){
    bA = true;  
  }
  if(digitalRead(iB) == 1){
    bB = true;  
  }
  if(digitalRead(iC) == 1){
    bC = true;  
  }
  if(digitalRead(iD) == 1){
    bD = true;  
  }

  // This is for debugging the switches
  //Serial.println(digitalRead(iA));
  //Serial.println(digitalRead(iB));
  //Serial.println(digitalRead(iC));
  //Serial.println(digitalRead(iD));
  //Serial.println("");
  
  // Choose outputs based on the booleans
  //This tests each case where EW is true
  if((bB == true and bD == true) or 
  (bA == false and bB == true) or 
  (bC == false and bD == true) or 
  (bA == false and bB == false and bC == false and bD == false) or
  (bA == true and bB == true and bC == false and bD == false) or
  (bA == false and bB == false and bC == true and bD == true) 
  ){
    // If EW is true then bNS is set to false
    bNS = false;
  }
  else{
    //If EW is false then bNS is set to true
    bNS = true;
  }
  
  //All LEDs are set to off 
  digitalWrite(iEWGreen, LOW);
  digitalWrite(iNSGreen, LOW);
  digitalWrite(iEWRed, LOW);
  digitalWrite(iNSRed, LOW);  

  //This checks if it is daytime
  //If daytime
  if(iSensorRead > 400){
    //If bNS is true, output the NS outputs (NS Green on, and EW Red on)
    if(bNS == true){ 
      digitalWrite(iNSGreen, HIGH);
      digitalWrite(iEWRed, HIGH);
    } else{
    //If bNS is false, output the EW outputs (EW Green on, and NS Red on)  
      digitalWrite(iEWGreen, HIGH);
      digitalWrite(iNSRed, HIGH);
   }
  }
  //If it is not daytime than it is night time
  else{
    // iCount checks how many times the output leds have been off
    // if there have been 3 instances of the leds not being on, then the leds are turned on
    // and the counter is reset.
    // Doing this puts the leds on 25% of the time.
    if(iCount > 3){
      //If bNS is true, output the NS outputs (NS Green on, and EW Red on)  
      if(bNS == true){ 
        digitalWrite(iNSGreen, HIGH);
        digitalWrite(iEWRed, HIGH);
      } else{
        //If bNS is false, output the EW outputs (EW Green on, and NS Red on)
        digitalWrite(iEWGreen, HIGH);
        digitalWrite(iNSRed, HIGH);
      }
      //If leds have been put on, the counter is reset
      iCount = 0;
   }
   else{
    //If the leds have not been put on, add one to the counter
    iCount++;
   }
  }
}
