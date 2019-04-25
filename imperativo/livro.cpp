#include <iostream>
#include <string>
#include "constantes.cpp"
#include "utilitario.cpp"
#include "livro.struct.cpp"
#include "livrodb.cpp"

using namespace std;

int cadastroLivro();
void listagemLivros();

void listagemLivros() {
    vector<struct Livro> livros;

    if (!listaLivros(livros)) {
        if (livros.size() == 0) {
            cout << "--- Nenhum livro cadastrado! ---" << endl << endl;
        } else {
            string linha;

            for (size_t indice = 0; indice < livros.size(); indice++) {
                struct Livro livro = livros.at(indice);
                cout << "#" << livro.id << " " << livro.nome << " - " << livro.autor << "(" << livro.paginas << "pgs.)"
                     << endl;
            }
        }
    }
}

/**
 * Exibe o cadastro de livro.
 *
 * @return 0 (sucesso) e 1 (erro)
 */
int cadastroLivro() {
    int retorno;
    char escolha;
    struct Livro livro;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Cadastrar Livro - " << endl << endl;
    cout << "Nome: ";
    getline(cin >> ws, livro.nome);
    cout << "Autor: ";
    getline(cin >> ws, livro.autor);
    cout << "Total de páginas: ";
    cin >> livro.paginas;
    cout << "Este livro é de ficcao? (S/N): ";
    cin >> escolha;
    livro.ficcao = (escolha == 's' || escolha == 'S') ? 1 : 0;
    cout << "Este livro é de nao ficcao? (S/N): ";
    cin >> escolha;
    livro.naoFiccao = (escolha == 's' || escolha == 'S') ? 1 : 0;
    cout << "Este livro é de romance? (S/N): ";
    cin >> escolha;
    livro.romance = (escolha == 's' || escolha == 'S') ? 1 : 0;
    cout << "Este livro é de horror? (S/N): ";
    cin >> escolha;
    livro.horror = (escolha == 's' || escolha == 'S') ? 1 : 0;
    cout << "Este livro é de biografia? (S/N): ";
    cin >> escolha;
    livro.biografia = (escolha == 's' || escolha == 'S') ? 1 : 0;

    retorno = insereLivro(livro);

    if (!retorno) {
        exibeMensagem("Livro criado com sucesso.");
    }

    return retorno;
}