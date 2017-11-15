#ifndef POLITICAROUNDROBINPRIO_H
#define POLITICAROUNDROBINPRIO_H

#include "Politica.h"
#include "ColaPrioridad.h"
#include "proceso.h"
#include "Reloj.h"

class PoliticaRoundRobinPrio:public Politica{
public:
  PoliticaRoundRobinPrio(){}
  PoliticaRoundRobinPrio(Reloj* r){
    cola = new ColaPrioridad();
    reloj = r;
  }
  ~PoliticaRoundRobinPrio(){}
  void actualizar();
  void actualizar_proceso_actual();
  void sacar_proceso_actual();
  void cambiar_proceso_actual();
  void add_proceso(proceso* p);

private:
  ColaPrioridad* cola;
  Time quantum = seconds(2);
  Time t_ciclo = seconds(0);

};




void PoliticaRoundRobinPrio::actualizar(){
  if(b_actualizar){
    //actualizar actual proceso
    actualizar_proceso_actual();

    // si hay un proceso actual
    if(proceso_actual != nullptr){

      if(proceso_actual->tiempo_actual > proceso_actual->tiempo_servicio)
        sacar_proceso_actual();

      if(t_ciclo >= quantum){
        cambiar_proceso_actual();
        cola->incrementar_prioridad(1);
      }
      t_ciclo += reloj->get_delta();
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

void PoliticaRoundRobinPrio::actualizar_proceso_actual(){
  if(proceso_actual != nullptr){
    proceso_actual->tiempo_actual += reloj->get_delta().asSeconds();
  }
}

void PoliticaRoundRobinPrio::sacar_proceso_actual(){
  // cola no vacia
  t_ciclo = seconds(0);
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

void PoliticaRoundRobinPrio::cambiar_proceso_actual()
{
  if(!cola->empty()){

    proceso* temp = cola->top();
    cola->pop();
    proceso_actual->estado = 1;
    proceso_actual->prioridad = proceso_actual->prioridad_inicial;
    cola->push_prioridad(proceso_actual);
    proceso_actual = temp;
    proceso_actual->estado = 2;
  }
  t_ciclo = seconds(0);
}


void PoliticaRoundRobinPrio::add_proceso(proceso* p){
  cola->push_prioridad(p);
  procesos.push_back(p);
}










#endif
