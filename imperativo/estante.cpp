#include <iostream>
#include <string>
#include "constantes.cpp"
#include "utilitario.cpp"

using namespace std;

vector<struct Estante> estantes;
void listagemEstantes(struct Usuario &usuario);
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