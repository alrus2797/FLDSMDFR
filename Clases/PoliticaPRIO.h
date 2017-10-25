#ifndef POLITICAPRIO_H
#define POLITICAPRIO_H

#include "Politica.h"
#include "HeapPRIO.h"
#include "proceso.h"

class PoliticaPRIO:public Politica{
public:
  PoliticaPRIO(){}
  PoliticaPRIO(Reloj* r){
    estructura = new HeapPrio<proceso*>();
    reloj = r;
  }
  ~PoliticaPRIO(){}
  void actualizar();
  void actualizar_proceso_actual();
  void sacar_proceso_actual();
  void cambiar_proceso_actual();

private:


};




void PoliticaPRIO::actualizar(){
  if(b_actualizar){
    cout<<"proceso_actual "<<proceso_actual<<endl;
    //actualizar actual proceso
    actualizar_proceso_actual();

    // si hay un proceso actual
    if(proceso_actual != nullptr){
      cout<<"as"<<endl;
      if(proceso_actual->tiempo_actual > proceso_actual->tiempo_servicio)
        sacar_proceso_actual();
      if(proceso_actual->prioridad_inicial > estructura->top()->prioridad_inicial)
        cambiar_proceso_actual();
    }

    // si no hay proceso actual
    else{
      // si la cola no esta vacia
      if(!estructura->empty()){
        cout<<"sacara"<<endl;
        proceso_actual = estructura->top();
        estructura->pop();
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
  if(!estructura->empty()){
    proceso_actual->estado = 4;
    proceso_actual = estructura->top();
    proceso_actual->estado = 2;
    estructura->pop();
    return;
  }
  proceso_actual = nullptr;

}

void PoliticaPRIO::cambiar_proceso_actual()
{
  if (!estructura->empty())
  {
    proceso_actual->estado = 1;
    proceso_actual = estructura->top();
    proceso_actual->estado = 2;
    estructura->pop();
    return;
  }

}

#endif
