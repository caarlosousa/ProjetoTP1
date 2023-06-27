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
        cin >> campo1;
        cout << texto2 << " ";
        cin >> campo2;

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

    Desenvolvedor existente;
    existente = cntrISDesenvolvedor->visualizar(matricula);
    if (existente.getMatricula().getValor() == desenvolvedor.getMatricula().getValor()) {
        cout << texto9 << endl;
        getch();
        return;
    }

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
            cout << texto2 << "";
            getline(cin, campo1);
            cout << texto4 << "";
            getline(cin, campo2);
            cout << texto5 << "";
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


}

void CntrIATeste::editar(Matricula matricula) {

}

bool CntrIATeste::descadastrar(Matricula matricula) {
    return true;
}
