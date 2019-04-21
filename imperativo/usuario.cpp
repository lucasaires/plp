#include <iostream>
#include <string>
#import "constantes.cpp"
#import "utilitario.cpp"
#import "usuario.model.cpp"
#import "usuariodb.cpp"

using namespace std;

int cadastroUsuario();
int edicaoPerfilUsuario(struct Usuario &usuario);
int remocaoUsuario(int id);

/**
 * Exibe o formulario de cadastro de usuario.
 */
struct Usuario autenticacaoUsuario() {
    struct Usuario usuario;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Autenticacao - " << endl << endl;
    cout << "E-mail: ";
    getline(cin >> ws, usuario.email);
    cout << "Senha: ";
    getline(cin, usuario.senha);

    if (autenticaUsuario(usuario) == 0 && usuario.id > 0) {
        exibeMensagem("Seja bem-vindo.");
    } else {
        exibeMensagemErro("Nao existe usuario com o e-mail ou senha informados.");
    }

    return usuario;
}

/**
 * Exibe o cadastro de usuario.
 *
 * @return 0 (sucesso) e 1 (erro)
 */
int cadastroUsuario() {
    int retorno;
    char escolha;
    struct Usuario usuario;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Quero me Cadastrar - " << endl << endl;
    cout << "Nome: ";
    getline(cin >> ws, usuario.nome);
    cout << "E-mail: ";
    getline(cin, usuario.email);
    cout << "Senha: ";
    getline(cin, usuario.senha);
    cout << "Tem interesse em livros de ficcao? (S/N): ";
    cin >> escolha;
    usuario.ficcao = (escolha == 's' || escolha == 'S') ? 1 : 0;
    cout << "Tem interesse em livros de nao ficcao? (S/N): ";
    cin >> escolha;
    usuario.naoFiccao = (escolha == 's' || escolha == 'S') ? 1 : 0;
    cout << "Tem interesse em livros de romance? (S/N): ";
    cin >> escolha;
    usuario.romance = (escolha == 's' || escolha == 'S') ? 1 : 0;
    cout << "Tem interesse em livros de horror? (S/N): ";
    cin >> escolha;
    usuario.horror = (escolha == 's' || escolha == 'S') ? 1 : 0;
    cout << "Tem interesse em livros de biografia? (S/N): ";
    cin >> escolha;
    usuario.biografia = (escolha == 's' || escolha == 'S') ? 1 : 0;

    retorno = insereUsuario(usuario);

    if (!retorno) {
        exibeMensagem("Perfil criado com sucesso.");
    }

    return retorno;
}

/**
 * Exibe a edicao do perfil do usuario.
 *
 * @param usuario
 * @return 0 (sucesso) e 1 (erro)
 */
int edicaoPerfilUsuario(struct Usuario &usuario) {
    int retorno, campo;
    char genero;
    char edicao = 'S';

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Editar Meu Perfil - " << endl << endl;
    cout << "Qual campo deseja modificar?" << endl;
    cout << "(1) Nome: " << usuario.nome << endl;
    cout << "(2) E-mail: " << usuario.email << endl;
    cout << "(3) Senha" << endl;

    char ficcao = (usuario.ficcao == 1) ? 'S' : 'N';
    cout << "(4) Interesse em Ficcao? (S/N): " << ficcao << endl;
    char naoFiccao = (usuario.naoFiccao == 1) ? 'S' : 'N';
    cout << "(5) Interesse em Não Ficcao? (S/N): " << naoFiccao << endl;
    char romance = (usuario.romance == 1) ? 'S' : 'N';
    cout << "(6) Interesse em Romance? (S/N): " << romance << endl;
    char horror = (usuario.horror == 1) ? 'S' : 'N';
    cout << "(7) Interesse em Horror? (S/N): " << horror << endl;
    char biografia = (usuario.biografia == 1) ? 'S' : 'N';
    cout << "(8) Interesse em Biografia? (S/N): " << biografia << endl;

    while (edicao != 'N' && edicao != 'n') {
        cout << "Campo: ";
        cin >> campo;

        switch (campo) {
            case 1:
                cout << "Nome: ";
                getline(cin >> ws, usuario.nome);
                break;
            case 2:
                cout << "E-mail: ";
                getline(cin >> ws, usuario.email);
                break;
            case 3:
                cout << "Senha: ";
                getline(cin >> ws, usuario.senha);
                break;
            case 4:
                cout << "Tem interesse em livros de ficcao? (S/N): ";
                cin >> genero;
                usuario.ficcao = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            case 5:
                cout << "Tem interesse em livros de nao ficcao? (S/N): ";
                cin >> genero;
                usuario.naoFiccao = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            case 6:
                cout << "Tem interesse em livros de romance? (S/N): ";
                cin >> genero;
                usuario.romance = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            case 7:
                cout << "Tem interesse em livros de horror? (S/N): ";
                cin >> genero;
                usuario.horror = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            case 8:
                cout << "Tem interesse em livros de biografia? (S/N): ";
                cin >> genero;
                usuario.biografia = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            default:
                exibeMensagemErro("Campo invalido!");
        }

        cout << "Deseja editar outro campo? (S/N): ";
        cin >> edicao;
    }

    retorno = editaUsuario(usuario);

    if (!retorno) {
        exibeMensagem("Perfil editado com sucesso.");
    }

    return retorno;
}

/**
 * Remove o perfil do usuario atual.
 *
 * @param id
 * @return 0 (sucesso) e 1 (erro)
 */
int remocaoUsuario(int id) {
    int retorno = removeUsuario(id);

    if(!retorno) {
        exibeMensagem("Usuario removido com sucesso.");
    }

    return retorno;
}
