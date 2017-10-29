//Resistance Variables
const int analogPin= A0;
int raw= 0;
int Vin= 3.3;
int initialResistance;
int finalResistance;
float Vout= 0;
float R1= 1000;
float R2= 0;
float buffer= 0;
String myResistance;


//Water Level variables
const int waterPin = A1;
int rawWaterLevel = 0;
int initialWaterLevel;
int finalWaterLevel;
String myWaterLevel;


const int buttonPin = D0;
int buttonState = 0;

float densityMetric = 0;
String myDensityMetric;
String hydrationStatus;

int getResistance()
{
 raw= analogRead(analogPin);
buffer= raw * Vin;
Vout= (buffer)/4096.0;
buffer= (Vin/Vout) -1;
R2= R1 * buffer;
R2 = R2;
return R2;
}


void setup()
{
//Sensors setup
pinMode(analogPin, INPUT);
pinMode(analogPin, INPUT);

//Button setup
pinMode(buttonPin, INPUT);
}

void loop()
{
//Button Checker
buttonState = digitalRead(buttonPin);
if (buttonState == LOW) {

//initial resistance measure
initialResistance = getResistance();

//Initial Water Level measure
initialWaterLevel = analogRead(waterPin);

delay(10000);

//Final reading
finalResistance = getResistance();

//Water Level measure
finalWaterLevel = analogRead(waterPin);

float diffResistance = abs(finalResistance-initialResistance);
float diffWaterLevel = 2*abs(finalWaterLevel-initialWaterLevel);

densityMetric = diffResistance/diffWaterLevel;
myDensityMetric = String(densityMetric);

if(densityMetric > 4)
{
    hydrationStatus = "You are dehydrated, try to drink more water";
}
else
{
    hydrationStatus = "You are hydrated, great job!";
}

Particle.publish("Output", hydrationStatus, 60, PRIVATE);
Particle.publish("Ion Density:", myDensityMetric, 60, PRIVATE);

}

delay(150);

}


