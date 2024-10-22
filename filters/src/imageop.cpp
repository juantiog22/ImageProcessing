/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>
#include <math.h>
#include <cassert>

using namespace std;

Image Image::Crop(int filas, int col, int filas_sub, int cols_sub) const{

    Image subimage(filas_sub, cols_sub);

    for(int i=0; i<filas_sub; i++){
        for(int j=0; j<cols_sub; j++){
            subimage.set_pixel(i, j, this->get_pixel(filas+i, col +j));
        }
    }

    return subimage;
}

Image Image::Zoom2X(int fila, int col, int lado) const {

    Image subimage(2*lado-1, 2*lado-1);
    int aux1=0, aux2=0;


    //Copiamos la imagen en otra de dimension 2*N-1
    for(int i=0; i<2*lado-1; i+=2){
        for(int j=0; j<2*lado-1; j+=2){
            subimage.set_pixel(i,j,this->get_pixel(fila+aux1, col+aux2));
            aux2++;
        }
        aux1++;
        aux2=0;
    }

    //Hacemos la media de las filas
    for(int i=1; i<2*lado-1; i+=2){
        for(int j=0; j<2*lado-1; j+=2) {
            float media = subimage.get_pixel(i-1, j) + subimage.get_pixel(i+1, j);
            media /= 2;
            subimage.set_pixel(i,j, (byte)roundf(media));
        }
    }

    //Hacemos la media de las columnas
    for(int i=0; i<2*lado-1; i+=2){
        for(int j=1; j<2*lado-1; j+=2) {
            float media = subimage.get_pixel(i, j-1) + subimage.get_pixel(i, j+1);
            media /= 2;
            subimage.set_pixel(i,j, (byte)roundf(media));
        }
    }

    //Hacemos la media de las diagonales
    for(int i=1; i<2*lado-1; i+=2) {
        for (int j = 1; j < 2 * lado - 1; j += 2) {
            float media = subimage.get_pixel(i-1, j-1) + subimage.get_pixel(i+1, j-1) + subimage.get_pixel(i-1, j+1) + subimage.get_pixel(i+1, j+1);
            media /= 4;
            subimage.set_pixel(i,j, (byte)roundf(media));
        }
    }


    return subimage;

}

double Image::Mean(int i, int j, int height, int width) const {

    double total=0;

    for(int a=i;a<width+i;a++){
        for(int h=j;h<height+j;h++){
            total+=this->get_pixel(a,h);
        }
    }

    return round(total/(height*width));
}



Image Image::Subsample(int factor) const {

    int num_col= floor(this->get_cols()/factor);
    int num_filas= floor(this->get_rows()/factor);
    float media;
    Image icono(num_filas,num_col);

    if(factor<0){
        cout<<"El parametro introducido es incorrecto";
        exit(0);
    }

    for(int i=0;i<num_filas;i++){
        for(int j=0;j<num_col;j++){
            media=  this->Mean(i*factor,j*factor,factor,factor);
            icono.set_pixel(i,j,(byte) media);
        }
    }

    return icono;
}

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2){

    float a, b, min, max;
    float pixel;
    byte thispixel;

    if (0 > (in1, in2, out1, out2) && 255 < (in1, in2, out1, out2)  && in1 < in2 && out1 < out2){
        cout <<"Los parametros introducidos son incorrectos";
        exit(0);
    }

    for (int i = 0; i < this->get_rows() * this->get_cols(); i++) {
        pixel = 0;
        thispixel = this->get_pixel(i);

        if (0 <= thispixel && thispixel < in1)
            a = 0, b = (float) in1, min = 0, max = (float) out1;

        if (in1 <= thispixel && thispixel <= in2)
            a = (float) in1, b = (float) in2, min = (float) out1, max = (float) out2;

        if (in2 < thispixel && thispixel <= 255)
            a = (float) in2, b = 255, min = (float) out2, max = 255;

        pixel = (min + (((max - min) / (b - a)) * ((float)thispixel - a)));
        this->set_pixel(i, (byte)roundf(pixel));
    }

}

void Image::ShuffleRows() {
    const int p =  9973  ;
    Image temp(rows,cols);
    int newr;
    for (int r=0; r<rows; r++){
        newr = (r*p) % rows;
        for (int c=0; c<cols;c++)
            temp.set_pixel(r,c,get_pixel(newr,c));
    }
    Copy(temp);
}



