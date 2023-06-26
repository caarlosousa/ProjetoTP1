#include "Testes.h"

bool TUDominios::run() {
    setUp();
    testarCenarioValido();
    testarCenarioInvalido();
    tearDown();
    return estado;
}

void TUClasse::setUp() {
    classe = new Classe();
    estado = sucesso;
}

void TUClasse::testarCenarioValido() {
    try {
        classe->setValor(valorValido);
        if (classe->getValor() != valorValido) {
            estado = falha;
        }
    }
    catch (invalid_argument &excecao) {
        estado = falha;
    }
}

void TUClasse::testarCenarioInvalido() {
    try {
        classe->setValor(valorInvalido);
        estado = falha;
        }
    catch (invalid_argument &excecao) {
        if (classe->getValor() == valorInvalido) {
            estado = falha;
        }
    }
}

void TUClasse::tearDown() {
    delete classe;
}

void TUCodigo::setUp() {
    codigo = new Codigo();
    estado = sucesso;
}

void TUCodigo::testarCenarioValido() {
    try {
        codigo->setValor(valorValido);
        if (codigo->getValor() != valorValido) {
            estado = falha;
        }
    }
    catch (invalid_argument &excecao) {
        estado = falha;
    }
}

void TUCodigo::testarCenarioInvalido() {
    try {
        codigo->setValor(valorInvalido);
        estado = falha;
        }
    catch (invalid_argument &excecao) {
        if (codigo->getValor() == valorInvalido) {
            estado = falha;
        }
    }
}

void TUCodigo::tearDown() {
    delete codigo;
}

void TUData::setUp() {
    data = new Data();
    estado = sucesso;
}

void TUData::testarCenarioValido() {
    try {
        data->setValor(valorValido);
        if (data->getValor() != valorValido) {
            estado = falha;
        }
    }
    catch (invalid_argument &excecao) {
        estado = falha;
    }
}

void TUData::testarCenarioInvalido() {
    try {
        data->setValor(valorInvalido);
        estado = falha;
        }
    catch (invalid_argument &excecao) {
        if (data->getValor() == valorInvalido) {
            estado = falha;
        }
    }
}

void TUData::tearDown() {
    delete data;
}

void TUMatricula::setUp() {
    matricula = new Matricula();
    estado = sucesso;
}

void TUMatricula::testarCenarioValido() {
    try {
        matricula->setValor(valorValido);
        if (matricula->getValor() != valorValido) {
            estado = falha;
        }
    }
    catch (invalid_argument &excecao) {
        estado = falha;
    }
}

void TUMatricula::testarCenarioInvalido() {
    try {
        matricula->setValor(valorInvalido);
        estado = falha;
        }
    catch (invalid_argument &excecao) {
        if (matricula->getValor() == valorInvalido) {
            estado = falha;
        }
    }
}

void TUMatricula::tearDown() {
    delete matricula;
}

void TUResultado::setUp() {
    resultado = new Resultado();
    estado = sucesso;
}

void TUResultado::testarCenarioValido() {
    try {
        resultado->setValor(valorValido);
        if (resultado->getValor() != valorValido) {
            estado = falha;
        }
    }
    catch (invalid_argument &excecao) {
        estado = falha;
    }
}

void TUResultado::testarCenarioInvalido() {
    try {
        resultado->setValor(valorInvalido);
        estado = falha;
        }
    catch (invalid_argument &excecao) {
        if (resultado->getValor() == valorInvalido) {
            estado = falha;
        }
    }
}

void TUResultado::tearDown() {
    delete resultado;
}

void TUSenha::setUp() {
    senha = new Senha();
    estado = sucesso;
}

void TUSenha::testarCenarioValido() {
    try {
        senha->setValor(valorValido);
        if (senha->getValor() != valorValido) {
            estado = falha;
        }
    }
    catch (invalid_argument &excecao) {
        estado = falha;
    }
}

void TUSenha::testarCenarioInvalido() {
    try {
        senha->setValor(valorInvalido);
        estado = falha;
        }
    catch (invalid_argument &excecao) {
        if (senha->getValor() == valorInvalido) {
            estado = falha;
        }
    }
}

void TUSenha::tearDown() {
    delete senha;
}

void TUTelefone::setUp() {
    telefone = new Telefone();
    estado = sucesso;
}

void TUTelefone::testarCenarioValido() {
    try {
        telefone->setValor(valorValido);
        if (telefone->getValor() != valorValido) {
            estado = falha;
        }
    }
    catch (invalid_argument &excecao) {
        estado = falha;
    }
}

void TUTelefone::testarCenarioInvalido() {
    try {
        telefone->setValor(valorInvalido);
        estado = falha;
        }
    catch (invalid_argument &excecao) {
        if (telefone->getValor() == valorInvalido) {
            estado = falha;
        }
    }
}

void TUTelefone::tearDown() {
    delete telefone;
}

void TUTexto::setUp() {
    texto = new Texto();
    estado = sucesso;
}

void TUTexto::testarCenarioValido() {
    try {
        texto->setValor(valorValido);
        if (texto->getValor() != valorValido) {
            estado = falha;
        }
    }
    catch (invalid_argument &excecao) {
        estado = falha;
    }
}

void TUTexto::testarCenarioInvalido() {
    try {
        texto->setValor(valorInvalido);
        estado = falha;
        }
    catch (invalid_argument &excecao) {
        if (texto->getValor() == valorInvalido) {
            estado = falha;
        }
    }
}

void TUTexto::tearDown() {
    delete texto;
}

bool TUEntidades::run() {
    setUp();
    testarCenarioValido();
    tearDown();
    return estado;
}

void TUDesenvolvedor::setUp() {
    desenvolvedor = new Desenvolvedor();
    estado = sucesso;
}

void TUDesenvolvedor::testarCenarioValido() {
    Matricula matricula;
    matricula.setValor(valorValidoMatricula);
    desenvolvedor->setMatricula(matricula);
    if (desenvolvedor->getMatricula().getValor() != valorValidoMatricula) {
        estado = falha;
    }

    Texto nome;
    nome.setValor(valorValidoTexto);
    desenvolvedor->setNome(nome);
    if (desenvolvedor->getNome().getValor() != valorValidoTexto) {
        estado = falha;
    }

    Senha senha;
    senha.setValor(valorValidoSenha);
    desenvolvedor->setSenha(senha);
    if (desenvolvedor->getSenha().getValor() != valorValidoSenha) {
        estado = falha;
    }

    Telefone telefone;
    telefone.setValor(valorValidoTelefone);
    desenvolvedor->setTelefone(telefone);
    if (desenvolvedor->getTelefone().getValor() != valorValidoTelefone) {
        estado = falha;
    }
}

void TUDesenvolvedor::tearDown() {
    delete desenvolvedor;
}

void TUTeste::setUp() {
    teste = new Teste();
    estado = sucesso;
}

void TUTeste::testarCenarioValido() {
    Codigo codigo;
    codigo.setValor(valorValidoCodigo);
    teste->setCodigo(codigo);
    if (teste->getCodigo().getValor() != valorValidoCodigo) {
        estado = falha;
    }

    Texto nome;
    nome.setValor(valorValidoTexto);
    teste->setNome(nome);
    if (teste->getNome().getValor() != valorValidoTexto) {
        estado = falha;
    }

    Classe classe;
    classe.setValor(valorValidoClasse);
    teste->setClasse(classe);
    if (teste->getClasse().getValor() != valorValidoClasse) {
        estado = falha;
    }
}

void TUTeste::tearDown() {
    delete teste;
}

void TUCasoDeTeste::setUp() {
    casoTeste = new CasoDeTeste();
    estado = sucesso;
}

void TUCasoDeTeste::testarCenarioValido() {
    Codigo codigo;
    codigo.setValor(valorValidoCodigo);
    casoTeste->setCodigo(codigo);
    if (casoTeste->getCodigo().getValor() != valorValidoCodigo) {
        estado = falha;
    }

    Texto nome;
    nome.setValor(valorValidoTexto);
    casoTeste->setNome(nome);
    if (casoTeste->getNome().getValor() != valorValidoTexto) {
        estado = falha;
    }

    Data data;
    data.setValor(valorValidoData);
    casoTeste->setData(data);
    if (casoTeste->getData().getValor() != valorValidoData) {
        estado = falha;
    }

    Texto acao;
    acao.setValor(valorValidoTexto);
    casoTeste->setAcao(acao);
    if (casoTeste->getAcao().getValor() != valorValidoTexto) {
        estado = falha;
    }

    Texto resposta;
    resposta.setValor(valorValidoTexto);
    casoTeste->setResposta(resposta);
    if (casoTeste->getResposta().getValor() != valorValidoTexto) {
        estado = falha;
    }

    Resultado resultado;
    resultado.setValor(valorValidoResultado);
    casoTeste->setResultado(resultado);
    if (casoTeste->getResultado().getValor() != valorValidoResultado) {
        estado = falha;
    }
}

void TUCasoDeTeste::tearDown() {
    delete casoTeste;
}
