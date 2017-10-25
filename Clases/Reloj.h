#ifndef RELOJ_H
#define RELOJ_H

#include <TGUI/TGUI.hpp>

using namespace tgui;
using namespace sf;


class Reloj{
public:
  Reloj(){}
  ~Reloj(){}

  void iniciar();
  void actualizar();
  void actualizar_delta();
  Time get_tiempo();
  void detener();
  void continuar();
  void reiniciar();
  Time get_delta();
private:
  Clock* reloj;
  Time delta;
  Time tiempo;
  bool parar = false;
  Time anterior_tiempo;

};

Time Reloj::get_delta(){
  return delta;
}

void Reloj::reiniciar(){
  tiempo = seconds(0);
  anterior_tiempo = seconds(0);
}

void Reloj::iniciar(){
  reloj = new Clock();
  anterior_tiempo = reloj->getElapsedTime();
}

void Reloj::actualizar_delta(){
  if(parar){
    anterior_tiempo = reloj->getElapsedTime();
    delta = seconds(0);
    return;
  }

  delta = reloj->getElapsedTime() - anterior_tiempo;
  anterior_tiempo = reloj->getElapsedTime();
}

Time Reloj::get_tiempo(){
  return tiempo;
}


void Reloj::detener(){
  parar = true;
}

void Reloj::continuar(){
  parar = false;
}

void Reloj::actualizar(){
  actualizar_delta();
  tiempo += delta;
}



#endif
