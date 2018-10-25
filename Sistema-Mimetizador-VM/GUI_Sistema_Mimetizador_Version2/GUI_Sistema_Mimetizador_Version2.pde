//***IMPORTANTE**** para conseguir lalibreria ControlP5 en necesario hacer los siguiente:
// ir a Sketch -> Importar biblioteca... -> Añadir biblioteca -> escribir en el campo de texto ControlP5 , dar clic e instalar.
import controlP5.*; //Importamos la librería que nos ayudará a crear la GUI
import processing.serial.*;//Importamos la libreria para establecer la comunicacion con puerto serial y arduino
Serial puerto; //objeto tipo Serial
ControlP5 cp5; //definimos un objeto tipo ControlP5
int posY; // apuntador para posicion variable de Y
PFont letra;//letra personalizada
int esp = 40;
int contador; //contador de mensajes
//Campos de Texto
Textfield txtCamp[] = new Textfield[10];
//Botones
Button btnEliminar[] = new Button[10];
Button btnAgregar,btnEnviar;
//Etiquetas
Textlabel lblAgregarbtn;
Textlabel lblNotifica;


void setup(){
  ControlP5 conP5 = new ControlP5(this);
  contador = 1;
  letra = createFont("calibri light",16); //Creamos la letra personalizada
  //colores
  conP5.setColorForeground(0xff000000);
  conP5.setColorBackground(100);
  conP5.setColorActive(0xff000000);
  printArray(Serial.list());//impime los puertos Serial disponibles
  puerto = new Serial(this,"/dev/ttyUSB0",9600); //creamos el objeto tipo Serial con la configuracion para el puerto serial, en este caso ttyUSB0
  creaPar( " ", contador,esp);
  size(900, 450);
  btnEnviar = conP5.addButton("Enviar Mensaje(s)")
                    .setValue(1)
                    .setPosition(370, 15)
                    .setSize(200, 20)
                     ;
  lblAgregarbtn = conP5.addTextlabel("")
                        .setPosition(50,12)
                        .setFont(letra)
                        .setColor(255)
                        .setText("<-- Clic para agregar otro mensaje")
                        ;
  btnAgregar = conP5.addButton("+")
                    .setValue(0)
                    .setPosition(20, 10)
                    .setSize(25, 25)
                    ;
}
void draw(){
  background(100);
  fill(255);
  
   for (int i= 0; i<contador; i++) {//for para recorrer el arreglo para eliminar
    if (btnEliminar[i].isPressed()) {
        btnEliminar[i].remove();
        txtCamp[i].remove();
        if(contador<=10){
        notifica(contador,false);
        }
        contador--;
    }
  }
 if (btnEnviar.isPressed()) {
     verificaYEnvia();
  }else if (btnAgregar.isPressed()) {// checar si es presionado el boton agregar, si sí, se crea un nuevo par( textField con botón)
    if (contador < txtCamp.length) {
      contador++;
      posY = esp*contador;
      creaPar( "", contador,posY);
      delay(500);
    } else {
      notifica(contador,true);
      delay(500);
    }
  } 
}
void notifica(int cont,Boolean b){//avisa si llegaste al limite de mensajes
  cp5 = new ControlP5(this);//creamos objeto tipo ControlP5
  if(b){
    lblNotifica = cp5.addTextlabel("")
                        .setPosition(600,120)
                        .setFont(letra)
                        .setColor(255)
                        .setText("Limite de campos de mensajes")
                        ;
  }else{
    if(cont>1 ){
    lblNotifica.remove();
    lblNotifica = cp5.addTextlabel("")
                     .setPosition(600,120)
                     .setFont(letra)
                     .setColor(255)
                     .setText(" ")
                     ;
  }
}
}
String fechaMensaje(){//Metodo que sera llamado para obtener la fecha y hora del mensaje que sera enviado al puerto serie
  return day() + "/"+ month() +"/"+year()+" "+hour()+":"+minute(); 
}
void verificaYEnvia(){
  for (int k = 0; k < contador;k++) {
      if (txtCamp[k].isFocus()) {
          puerto.write(txtCamp[k].getText() + fechaMensaje());
          delay(200);      
      }
    }
}
void creaPar( String textfield, int cont,int y) {
  cp5 = new ControlP5(this); // creamos objeto tipo ControlP5 para poder usar los .add/set en el metodo
 
  btnEliminar[cont-1] = cp5.addButton("Eliminar mensaje " + cont)
    .setValue(0)
    .setPosition(20, y)
    .setSize(100, 20)
    ;
  txtCamp[cont-1] = cp5.addTextfield("")
    .setValue(""+textfield) 
    .setPosition(130, y)
    .setSize(400, 20)
    .setFont(letra)
    .setFocus(true)
    .setColor(color(255, 255, 255))
    .setColorCursor(color(255, 255, 255))
    ;
}
//public void keyTyped(KeyEvent e) 

//    {
//if (txtMensaje.getValue().length()== 129) 

//         println("limite"); 
//    } 
