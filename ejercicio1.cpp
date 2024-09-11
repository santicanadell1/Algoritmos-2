#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
//funciones auxiliares
int max(int a, int b){
    return a > b ? a : b;
}
class Biblioteca {
    private:
        struct nodoAvl{
            int id;
            char* titulo;
            nodoAvl* der;
            nodoAvl* izq;
            int altura;
            bool habilitado;
        };
        //funciones auxiliares
        
        int alturaAux(nodoAvl* nodo){
            if(!nodo) return 0;
            return 1 + max(alturaAux(nodo->der),alturaAux(nodo->izq));
        }
        int balanceAux(nodoAvl* nodo){
            int alturaDer = nodo->der? nodo->der->altura : 0;
            int alturaIzq = nodo->izq? nodo->izq->altura : 0;
            return alturaDer - alturaIzq;
        }
        nodoAvl* rotaIzq(nodoAvl* A){
            nodoAvl* B = A->der;
            nodoAvl* T2 = B->izq;
            A->der = T2;
            B->izq = A;
            A->altura = 1 + max(A->der->altura,A->izq->altura);
            B->altura = 1 + max(B->der->altura, B->izq->altura);
            return B;
        }
        nodoAvl* rotaDer(nodoAvl* B){
            nodoAvl* A = B->izq;
            nodoAvl* T2 = A->der;
            B->izq = T2;
            A->der = B;
            B->altura = 1 + max(B->der->altura, B->izq->altura);
            A->altura = 1 + max(A->der->altura,A->izq->altura);
            return A;
        }
        nodoAvl* insertarAux(nodoAvl*nodo,int d, char* titulo){
            std::cout << "inserta numero";
            if(!nodo){
                nodoAvl* nuevo = new nodoAvl;
                nuevo->altura = 1;
                nuevo->id = d;
                nuevo->titulo = titulo;
                nuevo->habilitado = true;
                nuevo->der = NULL;
                nuevo->izq = NULL;
                cantHab ++;
                cantTotal;
                return nuevo;
            }
            if(nodo->id < d){
                nodo->der = insertarAux(nodo->der,d,titulo);
            }
            else if(nodo->id > d){
                nodo->izq = insertarAux(nodo->izq,d,titulo);
            }
            else{
                nodo->titulo = titulo;
                nodo->habilitado = true;
                return nodo;
            }
            nodo->altura = 1+max(alturaAux(nodo->izq), alturaAux(nodo->der));
            int balance = balanceAux(nodo);
            bool desbalanceDer = balance > 1;
            bool desbalanceIzq = balance < -1;
            //caso der-der
            if(desbalanceDer && nodo->der->id < d){
                return rotaIzq(nodo);
            }
            //caso der-izq
            if(desbalanceDer && nodo->der->id > d){
                nodo->der = rotaDer(nodo->der);
                return rotaIzq(nodo);
            }
            //caso izq-der
            if(desbalanceIzq && nodo->izq->id < d){
                nodo->izq =rotaIzq(nodo->izq);
                return rotaDer(nodo);
            }
            //caso izq-izq
            if(desbalanceIzq && nodo->izq->id > d){
                return rotaDer(nodo);
            }
            return nodo;
        }

        void inOrderAux(nodoAvl* nodo){
            if(!nodo)return;
            inOrderAux(nodo->izq);
            std::cout << nodo->id << std::endl;
            inOrderAux(nodo->der);
        }

        void buscarAux(nodoAvl* nodo ,int d){
            if(!nodo){
                std::cout << "libro_no_encontrado";
            }
            else if(d > nodo->id){
                buscarAux(nodo->der , d);
            }
            else if(d < nodo->id){
                buscarAux(nodo->izq , d);
            }
            else{
                std::cout << nodo->titulo + ' ' + nodo->habilitado?'H':'D';
            }
        }
        
        void habilitarAux(nodoAvl* nodo,int d){
            if(!nodo){
               std::cout << "libro_no_encontrado"; 
            };
            if(nodo->id == d){
                if(nodo->habilitado){
                cantHab--;
                cantInhab++;
                }
                else{
                  cantHab++;
                cantInhab--;  
                }
                nodo->habilitado = !nodo->habilitado;
            }
            else if(nodo->id>d){
                habilitarAux(nodo->izq,d);
            }
            else if(nodo->id<d){
                habilitarAux(nodo->der,d);
            }
        }

        void cantLibrosAux(nodoAvl* nodo){
            std::cout << cantTotal + ' ' + cantHab + ' ' + cantInhab;
        }
        void destruirNodo(nodoAvl * nodo){
            if(!nodo){
                return;
            }
            destruirNodo(nodo->der);
            destruirNodo(nodo->izq);
            delete nodo;
            nodo = NULL;
        }

        //Atributos
        nodoAvl* raiz;
        int cantHab;
        int cantInhab;
        int cantTotal;
    public:
    //funciones publicas
        void insertar(int d, char* titulo){
            raiz = insertarAux(raiz,d,titulo);
        }
        int altura(){
            return raiz->altura;
        }
        void inOrder(){
            inOrderAux(raiz);
        }
        void buscar(int d){
            buscarAux(raiz ,d);
        }
        void habilitar(int id){
            habilitarAux(raiz,id);
        };
        void cantLibros(){
            cantLibrosAux(raiz);
        }
        void eliminarAVL(){
            destruirNodo(raiz);
        }

        
};

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) 
    {
        
    }
}