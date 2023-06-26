#ifndef TESTES_H_INCLUDED
#define TESTES_H_INCLUDED

#include "Dominios.h"
#include "Entidades.h"

class TUDominios {
    protected:
        virtual void setUp() = 0;
        virtual void tearDown() = 0;
        virtual void testarCenarioValido() = 0;
        virtual void testarCenarioInvalido() = 0;
        bool estado;
    public:
        virtual ~TUDominios() {}
        const bool sucesso = true;
        const bool falha = false;
        bool run();
};

class TUClasse : public TUDominios {
    private:
        const string valorValido = "FUMACA";
        const string valorInvalido = "MOTOCICLETA";
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        void testarCenarioInvalido() override;
        Classe *classe;
};

class TUCodigo : public TUDominios {
    private:
        const string valorValido = "abc123";
        const string valorInvalido = "12addc";
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        void testarCenarioInvalido() override;
        Codigo *codigo;
};

class TUData : public TUDominios {
    private:
        const string valorValido = "30/JAN/2023";
        const string valorInvalido = "32/FEV/2020";
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        void testarCenarioInvalido() override;
        Data *data;
};

class TUMatricula : public TUDominios {
    private:
        const string valorValido = "1234563";
        const string valorInvalido = "1234569";
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        void testarCenarioInvalido() override;
        Matricula *matricula;
};

class TUResultado : public TUDominios {
    private:
        const string valorValido = "APROVADO";
        const string valorInvalido = "reprovado";
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        void testarCenarioInvalido() override;
        Resultado *resultado;
};

class TUSenha : public TUDominios {
    private:
        const string valorValido = "Ab23c1";
        const string valorInvalido = "aa11@e";
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        void testarCenarioInvalido() override;
        Senha *senha;
};

class TUTelefone : public TUDominios {
    private:
        const string valorValido = "+1234567";
        const string valorInvalido = "+123456";
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        void testarCenarioInvalido() override;
        Telefone *telefone;
};

class TUTexto : public TUDominios {
    private:
        const string valorValido = "Ola, bom dia!";
        const string valorInvalido = "luís felipe";
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        void testarCenarioInvalido() override;
        Texto *texto;
};

class TUEntidades {
    protected:
        virtual void setUp() = 0;
        virtual void tearDown() = 0;
        virtual void testarCenarioValido() = 0;
        const string valorValidoClasse = "FUMACA";
        const string valorValidoCodigo = "abc123";
        const string valorValidoData = "26/MAR/2020";
        const string valorValidoMatricula = "1234563";
        const string valorValidoResultado = "APROVADO";
        const string valorValidoSenha = "123456";
        const string valorValidoTelefone = "+1234567";
        const string valorValidoTexto = "Ola, bom dia!";
        bool estado;
    public:
        const bool sucesso = true;
        const bool falha = false;
        bool run();

};

class TUDesenvolvedor : public TUEntidades {
    private:
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        Desenvolvedor *desenvolvedor;
};

class TUTeste : public TUEntidades {
    private:
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        Teste *teste;
};

class TUCasoDeTeste : public TUEntidades {
    private:
        void setUp() override;
        void tearDown() override;
        void testarCenarioValido() override;
        CasoDeTeste *casoTeste;
};
#endif // TESTES_H_INCLUDED
