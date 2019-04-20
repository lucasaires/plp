#include <iostream>
#include <string>
#import "constantes.cpp"
#import "utilitario.cpp"
#import "usuario.model.cpp"
#import "usuariodb.cpp"

using namespace std;

void cadastroUsuario();

/**
 * Exibe o formulario de cadastro de usuario.
 */
void cadastroUsuario() {
    struct Usuario usuario;
    char escolha;

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

    if (insereUsuario(usuario) == 0) {
        exibeMensagem("Perfil criado com sucesso.");
    }
}
