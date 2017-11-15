#ifndef COLAFIFO_H
#define COLAFIFO_H

#include "proceso.h"

class ColaFIFO{
public:
  ColaFIFO(){}
  ~ColaFIFO(){}
  void pop();
  proceso* top();
  void push(proceso*);
  bool empty();
private:
  list<proceso*> cola;
};



void ColaFIFO::pop(){
  cola.pop_front();
}


proceso* ColaFIFO::top(){
  return cola.front();
}


void ColaFIFO::push(proceso* d){
  cola.push_back(d);
}


bool ColaFIFO::empty(){
  return cola.empty();
}

#endif
