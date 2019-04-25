#include <iostream>
#include <string>
#include "constantes.cpp"
#include "utilitario.cpp"
#include "livro.struct.cpp"
#include "livrodb.cpp"

using namespace std;

int cadastroLivro();
void exibeMenuLivro();
void listagemLivros();
string obtemGenerosExistentes(struct Livro &livro);

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

/**
 * Exibe a listagem de livros juntamente com o submenu.
 * 1 - Cadastrar livros
 * 2 - Editar livro
 * 3 - Remover livro
 * 4 - Voltar para o menu principal
 */
void exibeMenuLivro() {
    int opcao;

    while (opcao != 4) {
        cout << " .::. PrompSkoob .::." << endl;
        cout << " - Gerenciar Livro - " << endl << endl;
        listagemLivros();
        cout << " (1) Cadastrar | (2) Editar | (3) Remover | (4) Voltar" << endl << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 1:
                cadastroLivro();
                break;
            default:
                if (opcao != 4)
                    exibeMensagemErro("Opcao invalida!");
        }
    }
}

/**
 * Lista todos os livros cadastrados no PrompSkoob.
 */
void listagemLivros() {
    vector<struct Livro> livros;

    if (!listaLivros(livros)) {
        if (livros.size() == 0) {
            cout << "--- Nenhum livro cadastrado! ---" << endl << endl;
        } else {
            string linha;

            for (size_t indice = 0; indice < livros.size(); indice++) {
                struct Livro livro = livros.at(indice);
                cout << "#" << livro.id << " - " << livro.nome << " - " << livro.autor << " (" << livro.paginas
                     << "pgs) " << obtemGenerosExistentes(livro) << endl;
            }
            cout << endl;
        }
    }
}

/**
 * Retorna em formato string todos os generos separados por virgulas. Ex.: (Ficcao, Biografia)
 *
 * @param livro
 * @return
 */
string obtemGenerosExistentes(struct Livro &livro) {
    string generos = "";
    generos += (livro.ficcao) ? "Ficcao, " : "";
    generos += (livro.naoFiccao) ? "Nao Ficcao, " : "";
    generos += (livro.romance) ? "Romance, " : "";
    generos += (livro.horror) ? "Horror, " : "";
    generos += (livro.biografia) ? "Biografia, " : "";
    generos = (generos.size() > 0) ? ("(" + generos.substr(0, generos.size() - 2) + ")") : "";

    return generos;
}
