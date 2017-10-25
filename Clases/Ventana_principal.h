#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include "Ventana.h"
#include "Politica.h"
#include "PoliticaFIFO.h"

class VentanaPrincipal: public Ventana{
public:
  VentanaPrincipal(){}
  ~VentanaPrincipal(){}
  void loadWidgets();
  void post_inicio();
  void actualizar();
  void actualizar_politicas();
  void actualizarLabelsProcesos();
  void posicionarProcesos();
private:
  vector<Politica*> politicas;
  vector<proceso*> procesos;
  Time quantum = seconds(0);
  float pos_x = 20;
  float pos_y = 200;
  vector<string> estados = {"creating", "ready", "running", "blocked", "finished"};
  vector<sf::Color> colores = {sf::Color::Yellow, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Magenta};
};



void VentanaPrincipal::loadWidgets(){
  auto theme = tgui::Theme::create("widgets/Black.txt");

  // Get a bound version of the window size
  // Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
  auto windowWidth = tgui::bindWidth(*gui);
  auto windowHeight = tgui::bindHeight(*gui);

  // Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
  auto picture = tgui::Picture::create();
  picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(600, windowHeight));
  gui->add(picture);

  // process name edit box
  EditBox::Ptr nombreP = EditBox::create();
  nombreP->setSize(200, 30);
  nombreP->setPosition(50, 50);
  nombreP->setDefaultText("Nombre del Proceso");
  gui->add(nombreP, "nombreP");

  // service time edit box
  EditBox::Ptr tiempoServ = EditBox::create();
  tiempoServ->setSize(150, 30);
  tiempoServ->setPosition(300, 50);
  tiempoServ->setDefaultText("Tiempo de Servicio");
  gui->add(tiempoServ, "tiempoServ");


  // priority edit box
  EditBox::Ptr prioridad = EditBox::create();
  prioridad->setSize(150, 30);
  prioridad->setPosition(500, 50);
  prioridad->setDefaultText("prioridad");
  gui->add(prioridad, "prioridad");




  Button::Ptr crearProc = Button::create();
  crearProc->setSize(150, 50);
  crearProc->setPosition(50, 100);
  crearProc->setText("Crear Proceso");
  gui->add(crearProc, "crearProc");



  Label::Ptr nomPro = Label::create();
  nomPro->setSize(100, 30);
  nomPro->setPosition(pos_x + 50, pos_y - 35);
  nomPro->setText("Nombre");
  gui->add(nomPro);
  auto rend1 = nomPro-> getRenderer();
  rend1->setBackgroundColor(sf::Color(180, 180, 180));


  Label::Ptr tiemServ = Label::create();
  tiemServ->setSize(100, 30);
  tiemServ->setPosition(pos_x + 350, pos_y - 35);
  tiemServ->setText("T. servicio");
  gui->add(tiemServ);
  auto rend2 = tiemServ-> getRenderer();
  rend2->setBackgroundColor(sf::Color(180, 180, 180));


  Label::Ptr nomEstado = Label::create();
  nomEstado->setSize(100, 30);
  nomEstado->setPosition(pos_x + 220, pos_y - 35);
  nomEstado->setText("Estado");
  gui->add(nomEstado);
  auto rend3 = nomEstado-> getRenderer();
  rend3->setBackgroundColor(sf::Color(180, 180, 180));

  auto createProccess = [&](EditBox::Ptr prioridad, EditBox::Ptr nombreP, EditBox::Ptr tiempoServ) {

    string nombreProceso = nombreP->getText().toAnsiString();
    proceso* proc = new proceso(nombreProceso, tgui::stoi(prioridad->getText().toAnsiString()), tgui::stoi(tiempoServ->getText().toAnsiString()) );

    proc->l_nombre = Label::create();
    proc->l_nombre->setSize(150, 30);
    proc->l_nombre->setText(nombreProceso);
    proc->l_estado = Label::create();
    proc->l_estado->setSize(100, 30);
    proc->l_estado->setText("nuevo");
    proc->l_tiempo = Label::create();
    proc->l_tiempo->setSize(100, 30);
    proc->l_tiempo->setText("0");

    proc->b_bloquear = Button::create();
    proc->b_bloquear->setSize(150, 30);
    proc->b_bloquear->setText("bloquear");
    proc->b_desbloquear = Button::create();
    proc->b_desbloquear->setSize(150, 30);
    proc->b_desbloquear->setText("desbloquear");

    gui->add(proc->b_bloquear);
    gui->add(proc->b_desbloquear);





    auto rend1 = proc->l_nombre-> getRenderer();
    rend1->setBackgroundColor(sf::Color(210, 210, 210));
    gui->add(proc->l_nombre);

    auto rend2 = proc->l_estado-> getRenderer();
    rend2->setBackgroundColor(sf::Color(210, 210, 210));
    gui->add(proc->l_estado);

    auto rend3 = proc->l_tiempo-> getRenderer();
    rend3->setBackgroundColor(sf::Color(210, 210, 210));
    gui->add(proc->l_tiempo);

    politicas.at(0)->add_proceso(proc);
    procesos.push_back(proc);

    auto block = [&](int pos){
        //proc->bloqueado = true;
        //procesos.at(pos)->estado = 1;
    };

    auto unblock = [&](int pos){
        //procesos.at(pos)->bloqueado = false;

    };

    int pos = procesos.size() - 1;

    proc->b_bloquear->connect("pressed", block, pos);
    proc->b_desbloquear->connect("pressed", unblock, pos);
  };
  crearProc->connect("pressed", createProccess, prioridad, nombreP, tiempoServ);

}

void VentanaPrincipal::post_inicio(){

  politicas = {new PoliticaFIFO(reloj)};
  politicas.at(0)->b_actualizar = true;

}



void VentanaPrincipal::actualizar(){
  reloj->actualizar();

  actualizar_politicas();
  actualizarLabelsProcesos();
  posicionarProcesos();
}


void VentanaPrincipal::actualizar_politicas(){
  for(auto pol : politicas){
    pol->actualizar();
  }
}

void VentanaPrincipal::actualizarLabelsProcesos(){
  for(int i = 0; i < procesos.size(); i++){
    procesos.at(i)->l_tiempo->setText(to_string(procesos.at(i)->tiempo_actual));
    procesos.at(i)->l_estado->setText(estados[procesos.at(i)->estado]);
    procesos.at(i)->l_estado->setTextColor(colores.at(procesos.at(i)->estado));

  }
}

void VentanaPrincipal::posicionarProcesos(){
  for(int i = 0; i < procesos.size(); i++){
    procesos.at(i)->l_nombre->setPosition(pos_x + 50, pos_y + i * 50);
    procesos.at(i)->l_estado->setPosition(pos_x + 220, pos_y + i * 50);
    procesos.at(i)->l_tiempo->setPosition(pos_x + 350, pos_y + i * 50);
    procesos.at(i)->b_bloquear->setPosition(pos_x + 480, pos_y + i * 50);
    procesos.at(i)->b_desbloquear->setPosition(pos_x + 610, pos_y + i * 50);
  }
}


#endif
