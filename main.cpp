#include "controlador.h"

#include "Ventana.h"



int main(int argc, char const *argv[]) {
  //Controlador cont;
  Ventana wi;
  wi.iniciar();
  wi.loop();

  //cont.iniciar();

  return 0;
}
