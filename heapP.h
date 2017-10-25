#include "proceso.h"
#include <queue>
using namespace std;




class cola_procesos{
public:
  cola_procesos(){}
  ~cola_procesos(){}
  priority_queue<proceso*, vector<proceso*>, compareProceso> heap_procesos;

  // añade un proceso al heap
  void add_proceso(proceso* p){
    heap_procesos.push(p);
  }

  // obtiene el proceso con mayor prioridad y lo saca de la cola
  bool get_proceso(proceso*& p){
    if (heap_procesos.empty() == true)
      return false;

    p = heap_procesos.top();

    return true;
  }

  void pop_proceso(){
    heap_procesos.pop();
  }

  // aumenta la prioridad de todos los elementos en la cola dado un valor
  void aumentar_prioridad(int valor){
    cola_procesos heap_temp;

    proceso* proc_temp;
    while(get_proceso(proc_temp)){
      pop_proceso();
      proc_temp->prioridad += valor;
      heap_temp.add_proceso(proc_temp);
    }
    heap_procesos = heap_temp.heap_procesos;
  }

friend class Controlador;
};
