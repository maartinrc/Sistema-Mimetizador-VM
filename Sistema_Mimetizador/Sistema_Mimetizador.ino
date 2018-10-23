#include <LiquidCrystal.h>
#define RS 3
#define E 5
#define D4 6
#define D5 9
#define D6 10
#define D7 11

char c =0;
boolean x=false;
String mensajes[3] ; //cambiar a 4, para que el default sea el del tiempo
String clon[3];
int contador;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  contador = 0;

}




void loop() {
  if (Serial.available()) { //Verificar si te tiene informacion pendiente de leer en el bus Serial

    delay(100);//retardo para permitir que informacion termine de recibirse en el bus Serial
    lcd.clear();//quitar cualquier texto o imagen que se encuentre en la LCD

    while (Serial.available() > 0) {
      c = Serial.read(); //Leer 1 carácter
      mensajes[contador]+=c;//Almacena el mensaje
      delay(25);
    }
    clon[contador]=(mensajes[contador]);
   lcd.print(mensajes[contador]);//imprime el mensaje en el lcd
   contador++;
   x=true;
  }
if(x){
for(int index=0;index<contador;index++){
 
  Serial.println(clon[contador]);
}
x=false;
}
  
}
