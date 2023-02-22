#include<iostream>
#include"Funciones.h"

int main(int argc, char*argv[]){
    if(argc!=2){
        std::cerr<<"Error in number of arguments"<<std::endl;
        return -1;
    }
    else{

       Funciones leerArchivo;  
       leerArchivo.VerificacionDeArchivo(argv[1]);
    }
    return 0;
}