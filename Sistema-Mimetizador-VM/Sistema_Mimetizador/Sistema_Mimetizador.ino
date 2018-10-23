//#include <Time.h>
#include <LiquidCrystal.h>
#define RS 3
#define E 5
#define D4 6
#define D5 9
#define D6 10
#define D7 11
#define boton 2
#define browser 7

char caracteres;

boolean isMessage;

boolean isRead;

String mensajes[3] ; //cambiar a 4, para que el default sea el del tiempo

int contMessage;

int cont;

String bannerMessage;

int tam_texto;

int spaceMessage;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

    void setup()
    {
        pinMode(boton,INPUT);
        pinMode(browser,INPUT);
        lcd.begin(16, 2);
        isMessage=false;
        isRead=false;
        caracteres=0;
        contMessage = 0;
        cont=-1;
        bannerMessage="Mensajes totales 0";
        tam_texto=0;
        spaceMessage=sizeof(mensajes);
  
        attachInterrupt(digitalPinToInterrupt(boton), interrupcion,RISING);
        Serial.begin(9600);

    }
    void loop() 
    {
   
        if (Serial.available())  //Verificar si te tiene informacion pendiente de leer en el bus Serial
         {
            delay(100);//retardo para permitir que informacion termine de recibirse en el bus Serial
            lcd.clear();//quitar cualquier texto o imagen que se encuentre en la LCD

            while (Serial.available() > 0) 
              {
                  caracteres = Serial.read(); //Leer 1 carácter
                  mensajes[contMessage]+=caracteres;//Almacena el mensaje
                  delay(25);
              }
            lcd.print(mensajes[contMessage]);//imprime el mensaje en el lcd
            contMessage++;
            isMessage=true;
          }
         if(isMessage==true)
          {
            bannerMessage="Mensajes totales ";
            String letrero=bannerMessage + contMessage;
            tam_texto=letrero.length();
            sliceMessage(tam_texto,letrero);     
          }
          else
          {
            tam_texto=bannerMessage.length();
            sliceMessage(tam_texto,bannerMessage);
//
//            int tam =getFecha().length();
//            sliceMessage_2(tam,getFecha());
          }

          while(isRead)
          {             
                if(cont<spaceMessage)
                {
                    bannerMessage=mensajes[cont];
                    tam_texto=bannerMessage.length();
                    sliceMessage(tam_texto,bannerMessage);
                }
                else
                {
                    cont=-1;
                    isRead=!isRead;
                }
               
          }
            
    }

    void sliceMessage(int lenghtText,String texto)
      {
          // Mostramos entrada texto por la izquierda
          for(int i=lenghtText; i>0 ; i--)
          {
              String texto_1 = texto.substring(i-1);
 
              // Limpiamos pantalla
              lcd.clear();
 
              //Situamos el cursor
              lcd.setCursor(0, 0);
 
              // Escribimos el texto
              lcd.print(texto_1);
 
              // Esperamos
              delay(300);
          }
 
           // Desplazamos el texto hacia la derecha
          for(int i=1; i<=16;i++)
          {
              // Limpiamos pantalla
              lcd.clear();
 
              //Situamos el cursor
              lcd.setCursor(i, 0);
 
              // Escribimos el texto
              lcd.print(texto);
 
              // Esperamos
              delay(200);
          }

      }
    void interrupcion()
    {
      isRead=true;
      cont++;
      spaceMessage=contMessage;
    }

    /*
FUNCION PARA OBTENER LA FECHA EN MODO TEXTO
Devuelve: DD-MM-AAAA HH:MM:SS
*/
//String getFecha(){
//
//String fecha="";
//int hora=0;
//int minuto=0;
//int dia = 0;
//int mes=0;
////int año=0;
//
// hora=hour();
// minuto=minute();
// dia = day();
// mes=month();
//// año=year();
//fecha="Hora: ".concat(hora)+"fdf".concat(minuto)+" Fecha: ".concat(dia)+"/".concat(mes);
//
//  return fecha;
//}
    
 
//    void sliceMessage_2(int lenghtText,String texto)
//      {
//          // Mostramos entrada texto por la izquierda
//          for(int i=lenghtText; i>0 ; i--)
//          {
//              String texto_1 = texto.substring(i-1);
// 
//              // Limpiamos pantalla
//              lcd.clear();
// 
//              //Situamos el cursor
//              lcd.setCursor(1, 0);
// 
//              // Escribimos el texto
//              lcd.print(texto_1);
// 
//              // Esperamos
//              delay(300);
//          }
//      } 
