#ifndef POLITICAPRIO_H
#define POLITICAPRIO_H

#include "Politica.h"
#include "ColaPrioridad.h"
#include "proceso.h"
#include "Reloj.h"

class PoliticaPRIO:public Politica{
public:
  PoliticaPRIO(){}
  PoliticaPRIO(Reloj* r){
    cola = new ColaPrioridad();
    reloj = r;
  }
  ~PoliticaPRIO(){}
  void actualizar();
  void actualizar_proceso_actual();
  void sacar_proceso_actual();
  void cambiar_proceso_actual();
  void add_proceso(proceso* p);

private:
  ColaPrioridad* cola;

};




void PoliticaPRIO::actualizar(){
  if(b_actualizar){

    //actualizar actual proceso
    actualizar_proceso_actual();

    // si hay un proceso actual
    if(proceso_actual != nullptr){

      if(proceso_actual->tiempo_actual > proceso_actual->tiempo_servicio)
        sacar_proceso_actual();
      if(!cola->empty()){
        cambiar_proceso_actual();
      }
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

void PoliticaPRIO::actualizar_proceso_actual(){
  if(proceso_actual != nullptr){
    proceso_actual->tiempo_actual += reloj->get_delta().asSeconds();
  }
}

void PoliticaPRIO::sacar_proceso_actual(){
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

void PoliticaPRIO::cambiar_proceso_actual()
{
  proceso* temp = cola->top();
  if(temp->prioridad < proceso_actual->prioridad){
    cola->pop();
    proceso_actual->estado = 1;
    cola->push_prioridad_inv(proceso_actual);
    proceso_actual = temp;
    proceso_actual->estado = 2;
  }

}


void PoliticaPRIO::add_proceso(proceso* p){
  cola->push_prioridad_inv(p);
  procesos.push_back(p);
}










#endif
