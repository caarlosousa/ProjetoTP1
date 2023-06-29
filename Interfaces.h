#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "acessoDB.h"
#include <stdexcept>

class ISAutenticacao {
    public:
        virtual bool autenticar(const Matricula&, const Senha&) = 0;
        virtual ~ISAutenticacao(){}
};

class ISDesenvolvedor {
    public:
        virtual bool cadastrar(const Desenvolvedor&) = 0;
        virtual Desenvolvedor visualizar(const Matricula&) = 0;
        virtual bool editar(const Desenvolvedor&) = 0;
        virtual bool descadastrar(const Matricula&) = 0;
        virtual ~ISDesenvolvedor(){}
};

class ISTeste {
    public:
        virtual bool cadastrar(const Teste&) = 0;
        virtual Teste visualizar(const Codigo&) = 0;
        virtual bool editar(const Teste&) = 0;
        virtual bool descadastrar(const Codigo&) = 0;
        virtual ~ISTeste(){}
};

class ISCasoDeTeste {
    public:
        virtual bool cadastrar(const CasoDeTeste&) = 0;
        virtual CasoDeTeste visualizar(const CasoDeTeste&) = 0;
        virtual bool editar(const CasoDeTeste&) = 0;
        virtual bool descadastrar(const CasoDeTeste&) = 0;
        virtual ~ISCasoDeTeste(){}
};

class IAAutenticacao {
    public:
        virtual bool autenticar(Matricula*) = 0;
        virtual void setCntrISAutenticacao(ISAutenticacao*) = 0;
        virtual ~IAAutenticacao(){}
};

class IADesenvolvedor {
    public:
        virtual bool executar(Matricula) = 0;
        virtual void cadastrar() = 0;
        virtual void setCntrISDesenvolvedor(ISDesenvolvedor*) = 0;
        virtual ~IADesenvolvedor(){}
};

class IATeste {
    public:
        virtual void executar(Matricula) = 0;
        virtual void setCntrISTeste(ISTeste*) = 0;
        virtual ~IATeste(){}
};

class IACasoDeTeste {
    public:
        virtual void executar(Matricula) = 0;
        virtual void setCntrISCasoDeTeste(ISCasoDeTeste*) = 0;
        virtual ~IACasoDeTeste(){}
};

#endif // INTERFACES_H_INCLUDED
