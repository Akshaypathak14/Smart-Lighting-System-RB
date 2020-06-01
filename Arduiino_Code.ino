 int calibrationTime = 30;        
//the time when the sensor outputs a low impulse 
long unsigned lowIn;         
//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped 
long unsigned  pause = 5000;  
boolean lockLow = true; 
boolean takeLowTime;  
int pir1Pin = 4; //the digital pin connected to the PIR1 sensor's output 
int pir2Pin = 5;//the digital pin connected to the PIR2 sensor's output 
int RelayPin = 12; //the digital pin connected to the Relay input 
void setup(){ 
	Serial.begin(9600); 
	pinMode(pir1Pin, INPUT); 
	pinMode(pir2Pin, INPUT); 
	pinMode(RelayPin, OUTPUT); 
	digitalWrite(pir1Pin, LOW); 
	digitalWrite(pir2Pin, LOW); 
	//give the sensor some time to calibrate 
	Serial.print("calibrating sensor "); 
	for(int i = 0; i < calibrationTime; i++){ 
		Serial.print("."); 
		delay(1000); 
	} 
	Serial.println(" done"); 
	Serial.println("SENSOR ACTIVE"); 
	delay(50); 
} 
//////////////////////////// 
//LOOP 
void loop(){ 
	if(digitalRead(pir1Pin) == HIGH){ 
		digitalWrite(RelayPin, LOW);   //the tube light visualizes the sensors output pin state 
		if(lockLow){  
			//makes sure we wait for a transition to LOW before any further output is made: 
			lockLow = false;            
			Serial.println("---"); 
			Serial.print("motion detected at "); 
			Serial.print(millis()/1000); 
			Serial.println(" sec"); 
			delay(50); 
		}         
		takeLowTime = true; 
	} 
	if(digitalRead(pir1Pin) == LOW){       
		digitalWrite(RelayPin, HIGH);  //the tube light  visualizes the sensors output pin state 
		if(takeLowTime){ 
			lowIn = millis();          //save the time of the transition from high to LOW 
			takeLowTime = false;       //make sure this is only done at the start of a LOW phase 
		} 
		//if the sensor is low for more than the given pause, 
		//we assume that no more motion is going to happen 
		if(!lockLow && millis() - lowIn > pause){  
			//makes sure this block of code is only executed again after 
			//a new motion sequence has been detected 
			lockLow = true;                        
			Serial.print("motion ended at ");      //output 
			Serial.print((millis() - pause)/1000); 
			Serial.println(" sec"); 
			delay(50); 
		} 
	} 
	if(digitalRead(pir2Pin) == HIGH){ 
		digitalWrite(RelayPin, LOW);   //the led visualizes the sensors output pin state 
		if(lockLow){  
			//makes sure we wait for a transition to LOW before any further output is made: 
			lockLow = false;            
			Serial.println("---"); 
			Serial.print("motion detected at "); 
			Serial.print(millis()/1000); 
			Serial.println(" sec"); 
			delay(50); 
		}         
		takeLowTime = true; 
	} 
	
	if(digitalRead(pir2Pin) == LOW){       
		digitalWrite(RelayPin, HIGH);  //the led visualizes the sensors output pin state 
		
		if(takeLowTime){ 
			lowIn = millis();          //save the time of the transition from high to LOW 
			takeLowTime = false;       //make sure this is only done at the start of a LOW phase 
		} 
		//if the sensor is low for more than the given pause, 
		//we assume that no more motion is going to happen 
		if(!lockLow && millis() - lowIn > pause){  
			//makes sure this block of code is only executed again after 
			//a new motion sequence has been detected 
			lockLow = true;                        
			Serial.print("motion ended at ");      //output 
			Serial.print((millis() - pause)/1000); 
			Serial.println(" sec"); 
			delay(50); 
		} 
	} 
}
