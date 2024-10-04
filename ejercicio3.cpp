#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
struct objeto{
    int precio;
    int id;
 };
class minHeap
{
private:
    int* posiciones;
    int capacidad;
    int pos; //primero libre
    objeto** vec;

    bool lleno(){
        return pos > capacidad;
    }

    bool vacio(){
        return pos == 1;
    }

    void swap(int pos1, int pos2){
        objeto* aux = vec[pos1];
        vec[pos1] = vec[pos2];
        vec[pos2] = aux;
        posiciones[vec[pos1]->id] = pos2;
        posiciones[vec[pos2]->id] = pos1;
    }
    int padre(int pos){
        return pos/2;
    }
    
    int hijo(int pos){
        return pos*2;
    }

    bool comparar(int pos, int posPadre){
        bool menor = false;
        if(vec[pos]->precio < vec[posPadre]->precio){
            menor = true;
        }
        else if(vec[pos]->precio == vec[posPadre]->precio && vec[pos]->id > vec[posPadre]->id){
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
        
    }
public:
     minHeap(int tam){
        posiciones = new int[tam+1]();
        vec = new objeto*[tam+1];
        pos = 1;
        capacidad = tam;
     };
    ~minHeap(){
        for(int i = 1; i < pos;i++){
            delete vec[pos];
        }
        delete[] vec;
        delete[] posiciones;
    };
    void insertar(int precio, int id){
        if(lleno())return;
        if(posiciones[id] == 0){
            objeto* nuevo = new objeto;
            nuevo->id = id;
            nuevo->precio = precio;
            vec[pos] = nuevo;
            flotar(pos);
            pos ++;
        }
        else{

        }
    }
    void desencolar(){
        if(!vacio){

        }
    }
};


int main()
{
    // TODO
    return 0;
}