#ifndef CONTROLADORAS_H_INCLUDED
#define CONTROLADORAS_H_INCLUDED

#include "Interfaces.h"

#define CLR_SCR system("cls");

class CntrAControle {
    private:
        Matricula matricula;
        IAAutenticacao *cntrAAutenticacao;
        IADesenvolvedor *cntrADesenvolvedor;
        IATeste *cntrATeste;
    public:
        void executar();
        void setCntrAAutenticacao(IAAutenticacao*);
        void setCntrADesenvolvedor(IADesenvolvedor*);
        void setCntrATeste(IATeste*);
};

void inline CntrAControle::setCntrAAutenticacao(IAAutenticacao* cntr) {
    cntrAAutenticacao = cntr;
}

void inline CntrAControle::setCntrADesenvolvedor(IADesenvolvedor* cntr) {
    cntrADesenvolvedor = cntr;
}

void inline CntrAControle::setCntrATeste(IATeste* cntr) {
    cntrATeste = cntr;
}

class CntrIAAutenticacao: public IAAutenticacao {
    private:
        ISAutenticacao *cntrISAutenticacao;
    public:
        bool autenticar(Matricula*);
        void setCntrISAutenticacao(ISAutenticacao*);
};

void inline CntrIAAutenticacao::setCntrISAutenticacao(ISAutenticacao* cntrISAutenticacao) {
    this->cntrISAutenticacao = cntrISAutenticacao;
}

class CntrIADesenvolvedor: public IADesenvolvedor {
    private:
        ISDesenvolvedor *cntrISDesenvolvedor;
        void visualizar(Matricula);
        void editar(Matricula);
        bool descadastrar(Matricula);
    public:
        bool executar(Matricula);
        void cadastrar();
        void setCntrISDesenvolvedor(ISDesenvolvedor*);
};

void inline CntrIADesenvolvedor::setCntrISDesenvolvedor(ISDesenvolvedor *cntrISDesenvolvedor) {
    this->cntrISDesenvolvedor = cntrISDesenvolvedor;
}

class CntrIATeste: public IATeste {
    private:
        ISTeste *cntrISTeste;
    public:
        void executar(Matricula);
        void setCntrISTeste(ISTeste*);
};

void inline CntrIATeste::setCntrISTeste(ISTeste* cntrISTeste) {
    this->cntrISTeste = cntrISTeste;
}

class CntrISAutenticacao: public ISAutenticacao {
    public:
        bool autenticar(const Matricula&, const Senha&);
};

class CntrISDesenvolvedor: public ISDesenvolvedor {
    private:
        list<Teste> visualizarTestes(Matricula);
        list<CasoDeTeste> visualizarCasosDeTestes(Matricula);
    public:
        bool cadastrar(const Desenvolvedor&);
        Desenvolvedor visualizar(const Matricula&);
        bool editar(const Desenvolvedor&);
        bool descadastrar(const Matricula&);
};

class CntrISTeste: public ISTeste {
    public:
        bool cadastrar(const Teste&);
        bool visualizar(const Teste&);
        bool editar(const Teste&);
        bool descadastrar(const Teste&);
};

#endif // CONTROLADORAS_H_INCLUDED
