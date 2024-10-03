#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
class minHeap
{
private:
    int capacidad;
    int pos; //primeo libre
    int* vec;

    bool lleno(){
        return pos > capacidad;
    }

    bool vacio(){
        return pos == 1;
    }

    void swap(int pos1, int pos2){
        int aux = vec[pos1];
        vec[pos1] = vec[pos2];
        vec[pos2] = aux;
    }
    int padre(int pos){
        return pos/2;
    }
    bool comparar(int pos, int posPadre){
        return vec[pos] < vec[posPadre];
    }

    void flotar(int pos){
        if(pos == 1) return;
        int posPadre = padre(pos);
        if(comparar(pos,posPadre)){
            swap(pos,posPadre);
            flotar(posPadre);
        }
    }
public:
     minHeap(int tam){
        vec = new int[tam+1];
     };
    ~minHeap();
};


int main()
{
    // TODO
    return 0;
}