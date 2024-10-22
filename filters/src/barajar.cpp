//
// Created by jdrgj on 18/10/2022.
//
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <image.h>

using namespace std;
void chrono_experiment(Image image, int repetitions) {
    // Medimos el tiempo antes de iniciar el expermiento
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();

    // Realizamos el experimento tantas veces como indique repetitions, para tener cierta robustez
    // en el resultado (no todas las ejecuciones tardan lo mismo)
    for (int k = 0; k < repetitions; ++k){
        image.ShuffleRows();
    }

    // Medimos el tiempo al finalizar el experimento
    chrono::high_resolution_clock::time_point finish_time = chrono::high_resolution_clock::now();

    // Calculamos la diferencia entre el inicio y el final
    chrono::duration<double> total_duration = chrono::duration_cast<chrono::duration<double>>(finish_time - start_time);

    // Dividimos el tiempo total entre el número de repeticiones para obtener el tiempo medio por ejecución
    cout << image.size() << "\t" << total_duration.count()/repetitions << endl;
}

int main (int argc, char *argv[]){


    for (int i = 100; i < 5000; i += 100){
        Image image(100,i);
        chrono_experiment(image,50);
    }

    char *origen, *destino;
    Image image;

    if(argc != 3){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: Barajar FichImagenOriginal> <FichImagenDestino>\n";
        exit (1);
    }

    //Obtener parámetros
    origen = argv[1];
    destino = argv[2];

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    Image shuffleimage(image);
    shuffleimage.ShuffleRows();

    // Guardar la imagen resultado en el fichero
    if (shuffleimage.Save(destino))
        cout << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la subimagen
    cout << endl;
    cout << "Dimensiones de " << destino << ":" << endl;
    cout << "   Imagen   = " << shuffleimage.get_rows()  << " filas x " << shuffleimage.get_cols() << " columnas " << endl;

    return 0;

}