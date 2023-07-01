#include <TimerOne.h> //librerias que se usan
#include <LedControl.h>

LedControl MATLED = LedControl(11,13,10,1);	// crea objeto

byte caracter[8]{                                 //caracteres para la matriz
  0xe0, 0xfe, 0xfc, 0xf0, 0xfc, 0xff, 0xfe, 0xf8
};
byte caracter_2[8]{
  0xe0, 0xfc, 0xfc, 0xf0, 0xfc, 0xfe, 0xfc, 0xf0
};
byte caracter_3[8]{
  0xe0, 0xf0, 0xfc, 0xf0, 0xfe, 0xfc, 0xf0, 0xf0
};

#define demora 500  //definimos este tiempo para usarlo en un delay

#define buzz 4 //definicion y creacion de variables que se usaran
int MQ2 = A5;

#define umbral 250 // sensibilidad de cuanto debe sobre pasar para que se active el circuito
int lectura;//variable para guardar datos

#define led 5 //led para indicar cuando se active la interrupcion
volatile long int Time=0; //variable que mostrara cuantas veces a pasado la interrupcion


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //activamos el monitor serial

  pinMode(buzz,OUTPUT); //salidas y entradas para el uso
  pinMode(MQ2,INPUT);
  pinMode(led,OUTPUT);

  MATLED.shutdown(0,false);			// enciende la matriz
  MATLED.setIntensity(0,10);			// establece brillo
  MATLED.clearDisplay(0);			// blanquea matriz

  Timer1.initialize(5000000); //tiempo de 5 sec de la interrupcion
  Timer1.attachInterrupt(Temporizador);//la funcion que usara de ISR

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Sensor = "); //muestra en el monitor serial
  Serial.println(lectura);//muestra el valor que tenga lectura
  delay(100);
  digitalWrite(led,LOW); //apaga la led

  if (lectura > umbral){//if para saber si lectura pasa a umbral se activara buzzer y matriz
    buzzer(); //funciones vacias
    matriz();

  }else{
    noTone(buzz); //apagar el buzzer y matriz
    MATLED.clearDisplay(0);
  }
  delay(100);
}

void buzzer() { //funcion de alarma para el buzzer
  tone(buzz,1000);
  delay(100);
  noTone(buzz);
  tone(buzz,1000);
  delay(100);
  noTone(buzz);
  tone(buzz,1000);
  delay(100);
  noTone(buzz);
  tone(buzz,1000);
  delay(100);
  noTone(buzz);
  tone(buzz,1000);
  delay(100);
  noTone(buzz);
  
}

void matriz() { //funcion para la animacion de la matriz
  for (int i = 0; i < 8; i++)  		// bucle itera 8 veces por el array
  {
    MATLED.setRow(0,i,caracter[i]);
  }
    delay(demora);

  for (int i = 0; i < 8; i++)  		// bucle itera 8 veces por el array
  {
    MATLED.setRow(0,i,caracter_2[i]);
  }
    delay(demora);

  for (int i = 0; i < 8; i++)  		// bucle itera 8 veces por el array
  {
    MATLED.setRow(0,i,caracter_3[i]);
  }
    delay(demora);

}

void Temporizador(void) { //funcion para interrupción cuendo ejecuta el timer
  Time++;       //para para enseñar cuantas veces a pasado la interrupcion
  if(Time>10){
    Time=0;
  }
  Serial.print("contador de 0 a 10 cada 5sec = ");
  Serial.println(Time);

  lectura = analogRead(MQ2);//lectura guarda el valor que envia el sensor MQ2
  digitalWrite(led,HIGH);
  delay(100);

}
