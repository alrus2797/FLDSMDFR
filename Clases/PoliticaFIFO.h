#ifndef POLITICAFIFO_H
#define POLITICAFIFO_H

#include "Politica.h"
#include "ColaFIFO.h"
#include "proceso.h"

class PoliticaFIFO:public Politica{
public:
  PoliticaFIFO(){}
  PoliticaFIFO(Reloj* r){
    estructura = new ColaFIFO<proceso*>();
    reloj = r;
  }
  ~PoliticaFIFO(){}
  void actualizar();
  void actualizar_proceso_actual();
  void sacar_proceso_actual();

private:


};




void PoliticaFIFO::actualizar(){
  if(b_actualizar){
    cout<<"proceso: "<<proceso_actual<<endl;
    //actualizar actual proceso
    actualizar_proceso_actual();

    // si hay un proceso actual
    if(proceso_actual != nullptr){
      cout<<"se pone fifo"<<endl;
      if(proceso_actual->tiempo_actual > proceso_actual->tiempo_servicio)
        sacar_proceso_actual();
    }

    // si no hay proceso actual
    else{
      // si la cola no esta vacia
      if(!estructura->empty()){
        proceso_actual = estructura->top();
        estructura->pop();
        proceso_actual->estado = 2;

      }
    }

  }
}

void PoliticaFIFO::actualizar_proceso_actual(){
  if(proceso_actual != nullptr){
    proceso_actual->tiempo_actual += reloj->get_delta().asSeconds();
  }
}

void PoliticaFIFO::sacar_proceso_actual(){
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

#endif
