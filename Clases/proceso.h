#ifndef PROCESO_H
#define PROCESO_H

/* -*- C++ -*- */
#include <iostream>
#include <TGUI/TGUI.hpp>


using namespace sf;
using namespace std;
using namespace tgui;



class proceso{
public:
    proceso(){}
    proceso(string nom, int pr, int t_serv){
      nombre = nom;
      prioridad = pr;
      prioridad_inicial = pr;
      tiempo_servicio = t_serv;
    }
    ~proceso(){}


    string nombre;
    int prioridad = 0;
    int prioridad_inicial;
    int estado = 1;
    float tiempo_servicio;
    float tiempo_actual = 0;
    Label::Ptr l_nombre;
    Label::Ptr l_estado;
    Label::Ptr l_tiempo;
    Button::Ptr b_bloquear;
    Button::Ptr b_desbloquear;



friend class comparePrio;
friend class heap;
friend class Controlador;


};


class comparePrio
{
public:
  bool operator()(proceso*& t1, proceso*& t2) // Returns true if t1 is earlier than t2
  {
     return (t1)->prioridad < (t2)->prioridad;
      //return true;
     //return false;
  }
};



#endif
