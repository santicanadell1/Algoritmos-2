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
    int capacidad;
    int pos; //primeo libre
    objeto** vec;
    int min(int i1, int i2){
        return vec[i1]->precio < vec[i2]->precio ? i1 : i2;
    }
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
    }
    int padre(int pos){
        return pos/2;
    }
    bool comparar(int pos, int posPadre){
        bool menor = false;
        if(vec[pos]->precio < vec[posPadre]->precio){
            menor = true;
        }
        else  if(vec[pos]->precio < vec[posPadre]->precio && vec[pos]->id > vec[posPadre]->id){
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
    
public:
     minHeap(int tam){
        vec = new objeto*[tam+1]();
        capacidad = tam;
        pos = 1;
     };
    ~minHeap(){
        for (int i = 0; i < capacidad+1; i++){
            delete vec[i];
        }
        delete[] vec;
    };
    void encolar(int id, int precio){
        if(!lleno()){
            objeto* nuevo = new objeto;
            nuevo->id = id;
            nuevo->precio = precio;
            vec[pos] = nuevo;
            flotar(pos);
            pos++;
        }
    }
    objeto* desencolar(){
        objeto* desencolado = vec[1];
        swap(1,pos-1);
        vec[pos-1] = NULL;
        pos --;
        hundir(1);
        return desencolado;
    }
};


int main()
{
    // TODO
    int N;
    cin >> N;
    int* ids = new int[N];
    int pos;
    int precio;
    for(int i = 1; i<N+1 ; i++){
        cin >> pos;
        cin >> precio;
        if(precio < ids[pos]) ids[pos] = precio;
    }
    minHeap heap = minHeap(N);
    for(int i = 1; i<=N; i++){
        heap.encolar(i,ids[i]);
    }
    int K;
    cin >> K;
    for(int i = 1; i <= K; i++){
        objeto* desencolado = heap.desencolar();
        std::cout << std::to_string(desencolado->id);
        delete desencolado;
    }
    return 0;
}