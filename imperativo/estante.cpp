#include <iostream>
#include <string>
#include "constantes.cpp"
#include "utilitario.cpp"

using namespace std;

vector<struct Estante> estantes;

void listagemEstantes(struct Usuario &usuario);
int mudaSituacao(struct Usuario &usuario);
vector<Livro> obtemLivrosEstante(vector<struct Estante> estantes);
string obtemSituacao(int status);

/**
 * Lista todos os livros disponiveis na estante.
 */
void listagemEstantes(struct Usuario &usuario) {
    if (!listaLivrosEstante(usuario)) {
        if (usuario.estantes.size() == 0) {
            cout << "--- Nenhum livro encontrado! ---" << endl << endl;
        } else {
            string linha;

            for (size_t indice = 0; indice < usuario.estantes.size(); indice++) {
                struct Estante estante = usuario.estantes.at(indice);
                cout << "#" << estante.livro.id << " - " << estante.livro.nome << " - " << estante.livro.autor << " ("
                     << estante.livro.paginas << "pgs) [" << obtemSituacao(estante.situacao) << "]" << endl;
            }
            cout << endl;
        }
    }
}

/**
 * Muda a situacao do livro da estante.
 *
 * @param usuario
 * @return 0 (sucesso) e 1 (erro)
 */
int mudaSituacao(struct Usuario &usuario) {
    int retorno, situacao;

    struct Livro livro;
    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Mudar Status de Leitura  - " << endl << endl;
    livro.id = 0;
    escolheLivro(obtemLivrosEstante(usuario.estantes), livro);
    cout << "Digite o status de leitura do livro (Nao Lido[1], Lendo[2], Lido[3], Abandonei[4]) : ";
    cin >> situacao;
    retorno = mudarSituacao(usuario.id, livro.id, situacao);

    if (!retorno)
        exibeMensagem("O status da leitura modificado com sucesso.");

    return retorno;
}

/**
 * Retorna todos os livros adicionados na estante.
 *
 * @param estantes
 * @return
 */
vector<Livro> obtemLivrosEstante(vector<struct Estante> estantes) {
    vector<Livro> livros;

    for (size_t indice = 0; indice < estantes.size(); indice++)
        livros.push_back(estantes.at(indice).livro);

    return livros;
}

/**
 * Retorna em formato string a situacao atual do livro.
 *
 * @param status
 * @return
 */
string obtemSituacao(int status) {
    string situacao = "Nao Lido";

    if (status == LIDO) {
        situacao = "Lido";
    } else if (status == LENDO) {
        situacao = "Lendo";
    } else if (status == ABANDONEI) {
        situacao = "Abandonei";
    }

    return situacao;
}