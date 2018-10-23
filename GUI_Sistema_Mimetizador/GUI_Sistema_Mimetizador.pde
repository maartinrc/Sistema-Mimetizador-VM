import interfascia.*; //Importamos la librería que nos ayudará a crear la GUI
import processing.serial.*;//Importamos la libreria para establecer la comunicacion con puerto serial y arduino

Serial puerto;//Objeto tipo Serial
GUIController c;//Creamos objeto tipo GUIController
//TextField
IFTextField txtMensaje;
//Botones
IFButton btnLimpiar;
IFButton btnAgregarMensaje;
IFButton btnEnviarMensaje;
IFButton btnBorrar;
//Etiquetas
IFLabel lblEscribeMsj;
IFLabel lblMsj;
IFLabel lblMsj1cont;
IFLabel lblMsj2cont;
IFLabel lblMsj3cont;

int cont;//contador para los mensajes

void setup(){
  size(900,400);//tamano de la "pantalla" donde estara la interfaz
  background(100);//fondo gris
  cont = 0;//contador
 c = new GUIController(this);//c estara controllando los componentes en este sketch
 
 //printArray(Serial.list());//impime los puertos Serial disponibles
  puerto = new Serial(this,"/dev/ttyUSB0",9600);
 //TextField
 txtMensaje = new IFTextField("Input",50,50,400);
 
 //BOTONES
 btnLimpiar = new IFButton("Limpiar",480,50);
 btnAgregarMensaje = new IFButton("Agregar mensaje",50, 20);
 btnEnviarMensaje = new IFButton("Enviar mensaje",50,80);
 

 //Etiquetas
 lblEscribeMsj = new IFLabel("Escribe un mensaje", 50,30);
 lblMsj = new IFLabel("",50,150);
 lblMsj1cont =new IFLabel("",50,210);
 lblMsj2cont =new IFLabel("",50,240);
 lblMsj3cont =new IFLabel("",50,270);
 
  //Agregar Listener al componente que lo necesite
   btnLimpiar.addActionListener(this);
   btnEnviarMensaje.addActionListener(this);
   
  //Agregar componentes al obejto GUIController
  c.add(lblEscribeMsj);
  c.add(txtMensaje);
  //c.add(btnAgregarMensaje);
  c.add(btnLimpiar);
  c.add(btnEnviarMensaje);
  c.add(lblMsj);
  c.add(lblMsj1cont);
  c.add(lblMsj2cont);
  c.add(lblMsj3cont);
}

void draw(){
  
}

void actionPerformed(GUIEvent e){//Metodo que se ejecuta al interactuar con los componentes a los que se agrego el listener
    if(e.getSource() == btnLimpiar){
      txtMensaje.setValue("");
    }else if(e.getSource() == btnEnviarMensaje){
      if(txtMensaje.getValue() != ""){
      cont++;
      mostrarMensajes();//no se muestra si el TextField esta vacio
      }
    }
    
  
}


void mostrarMensajes(){
   lblMsj.setLabel("Mensajes enviados");
  if(cont == 1){
    lblMsj1cont.setLabel(cont+".- "+txtMensaje.getValue());
    puerto.write(txtMensaje.getValue());
    txtMensaje.setValue("");
    c.add(btnBorrar);
  }else if(cont == 2){
    lblMsj2cont.setLabel(cont+".- "+txtMensaje.getValue());
    puerto.write(txtMensaje.getValue());
    txtMensaje.setValue("");
  }else if(cont == 3){
    lblMsj3cont.setLabel(cont+".- "+txtMensaje.getValue());
    puerto.write(txtMensaje.getValue());
    txtMensaje.setValue("");
  }
    
  
}
