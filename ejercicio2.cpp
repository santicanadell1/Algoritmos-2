#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

class Biblioteca {
    private:
        struct libro{
            int id;
            string titulo;
            bool habilitado;
        };
        //funciones auxiliares
        int normalizado(int c, int l){
            return abs(c)%l;
        }
        int funcionHash1(int c){
            return c % largo;
        }
        int funcionHash2(int c){
            return (c*2 % largo)+ 1;
        }
        int dobleHash(int c, int i) {
        return (funcionHash1(c) + i * funcionHash2(c)) % largo;
        }
        void rehash(){
            largo = largo * 2;
            delete[] ocupado;
            ocupado = new bool[largo]();
            libro** nuevo = new libro*[largo];
            for(int i = 0; i< largo/2; i++){
                if(hash[i]){
                    int clave = hash[i]->id;
                    int j = 0;
                    int bucket = dobleHash(clave,j);
                    while(ocupado[clave]){
                        j++;
                        bucket = dobleHash(clave,j);
                    }
                    ocupado[bucket] = true;
                    nuevo[bucket] = hash[i];
                }
            }
            delete[] hash;
            hash = nuevo;
        }
        void insertarAux( int d , string nombre){
            if(cantElem >= 0.5*largo){
                rehash();
            }
            int intento = 0;
            int indice=dobleHash(d,intento);
            while(ocupado[indice] && hash[indice]->id != d){
                intento ++;
                indice= dobleHash(d,intento);
            }
            if(hash[indice]->id == d){
                hash[indice]->titulo = nombre;
            }
            else{
            libro* nuevo = new libro;
            nuevo->habilitado = true;
            cantHab++;
            nuevo->id = d;
            nuevo->titulo = nombre;
            hash[indice] = nuevo;
            ocupado[indice] = true;
            cantElem++;
            }
        }
        void buscarAux(int d){
            int intento = 0;
            int indice=dobleHash(d,intento);
            while(ocupado[indice]&&hash[indice]->id != d){
                intento ++;
                indice= dobleHash(d,intento);
            }
            if(hash[indice]->id == d){
                std::cout << hash[indice]->titulo + " " + (hash[indice]->habilitado? "H":"D");
            }else{
                std::cout << "libro_no_encontrado";
            }
        }
        void habilitarAux(int d){
            int intento = 0;
            int indice=dobleHash(d,intento);
            while(ocupado[indice]&&hash[indice]->id != d){
                intento ++;
                indice= dobleHash(d,intento);
            }
            if(hash[indice]->id == d){
                if(hash[indice]->habilitado){
                cantHab--;
                cantInhab++;
                }
                else{
                  cantHab++;
                cantInhab--;  
                }
                hash[indice]->habilitado = !hash[indice]->habilitado;
            }else{
                std::cout << "libro_no_encontrado";
            }
        }
        void cantLibrosAux(){
            std::cout << cantElem + ' ' + cantHab + ' ' + cantInhab;
        }

        //atributos
        libro** hash;
        bool* ocupado;
        int largo;
        int cantElem;
        int cantHab;
        int cantInhab;
    public:
        Biblioteca(int lar){
            largo = lar;
            hash = new libro*[lar]();
            ocupado = new bool[lar]();
            cantElem=0;
            cantHab = 0;
            cantInhab = 0;
        }
        void insertar(int d , string nombre){
            insertarAux(d, nombre);
        }
        void buscar(int d){
            buscarAux(d);
        }
        void habilitar(int d){
            habilitarAux(d);
        }
    
        void cantLibros(){
             cantLibrosAux();
        }
};
int main() {
    int N;
    cin >> N;  // Leer el número de operaciones
    Biblioteca biblioteca(30);

    for (int i = 0; i < N; ++i) {
        string operacion;
        cin >> operacion;

        if (operacion == "ADD") {
            int id;
            string titulo;
            cin >> id >> titulo;
            biblioteca.insertar(id, titulo);
        } else if (operacion == "FIND") {
            int id;
            cin >> id;
            biblioteca.buscar(id);
        } else if (operacion == "TOGGLE") {
            int id;
            cin >> id;
            biblioteca.habilitar(id);
        } else if (operacion == "COUNT") {
            biblioteca.cantLibros();
        }
    }

    return 0;
}