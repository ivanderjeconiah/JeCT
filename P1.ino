#define RELE1 x
#define RELE2 x
#define SW1 X
#define SW2 x
#define voltSens x

//var
float voltSensor;
int in1,in2;

void Volt(){
  int value=0;
  float R1=30000.0;
  float voltage=0.0;
  float R2=7500.0;
  value=analogRead(voltSens);
  voltage=value*(5.0/1023.0);
  voltSensor=(voltage/R2/(R2+R1));
}

void setup(){
  Serial.begin(9600);
  Serial.println("Starting");
  
}

void loop(){

}
