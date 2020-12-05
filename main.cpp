#include<iostream>
#include<string>
#include<enrutador.h>
#include<vector>
#include<fstream>


using namespace std;
void crearRed(vector<Enrutador> &,string ,string);
void eliminadorEnrutadorVec(vector<Enrutador> &,string );
void eliminardeRedEnrutadores(string ,string &);
void imprimirTablaEnrutamiento(vector<Enrutador> red,string enrutador);
void imprimirRed(vector<Enrutador> );


int main(){

     vector<Enrutador> Red;
    string  RedEnrutadores,Relacion,Nrelacion,continuarPrograma="si",nuevoEnrutador,eliminarEnrutador;

    int opcionesPrograma;
    while(continuarPrograma=="si")
    {
        cout<<"Que desea realizar?\n1.Agregar Red de Enrutadores y su relacion desde consola.\n2.Agregar enrutador en la red.\n3.Eliminar enrutador de la red\n4.Agregar Red enrutadores desde fichero\n5.Imprimir tabla de enrutamiento individual\n6.Imprimir red:";
        cin>>opcionesPrograma;
        switch (opcionesPrograma) {
        case 1:
        {
            cout<<"Ingrese el nombre de los enrutadores de la red a trabajar: ";cin>>RedEnrutadores;
            cout<<"\nIngrese enlace-costo de enrutadores\nde la siguiente manera 'AB#-', no olvidar poner al final el simbolo '-':";cin>>Relacion;cout<<endl;
            if(Relacion[Relacion.size()-1]=='-')
            {
                crearRed(Red,RedEnrutadores,Relacion);
            }
            else
            {
                cout<<"\nIngreso mal la ultima relacion, por favor no olvide ubicar al final el simbolo '-'"<<endl;
            }
            break;
        }
        case 2:
        {
            bool find=0;
            cout<<"\nIngrese el nombre del nuevo enrutador:";cin>>nuevoEnrutador;cout<<endl;
            cout<<"\nIngrese enlace/costo del nuevo enrutador\nde la siguiente manera 'AB#-', no olvidar poner al final el simbolo '-':";cin>>Nrelacion;cout<<endl;
            RedEnrutadores+=nuevoEnrutador;Relacion+=Nrelacion;
            for(auto it=Red.begin();it!=Red.end();it++){
                if(it->getNombreNodo()==nuevoEnrutador){
                    find=1;
                }
            }
            if(find==0){
                Red.clear();
                crearRed(Red,RedEnrutadores,Relacion);
            }
            else{
                cout<<"\nEl enrutador ya existe"<<endl;
            }



            break;
        }
        case 3:
        {   bool find2=0;string rela;
            cout<<"\nIngrese el nombre del enrutador a eliminar:";cin>>eliminarEnrutador;cout<<endl;
            for(auto it=Red.begin();it!=Red.end();it++){
                if(it->getNombreNodo()==eliminarEnrutador){
                    find2=1;break;
                 }
            }
            if(find2==1){
                int p=RedEnrutadores.find(eliminarEnrutador);
                RedEnrutadores.erase(p,p+1);
                eliminardeRedEnrutadores(eliminarEnrutador,Relacion);
                eliminadorEnrutadorVec(Red,eliminarEnrutador);
            }
            else{
                cout<<"\nEl enrutador no existe"<<endl;
            }



            break;
        }
        case 4:
        {
            string NombreFichero,caracter1,caracter2;bool final=false;
            ifstream leer;
            RedEnrutadores="";//reset variable
            cout<<"\nIngrese el nombre del archivo (sin extension .txt): ";cin>>NombreFichero;
            NombreFichero+=".txt";
            leer.open(NombreFichero);
            if(!leer.fail())
            {
                while(final==false)//ciclo para enrutadores
                {
                    leer>>caracter1;
                    if(caracter1!="-")
                    {
                        RedEnrutadores+=caracter1;
                    }
                    else
                    {
                        final=true;
                    }
                }

                while(!leer.eof())//ciclo definir relacion de enrutadores
                {
                    leer>>caracter1;
                    Relacion+=caracter1;
                    leer>>caracter1;
                    Relacion+=caracter1;
                    leer>>caracter1;
                    Relacion+=caracter1;
                    Relacion+="-";
                }
                crearRed(Red,RedEnrutadores,Relacion);
            }
            else
            {
                cout<<"\nEl archivo no exite"<<endl;
            }
            break;
        }
        case 5:
        {
            string nombreEnrutador;
            cout<<"\nDe que enrutador desea observar su tabla?: ";cin>>nombreEnrutador;
            imprimirTablaEnrutamiento(Red,nombreEnrutador);
            break;
        }
        case 6:
        {
            imprimirRed(Red);
        }
        }

        cout<<"\nDesea continuar en el programa?: ";cin>>continuarPrograma;
        //system("pause");
        system("CLS");
    }

    return 0;
}
void crearRed(vector<Enrutador> &Red,string RedEnrutadores, string Relacion)
{
    string itm;
    for(int i=0;i<RedEnrutadores.size();i++)
    {
        itm=RedEnrutadores[i];//creo nombre para objeto
        Enrutador enrutador(itm);//genero un objeto enrutador
        enrutador.inputtablaEnrutamiento(Relacion);
        Red.push_back(enrutador);
    }
}


void eliminadorEnrutadorVec( vector<Enrutador> &Red,string enrutador){

    for(auto it=begin(Red);it!=end(Red);it++){

        if(it->getNombreNodo()==enrutador)
        {
            Red.erase(it);
        }
    }
    for(auto it=begin(Red);it!=end(Red);it++){
        map<string,int> mapa=it->getTablaEnrutamiento();
        for(auto par=mapa.begin();par!=mapa.end();par++){
            if(par->first==enrutador){
                mapa.erase(par);
                break;
            }
        }
        it->setTablaEnrutamiento(mapa);
    }
}

void imprimirTablaEnrutamiento(vector<Enrutador> red,string enrutador){
    for(auto it=begin(red);it!=end(red);it++){
        if(it->getNombreNodo()==enrutador)
        {
            cout<<"\nTabla de enrutamiento de: "<<it->getNombreNodo()<<endl;
            map<string,int> nuevo=it->getTablaEnrutamiento();
            cout<<"Enrutador=valor enlace"<<endl;
            for(auto par=nuevo.begin();par!=nuevo.end();par++){
                cout<<par->first<<" = "<<par->second<<endl;
            }
        }
    }
}

void imprimirRed(vector<Enrutador> red){

    for(auto it=begin(red);it!=end(red);it++){
        cout<<"\nTabla de enrutamiento de: "<<it->getNombreNodo()<<endl;
        map<string,int> nuevo=it->getTablaEnrutamiento();
        cout<<"Enrutador=valor enlace"<<endl;
        for(auto par=nuevo.begin();par!=nuevo.end();par++){
            cout<<par->first<<" = "<<par->second<<endl;
        }
    }
}

void eliminardeRedEnrutadores(string enrutador,string &RedEnrutadores){
    int tamRed=RedEnrutadores.size();

    vector<int> pos;
    vector<int> pos1;
    for(int i=0;i<tamRed;i++){//ciclo copia RedEnrutadores sin '-'
        if(RedEnrutadores[i]=='-'){
             pos.push_back(i);
        }
    }

    for(auto it=pos.begin();it!=pos.end();it++){
        int posR=RedEnrutadores.find(enrutador);
        if(posR>=0){
        for(int i=0;i<tamRed;i++){//ciclo copia RedEnrutadores sin '-'
            if(RedEnrutadores[i]=='-'){
                 pos1.push_back(i);
            }
        }
        for(auto it1=pos1.begin();it1!=pos1.end();it1++){
            if(posR<*it1 & it1==pos1.begin()){
                RedEnrutadores.erase(0,*it+1);
            }
            else if(posR>*it1 & posR<*(it1+1) ){
                RedEnrutadores.erase(*it+1,*(it+1));
            }
        }
        pos1.clear();
    }
        else{
            break;
        }
   }
}
