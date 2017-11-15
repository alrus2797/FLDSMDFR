#ifndef COLAPRIORIDAD_H
#define COLAPRIORIDAD_H

#include <iostream>
#include <list>
#include "proceso.h"


class ColaPrioridad{
public:
public:
  ColaPrioridad(){}
  ~ColaPrioridad(){}
  void pop();
  proceso* top();
  void push_prioridad(proceso*);
  void push_prioridad_inv(proceso*);
  void push_tiempo_servicio(proceso*);
  void push(proceso*);
  bool empty();
  void show();
  void incrementar_prioridad(float );
private:
  list<proceso*> cola;
};



void ColaPrioridad::pop(){
  cola.pop_front();
}


proceso* ColaPrioridad::top(){
  return cola.front();
}


void ColaPrioridad::show(){
  for(auto it : cola){
    cout<<it->nombre<<" -> ";
  }
  cout<<endl;
}

void ColaPrioridad::push(proceso* d){

  cola.push_back(d);

}


void ColaPrioridad::push_prioridad(proceso* d){
  if(cola.size() == 0){
    cola.push_back(d);
    return;
  }

  auto it = cola.begin();
  while(it != cola.end()){
    if(d->prioridad > (*it)->prioridad){
      cola.insert(it, d);
      return;
    }
    it++;
  }
  cola.push_back(d);

}


void ColaPrioridad::push_prioridad_inv(proceso* d){
  if(cola.size() == 0){
    cola.push_back(d);
    return;
  }

  auto it = cola.begin();
  while(it != cola.end()){
    if(d->prioridad < (*it)->prioridad){
      cola.insert(it, d);
      return;
    }
    it++;
  }
  cola.push_back(d);

}


void ColaPrioridad::push_tiempo_servicio(proceso* d){
  if(cola.size() == 0){
    cola.push_back(d);
    return;
  }

  auto it = cola.begin();
  while(it != cola.end()){
    if(d->tiempo_servicio - d->tiempo_actual < (*it)->tiempo_servicio - (*it)->tiempo_actual ){
      cola.insert(it, d);
      return;
    }
    it++;
  }
  cola.push_back(d);

}


bool ColaPrioridad::empty(){
  return cola.empty();
}

void ColaPrioridad::incrementar_prioridad(float pr){
  for(auto& it : cola){
    it->prioridad += pr;
  }
}

#endif
