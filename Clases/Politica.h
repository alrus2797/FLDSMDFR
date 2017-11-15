#ifndef POLITICA_H
#define POLITICA_H


#include "Reloj.h"
#include "proceso.h"

using namespace std;

class Politica{
public:
  Politica(){}
  ~Politica(){}
  virtual proceso* get_actual();
  virtual void actualizar(){}

  virtual void add_proceso(proceso*){}
private:
  bool b_actualizar = false;
  vector<proceso*> procesos;
  Reloj* reloj;
  proceso* proceso_actual = nullptr;
friend class PoliticaFIFO;
friend class PoliticaPRIO;
friend class VentanaPrincipal;
friend class PoliticaSPF;
friend class PoliticaRSPF;
friend class PoliticaRoundRobin;
};




proceso* Politica::get_actual(){
  return proceso_actual;
}

#endif
