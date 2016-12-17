#include <DCMotor.h>

#define SIG_LINEA 0
#define INTER_IZQ 1
#define INTER_DER 2
#define INTER_DUO 3
#define SIG_LINEA_DER 4
#define SIG_LINEA_IZQ 5
#define acomodo 6 
#define acomodoo 6 

DCMotor motor_der(M0_EN, M0_D0, M0_D1, false);
DCMotor motor_izq(M1_EN, M1_D0, M1_D1, false);

int S_IZQ;
int S_DER_EXT;
int S_DER;
int i = 0;
int S_IZQ_EXT;
int LDR_IZQ;
int LDR_DER;
int estado;
void setup(){
  estado = SIG_LINEA;
  Serial.begin(115200);
}
void loop(){
  if(estado == SIG_LINEA){
    S_IZQ = analogRead(2);
    S_DER_EXT = analogRead(3);
    S_DER = analogRead(4);
    S_IZQ_EXT = analogRead(5);
    LDR_IZQ = analogRead(1);
    LDR_DER = analogRead(0);

    if(LDR_DER >= 850){
      if(LDR_IZQ >= 650){
        estado = INTER_DUO;
      }
      else{
        estado = INTER_DER;
      }
    }
    else if(LDR_IZQ >= 650){
      if(LDR_DER >= 850){
        estado = INTER_DUO;
      }
      else{
        estado = INTER_IZQ;
      }
    }
    else if(S_IZQ >= 115 || S_DER >= 100){
      motor_der.setSpeed(40);
      motor_izq.setSpeed(40);
      delay(100);   
    }
    else if(S_IZQ_EXT >= 100){
      motor_izq.setSpeed(50);
      motor_der.setSpeed(-35);
    }
    else if(S_DER_EXT >= 100){
      motor_izq.setSpeed(-35);
      motor_der.setSpeed(50);
    }
    else{
      motor_der.setSpeed(40);
      motor_izq.setSpeed(40);
    }
  }
  if(estado == INTER_IZQ){
    motor_izq.setSpeed(-50);
    motor_der.setSpeed(-50);
    delay(450);
    i++;
    estado = acomodo;
  }
  if(estado == INTER_DER){
    motor_izq.setSpeed(-50);
    motor_der.setSpeed(-50);
    delay(950);
    motor_izq.setSpeed(-50);
    motor_der.setSpeed(50);
    delay(1200);
    estado = SIG_LINEA_DER;
  }
  if(estado == INTER_DUO){
    motor_izq.setSpeed(-40);
    motor_der.setSpeed(-40);
    delay(950);
    motor_der.setSpeed(40);
    motor_izq.setSpeed(-40);
    delay(2750);  
  }
  if(estado == acomodo){
    S_IZQ = analogRead(2);
    S_DER_EXT = analogRead(3);
    S_DER = analogRead(4);
    S_IZQ_EXT = analogRead(5);
    if(S_IZQ_EXT >= 100 && i == 2){
      motor_der.setSpeed(0);
      motor_izq.setSpeed(0);
      delay(100);
      estado = SIG_LINEA_IZQ;
    }
    else{
      motor_der.setSpeed(0);
      motor_izq.setSpeed(-40);
      i = 2;    
    }  
  }
  if(estado == SIG_LINEA_IZQ){
    motor_der.setSpeed(30);
    motor_izq.setSpeed(40);
    delay(400);
    estado = SIG_LINEA;
  }
}










