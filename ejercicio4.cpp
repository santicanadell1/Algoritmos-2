#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
struct posicion{
    int id;
    int pos;
    posicion* sig;
};
struct pedido
{
    int id;
    int prioridad;
    string items;
    bool paraLlevar;
};


class colaDePrioridad{
    private:
    //heap
        int capacidad;
        int pos; //primeo libre
        pedido** vec;
    int min(int i1, int i2){
        return vec[i1]->prioridad < vec[i2]->prioridad ? i1 : i2;
    }
    bool lleno(){
        return pos > capacidad;
    }

    bool vacio(){
        return pos == 1;
    }

    void swap(int pos1, int pos2){
        pedido* aux = vec[pos1];
        vec[pos1] = vec[pos2];
        vec[pos2] = aux;
        insertarAux(vec[pos1]->id,pos1);
        insertarAux(vec[pos2]->id,pos2);
    }
    int padre(int pos){
        return pos/2;
    }
    bool comparar(int pos, int posPadre){
        bool menor = false;
        if(vec[pos]->prioridad < vec[posPadre]->prioridad){
            menor = true;
        }
        else if(vec[pos]->prioridad == vec[posPadre]->prioridad && vec[pos]->paraLlevar == true && vec[posPadre]->paraLlevar == false){
            menor = true;
        }
        else  if(vec[pos]->prioridad == vec[posPadre]->prioridad && vec[pos]->paraLlevar == vec[posPadre]->paraLlevar &&vec[pos]->id < vec[posPadre]->id){
            menor = true;
        }
        return menor;
    }

    void flotar(int pos){
        if(pos == 1) return;
        int posPadre = padre(pos);
        if(comparar(pos,posPadre)){
            swap(pos,posPadre);
            flotar(posPadre);
        }
    }

    void hundir(int pos){
        if (pos == capacidad) return;
        if(comparar(pos*2, pos*2+1)){
            if(comparar(pos*2,pos)){
                swap(pos,pos*2);
                hundir(pos*2);
            }
        }else{
            if(comparar(pos*2+1,pos)){
                swap(pos,pos*2+1);
                hundir(pos*2+1);
            }
        }
    }
    //Hash
        posicion** hash;
        int largo;
        int cantElem;
        int funcionHash1(int c){
            return c % largo;
        }
        // void rehash(){
        //     largo = largo * 2;
        //     posicion** nuevo = new posicion*[largo];
        //     for(int i = 0; i< largo/2; i++){
        //         if(hash[i]){
        //             int clave = hash[i]->id;
        //             int bucket = funcionHash1(clave);
        //             nuevo[bucket] = hash[i];
        //         }
        //     }
        //     delete[] hash;
        //     hash = nuevo;
        // }
        void insertarAux(int id, int pos){
            if(cantElem >= 0.7*largo){
                //rehash();
            }
            int indice= funcionHash1(id);
            posicion* buck = hash[indice];
            while(buck->sig){
                if(buck->id == id){
                    buck->pos = pos;
                    break;
                }
                buck = buck->sig;
            }
                if(!buck->sig){
                    posicion* nuevo = new posicion;
                    nuevo->id = id;
                    nuevo->pos = pos;
                    nuevo->sig = NULL;
                    buck->sig = nuevo;
                }
        }
        int buscarAux(int id){
            int indice=funcionHash1(id);
            posicion* buck = hash[indice];
            while(buck->sig){
                if(buck->id == id)return buck->pos;
                buck = buck->sig;
            }
        }
    public:
        colaDePrioridad(int n){
            hash = new posicion*[n]();
            largo = n;
            cantElem = 0;
            capacidad = n;
            pos = 1; //primeo libre
            vec = new pedido*[capacidad+1]();
        }
        ~colaDePrioridad(){

        }
        void encolar(int id, int prioridad, string items, bool llevar){
        if(!lleno()){
            pedido* nuevo = new pedido;
            nuevo->id = id;
            nuevo->prioridad = prioridad;
            nuevo->paraLlevar = llevar;
            nuevo->items = items;
            vec[pos] = nuevo;
            flotar(pos);
            pos++;
        }
    }
    pedido* desencolar(){
        pedido* desencolado = vec[1];
        swap(1,pos-1);
        vec[pos-1] = NULL;
        pos --;
        hundir(1);
        return desencolado;
    }
    void eliminar(int id){
        int posicion = buscarAux(id);
        pedido* desencolado = vec[posicion];
        swap(posicion,pos-1);
        vec[pos-1] = NULL;
        pos --;
        hundir(posicion);
        flotar(posicion);
        delete desencolado;
    }
    void cambiarPedido(int id){
        int posicion = buscarAux(id);
        vec[posicion]->paraLlevar = !vec[posicion]->paraLlevar;
        hundir(posicion);
        flotar(posicion);
    }
    int cantElemEncolados(){
        return pos;
    }

};
int main(){
    // TODO
    int N;
    cin >> N;
    colaDePrioridad cola = colaDePrioridad(N);
    int O;
    cin >> O;
    for (int i = 0; i< O; i++){
        string operacion;
        cin >> operacion;

        if (operacion == "I") {
            int id;
            string items;
            bool paraLlevar;
            int prioridad;
            cin >> id >> prioridad >> paraLlevar >> items;
            cola.encolar(id,prioridad,items,paraLlevar);
        } else if (operacion == "E") {
            int id;
            cin >> id;
            cola.eliminar(id);
        } else if (operacion == "C") {
            int id;
            cin >> id;
            cola.cambiarPedido(id);
        }
    }
    int cant = cola.cantElemEncolados();
    for(int i = 1; i < cant ; i++ ){
        pedido* ped = cola.desencolar();
        std::cout << std::to_string(ped->id) << std::to_string(ped->prioridad) << std::to_string(ped->paraLlevar) << ped->items << std::endl;
    }
    return 0;
}