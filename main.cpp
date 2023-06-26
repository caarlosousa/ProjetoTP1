#include <iostream>
#include <string>
#include "Dominios.h"
#include "Entidades.h"
#include "Interfaces.h"
#include "Controladoras.h"

using namespace std;

int main(){
    CntrAControle *cntrAControle;
    IAAutenticacao *cntrAAutenticacao;
    IADesenvolvedor *cntrADesenvolvedor;
    //IATeste *cntrATeste;

    cntrAControle = new CntrAControle();
    cntrAAutenticacao = new CntrIAAutenticacao();
    cntrADesenvolvedor = new CntrIADesenvolvedor();
    //cntrATeste = new CntrIATeste();

    ISAutenticacao *cntrISAutenticacao;
    ISDesenvolvedor *cntrISDesenvolvedor;
    //ISTeste *cntrISTeste;

    cntrISAutenticacao = new CntrISAutenticacao();
    cntrISDesenvolvedor = new CntrISDesenvolvedor();
    //cntrISTeste = new CntrISTeste();

    cntrAControle->setCntrAAutenticacao(cntrAAutenticacao);
    cntrAControle->setCntrADesenvolvedor(cntrADesenvolvedor);
    //cntrAControle->setCntrATeste(cntrATeste);

    cntrAAutenticacao->setCntrISAutenticacao(cntrISAutenticacao);
    cntrADesenvolvedor->setCntrISDesenvolvedor(cntrISDesenvolvedor);
    //cntrATeste->setCntrISTeste(cntrISTeste);

    cntrAControle->executar();

    return 0;
}
