


#include <iostream>

#include <vector>

#include <queue>

#include <stdlib.h>
#include <time.h>

using namespace std;





class Grafo {

private:

    int numVertices;

    vector<vector<int>> matrizAdy;
    struct Vertice {
        int id;
        int distancia; 
        bool visitado;
    };
    vector<Vertice> vertices;
    vector<int>camino;

public:

    Grafo(int n) {

        numVertices = n;

        matrizAdy.resize(n, vector<int>(n, 0));
        camino.resize(numVertices, -1);
    }



    void agregarArista(int origen, int destino, int peso) {

        matrizAdy[origen][destino] = peso;//enlace

        matrizAdy[destino][origen] = peso;

    }
    void generarMatrizAleatoria() {
      
        for (int i = 0; i < matrizAdy.size(); i++) {
            Vertice newVertice = {i,INT_MAX,false};
            for (int j = 0; j < matrizAdy.size(); j++) {
                int x = rand() % 100;
                int aux = 0;
                if (x < 30) {
                    aux = 1 + rand() % 9;
                 
                }
                agregarArista(i, j, aux);
              
            }
            vertices.push_back(newVertice);
        }
        int contador = 0;
       
        for (int i = 0; i < matrizAdy.size(); i++) {
            for (int j = 0; j < matrizAdy.size(); j++) {
                if(matrizAdy[i][j] !=0 ){
                    contador++;
                }
            }
            if (contador == 0) { matrizAdy[i][rand() % numVertices]= 1 + rand() % 9; }
            contador = 0;
            
        }

    }

    void crearMatriz() {
        int aux=0;
        cout << " Ingresa el valor para: "<<endl;
        for (int i = 0; i < matrizAdy.size(); i++) {
            for (int j = 0; j < matrizAdy.size(); j++) {
                cout << "[ " << i << " , " << j << " ]";
                cin >> aux;
                agregarArista(i, j, aux);
            }
        }
      
    }


    void BFS(int origen) {

        vector<bool> visitado(numVertices, false);

        queue<int> cola;



        visitado[origen] = true;

        cola.push(origen);



        while (!cola.empty()) {

            int actual = cola.front();

            cola.pop();

            cout << actual << " ";



            for (int i = 0; i < numVertices; i++) {

                if (matrizAdy[actual][i] && !visitado[i]) {

                    visitado[i] = true;

                    cola.push(i);

                }

            }

        }

    }

    void mostrar() {
        for (int i = 0; i < matrizAdy.size(); i++) {
            for (int j = 0; j < matrizAdy.size(); j++) {
                cout << "[" << matrizAdy[i][j] << "]" << " ";
            }
            cout << endl;
        }
    }

    void algoritmoDijkstra(int inicio,int final) {
        if (inicio < 0 || inicio >= numVertices || final < 0 || final >= numVertices) {
            cout << endl;
            cout << "Los datos ingresados son invalidos"<<endl;
            return;
        }
        vertices[inicio].distancia = 0;

        for (int i = 0; i < numVertices - 1; i++) {
            int minDistancia = INT_MAX;
            int indicadorMin = -1;
            for (int j = 0; j < numVertices; j++) {
                if (vertices[j].visitado == false && vertices[j].distancia < minDistancia) {
                    minDistancia = vertices[j].distancia;
                    indicadorMin = j;
                }
            }

            if (indicadorMin == -1) {
                break;
            }

            vertices[indicadorMin].visitado = true;

            for (int j = 0; j < numVertices; j++) {
                if (!vertices[j].visitado  && matrizAdy[indicadorMin][j]&& vertices[indicadorMin].distancia != INT_MAX
                    && vertices[indicadorMin].distancia + matrizAdy[indicadorMin][j] < vertices[j].distancia) {
                    vertices[j].distancia = vertices[indicadorMin].distancia + matrizAdy[indicadorMin][j];
                    camino[j] = indicadorMin;
                }
            }
        }
        if (vertices[final].distancia == INT_MAX) {
            cout << "No existe un camino válido entre los vértices " << inicio << " y " << final << "." << endl;
        }
        else {
            cout << "Camino minimo desde el vertice " << inicio << " al vértice " << final << ": ";
            vector<Vertice> caminoMinimo;
            int verticeActual = final;
            while (verticeActual != -1) {
                caminoMinimo.push_back(vertices[verticeActual]);
                verticeActual = camino[verticeActual];
            }

            for (int i = caminoMinimo.size() - 1; i >= 0; --i) {
                cout << vertices[i].id;
                if (i != 0) {
                    cout << " -> ";
                }
            }
            cout << endl;
            cout << "Distancia minima: " << vertices[final].distancia << endl;
        }




    }
};

int validarN(int min, int max) {
    int opcion;
    do
    {
        cin >> opcion;
        if (opcion < min || opcion > max) {
            cout << "Valor ingresado es incorrecto " << endl;
        }
    } while (opcion < min ||opcion>max);
    return opcion;
}
void generacionAutomatica() {
    int origen;
    int destino;
    srand(time(NULL));
    int n;
    cout << "INGRESA UN NUMERO DEL 5 AL 15" << endl;
    n = validarN(5, 15);
    Grafo* grafo = new Grafo(n);
    //grafo->crearMatriz();
    grafo->generarMatrizAleatoria();
    grafo->mostrar();
    cout << endl;
    cout << "INGRESE EL VERTICE ORIGEN" << endl;

    origen = validarN(0, n);
    cout << "INGRESE EL VERTICE DESTINO" << endl;

    destino = validarN(0, n);
    grafo->algoritmoDijkstra(origen, destino);
}

void ingresoManual() {
    int origen;
    int destino;
    srand(time(NULL));
    int n;
    cout << "INGRESA UN NUMERO DEL 5 AL 15" << endl;
    n = validarN(5, 15);
    Grafo* grafo = new Grafo(n);
    //grafo->crearMatriz();
    grafo->crearMatriz();
    grafo->mostrar();
    cout << endl;
    cout << "INGRESE EL VERTICE ORIGEN" << endl;

    origen = validarN(0, n);
    cout << "INGRESE EL VERTICE DESTINO" << endl;

    destino = validarN(0, n);
    grafo->algoritmoDijkstra(origen, destino);
}
int main()
{
    int opcion;
    do
    {
        cout << "INGRESE UNA OPCION" << endl;
        cout << "1.GENERACION AUTOMATICA DE LA MATRIZ" << endl;
        cout << "2.INGRESO MANUAL DEL PESO DE ARISTAS" << endl;
        opcion = validarN(1, 2);
        system("cls");
        switch (opcion)
        {
        case 1: generacionAutomatica(); break;
        case 2:ingresoManual(); break;
        default:
            break;
        }
    } while (opcion!=3);
   
}
