#include <iostream>
#include <string>
#include "constantes.cpp"
#include "utilitario.cpp"
#include "livro.struct.cpp"
#include "livrodb.cpp"
#include "estantedb.cpp"

using namespace std;

vector<struct Livro> livros;

int adicionaLivro(struct Usuario usuario);
int cadastroLivro();
int edicaoLivro();
void escolheLivro(vector<struct Livro> livros, struct Livro &livro);
void listagemLivros();
struct Livro localizaLivroPorID(vector<struct Livro> livros, int id);
string obtemGenerosExistentes(struct Livro &livro);
int remocaoLivro();

/**
 * Adiciona o livro na estante do usuario logado.
 *
 * @param usuario
 * @return
 */
int adicionaLivro(struct Usuario usuario) {
    int retorno = 0;
    char adicao = 'S';
    struct Livro livro;

    while (adicao != 'N' && adicao != 'n') {
        cout << " .::. PrompSkoob .::." << endl;
        cout << " - Adicionar Livro na Estante  - " << endl << endl;
        livro.id = 0;
        escolheLivro(livros, livro);
        retorno = adicionaLivroEstante(usuario.id, livro.id);

        if (!retorno)
            exibeMensagem("Livro adicionado a sua estante com sucesso.");

        cout << "Deseja adicionar outro livro a sua estante? (S/N): ";
        cin >> adicao;
    }

    return retorno;
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

    if (!retorno)
        exibeMensagem("Livro criado com sucesso.");

    return retorno;
}

/**
 * Exibe a edicao do perfil do usuario.
 *
 * @param livro
 * @return 0 (sucesso) e 1 (erro)
 */
int edicaoLivro() {
    int retorno, campo;
    char genero;
    char edicao = 'S';
    struct Livro livro;
    livro.id = 0;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Editar Livro - " << endl << endl;
    escolheLivro(livros, livro);

    cout << "Qual campo deseja modificar?" << endl;
    cout << "(1) Nome: " << livro.nome << endl;
    cout << "(2) Autor: " << livro.autor << endl;
    cout << "(3) Total Paginas: " << livro.paginas << endl;
    char ficcao = (livro.ficcao == 1) ? 'S' : 'N';
    cout << "(4) Ficcao: " << ficcao << endl;
    char naoFiccao = (livro.naoFiccao == 1) ? 'S' : 'N';
    cout << "(5) Nao Ficcao: " << naoFiccao << endl;
    char romance = (livro.romance == 1) ? 'S' : 'N';
    cout << "(6) Romance: " << romance << endl;
    char horror = (livro.horror == 1) ? 'S' : 'N';
    cout << "(7) Horror: " << horror << endl;
    char biografia = (livro.biografia == 1) ? 'S' : 'N';
    cout << "(8) Biografia: " << biografia << endl;

    while (edicao != 'N' && edicao != 'n') {
        cout << "Campo: ";
        cin >> campo;

        switch (campo) {
            case 1:
                cout << "Nome: ";
                getline(cin >> ws, livro.nome);
                break;
            case 2:
                cout << "Autor: ";
                getline(cin >> ws, livro.autor);
                break;
            case 3:
                cout << "Total de Paginas: ";
                cin >> livro.paginas;
                break;
            case 4:
                cout << "Livro de ficcao? (S/N): ";
                cin >> genero;
                livro.ficcao = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            case 5:
                cout << "Livro de nao ficcao? (S/N): ";
                cin >> genero;
                livro.naoFiccao = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            case 6:
                cout << "Livro de romance? (S/N): ";
                cin >> genero;
                livro.romance = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            case 7:
                cout << "Livro de horror? (S/N): ";
                cin >> genero;
                livro.horror = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            case 8:
                cout << "Livro de biografia? (S/N): ";
                cin >> genero;
                livro.biografia = (genero == 's' || genero == 'S') ? 1 : 0;
                break;
            default:
                exibeMensagemErro("Campo invalido!");
        }

        cout << "Deseja editar outro campo? (S/N): ";
        cin >> edicao;
    }

    retorno = editaLivro(livro);

    if (!retorno)
        exibeMensagem("Livro editado com sucesso.");

    return retorno;
}

/**
 * Lista todos os livros cadastrados no PrompSkoob.
 */
void listagemLivros() {
    if (!listaLivros(livros)) {
        if (livros.size() == 0) {
            cout << "--- Nenhum livro encontrado! ---" << endl << endl;
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
 * Localiza um livro da listagem atraves do ID.
 *
 * @param livros
 * @param id
 * @return
 */
struct Livro localizaLivroPorID(vector<struct Livro> livros, int id) {
    struct Livro livro;

    for (size_t indice = 0; indice < livros.size(); indice++) {
        livro = livros.at(indice);

        if (livro.id == id)
            return livro;
    }

    livro.id = 0;

    return livro;
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

/**
 * Remove um livro.
 *
 * @return 0 (sucesso) e 1 (erro)
 */
int remocaoLivro() {
    int retorno;
    struct Livro livro;
    livro.id = 0;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Remover Livro - " << endl << endl;
    escolheLivro(livros, livro);

    char confirmacao;
    cout << "Deseja realmente remover este livro? (S/N) : ";
    cin >> confirmacao;
    cout << endl;

    if (confirmacao == 's' || confirmacao == 'S') {
        retorno = removeLivro(livro.id);

        if (!retorno)
            exibeMensagem("Livro removido com sucesso.");

        return retorno;
    }

    return retorno;
}

/**
 * Escolhe o livro de acordo com ID do livro.
 * @param livro
 */
void escolheLivro(vector<struct Livro> livros, struct Livro &livro) {
    int idLivro;

    while (livro.id == 0) {
        cout << "Informe o ID do livro: ";
        cin >> idLivro;
        cout << endl;
        livro = localizaLivroPorID(livros, idLivro);

        if (livro.id == 0)
            exibeMensagemErro("O ID informado invalido!");
    }
}