//SERVICO
#include "Controladoras.h"
#include "Dominios.h"
#include "Entidades.h"
#include "acessoDB.h"
// APRESENTACAO CONTROLE
void CntrAControle::executar(){

    char texto1[] = "Selecione um dos servicos: ";
    char texto2[] = "1 - Acessar o sistema.";
    char texto3[] = "2 - Cadastrar-se no sistema.";
    char texto4[] = "3 - Encerrar execucao do sistema.";

    char texto5[] = "Selecione um dos servicos: ";
    char texto6[] = "1 - Servicos de desenvolvedor.";
    char texto7[] = "2 - Servicos de teste.";
    char texto8[] = "3 - Encerrar sessao.";

    char texto9[] = "Dados incorretos ou falha na autenticacao. Tente novamente.";

    int campo;

    bool apresentar = true;

    while(apresentar) {
        CLR_SCR;

        cout << texto1 << endl;
        cout << texto2 << endl;
        cout << texto3 << endl;
        cout << texto4 << endl;

        campo = getch() - 48;

        switch(campo) {
            case 1:
                if(cntrAAutenticacao->autenticar(&matricula)) {
                    bool apresentar = true;
                    while (apresentar) {
                        CLR_SCR;
                        cout << texto5 << endl;
                        cout << texto6 << endl;
                        cout << texto7 << endl;
                        cout << texto8 << endl;

                        campo = getch() - 48;

                        switch(campo) {
                            case 1:
                                if(!cntrADesenvolvedor->executar(matricula)) {
                                    apresentar = false;
                                    CLR_SCR;
                                    cout << "Matricula nao existe." << endl;
                                    getch();
                                }
                                break;
                            case 2:
                                cntrATeste->executar(matricula);
                                break;
                            case 3: apresentar = false;
                                break;
                        }
                    }
                } else {
                    CLR_SCR;
                    cout << texto9 << endl;
                    getch();
                }
                break;
            case 2:
                cntrADesenvolvedor->cadastrar();
                break;
            case 3:
                apresentar = false;
                break;
        }
    }
    return;
}

// APRESENTACAO AUTENTICACAO
bool CntrIAAutenticacao::autenticar(Matricula *matricula) {
    char texto1[]="Digite a matricula: ";
    char texto2[]="Digite a senha: ";
    char texto3[]="Dado em formato incorreto. Digite algo.";

    string campo1, campo2;

    Senha senha;

    while(true) {
        CLR_SCR;

        cout << texto1 << " ";
        getline(cin, campo1);
        cout << texto2 << " ";
        getline(cin, campo2);

        try {
            matricula->setValor(campo1);
            senha.setValor(campo2);
            break;
        } catch (invalid_argument &exp) {
            CLR_SCR;
            cout << texto3 << endl;
            getch();
        }
    }
    return (cntrISAutenticacao->autenticar(*matricula, senha));
}

// SERVICO AUTENTICACAO
bool CntrISAutenticacao::autenticar(const Matricula& matricula, const Senha& senha){
    ComandoLerSenha lerSenha(matricula);
    if (!lerSenha.executar())
        return 0;
    string senhaRecuperada;
    senhaRecuperada = lerSenha.getResultado();
    return (senha.getValor() == senhaRecuperada);
}

// APRESENTACAO DESENVOLVEDOR

bool CntrIADesenvolvedor::executar(Matricula matricula) {

    char texto1[] = "Selecione um dos servicos: ";
    char texto2[] = "1 - Visualizar dados.";
    char texto3[] = "2 - Editar dados.";
    char texto4[] = "3 - Descadastrar conta.";
    char texto5[] = "4 - Retornar.";

    int campo;

    bool apresentar = true;

    while(apresentar) {

        CLR_SCR;

        cout << texto1 << endl;
        cout << texto2 << endl;
        cout << texto3 << endl;
        cout << texto4 << endl;
        cout << texto5 << endl;

        campo = getch() - 48;

        switch(campo) {
            case 1:
                visualizar(matricula);
                break;
            case 2:
                editar(matricula);
                break;
            case 3:
                if(descadastrar(matricula)) {
                    cout << "Desenvolvedor descadastrado com sucesso." << endl;
                    getch();
                    return false;
                }
                break;
            case 4:
                apresentar = false;
                break;
        }
    }
    return true;
}

void CntrIADesenvolvedor::cadastrar() {

    char texto1[] = "Complete com os seus dados: ";
    char texto2[] = "Nome:";
    char texto3[] = "Matricula:";
    char texto4[] = "Senha:";
    char texto5[] = "Telefone:";
    char texto6[] = "Dados em formato invalido. Pressione qualquer tecla para continuar.";
    char texto7[] = "Desenvolvedor cadastrado com sucesso. Pressione qualquer tecla para continuar.";
    char texto8[] = "Falha ao realizar o cadastramento. Pressione qualquer tecla para continuar.";
    char texto9[] = "Desenvolvedor ja cadastrado anteriormente. Pressione qualquer tecla para continuar.";

    string campo1, campo2, campo3, campo4;

    Texto nome;
    Matricula matricula;
    Senha senha;
    Telefone telefone;

    CLR_SCR;

    cout << texto1 << endl;
    cout << texto2 << " ";
    getline(cin, campo1);
    cout << texto3 << " ";
    getline(cin, campo2);
    cout << texto4 << " ";
    getline(cin, campo3);
    cout << texto5 << " ";
    getline(cin, campo4);

    try{
        nome.setValor(string(campo1));
        matricula.setValor(string(campo2));
        senha.setValor(string(campo3));
        telefone.setValor(string(campo4));
    }
    catch(invalid_argument &excecao) {
        cout << texto6 << endl;
        getch();
        return;
    }

    Desenvolvedor desenvolvedor;
    desenvolvedor.setNome(nome);
    desenvolvedor.setMatricula(matricula);
    desenvolvedor.setSenha(senha);
    desenvolvedor.setTelefone(telefone);

    if(cntrISDesenvolvedor->cadastrar(desenvolvedor)) {
        cout << texto7 << endl;
        getch();
        return;
    }

    cout << texto8 << endl;
    getch();

    return;
}

void CntrIADesenvolvedor::visualizar(Matricula matricula) {

    Desenvolvedor desenvolvedor;
    desenvolvedor = cntrISDesenvolvedor->visualizar(matricula);

    CLR_SCR;

    char texto1[] = "Aqui estao os seus dados atuais: ";
    char texto2[] = "Nome: ";
    char texto3[] = "Matricula: ";
    char texto4[] = "Senha: ";
    char texto5[] = "Telefone: ";
    char texto6[] = "Digite qualquer tecla para continuar.";

    cout << texto1 << endl;
    cout << texto2 << desenvolvedor.getNome().getValor() << endl;
    cout << texto3 << desenvolvedor.getMatricula().getValor() << endl;
    cout << texto4 << desenvolvedor.getSenha().getValor() << endl;
    cout << texto5 << desenvolvedor.getTelefone().getValor() << endl;
    cout << texto6 << endl;
    getch();
}

void CntrIADesenvolvedor::editar(Matricula matricula) {

    Texto nome;
    Senha senha;
    Telefone telefone;
    Desenvolvedor desenvolvedor;
    desenvolvedor = cntrISDesenvolvedor->visualizar(matricula);

    char texto1[] = "Aqui estao os seus dados atuais: ";
    char texto2[] = "Nome: ";
    char texto3[] = "Matricula: ";
    char texto4[] = "Senha: ";
    char texto5[] = "Telefone: ";
    char texto6[] = "Insira seus novos dados: ";
    char texto7[] = "Dados invalidos. Tente novamente.";
    char texto8[] = "1 - Inserir novamente.";
    char texto9[] = "2 - Retornar.";
    char texto10[] = "Dados atualizados com sucesso.";
    char texto11[] = "Falha ao editar dados.";
    char texto12[] = "Digite qualquer tecla para retornar.";
    char texto13[] = "------------------------------------";

    int campo;
    string campo1, campo2, campo3;
    bool apresentar = true;

    while(apresentar) {
        try {
            CLR_SCR;

            cout << texto1 << endl;
            cout << texto2 << desenvolvedor.getNome().getValor() << endl;
            cout << texto3 << desenvolvedor.getMatricula().getValor() << endl;
            cout << texto4 << desenvolvedor.getSenha().getValor() << endl;
            cout << texto5 << desenvolvedor.getTelefone().getValor() << endl;
            cout << texto13 << endl;
            cout << texto6 << endl;

            cout << texto2;
            getline(cin, campo1);

            cout << texto4;
            getline(cin, campo2);

            cout << texto5;
            getline(cin, campo3);

            nome.setValor(campo1);
            senha.setValor(campo2);
            telefone.setValor(campo3);
            desenvolvedor.setNome(nome);
            desenvolvedor.setSenha(senha);
            desenvolvedor.setTelefone(telefone);

            apresentar = false;
        }
        catch(invalid_argument &excecao) {
            cout << texto7 << endl;
            cout << texto8 << endl;
            cout << texto9 << endl;
            campo = getch() - 48;
            if (campo == 2) {
                return;
            }
            getch();
        }
    }
    if (cntrISDesenvolvedor->editar(desenvolvedor)) {
        cout << texto10 << endl;
    } else {
        cout << texto11 << endl;
    }
    cout << texto12 << endl;
    getch();
}

bool CntrIADesenvolvedor::descadastrar(Matricula matricula) {

    char texto1[] = "Tem certeza que deseja descadastrar Desenvolvedor?";
    char texto2[] = "1 - Sim.";
    char texto3[] = "2 - Nao.";
    char texto4[] = "Falha na exclusao. Tente novamente.";
    char texto5[] = "Descadastramento cancelado.";

    int campo;

    Desenvolvedor desenvolvedor;
    desenvolvedor = cntrISDesenvolvedor->visualizar(matricula);

    CLR_SCR;

    cout << texto1 << endl;
    cout << texto2 << endl;
    cout << texto3 << endl;

    campo = getch() - 48;

    switch(campo) {
        case 1:
            if (cntrISDesenvolvedor->descadastrar(matricula)) {
                return true;
            } else {
                cout << texto4 << endl;
                getch();
                return false;
            }
        case 2:
            cout << texto5 << endl;
            getch();
            return false;
    }
    return false;
}

//SERVICO DESENVOLVEDOR

bool CntrISDesenvolvedor::cadastrar(const Desenvolvedor &desenvolvedor) {
    ComandoCadastrarDesenvolvedor cadastrarDesenvolvedor(desenvolvedor);
    return cadastrarDesenvolvedor.executar();
}

Desenvolvedor CntrISDesenvolvedor::visualizar(const Matricula &matricula) {
    ComandoPesquisarDesenvolvedor pesquisarDesenvolvedor(matricula);
    pesquisarDesenvolvedor.executar();
    Desenvolvedor desenvolvedor;
    desenvolvedor = pesquisarDesenvolvedor.getResultado();

    return desenvolvedor;
}

bool CntrISDesenvolvedor::editar(const Desenvolvedor &desenvolvedor) {
    ComandoAtualizarDesenvolvedor atualizarDesenvolvedor(desenvolvedor);
    return atualizarDesenvolvedor.executar();
}

bool CntrISDesenvolvedor::descadastrar(const Matricula &matricula) {
    list<Teste> testes = visualizarTestes(matricula);
    Teste teste;
    Codigo codigoTeste;
    list<CasoDeTeste> casosDeTestes = visualizarCasosDeTestes(matricula);
    CasoDeTeste casoDeTeste;
    Codigo codigoCaso;

    while (!testes.empty()){
        teste = testes.back();
        testes.pop_back();
        codigoTeste = teste.getCodigo();
        ComandoDeletarTeste deletarTeste(codigoTeste);
        deletarTeste.executar();
    }

    while (!casosDeTestes.empty()){
        casoDeTeste = casosDeTestes.back();
        testes.pop_back();
        codigoCaso = casoDeTeste.getCodigo();
        ComandoDeletarCasoDeTeste deletarCasoDeTeste(codigoTeste);
        deletarCasoDeTeste.executar();
    }

    ComandoDeletarDesenvolvedor deletarDesenvolvedor(matricula);
    return deletarDesenvolvedor.executar();
}

list<Teste> CntrISDesenvolvedor::visualizarTestes(Matricula matricula) {
    ComandoPesquisarTestes pesquisarTestes(matricula);
    pesquisarTestes.executar();
    return pesquisarTestes.getResultado();
}

list<CasoDeTeste> CntrISDesenvolvedor::visualizarCasosDeTestes(Matricula matricula) {
    ComandoPesquisarCasosDeTestes pesquisarCasosDeTestes(matricula);
    pesquisarCasosDeTestes.executar();
    return pesquisarCasosDeTestes.getResultado();
}

//SERVICO TESTE--------------------------------------------------------
bool CntrISTeste::cadastrar(const Teste &teste) {
    ComandoCadastrarTeste cadastrarTeste(teste);
    return cadastrarTeste.executar();
}

Teste CntrISTeste::visualizar(const Codigo &codigo) {
    ComandoPesquisarTeste pesquisarTeste(codigo);
    pesquisarTeste.executar();
    Teste teste;
    teste = pesquisarTeste.getResultado();

    return teste;
}

bool CntrISTeste::editar(const Teste &teste) {
    ComandoAtualizarTeste atualizarTeste(teste);
    return atualizarTeste.executar();
}

bool CntrISTeste::descadastrar(const Codigo &codigo) {
    list<CasoDeTeste> casosDeTestes = visualizarCasosDeTestes(codigo);
    CasoDeTeste casoDeTeste;
    Codigo codigoCaso;

    while (!casosDeTestes.empty()){
        casoDeTeste = casosDeTestes.back();
        casosDeTestes.pop_back();
        codigoCaso = casoDeTeste.getCodigo();
        ComandoDeletarCasoDeTeste deletarCasoDeTeste(codigoCaso);
        deletarCasoDeTeste.executar();
    }

    ComandoDeletarTeste deletarTeste(codigo);
    return deletarTeste.executar();
}

list<CasoDeTeste> CntrISTeste::visualizarCasosDeTestes(Codigo codigoT) {
    ComandoPesquisarCasosDeTestes pesquisarCasosDeTestes(codigoT);
    pesquisarCasosDeTestes.executar();
    return pesquisarCasosDeTestes.getResultado();
}
// APRESENTACAO TESTE
void CntrIATeste::executar(Matricula matricula) {

    char texto1[] = "Selecione um dos servicos: ";
    char texto2[] = "1 - Visualizar Teste.";
    char texto3[] = "2 - Cadastrar teste.";
    char texto4[] = "3 - Editar teste.";
    char texto5[] = "4 - Descadastrar teste.";
    char texto6[] = "5 - Retornar.";

    int campo;

    bool apresentar = true;

    while(apresentar){

        CLR_SCR;

        cout << texto1 << endl;
        cout << texto2 << endl;
        cout << texto3 << endl;
        cout << texto4 << endl;
        cout << texto5 << endl;
        cout << texto6 << endl;

        campo = getch() - 48;

        switch(campo) {
            case 1:
                    visualizar(matricula);
                    break;
            case 2:
                    cadastrar(matricula);
                    break;
            case 3:
                    editar(matricula);
                    break;
            case 4:
                    descadastrar(matricula);
                    break;
            case 5:
                    apresentar = false;
                    break;
        }
    }
}

void CntrIATeste::cadastrar(Matricula matricula) {

    char texto1[] = "Insira os dados do seu teste: ";
    char texto2[] = "Codigo:";
    char texto3[] = "Nome:";
    char texto4[] = "Classe:";
    char texto5[] = "Teste cadastrado com sucesso. Digite algo para continuar.";
    char texto6[] = "Erro ao cadastrar teste. Digite algo para continuar.";
    char texto7[] = "Formato invalido. Digite algo para continuar.";

    string campo1, campo2, campo3;

    Codigo codigo;
    Texto nome;
    Classe classe;

    CLR_SCR;

    cout << texto1 << endl;
    cout << texto2 << " ";
    getline(cin, campo1);
    cout << texto3 << " ";
    getline(cin, campo2);
    cout << texto4 << " ";
    getline(cin, campo3);

    try {
        codigo.setValor(string(campo1));
        nome.setValor(string(campo2));
        classe.setValor(string(campo3));
    }
    catch(invalid_argument &excecao) {
        cout << texto7 << endl;
        getch();
        return;
    }

    Teste teste;
    teste.setCodigo(codigo);
    teste.setNome(nome);
    teste.setClasse(classe);
    teste.setMatricula(matricula);

    if(cntrISTeste->cadastrar(teste)) {
        cout << texto5 << endl;
        getch();
        return;
    }

    cout << texto6 << endl;
    getch();

    return;
}

void CntrIATeste::visualizar(Matricula matricula) {

    CLR_SCR;

    char texto1[] = "Digite o codigo do teste que deseja visualizar: ";
    char texto2[] = "Codigo: ";
    char texto3[] = "Nome: ";
    char texto4[] = "Classe: ";
    char texto5[] = "Digite qualquer tecla para continuar.";
    char texto6[] = "Formato invalido. Tente novamente.";

    string campo;
    Codigo codigo;
    Teste teste;

    cout << texto1;
    getline(cin, campo);

    try {
        codigo.setValor(campo);
        teste = cntrISTeste->visualizar(codigo);
        cout << texto2 << teste.getCodigo().getValor() << endl;
        cout << texto3 << teste.getNome().getValor() << endl;
        cout << texto4 << teste.getClasse().getValor() << endl;
        cout << texto5 << endl;
        getch();
    }
    catch (...) {
        cout << texto6 << endl;
        getch();
        return;
    }
}

void CntrIATeste::editar(Matricula matricula) {

    Codigo codigo;
    Texto nome;
    Classe classe;
    Teste teste;

    char texto1[] = "Insira o codigo do teste que deseja editar: ";
    char texto2[] = "Aqui estao os dados atuais do seu teste: ";
    char texto3[] = "Codigo: ";
    char texto4[] = "Nome: ";
    char texto5[] = "Classe: ";
    char texto6[] = "------------------------------------";
    char texto7[] = "Insira os novos dados do seu teste: ";
    char texto8[] = "Dados invalidos. Tente novamente.";
    char texto9[] = "1 - Inserir novamente.";
    char texto10[] = "2 - Retornar.";
    char texto11[] = "Teste atualizado com sucesso.";
    char texto12[] = "Falha ao editar teste.";

    int campo;
    string campoCodigo, campo1, campo2;
    bool apresentar = true;

    CLR_SCR;

    cout << texto1;
    getline(cin, campoCodigo);

    try {
        codigo.setValor(campoCodigo);
        teste = cntrISTeste->visualizar(codigo);
    }
    catch(...) {
        cout << texto8 << endl;
        getch();
        return;
    }

    while(apresentar) {
        try {
            CLR_SCR;

            cout << texto2 << endl;
            cout << texto3 << teste.getCodigo().getValor() << endl;
            cout << texto4 << teste.getNome().getValor() << endl;
            cout << texto5 << teste.getClasse().getValor() << endl;
            cout << texto6 << endl;
            cout << texto7 << endl;

            cout << texto4;
            cin.ignore();
            getline(cin, campo1);

            cout << texto5;
            getline(cin, campo2);

            nome.setValor(campo1);
            classe.setValor(campo2);
            teste.setNome(nome);
            teste.setClasse(classe);

            apresentar = false;
        }
        catch(invalid_argument &excecao) {
            cout << texto8 << endl;
            cout << texto9 << endl;
            cout << texto10 << endl;
            campo = getch() - 48;
            if (campo == 2) {
                return;
            }
            getch();
        }
    }
    if (cntrISTeste->editar(teste)) {
        cout << texto11 << endl;
    } else {
        cout << texto12 << endl;
    }
    cout << texto12 << endl;
    getch();
}

bool CntrIATeste::descadastrar(Matricula matricula) {

    char texto1[] = "Insira o codigo do teste que deseja descadastrar: ";
    char texto2[] = "Tem certeza que deseja descadastrar Teste?";
    char texto3[] = "1 - Sim.";
    char texto4[] = "2 - Nao.";
    char texto5[] = "Falha na exclusao. Tente novamente.";
    char texto6[] = "Descadastramento cancelado.";
    char texto7[] = "Descadastramento realizado com sucesso";
    char texto8[] = "Formato invalido. Pressione qualquer tecla para continaur.";

    int campo;
    string campoCodigo;
    Codigo codigo;

    CLR_SCR;

    cout << texto1;
    getline(cin, campoCodigo);

    try {
        codigo.setValor(campoCodigo);
    }
    catch(invalid_argument &excecao) {
        cout << texto8 << endl;
        getch();
        return false;
    }

    CLR_SCR;

    cout << texto2 << endl;
    cout << texto3 << endl;
    cout << texto4 << endl;

    campo = getch() - 48;

    switch(campo) {
        case 1:
            if (cntrISTeste->descadastrar(codigo)) {
                cout << texto7 << endl;
                getch();
                return true;
            } else {
                cout << texto5 << endl;
                getch();
                return false;
            }
        case 2:
            cout << texto6 << endl;
            getch();
            return false;
    }
    return false;
}

// APRESENTACAO CASO DE TESTE
void CntrIACasoDeTeste::executar(Matricula matricula) {

    char texto1[] = "Selecione um dos servicos: ";
    char texto2[] = "1 - Visualizar Caso de teste.";
    char texto3[] = "2 - Cadastrar Caso de teste.";
    char texto4[] = "3 - Editar Caso de teste.";
    char texto5[] = "4 - Descadastrar Caso de teste.";
    char texto6[] = "5 - Retornar.";

    int campo;

    bool apresentar = true;

    while(apresentar){

        CLR_SCR;

        cout << texto1 << endl;
        cout << texto2 << endl;
        cout << texto3 << endl;
        cout << texto4 << endl;
        cout << texto5 << endl;
        cout << texto6 << endl;

        campo = getch() - 48;

        switch(campo) {
            case 1:
                    visualizar(matricula);
                    break;
            case 2:
                    cadastrar(matricula);
                    break;
            case 3:
                    editar(matricula);
                    break;
            case 4:
                    descadastrar(matricula);
                    break;
            case 5:
                    apresentar = false;
                    break;
        }
    }
}

void CntrIACasoDeTeste::cadastrar(Matricula matricula) {

    char texto1[] = "Insira os dados do seu caso de teste: ";
    char texto2[] = "Codigo:";
    char texto3[] = "Nome:";
    char texto4[] = "Data:";
    char texto5[] = "Acao:";
    char texto6[] = "Resposta";
    char texto7[] = "Resultado:";
    char texto8[] = "Caso de teste cadastrado com sucesso. Digite algo para continuar.";
    char texto9[] = "Erro ao cadastrar caso de teste. Digite algo para continuar.";
    char texto10[] = "Formato invalido. Digite algo para continuar.";
    char texto11[] = "Código correspondente ao teste: ";

    string campo1, campo2, campo3, campo4, campo5, campo6, campo7;

    Codigo codigo;
    Texto nome;
    Data data;
    Texto acao;
    Texto resposta;
    Resultado resultado;
    Codigo casoDeTeste;

    CLR_SCR;

    cout << texto1 << endl;
    cout << texto2 << " ";
    getline(cin, campo1);
    cout << texto3 << " ";
    getline(cin, campo2);
    cout << texto4 << " ";
    getline(cin, campo3);
    cout << texto5 << " ";
    getline(cin, campo4);
    cout << texto6 << " ";
    getline(cin, campo5);
    cout << texto7 << " ";
    getline(cin, campo6);
    cout << texto11 << " ";
    getline(cin, campo7);

    try {
        codigo.setValor(string(campo1));
        nome.setValor(string(campo2));
        data.setValor(string(campo3));
        acao.setValor(string(campo4));
        resposta.setValor(string(campo5));
        resultado.setValor(string(campo6));
        casoDeTeste.setValor(string(campo7));
    }
    catch(invalid_argument &excecao) {
        cout << texto10 << endl;
        getch();
        return;
    }

    CasoDeTeste caso_de_teste;
    caso_de_teste.setCodigo(codigo);
    caso_de_teste.setNome(nome);
    caso_de_teste.setData(data);
    caso_de_teste.setAcao(acao);
    caso_de_teste.setResposta(resposta);
    caso_de_teste.setResultado(resultado);
    caso_de_teste.setCodigoTeste(casoDeTeste);

    if(cntrISCasoDeTeste->cadastrar(caso_de_teste)) {
        cout << texto8 << endl;
        getch();
        return;
    }

    cout << texto9 << endl;
    getch();

    return;
}

void CntrIACasoDeTeste::visualizar(Matricula matricula) {

    CLR_SCR;

    char texto1[] = "Digite o codigo do caso de teste que deseja visualizar: ";
    char texto2[] = "Codigo:";
    char texto3[] = "Nome:";
    char texto4[] = "Data:";
    char texto5[] = "Acao:";
    char texto6[] = "Resposta";
    char texto7[] = "Resultado:";
    char texto8[] = "Digite qualquer tecla para continuar.";
    char texto9[] = "Formato invalido. Tente novamente.";
    char texto10[] = "Código do teste correspondente: ";

    string campo;
    Codigo codigo;
    CasoDeTeste caso_de_teste;

    cout << texto1;
    getline(cin, campo);

    try {
        codigo.setValor(campo);
        caso_de_teste = cntrISCasoDeTeste->visualizar(codigo);
        cout << texto2 << caso_de_teste.getCodigo().getValor() << endl;
        cout << texto3 << caso_de_teste.getNome().getValor() << endl;
        cout << texto4 << caso_de_teste.getData().getValor() << endl;
        cout << texto5 << caso_de_teste.getAcao().getValor() << endl;
        cout << texto6 << caso_de_teste.getResposta().getValor() << endl;
        cout << texto7 << caso_de_teste.getResultado().getValor() << endl;
        cout << texto10 << caso_de_teste.getCodigoTeste().getValor() << endl;
        cout << texto8 << endl;
        getch();
    }
    catch (...) {
        cout << texto9 << endl;
        getch();
        return;
    }
}

void CntrIACasoDeTeste::editar(Matricula matricula) {

    Codigo codigo;
    Texto nome;
    Data data;
    Texto acao;
    Texto resposta;
    Resultado resultado;
    Codigo casoDeTeste;
    CasoDeTeste caso_de_teste;

    char texto1[] = "Insira o codigo do caso de teste que deseja editar: ";
    char texto2[] = "Aqui estao os dados atuais do seu teste: ";
    char texto3[] = "Codigo: ";
    char texto4[] = "Nome: ";
    char texto5[] = "Data: ";
    char texto6[] = "Acao: ";
    char texto7[] = "Resposta: ";
    char texto8[] = "Resultado: ";
    char texto9[] = "Codigo do teste correspondente: ";
    char texto10[] = "------------------------------------";
    char texto11[] = "Insira os novos dados do seu caso de teste: ";
    char texto12[] = "Dados invalidos. Tente novamente.";
    char texto13[] = "1 - Inserir novamente.";
    char texto14[] = "2 - Retornar.";
    char texto15[] = "Caso de teste atualizado com sucesso.";
    char texto16[] = "Falha ao editar caso de teste.";

    int campo;
    string campoCodigo, campo1, campo2, campo3, campo4, campo5;
    bool apresentar = true;

    CLR_SCR;

    cout << texto1;
    getline(cin, campoCodigo);

    try {
        codigo.setValor(campoCodigo);
        caso_de_teste = cntrISCasoDeTeste->visualizar(codigo);
    }
    catch(...) {
        cout << texto12 << endl;
        getch();
        return;
    }

    while(apresentar) {
        try {
            CLR_SCR;

            cout << texto2 << endl;
            cout << texto3 << caso_de_teste.getCodigo().getValor() << endl;
            cout << texto4 << caso_de_teste.getNome().getValor() << endl;
            cout << texto5 << caso_de_teste.getData().getValor() << endl;
            cout << texto6 << caso_de_teste.getAcao().getValor() << endl;
            cout << texto7 << caso_de_teste.getResposta().getValor() << endl;
            cout << texto8 << caso_de_teste.getResultado().getValor() << endl;
            cout << texto9 << caso_de_teste.getCodigoTeste().getValor() << endl;
            cout << texto10 << endl;
            cout << texto11 << endl;

            cout << texto4;
            cin.ignore();
            getline(cin, campo1);

            cout << texto5;
            getline(cin, campo2);

            cout << texto6;
            getline(cin, campo3);

            cout << texto7;
            getline(cin, campo4);

            cout << texto8;
            getline(cin, campo5);

            nome.setValor(campo1);
            data.setValor(campo2);
            acao.setValor(campo3);
            resposta.setValor(campo4);
            resultado.setValor(campo5);
            caso_de_teste.setNome(nome);
            caso_de_teste.setData(data);
            caso_de_teste.setAcao(acao);
            caso_de_teste.setResposta(resposta);
            caso_de_teste.setResultado(resultado);

            apresentar = false;
        }
        catch(invalid_argument &excecao) {
            cout << texto12 << endl;
            cout << texto13 << endl;
            cout << texto14 << endl;
            campo = getch() - 48;
            if (campo == 5) {
                return;
            }
            getch();
        }
    }
    if (cntrISCasoDeTeste->editar(caso_de_teste)) {
        cout << texto15 << endl;
    } else {
        cout << texto16 << endl;
    }
    cout << texto16 << endl;
    getch();
}

bool CntrIACasoDeTeste::descadastrar(Matricula matricula) {

    char texto1[] = "Insira o codigo do caso de teste que deseja descadastrar: ";
    char texto2[] = "Tem certeza que deseja descadastrar Caso de teste?";
    char texto3[] = "1 - Sim.";
    char texto4[] = "2 - Nao.";
    char texto5[] = "Falha na exclusao. Tente novamente.";
    char texto6[] = "Descadastramento cancelado.";
    char texto7[] = "Descadastramento realizado com sucesso";
    char texto8[] = "Formato invalido. Pressione qualquer tecla para continaur.";

    int campo;
    string campoCodigo;
    Codigo codigo;

    CLR_SCR;

    cout << texto1;
    getline(cin, campoCodigo);

    try {
        codigo.setValor(campoCodigo);
    }
    catch(invalid_argument &excecao) {
        cout << texto8 << endl;
        getch();
        return false;
    }

    CLR_SCR;

    cout << texto2 << endl;
    cout << texto3 << endl;
    cout << texto4 << endl;

    campo = getch() - 48;

    switch(campo) {
        case 1:
            if (cntrISCasoDeTeste->descadastrar(codigo)) {
                cout << texto7 << endl;
                getch();
                return true;
            } else {
                cout << texto5 << endl;
                getch();
                return false;
            }
        case 2:
            cout << texto6 << endl;
            getch();
            return false;
    }
    return false;
}

// SERVICO CASO DE TESTE
bool CntrISCasoDeTeste::cadastrar(const CasoDeTeste &casoDeTeste) {
    ComandoCadastrarCasoDeTeste cadastrarCasoDeTeste(casoDeTeste);
    return cadastrarCasoDeTeste.executar();
}

CasoDeTeste CntrISCasoDeTeste::visualizar(const Codigo &codigo) {
    ComandoPesquisarCasosDeTeste pesquisarCasoDeTeste(codigo);
    pesquisarTeste.executar();
    CasoDeTeste casoDeTeste;
    casoDeTeste = pesquisarTeste.getResultado();

    return casoDeTeste;
}

bool CntrISCasoDeTeste::editar(const CasoDeTeste &casoDeTeste) {
    ComandoAtualizarCasoDeTeste atualizarCasoDeTeste(casoDeTeste);
    return atualizarCasoDeTeste.executar();
}

bool CntrISCasoDeTeste::descadastrar(const Codigo &codigo) {
    ComandoDeletarCasoDeTeste deletarCasoDeTeste(codigo);
    return deletarCasoDeTeste.executar();
}

