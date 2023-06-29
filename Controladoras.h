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
        IACasoDeTeste *cntrACasoDeTeste;
    public:
        void executar();
        void setCntrAAutenticacao(IAAutenticacao*);
        void setCntrADesenvolvedor(IADesenvolvedor*);
        void setCntrATeste(IATeste*);
        void setCntrACasoDeTeste(IACasoDeTeste*);
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

void inline CntrAControle::setCntrACasoDeTeste(IACasoDeTeste* cntr) {
    cntrACasoDeTeste = cntr;
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
        void cadastrar(Matricula);
        void visualizar(Matricula);
        void editar(Matricula);
        bool descadastrar(Matricula);
    public:
        void executar(Matricula);
        void setCntrISTeste(ISTeste*);
};

void inline CntrIATeste::setCntrISTeste(ISTeste* cntrISTeste) {
    this->cntrISTeste = cntrISTeste;
}

class CntrIACasoDeTeste: public IACasoDeTeste {
    private:
        ISCasoDeTeste *cntrISCasoDeTeste;
        void cadastrar(Matricula);
        void visualizar(Matricula);
        void editar(Matricula);
        bool descadastrar(Matricula);
    public:
        void executar(Matricula);
        void setCntrISCasoDeTeste(ISCasoDeTeste*);
};

void inline CntrIACasoDeTeste::setCntrISCasoDeTeste(ISCasoDeTeste* cntrISCasoDeTeste) {
    this->cntrISCasoDeTeste = cntrISCasoDeTeste;
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
    private:
        list<CasoDeTeste> visualizarCasosDeTestes(Codigo);
    public:
        bool cadastrar(const Teste&);
        Teste visualizar(const Codigo&);
        bool editar(const Teste&);
        bool descadastrar(const Codigo&);
};

class CntrISCasoDeTeste: public ISCasoDeTeste {
    public:
        bool cadastrar(const CasoDeTeste&);
        CasoDeTeste visualizar(const Codigo&);
        bool editar(const CasoDeTeste&);
        bool descadastrar(const Codigo&);
};

#endif // CONTROLADORAS_H_INCLUDED
