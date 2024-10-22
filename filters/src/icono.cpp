//
// Created by jdrgj on 11/10/2022.
//

#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>

#include <image.h>


using namespace std;


int main(int argc, char *argv[]){

    char *origen, *destino;
    int factor;
    Image image;

    if(argc != 4){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: Icono FichImagenOriginal> <FichImagenDestino>\n";
        exit (1);
    }

    //Obtener parámetros
    origen = argv[1];
    destino = argv[2];
    factor = atoi(argv[3]);

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


    //Calcular el subsample
    Image subsample;
    subsample = image.Subsample(factor);

    // Guardar la imagen resultado en el fichero
    if (subsample.Save(destino))
        cout << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la subimagen
    cout << endl;
    cout << "Dimensiones de " << destino << ":" << endl;
    cout << "   Imagen   = " << subsample.get_rows()  << " filas x " << subsample.get_cols() << " columnas " << endl;

    return 0;


}