#include <DHT.h>
#include <LiquidCrystal.h>
#define RS 3
#define E 5
#define D4 6
#define D5 9
#define D6 10
#define D7 11
#define boton 2
#define browser 7
#define fotoResistencia A0
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 13
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

const long A = 1000; //Resistencia en oscuridad en KΩ
const int B = 15; //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10; //Resistencia calibracion en KΩ
int V;
int ilum;

char caracteres;

boolean isMessage;

boolean isRead;

String mensajes[5] ; //cambiar a 4, para que el default sea el del tiempo

int contMessage;

int contCaracteres;

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
        contCaracteres= 0;
        cont=-1;
        bannerMessage="Mensajes totales 0";
        tam_texto=0;
        spaceMessage=sizeof(mensajes);
        
         // Comenzamos el sensor DHT
        dht.begin();
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
                  contCaracteres++;
                  if(contCaracteres <= 140)
                  {
                    mensajes[contMessage]+=caracteres;//Almacena el mensaje
                  }
                  delay(25);
              }
            contMessage++;
            isMessage=true;
          }
         if(isMessage==true)
          {
            bannerMessage="Mensajes totales ";
            String letrero=bannerMessage + contMessage +" -> luminosidad "+ light()+tiempo();
            tam_texto=letrero.length();
            sliceMessage(tam_texto,letrero);     
          }
          else
          {
            String aux ="";
            aux=bannerMessage +" -> luminosidad "+ light()+tiempo();
            tam_texto=aux.length();
            sliceMessage(tam_texto,aux);
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
    
    String light()
    {
      V = analogRead(fotoResistencia);
      ilum = ((long)V*A*10)/((long)B*Rc*(1024-V)); //usar si LDR entre A0 y Vcc (como en el esquema anterior)
      ilum=map(ilum,8,110,0,100);
      if(ilum<0)
      {
          ilum=0;
      }
      else if(ilum>100)
      {
          ilum=100;
      }
      String sim="% ";
      String light= ilum + sim;
      
      return light;
    } 

    String tiempo()
    {
      // Leemos la humedad relativa
      float h = dht.readHumidity();
      // Leemos la temperatura en grados centígrados (por defecto)
      float t = dht.readTemperature();
 
      // Comprobamos si ha habido algún error en la lectura
      if (isnan(h) || isnan(t))
      {
      Serial.println("Error obteniendo los datos del sensor DHT11");
      return;
      }

      String aux=" Humedad: ";
      aux.concat(h);
      aux.concat(" %\t");
      aux.concat("Temperatura: ");
      aux.concat(t);
      aux.concat(" *C ");
      return  aux;
     }
