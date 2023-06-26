#ifndef ENTIDADES_H_INCLUDED
#define ENTIDADES_H_INCLUDED

#include "Dominios.h"

class Entidades {
protected:
    Texto nome;
public:
    void setNome(const Texto&);
    Texto getNome() const;
};

inline void Entidades::setNome(const Texto& nome) {
    this->nome = nome;
}

inline Texto Entidades::getNome() const {
    return nome;
}

class Desenvolvedor : public Entidades {
private:
    Matricula matricula;
    Senha senha;
    Telefone telefone;
public:
    void setMatricula(const Matricula&);
    Matricula getMatricula() const;
    void setSenha(const Senha&);
    Senha getSenha() const;
    void setTelefone(const Telefone&);
    Telefone getTelefone() const;
};

inline void Desenvolvedor::setMatricula(const Matricula& matricula) {
    this->matricula = matricula;
}

inline Matricula Desenvolvedor::getMatricula() const {
    return matricula;
}

inline void Desenvolvedor::setSenha(const Senha& senha) {
    this->senha = senha;
}

inline Senha Desenvolvedor::getSenha() const {
    return senha;
}

inline void Desenvolvedor::setTelefone(const Telefone& telefone) {
    this->telefone = telefone;
}

inline Telefone Desenvolvedor::getTelefone() const {
    return telefone;
}

class Teste : public Entidades {
private:
    Codigo codigo;
    Classe classe;
    Matricula matricula;
public:
    void setCodigo(const Codigo&);
    Codigo getCodigo() const;
    void setClasse(const Classe&);
    Classe getClasse() const;
    void setMatricula(const Matricula&);
    Matricula getMatricula() const;
};

inline void Teste::setCodigo(const Codigo& codigo) {
    this->codigo = codigo;
}

inline Codigo Teste::getCodigo() const {
    return codigo;
}

inline void Teste::setClasse(const Classe& classe) {
    this->classe = classe;
}

inline Classe Teste::getClasse() const {
    return classe;
}

inline void Teste::setMatricula(const Matricula& matricula) {
    this->matricula = matricula;
}

inline Matricula Teste::getMatricula() const {
    return matricula;
}

class CasoDeTeste : public Entidades {
private:
    Codigo codigo;
    Data data;
    Texto acao;
    Texto resposta;
    Resultado resultado;
    Codigo codigoteste;
public:
    void setCodigo(const Codigo&);
    Codigo getCodigo() const;
    void setData(const Data&);
    Data getData() const;
    void setAcao(const Texto&);
    Texto getAcao() const;
    void setResposta(const Texto&);
    Texto getResposta() const;
    void setResultado(const Resultado&);
    Resultado getResultado() const;
    void setCodigoTeste(const Codigo&);
    Codigo getCodigoTeste() const;
};

inline void CasoDeTeste::setCodigoTeste(const Codigo& codigoteste) {
    this->codigoteste = codigoteste;
}

inline Codigo CasoDeTeste::getCodigoTeste() const {
    return codigoteste;
}

inline void CasoDeTeste::setCodigo(const Codigo& codigo) {
    this->codigo = codigo;
}

inline Codigo CasoDeTeste::getCodigo() const {
    return codigo;
}

inline void CasoDeTeste::setData(const Data& data) {
    this->data = data;
}

inline Data CasoDeTeste::getData() const {
    return data;
}

inline void CasoDeTeste::setAcao(const Texto& acao) {
    this->acao = acao;
}

inline Texto CasoDeTeste::getAcao() const {
    return acao;
}

inline void CasoDeTeste::setResposta(const Texto& resposta) {
    this->resposta = resposta;
}

inline Texto CasoDeTeste::getResposta() const {
    return resposta;
}

inline void CasoDeTeste::setResultado(const Resultado& resultado){
    this->resultado = resultado;
}

inline Resultado CasoDeTeste::getResultado() const {
    return resultado;
}

#endif // ENTIDADES_H_INCLUDED
