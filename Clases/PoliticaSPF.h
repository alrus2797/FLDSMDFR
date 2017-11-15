#ifndef POLITICASPF_H
#define POLITICASPF_H

#include "Politica.h"
#include "ColaPrioridad.h"
#include "proceso.h"
#include "Reloj.h"

class PoliticaSPF:public Politica{
public:
  PoliticaSPF(){}
  PoliticaSPF(Reloj* r){
    cola = new ColaPrioridad();
    reloj = r;
  }
  ~PoliticaSPF(){}
  void actualizar();
  void actualizar_proceso_actual();
  void sacar_proceso_actual();

  void add_proceso(proceso* p);

private:
  ColaPrioridad* cola;

};




void PoliticaSPF::actualizar(){
  if(b_actualizar){

    //actualizar actual proceso
    actualizar_proceso_actual();

    // si hay un proceso actual
    if(proceso_actual != nullptr){

      if(proceso_actual->tiempo_actual > proceso_actual->tiempo_servicio)
        sacar_proceso_actual();
    }


    // si no hay proceso actual
    else{
      // si la cola no esta vacia
      if(!cola->empty()){
        proceso_actual = cola->top();
        cola->pop();
        proceso_actual->estado = 2;

      }
    }

  }
}

void PoliticaSPF::actualizar_proceso_actual(){
  if(proceso_actual != nullptr){
    proceso_actual->tiempo_actual += reloj->get_delta().asSeconds();
  }
}

void PoliticaSPF::sacar_proceso_actual(){
  // cola no vacia
  if(!cola->empty()){
    proceso_actual->estado = 4;
    proceso_actual = cola->top();
    proceso_actual->estado = 2;
    cola->pop();
    return;
  }
  proceso_actual->estado = 4;
  proceso_actual = nullptr;

}


void PoliticaSPF::add_proceso(proceso* p){
  cola->push_tiempo_servicio(p);
  procesos.push_back(p);
}










#endif
