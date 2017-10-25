#ifndef POLITICA_H
#define POLITICA_H

#include "Estructura.h"
#include "proceso.h"

using namespace std;

class Politica{
public:
  Politica(){}
  ~Politica(){}
  virtual proceso* get_actual();
  virtual void actualizar(){}

  virtual void add_proceso(proceso*);
private:
  bool b_actualizar = false;
  vector<proceso*> procesos;
  Estructura<proceso*>* estructura;
  Reloj* reloj;
  proceso* proceso_actual = nullptr;
friend class PoliticaFIFO;
friend class PoliticaPRIO;
friend class VentanaPrincipal;
};


void Politica::add_proceso(proceso* p){
  estructura->push(p);
  procesos.push_back(p);
}

proceso* Politica::get_actual(){
  return proceso_actual;
}

#endif
