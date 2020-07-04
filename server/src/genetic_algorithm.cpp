#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int modelo [] = {3,3,3,3,3,3};
int largo = 6;
int num = 4;
int pressure = 3;
float mutation_chance = 0.2;
int max_valor = 3; // 1,2,3
int valor_modelo = 3;
int max_generaciones = 100;

// Crea la poblacion.
vector<vector<int>> crearPoblacion(int num, int largo){
    srand(time(NULL));
    vector<vector<int>> Poblacion;
    for(int i=0;i<num;i++){
        vector<int> individuo;
        for(int j=0;j<largo;j++){
            individuo.push_back(rand() % max_valor + 1); // Valores del 1 al 3
        }        
        Poblacion.push_back(individuo);
    }
    return Poblacion;
}

// Funcion Fitness
vector<vector<int>> fitness(vector<vector<int>> population){
    vector<vector<int>> puntuados;
    for (unsigned int i = 0; i < population.size(); i++) { 
        vector<int> individuo;
        int contador = 0;
        for (unsigned int j = 0; j < population[i].size(); j++){
            individuo.push_back(population[i][j]);
        }
        // Fitness -> Contar la cantidad de numeros repetidos valor_modelo que hay
        for (unsigned int i = 0; i < individuo.size(); i++){
            if(individuo[i]==valor_modelo){
                contador += 1;
            }
        }
        // Agrega un valor al inicio con la cantidad de numero iguales
        individuo.insert(individuo.begin(), contador);
        puntuados.push_back(individuo);
    }
    population = puntuados;
    return population;
}

// Funcion seleccion y reproduccion
vector<vector<int>> selection_and_reproduction(vector<vector<int>> population){

    // Calcula el fitness
    population = fitness(population);

    // Ordena el vector
    sort(population.begin(), population.end());

    // Eliminar el primer valor de cada vector
    vector<vector<int>> puntuados;
    for (unsigned int i = 0; i < population.size(); i++) { 
        vector<int> individuo;
        for (unsigned int j = 1; j < population[i].size(); j++){
            individuo.push_back(population[i][j]);
        }
        puntuados.push_back(individuo);
    }

    population = puntuados;

    // Esto selecciona los 'n' individuos del final, donde n viene dado por 'pressure'
    unsigned int individuos_quitar = population.size() - pressure;
    vector<vector<int>> selected;
    for (unsigned int i = 0; i < population.size(); i++) {
        vector<int> individuo2;
        if (i >= individuos_quitar){
            for (unsigned int j = 0; j < population[i].size(); j++){
                individuo2.push_back(population[i][j]);
            }
            selected.push_back(individuo2);
        }   
    }

    // Se mezcla el material genetico para crear nuevos individuos
    for (unsigned int ii = 0; ii < population.size()-pressure; ii++){
        unsigned int punto = (rand() % largo + 1) - 1; //Se elige un punto para hacer el intercambio

        // Se eligen dos padres
        int size_selected = selected.size();
        unsigned int padre1 = (rand() % size_selected + 1) - 1;
        unsigned int padre2 = (rand() % size_selected + 1) - 1;
        if (padre1==padre2){
            while (padre1==padre2){
                padre2 = (rand() % size_selected + 1) - 1;
            }
        }
        vector<vector<int>> padre;
        for (unsigned int i = 0; i < selected.size(); i++) {
            vector<int> individuo3;
            if (i==padre1 || i==padre2){
                for (unsigned int j = 0; j < selected[i].size(); j++){
                        individuo3.push_back(selected[i][j]);
                }
                padre.push_back(individuo3);
            }
        }
        
        //Se mezcla el material genetico del padre 1 en cada nuevo individuo
        for (unsigned int j = 0; j <= punto; j++){
            population[ii][j] = padre[0][j];
        }
            
        //Se mezcla el material genetico del padre 1 en cada nuevo individuo
        unsigned indice_mayor = population[0].size() - 1;
        for (unsigned int j=indice_mayor; j>=((indice_mayor - punto)); j--) {
            population[ii][j] = padre[1][j];
            if (j==0){
                break;
            }
        }
    }

    return population;
}

// Funcion mutacion
vector<vector<int>> mutation(vector<vector<int>> population){  

    for (unsigned int ii = 0; ii < population.size()-pressure; ii++){
        //Cada individuo de la poblacion (menos los padres) tienen una probabilidad de mutar
            float aleatorio = float((rand() % 9999)) / float(10000);
            if (aleatorio <= mutation_chance){
                
                //  Se elige un punto al azar
                unsigned int punto = (rand() % largo + 1) - 1;

                // y un nuevo valor para este punto
                int nuevo_valor = (rand() % max_valor + 1);
    
                //Es importante mirar que el nuevo valor no sea igual al viejo
                while (nuevo_valor == population[ii][punto]){
                    nuevo_valor = (rand() % max_valor + 1);
                }
                    
                //Se aplica la mutacion
                population[ii][punto] = nuevo_valor;
            }
    }

    return population;
}

int main(){

    vector<vector<int>> population = crearPoblacion(num,largo);

    // Se muestra la poblacion inicial
    cout << "Poblacion Inicial:" << endl;
    for (unsigned int i = 0; i < population.size(); i++) { 
        for (unsigned int j = 0; j < population[i].size(); j++) 
            cout << population[i][j] << " "; 
        cout << endl;
    }
    
    //Se evoluciona la poblacion
    for (int i = 0; i<max_generaciones; i++){
        population = selection_and_reproduction(population);
        population = mutation(population);
    }

    // Se muestra la poblacion final
    cout << "Poblacion Final:" << endl;
    for (unsigned int i = 0; i < population.size(); i++) { 
        for (unsigned int j = 0; j < population[i].size(); j++) 
            cout << population[i][j] << " "; 
        cout << endl; 
    }

    return 0;
}
