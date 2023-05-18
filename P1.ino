#define RELE1 50
#define RELE2 51
#define SW1 2
#define SW2 3
#define voltSens A1

//var
float voltageSensor;
bool in1,in2;
uint8_t in1Val, in2Val;
int timer, rele1Timer,rele2Timer; 
float batas;
bool second=false;
bool rele1Stat=false,rele2Stat=false;


void Volt(){
  int value=0;
  value=analogRead(voltSens);
  voltageSensor=value*(5.0/1023.0);
}

void setup(){
  Serial.begin(9600);
  Serial.println("Starting");
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  digitalWrite(RELE1,LOW);
  digitalWrite(RELE2,LOW);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  in1=digitalRead(SW1);
  in2=digitalRead(SW2);
  Serial.println(in1);
  Serial.println(in2);
}

void loop(){
  if ((in1!=digitalRead(SW1)) && (in2!=digitalRead(SW2))){
    Serial.println(in1);
    Serial.println(in2);
    in1=digitalRead(SW1);
    in2=digitalRead(SW2);
    if(in1){
      in1Val=0;
      in2Val=5;
    }
    else if (in2){
      in2Val=0;
      in1Val=5;
    }
    batas=4.5;
    timer=millis();
    second=true;
  }

  if (second){
    if(millis()-timer<60000){
      Volt();
      Serial.println(voltageSensor);
      if(in1Val-voltageSensor>=batas){
        second=false;
        digitalWrite(RELE1,HIGH);
        rele1Stat=true;
        rele1Timer=millis();
      }
      else if (in2Val-voltageSensor>=batas){
        second=false;
        digitalWrite(RELE2,HIGH);
        rele2Stat=true;
        rele2Timer=millis();
      }
    }
    else {
      batas=batas-0.5;
      if(batas<3){
        second=false;
      }
      else{
        timer=millis();
      }   
    }
  }

  if(rele1Stat){
    if(millis()-rele1Timer>=3000){
      rele1Stat=false;
      digitalWrite(RELE1, LOW);
    }
  }

  if(rele2Stat){
    if(millis()-rele2Timer>=3000){
      rele2Stat=false;
      digitalWrite(RELE2,LOW);
    }
  }

  
}
