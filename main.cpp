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
    IATeste *cntrATeste;
    IACasoDeTeste *cntrACasoDeTeste;

    cntrAControle = new CntrAControle();
    cntrAAutenticacao = new CntrIAAutenticacao();
    cntrADesenvolvedor = new CntrIADesenvolvedor();
    cntrATeste = new CntrIATeste();
    cntrACasoDeTeste = new CntrIACasoDeTeste();

    ISAutenticacao *cntrISAutenticacao;
    ISDesenvolvedor *cntrISDesenvolvedor;
    ISTeste *cntrISTeste;
    ISCasoDeTeste *cntrISCasoDeTeste;

    cntrISAutenticacao = new CntrISAutenticacao();
    cntrISDesenvolvedor = new CntrISDesenvolvedor();
    cntrISTeste = new CntrISTeste();
    cntrISCasoDeTeste = new CntrIACasoDeTeste();

    cntrAControle->setCntrAAutenticacao(cntrAAutenticacao);
    cntrAControle->setCntrADesenvolvedor(cntrADesenvolvedor);
    cntrAControle->setCntrATeste(cntrATeste);
    cntrAControle->setCntrACasoDeTeste(cntrACasoDeTeste);

    cntrAAutenticacao->setCntrISAutenticacao(cntrISAutenticacao);
    cntrADesenvolvedor->setCntrISDesenvolvedor(cntrISDesenvolvedor);
    cntrATeste->setCntrISTeste(cntrISTeste);
    cntrACasoDeTeste->setCntrISCasoDeTeste(cntrISCasoDeTeste);

    cntrAControle->executar();

    return 0;
}
