#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include<string>
#include<map>
#include<vector>
using namespace std;

class Enrutador
{
    string NombreNodo;
    map<string,int> tablaEnrutamiento;

public:

    Enrutador();
    Enrutador(string nombre);
    void inputtablaEnrutamiento(string relacion);
    map<string, int> getTablaEnrutamiento();
    string getNombreNodo() const;
    void setTablaEnrutamiento(map<string, int> &tabla);
    //void eliminarEnrutador(map<string,int> tabla,string enrutador);


};

#endif // ENRUTADOR_H
