#ifndef DOMINIOS_H_INCLUDED
#define DOMINIOS_H_INCLUDED

#include <string>
#include <iostream>
#include <unordered_set>
#include <stdexcept>
#include <regex>

using namespace std;

/**
 * @brief Classe abstrata para representar os dom&iacute;nios de valores das classes.
 *
 * Esta classe define a interface comum para todas as classes que representam um dom&iacute;nio de valores.
 * Ela fornece m&eacute;todos para definir e obter o valor do dom&iacute;nio.
 * Todos os m&eacute;todos fornecidos s&atilde;o. herdados pelas classes do tipo Dom&iacute;nio, com cada uma
 * delas implementando o seu padr&atilde;o de valida&ccedil;&atilde;o.
 */
class Dominios {
    private:
        string valor;
        /**
        * @brief O valor do objeto do dom&iacute;nio desejado.
        *
        * O valor que o objeto vai receber, que pode varia de acordo com o dom&iacute;nio desejado.
        */
    protected:
        /**
         * @brief Verifica se um valor &eacute; v&aacute;lido para o dom&iacute;nio.
         * @param valor O valor a ser verificado.
         *
         * Este m&eacute;todo deve ser implementado pelas classes filhas para verificar se um valor &eacute; v&aacute;lido para o dom&iacute;nio.
         * Se o valor n&atilde;o for v&aacute;lido, o m&eacute;todo deve lan&ccedil;ar uma exce&ccedil;&atilde;o.
         */
        virtual void verificaValor(string) = 0;
    public:
        /**
         * @brief Destrutor virtual da classe Dom&iacute;nios.
         *
         * Este destrutor &eacute; virtual para permitir que as classes filhas tenham seus pr&oacute;prios destrutores.
         */
        virtual ~Dominios() {}

        /**
         * @brief Define o valor do dom&iacute;nio.
         * @param valor O valor a ser definido.
         * @throw invalid_argument Se o valor n&atilde;o for v&aacute;lido para o dom&iacute;nio.
         *
         * Este m&eacute;todo define o valor do dom&iacute;nio. Ele chama o m&eacute;todo "verificaValor" para verificar se o valor &eacute; v&aacute;lido.
         * Se o valor n&atilde;o for v&aacute;lido, o m&eacute;todo lan&ccedil;a uma exce&ccedil;&atilde;o do tipo "invalid_argument".
         */
        void setValor(string);

        /**
         * @brief Retorna o valor do dom&iacute;nio.
         * @return O valor do dom&iacute;nio.
         *
         * Este m&eacute;todo retorna o valor do dom&iacute;nio.
         */
        string getValor() const;
};

inline string Dominios::getValor() const {
    return valor;
}

/**
* @brief Classe concreta Classe. Herda m&eacute;todos da classe abstrata Dom&iacute;nios.
*/
class Classe : public Dominios {
    private:
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do valor do objeto tipo Classe.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor do objeto n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido s&atilde;o: "UNIDADE", "INTEGRACAO", "FUMACA", "SISTEMA", "REGRESSAO" e "ACEITACAO".
        */
        void verificaValor(string) override;

};

/**
* @brief Classe concreta Codigo. Herda m&eacute;todos da classe abstrata Dom&iacute;nios.
*/
class Codigo : public Dominios {
    private:
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do valor do objeto tipo Codigo.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor do objeto n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido devem ser da forma LLLDDD, onde os seus tr&ecirc;s L s&atilde;o letras
        * (A - Z, a - z) e os seus tr&ecirc;s &uacute;ltimos D s&atilde;o d&iacute;gitos (0 - 9).
        */
        void verificaValor(string) override;
};

/**
* @brief Classe concreta Data. Herda m&eacute;todos da classe abstrata Dom&iacute;nios.
*/
class Data : public Dominios {
    private:
        /**
        * @brief M&eacute;todo respons&aacute;vel por verificar se a data &eacute; referente a;
        * um ano bissexto.
        * @param valor O valor a ser verificado.
        */
        bool isBissexto(string);
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do m&ecirc;s inserido
        * na data.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor refente ao m&ecirc;s n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido s&atilde;o: "JAN", "FEV", "MAR", "ABR", "MAI", "JUN", "JUL",
        * "AGO", "SET", "OUT", "NOV" e "DEZ".
        */
        void verificaMes(string);
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do valor do objeto tipo Data.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor do objeto n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido devem ser da forma DD/MES/ANO, onde DD s&atilde;o os dias (1 - 31),
        * MES s&atilde;o os meses ("JAN", "FEV", "MAR", "ABR", "MAI", "JUN", "JUL", "AGO", "SET", "OUT",
        * "NOV" e "DEZ" e ANO s&atilde;o os anos de 2000 at&eacute; 2999.
        */
        void verificaValor(string) override;

};

/**
* @brief Classe concreta Matricula. Herda m&eacute;todos da classe abstrata Dom&iacute;nios.
*/
class Matricula : public Dominios {
    private:
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do valor do objeto tipo Matricula.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor do objeto n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido devem ser da forma DDDDDDX, onde todos os seus caracteres D s&atilde;o
        * d&iacute;gitos (0 - 9) O caracter X tamb&eacute;m &eacute; d&iacute;gito, por&eacute;m &eacute;
        * d&iacute;gito verificador calculado com m&oacute;dulo 10.
        */
        void verificaValor(string) override;
};

/**
* @brief Classe concreta Resultado. Herda m&eacute;todos da classe abstrata Dom&iacute;nios.
*/
class Resultado : public Dominios {
    private:
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do valor do objeto tipo Resultado.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor do objeto n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido s&atilde;o: "APROVADO" e "REPROVADO".
        */
        void verificaValor(string) override;
};

/**
* @brief Classe concreta Senha. Herda m&eacute;todos da classe abstrata Dom&iacute;nios.
*/
class Senha : public Dominios {
    private:
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do valor do objeto tipo Senha.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor do objeto n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido s&atilde;o devem ser da forma XXXXXX, onde X pode ser uma letra (A - Z, a - z),
        * um d&iacute; (0 - 9), ou caracteres especiais ("@", "#", "$", "%", "&"). N&atilde;o pode haver caracteres
        * repetidos.
        */
        void verificaValor(string) override;
};

/**
* @brief Classe concreta Telefone. Herda m&eacute;todos da classe abstrata Dom&iacute;nios.
*/
class Telefone : public Dominios {
    private:
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do valor do objeto tipo Telefone.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor do objeto n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido s&atilde;o devem ser da forma +XXXXXXX (7 d&iacute;gitos) a +XXXXXXXXXXXXXXX
        * (15 d&iacute;gitos), onde X &eacute; d&iacute;gito (0 - 9). Lembrando que &eacute;
        * necess&aacute;rio o uso do caracter "+".
        */
        void verificaValor(string) override;
};

/**
* @brief Classe concreta Texto. Herda m&eacute;todos da classe abstrata Dom&iacute;nios.
*/
class Texto : public Dominios {
    private:
        /**
        * @brief M&eacute;todo respons&aacute;vel pela valida&ccedil;&atilde;o do valor do objeto tipo Telefone.
        * @param valor O valor a ser verificado.
        * @throw invalid_argument Se o valor do objeto n&atilde;o for do formato v&aacute;lido.
        *
        * Os formatos v&aacute;lido s&atilde;o devem ter de 10 a 20 caracteres, onde cada caracter X pode ser
        * uma letra (A - Z, a - z), d&iacute;gito (0 - 9), sinais de pontua&ccedil;&atilde;o (.,;?!:-) ou um
        * caracter especial ("@", "#", "$", "%", "&"). N&atilde;o pode haver espa&ccedil;os em branco consecutivos
        * e nem o uso de acentua&ccedil;&atilde;o.
        */
        void verificaValor(string) override;
};

#endif // DOMINIOS_H_INCLUDED
