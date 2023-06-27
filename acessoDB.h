#ifndef ACESSODB_H_INCLUDED
#define ACESSODB_H_INCLUDED

#include "Dominios.h"
#include "Entidades.h"
#include <list>
#include "sqlite3.h"
#include <iostream>
#include <curses.h> // LEMBRAR DE MUDAR PRA CONIO.H
#include <string>
#include <stdio.h>

//Classe ElementoResultado.

class ElementoResultado {
private:
        string nomeColuna;
        string valorColuna;
public:
        void setNomeColuna(const string&);
        string getNomeColuna() const;
        void setValorColuna(const string&);
        string getValorColuna() const;
};
//---------------------------------------------------------------------------
//Classe ElementoResultado.

inline string ElementoResultado::getNomeColuna() const {
        return nomeColuna;
}

inline string ElementoResultado::getValorColuna() const {
        return valorColuna;
}

//---------------------------------------------------------------------------
//Classe ComandoSQL.

class ComandoSQL {
private:
        const char *nomeBancoDados;
        sqlite3 *bd;
        char *mensagem;
        int rc;
        bool conectar();
        bool desconectar();
        static int callback(void *, int, char **, char **);

protected:
        static list<ElementoResultado> listaResultado;
        string comandoSQL;
public:
        ComandoSQL() {
             nomeBancoDados = "BD_ProjetoTP1.db.db";
        }
        bool executar();
};

//---------------------------------------------------------------------------
//DESENVOLVEDOR--------------------------------------------------------------

class ComandoLerSenha:public ComandoSQL {
public:
        ComandoLerSenha(Matricula);
        string getResultado();
};

//---------------------------------------------------------------------------

class ComandoPesquisarDesenvolvedor:public ComandoSQL {
public:
        ComandoPesquisarDesenvolvedor(Matricula);
        Desenvolvedor getResultado();
};

//---------------------------------------------------------------------------

class ComandoCadastrarDesenvolvedor:public ComandoSQL {
public:
        ComandoCadastrarDesenvolvedor(Desenvolvedor);
};

//---------------------------------------------------------------------------
class ComandoAtualizarDesenvolvedor:public ComandoSQL {
public:
        ComandoAtualizarDesenvolvedor(Desenvolvedor);
};

//----------------------------------------------------------------------------
class ComandoDeletarDesenvolvedor: public ComandoSQL {
public:
    ComandoDeletarDesenvolvedor(Matricula);
};

//TESTE-------------------------------------------------------------------
//-------------------------------------------------------------------------
class ComandoPesquisarTestes:public ComandoSQL {
public:
        ComandoPesquisarTestes();
        ComandoPesquisarTestes(Matricula);
        list<Teste> getResultado();
};
//------------------------------------------------------------------------------
class ComandoPesquisarDonoTeste:public ComandoSQL {
public:
    ComandoPesquisarDonoTeste(Codigo);
    Matricula getResultado();
};
//-------------------------------------------------------------------------------
class ComandoPesquisarTeste:public ComandoSQL {
public:
        ComandoPesquisarTeste(Codigo);
        Teste getResultado();
};

//---------------------------------------------------------------------------

class ComandoCadastrarTeste:public ComandoSQL {
public:
        ComandoCadastrarTeste(Teste);
};

//---------------------------------------------------------------------------
class ComandoAtualizarTeste:public ComandoSQL {
public:
        ComandoAtualizarTeste(Teste);
};

//----------------------------------------------------------------------------
class ComandoDeletarTeste: public ComandoSQL {
public:
    ComandoDeletarTeste(Codigo);
};
//---------------------------------------------------------------------------
//CASO DE TESTE--------------------------------------------------------------
class ComandoPesquisarCasosDeTestes:public ComandoSQL {
public:
    ComandoPesquisarCasosDeTestes();
    ComandoPesquisarCasosDeTestes(Matricula);
    ComandoPesquisarCasosDeTestes(Codigo);
    list<CasoDeTeste> getResultado();
};
//--------------------------------------------------------------------------
class ComandoPesquisarCodigosCasodeTestes: public ComandoSQL {
public:
    ComandoPesquisarCodigosCasodeTestes(Matricula);
    list<Codigo> getResultado();
};

//---------------------------------------------------------------------------

class ComandoCadastrarCasoDeTeste:public ComandoSQL {
public:
        ComandoCadastrarCasoDeTeste(CasoDeTeste);
};

//---------------------------------------------------------------------------
class ComandoAtualizarCasoDeTeste:public ComandoSQL {
public:
        ComandoAtualizarCasoDeTeste(CasoDeTeste);
};

//----------------------------------------------------------------------------
class ComandoDeletarCasoDeTeste: public ComandoSQL {
public:
    ComandoDeletarCasoDeTeste(Codigo);
};


#endif // ACESSODB_H_INCLUDED



