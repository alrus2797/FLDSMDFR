#ifndef VENTANA_H
#define VENTANA_H

/* -*- C++ -*- */
#include <TGUI/TGUI.hpp>
#include "Reloj.h"


using namespace sf;
using namespace std;
using namespace tgui;



class Ventana{
public:
  Ventana(){}
  ~Ventana(){}
  virtual void cargar_widgets(){}
  virtual void iniciar();
  virtual void actualizar(){}
  virtual void dibujar(){}
  virtual void loadWidgets(){}
  virtual void post_inicio(){}
  void loop();

private:
  RenderWindow* window;
  Gui* gui;
  Event* evento;
  Reloj* reloj;





  float ventana_ancho = 800;
  float ventana_alto = 600;
  string ventana_nombre = "WII";

friend class VentanaPrincipal;
};





void Ventana::loop(){
  while (window->isOpen()) {
    evento = new Event();
    while (window->pollEvent(*evento))
    {
        if (evento->type == Event::Closed)
            window->close();
        else if (evento->type == Event::Resized)
        {
            window->setView(sf::View(sf::FloatRect(0, 0, evento->size.width, evento->size.height)));
            gui->setView(window->getView());
        }
        gui->handleEvent(*evento);
    }
    actualizar();
    window->clear();
    gui->draw();
    dibujar();
    window->display();

  }
}


void Ventana::iniciar(){
  window = new RenderWindow(VideoMode(ventana_ancho, ventana_alto),ventana_nombre);
  gui = new Gui(*window);
  reloj = new Reloj();
  reloj->iniciar();
  try{
      loadWidgets();
  }
  catch (const tgui::Exception& e){
      std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
  }
  post_inicio();
}



#endif
