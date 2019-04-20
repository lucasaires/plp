#include <iostream>
#include <string>
#import "constantes.cpp"
#import "utilitario.cpp"
#import "usuario.model.cpp"
#import "usuariodb.cpp"

using namespace std;

int cadastroUsuario();

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
 * Exibe o formulario de cadastro de usuario.
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
    usuario.ficcao =  (escolha ==  's' || escolha == 'S') ? 1 : 0;
    cout << "Tem interesse em livros de nao ficcao? (S/N): ";
    cin >> escolha;
    usuario.naoFiccao =  (escolha ==  's' || escolha == 'S') ? 1 : 0;
    cout << "Tem interesse em livros de romance? (S/N): ";
    cin >> escolha;
    usuario.romance =  (escolha ==  's' || escolha == 'S') ? 1 : 0;
    cout << "Tem interesse em livros de horror? (S/N): ";
    cin >> escolha;
    usuario.horror =  (escolha ==  's' || escolha == 'S') ? 1 : 0;
    cout << "Tem interesse em livros de biografia? (S/N): ";
    cin >> escolha;
    usuario.biografia =  (escolha ==  's' || escolha == 'S') ? 1 : 0;

    retorno = insereUsuario(usuario);

    if (!retorno) {
        exibeMensagem("Perfil criado com sucesso.");
    }

    return retorno;
}
