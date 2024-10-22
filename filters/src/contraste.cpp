//
// Created by jdrgj on 14/10/2022.
//


#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <image.h>


using namespace std;

int main(int argc, char *argv[]) {

    char *origen, *destino;
    byte e1, e2, s1, s2;
    Image image;

    if(argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: Contraste FichImagenOriginal> <FichImagenDestino>\n";
        exit (1);
    }

    //Obtener parámetros
    origen = argv[1];
    destino = argv[2];
    e1 = (byte)atoi(argv[3]);
    e2 = (byte)atoi(argv[4]);
    s1 = (byte)atoi(argv[5]);
    s2 = (byte)atoi(argv[6]);

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

    Image contrasteimage(image);
    contrasteimage.AdjustContrast(e1, e2, s1, s2);


    // Guardar la imagen resultado en el fichero
    if (contrasteimage.Save(destino))
        cout << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la imagen resultado
    cout << endl;
    cout << "Dimensiones de " << destino << ":" << endl;
    cout << "   Imagen   = " << contrasteimage.get_rows()  << " filas x " << contrasteimage.get_cols() << " columnas " << endl;

    return 0;

}