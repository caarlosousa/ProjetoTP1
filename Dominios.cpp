#include "Dominios.h"

void Dominios::setValor(string valor) {
    verificaValor(valor);
    this-> valor = valor;
}

void Classe::verificaValor(string valor) {
    string formatos[6] = {"UNIDADE", "INTEGRACAO",
    "FUMACA", "SISTEMA", "REGRESSAO", "ACEITACAO"};
    bool valida = false;

    for (const string &formato : formatos) {
        if (formato == valor) {
            valida = true;
            break;
        }
    }

    if (!valida) {
        throw invalid_argument("Classe invalida.");
    }

}

void Codigo::verificaValor(string valor) {
    const int tamanho = 6;

    if(valor.length() != tamanho){
        throw invalid_argument("Codigo invalido.");
    }

    string letras = valor.substr(0,3);
    string numeros = valor.substr(3);

    for(char c : letras){
        if(!isalpha(c)){
            throw invalid_argument("Codigo invalido.");
        }
    }

    for(char c : numeros){
        if(!isdigit(c)){
            throw invalid_argument("Codigo invalido.");
        }
    }
}

bool Data::isBissexto(string valor) {
    string subs;
    subs = valor.substr(7);
    int ano = stoi(subs);

    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        return true;
    } else {
        return false;
    }
}

void Data::verificaMes(string valor) {
    string mes = valor.substr(3,3);
    string mesesDoAno[12] = {"JAN", "FEV", "MAR", "ABR", "MAI",
    "JUN", "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};
    bool valida = false;

    for (string c : mesesDoAno) {
        if (c == mes) {
            valida = true;
            break;
        }
    }
    if (!valida) {
        throw invalid_argument("Data invalida.");
    }
}

void Data::verificaValor(string valor) {
    int ano = stoi(valor.substr(7));
    string mes = valor.substr(3,3);
    int dia = stoi(valor.substr(0,2));
    string barra1 = valor.substr(2,1);
    string barra2 = valor.substr(6,1);
    int diasDoMes = 0;

    if (mes == "FEV" && isBissexto(valor)) {
        diasDoMes = 29;
    } else if (mes == "FEV") {
        diasDoMes = 28;
    } else if (mes == "ABR" || mes == "JUN" || mes == "SET" || mes == "NOV") {
        diasDoMes = 30;
    } else {
        diasDoMes = 31;
    }

    verificaMes(valor);

    if (barra1 != "/" || barra2 != "/" || dia > diasDoMes || dia < 1 || ano < 2000 || ano > 2999) {
        throw invalid_argument("Data invalida.");
    }
}

void Matricula::verificaValor(string valor) {
    int soma = 0;
    int verificador = 0;
    const int tamanho = 7;

    if (valor.length() != tamanho) {
        throw invalid_argument("Matricula invalida.");
    }

    for (char c : valor) {
        if (!isdigit(c)) {
            throw invalid_argument("Matricula invalida.");
        }
    }

    for (int i = 0; i < tamanho - 1; i++) {
        if (i % 2 == 0) {
            soma += stoi(valor.substr(i, 1));
        } else {
            soma += 2 * (stoi(valor.substr(i, 1)));
        }
    }

    verificador = soma % 10;
    if (verificador != stoi(valor.substr(6, 1))) {
        throw invalid_argument("Matricula invalida.");
    }
}

void Resultado::verificaValor(string valor) {
    if (valor != "APROVADO" && valor != "REPROVADO") {
        throw invalid_argument("Resultado invalido.");
    }
}

void Senha::verificaValor(string valor) {
    unordered_set<char> caracteres;
    const int tamanho = 6;

    if (valor.length() != tamanho) {
        throw invalid_argument("Senha invalida.");
    }

    for (char c : valor) {
        if (!isalnum(c) && c !='@' && c != '#' &&
        c != '$' && c != '%' && c != '&'){
            throw invalid_argument("Senha invalida.");
        }
        if (caracteres.find(c) != caracteres.end()){
            throw invalid_argument("Senha invalida.");
        }
        caracteres.insert(c);
    }
}

void Telefone::verificaValor(string valor) {
    const int tamanhoMinimo = 7;
    const int tamanhoMaximo = 15;
    const string operadorOriginal = "+";
    string operador = valor.substr(0,1);
    string digitos = valor.substr(1);

    if (digitos.length() < tamanhoMinimo || digitos.length() > tamanhoMaximo) {
        throw invalid_argument("Telefone invalido.");
    }

    for (char c : digitos) {
        if (!isdigit(c)) {
            throw invalid_argument("Telefone invalido.");
        }
    }
}

void Texto::verificaValor(string valor) {
    if (valor.length() < 10 || valor.length() > 20) {
        throw invalid_argument("Texto invalido.");
    }
    regex padrao("[A-Za-z0-9.,;:!?@#$%& ]+");
    if (!regex_match(valor, padrao)) {
        throw invalid_argument("Texto invalido.");
    }
    regex padrao_acentos("[¡¿¬√…» ÕÃŒ”“‘’⁄Ÿ€«·‡‚„ÈËÍÌÏÓÛÚÙı˙˘˚Á]+");
    if (regex_search(valor, padrao_acentos)) {
        throw invalid_argument("Texto invalido.");
    }
    if (valor.find("  ") != string::npos) {
        throw invalid_argument("Texto invalido.");
    }
}
