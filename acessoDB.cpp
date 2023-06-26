//---------------------------------------------------------------------------

#include "acessoDB.h"

//Atributo estático container List.

list<ElementoResultado> ComandoSQL::listaResultado;


//---------------------------------------------------------------------------
//Classe ElementoResultado.

void ElementoResultado::setNomeColuna(const string& nomeColuna) {
        this->nomeColuna = nomeColuna;
}

void ElementoResultado::setValorColuna(const string& valorColuna){
        this->valorColuna = valorColuna;
}


//---------------------------------------------------------------------------
//Classe ComandoSQL.

bool ComandoSQL::conectar() {
    rc = sqlite3_open(nomeBancoDados, &bd);
    if( rc != SQLITE_OK )
        return 0;
    return 1;
}

bool ComandoSQL::desconectar() {
    rc =  sqlite3_close(bd);
    if( rc != SQLITE_OK )
        return 0;
    return 1;
}

bool ComandoSQL::executar() {
    if(!conectar())
        return 0;

    rc = sqlite3_exec(bd, comandoSQL.c_str(), callback, 0, &mensagem);
    if(rc != SQLITE_OK){
            sqlite3_free(mensagem);
            desconectar();
    }
    desconectar();

    return 1;
}

int ComandoSQL::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
    NotUsed=0;
    ElementoResultado elemento;
    int i;
    for(i=0; i<argc; i++){
    elemento.setNomeColuna(nomeColuna[i]);
    elemento.setValorColuna(valorColuna[i] ? valorColuna[i]: "NULL");
    listaResultado.push_front(elemento);
    }
    return 0;
}

//---------------------------------------------------------------------------
//Classe ComandoLerSenha.

ComandoLerSenha::ComandoLerSenha(Matricula matricula) {
    comandoSQL = "SELECT senha FROM desenvolvedor WHERE matricula = '";
    comandoSQL += matricula.getValor();
    comandoSQL += "'";
}

string ComandoLerSenha::getResultado() {
    ElementoResultado resultado;
    string senha;

    //Remover senha;
    if (listaResultado.empty())
        return "Erro";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    senha = resultado.getValorColuna();

    return senha;
}
//-----------------------------------------------------------------

ComandoPesquisarDesenvolvedor::ComandoPesquisarDesenvolvedor(Matricula matricula) {
    comandoSQL = "SELECT * FROM desenvolvedor WHERE matricula = '";
    comandoSQL += matricula.getValor();
    comandoSQL += "'";
}

Desenvolvedor ComandoPesquisarDesenvolvedor::getResultado() {
    ElementoResultado resultado;
    Texto nome;
    Matricula matricula;
    Senha senha;
    Telefone telefone;
    Desenvolvedor desenvolvedor;

    // Remover matricula;
    if (listaResultado.empty())
            throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    matricula.setValor(resultado.getValorColuna());

    // Remover nome;
    if (listaResultado.empty())
            throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    nome.setValor(resultado.getValorColuna());

    // Remover senha;
    if (listaResultado.empty())
            throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    senha.setValor(resultado.getValorColuna());

    // Remover telefone;
    if (listaResultado.empty())
            throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    telefone.setValor(resultado.getValorColuna());

    desenvolvedor.setNome(nome);
    desenvolvedor.setMatricula(matricula);
    desenvolvedor.setSenha(senha);
    desenvolvedor.setTelefone(telefone);

    return desenvolvedor;
}

//---------------------------------------------------------------------------
//Classe ComandoCadastrardesenvolvedor.

ComandoCadastrarDesenvolvedor::ComandoCadastrarDesenvolvedor(Desenvolvedor desenvolvedor) {
    comandoSQL = "INSERT INTO desenvolvedor VALUES (";
    comandoSQL += "'";
    comandoSQL += desenvolvedor.getMatricula().getValor();
    comandoSQL += "', '";
    comandoSQL += desenvolvedor.getNome().getValor();
    comandoSQL += "', '";
    comandoSQL += desenvolvedor.getSenha().getValor();
    comandoSQL += "', '";
    comandoSQL += desenvolvedor.getTelefone().getValor();
    comandoSQL += "')";
}


//---------------------------------------------------------------------------
//Classe ComandoAtualizardesenvolvedor.

ComandoAtualizarDesenvolvedor::ComandoAtualizarDesenvolvedor(Desenvolvedor desenvolvedor) {
    comandoSQL = "UPDATE desenvolvedor ";
    comandoSQL += "SET nome = '" + desenvolvedor.getNome().getValor();
    comandoSQL += "', senha = '" + desenvolvedor.getSenha().getValor();
    comandoSQL += "', telefone = '" + desenvolvedor.getTelefone().getValor();
    comandoSQL += "' WHERE matricula = '" + desenvolvedor.getMatricula().getValor() + "'";
}
//---------------------------------------------------------------------------
//Classe ComandoPesquisarTestes.
ComandoPesquisarTestes::ComandoPesquisarTestes() {
    comandoSQL = "SELECT * FROM TESTE";
}

ComandoPesquisarTestes::ComandoPesquisarTestes(Matricula matricula) {
    comandoSQL = "SELECT * FROM teste WHERE matricula = '";
    comandoSQL += matricula.getValor();
    comandoSQL += "'";
}

list<Teste> ComandoPesquisarTestes::getResultado() {
    ElementoResultado resultado;
    list<Teste> testes;
    Codigo codigo;
    Classe classe;
    Texto nome;
    Matricula matricula;
    Teste teste;

    while(!listaResultado.empty()){
        resultado = listaResultado.back();
        listaResultado.pop_back();

        codigo.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        nome.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        classe.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        matricula.setValor(resultado.getValorColuna());

        teste.setCodigo(codigo);
        teste.setClasse(classe);
        teste.setNome(nome);
        teste.setMatricula(matricula);
        testes.push_back(teste);
    }
    return testes;
}
//---------------------------------------------------------------------------
//Classe ComandoPesquisarTeste.
ComandoPesquisarTeste::ComandoPesquisarTeste(Codigo codigo) {
    comandoSQL = "SELECT * FROM teste WHERE codigo = '";
    comandoSQL += codigo.getValor();
    comandoSQL += "'";
}

Teste ComandoPesquisarTeste::getResultado() {
    ElementoResultado resultado;

    Codigo codigo;
    Classe classe;
    Texto nome;
    Matricula matricula;

    Teste teste;

    // Remover codigo;
    if (listaResultado.empty())
            throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    codigo.setValor(resultado.getValorColuna());

    // Remover classe;
    if (listaResultado.empty())
            throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    nome.setValor(resultado.getValorColuna());

    // Remover descricao;
    if (listaResultado.empty())
            throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    classe.setValor(resultado.getValorColuna());

    // Remover endereco;
    if (listaResultado.empty())
            throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    matricula.setValor(resultado.getValorColuna());

    teste.setCodigo(codigo);
    teste.setClasse(classe);
    teste.setNome(nome);
    teste.setMatricula(matricula);

    return teste;
}
//Classe ComandoPesquisarDonoTeste.
ComandoPesquisarDonoTeste::ComandoPesquisarDonoTeste(Codigo codigo) {
    comandoSQL = "SELECT matricula FROM teste WHERE codigo = '";
    comandoSQL += codigo.getValor();
    comandoSQL += "'";
}

Matricula ComandoPesquisarDonoTeste::getResultado() {
    ElementoResultado resultado;
    Matricula matricula;

    //Remover matricula;
    if (listaResultado.empty())
        throw "not found";
    resultado = listaResultado.back();
    listaResultado.pop_back();
    matricula.setValor(resultado.getValorColuna());

    return matricula;
}
//Classe ComandoCadastrarTeste.
ComandoCadastrarTeste::ComandoCadastrarTeste(Teste teste) {
    comandoSQL = "INSERT INTO teste VALUES (";
    comandoSQL += "'";
    comandoSQL += teste.getCodigo().getValor();
    comandoSQL += "', '";
    comandoSQL += teste.getNome().getValor();
    comandoSQL += "', '";
    comandoSQL += teste.getClasse().getValor();
    comandoSQL += "', '";
    comandoSQL += teste.getMatricula().getValor();
    comandoSQL += "')";
}
//Classe ComandoAtualizarTeste.
ComandoAtualizarTeste::ComandoAtualizarTeste(Teste teste) {
    comandoSQL = "UPDATE teste ";
    comandoSQL += "SET codigo = '" + teste.getCodigo().getValor();
    comandoSQL += "', nome = '" + teste.getNome().getValor();
    comandoSQL += "', classe = '" + teste.getClasse().getValor();
    comandoSQL += "', matricula = '" + teste.getMatricula().getValor();
    comandoSQL += "' WHERE codigo = '" + teste.getCodigo().getValor() + "'";
}

ComandoPesquisarCasosDeTestes::ComandoPesquisarCasosDeTestes(Matricula matricula){
    comandoSQL = "SELECT * FROM caso_de_teste WHERE codigoteste IN(SELECT codigo FROM teste WHERE matricula = '";
    comandoSQL += matricula.getValor();
    comandoSQL += "')";
}

list<CasoDeTeste> ComandoPesquisarCasosDeTestes::getResultado() {
    ElementoResultado resultado;
    list<CasoDeTeste> casosDeTestes;

    Codigo codigo;
    Texto nome;
    Data data;
    Texto acao;
    Texto resposta;
    Resultado resultado2;
    Codigo codigoteste;

    CasoDeTeste casoDeTeste;

    while(!listaResultado.empty()){
        resultado = listaResultado.back();
        listaResultado.pop_back();
        codigo.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        nome.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        data.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        acao.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        resposta.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        resultado2.setValor(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        codigoteste.setValor(resultado.getValorColuna());

        casoDeTeste.setCodigo(codigo);
        casoDeTeste.setNome(nome);
        casoDeTeste.setData(data);
        casoDeTeste.setAcao(acao);
        casoDeTeste.setResposta(resposta);
        casoDeTeste.setResultado(resultado2);
        casoDeTeste.setCodigoTeste(codigoteste);
        casosDeTestes.push_back(casoDeTeste);
    }
    return casosDeTestes;
}
ComandoDeletarDesenvolvedor::ComandoDeletarDesenvolvedor(Matricula matricula) {
        comandoSQL = "DELETE FROM desenvolvedor WHERE matricula = '";
        comandoSQL += matricula.getValor();
        comandoSQL += "'";
}

ComandoDeletarTeste::ComandoDeletarTeste(Codigo codigo) {
        comandoSQL = "DELETE FROM teste WHERE codigo = '";
        comandoSQL += codigo.getValor();
        comandoSQL += "'";
}

ComandoDeletarCasoDeTeste::ComandoDeletarCasoDeTeste(Codigo codigoC) {
        comandoSQL = "DELETE FROM caso_de_teste WHERE codigoC = '";
        comandoSQL += codigoC.getValor();
        comandoSQL += "'";
}

