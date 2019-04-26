#include <iostream>
#include <string>
#include "constantes.cpp"
#include "utilitario.cpp"

using namespace std;

int avalicaoLivro(struct Usuario &usuario);
int edicaoSituacao(struct Usuario &usuario);
void listagemEstantes(struct Usuario &usuario);
struct Estante obtemEstantePorLivro(vector<struct Estante> estantes, struct Livro &livro);
vector<Livro> obtemLivrosEstante(vector<struct Estante> estantes);
string obtemSituacao(int status);
int registroLeitura(struct Usuario &usuario);
int remocaoLivroEstante(struct Usuario &usuario);

/**
 * Registra a leitura de um livro na estante.
 *
 * @param usuario
 * @return
 */
int registroLeitura(struct Usuario &usuario) {
    int retorno = 0;
    struct Livro livro;
    struct Estante estante;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Registrar Leitura - " << endl << endl;
    livro.id = 0;
    escolheLivro(obtemLivrosEstante(usuario.estantes), livro);
    estante = obtemEstantePorLivro(usuario.estantes, livro);
    cout << "Quantas paginas foram lidas? ";
    cin >> estante.paginasLidas;

    while (estante.paginasLidas < 0 || estante.paginasLidas > livro.paginas) {
        exibeMensagemErro("Numero de pagina invalida!");
        cout << "Informe outro numero de paginas: ";
        cin >> estante.paginasLidas;
    }

    cout << "Deixe seu comentario sobre o livro: ";
    getline(cin >> ws, estante.comentario);

    retorno = registraLeitura(estante);

    if (!retorno)
        exibeMensagem("Registro de leitura realizado com sucesso.");

    return retorno;
}

/**
 * Avalia o livro da estante.
 *
 * @param usuario
 * @return 0 (sucesso) e 1 (erro)
 */
int avalicaoLivro(struct Usuario &usuario) {
    int retorno, nota = 0;

    struct Livro livro;
    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Avaliar Livro da Estante  - " << endl << endl;
    livro.id = 0;
    escolheLivro(obtemLivrosEstante(usuario.estantes), livro);
    cout << "De sua nota de avalicao no intervalo de 1 a 5: ";
    cin >> nota;

    while (nota < 0 || nota > 5) {
        exibeMensagemErro("Nota invalida!");
        cout << "Informe outra nota:";
        cin >> nota;
    }

    retorno = avaliaLivro(usuario.id, livro.id, nota);

    if (!retorno)
        exibeMensagem("Avaliacao realizada com sucesso.");

    return retorno;
}

/**
 * Lista todos os livros disponiveis na estante.
 */
void listagemEstantes(struct Usuario &usuario) {
    if (!listaLivrosEstante(usuario)) {
        if (usuario.estantes.size() == 0) {
            exibeMensagem("Nenhum livro adicionado a sua estante!");
        } else {
            string linha;

            for (size_t indice = 0; indice < usuario.estantes.size(); indice++) {
                struct Estante estante = usuario.estantes.at(indice);
                cout << "#" << estante.livro.id << " - " << estante.livro.nome << " - " << estante.livro.autor << " ("
                     << estante.livro.paginas << "pgs) [" << obtemSituacao(estante.situacao) << "] - Minha Nota: "
                     << estante.nota;

                if (!estante.comentario.empty())
                    cout << " - Comentario: " << estante.comentario;

                cout << " - Paginas lidas: " << estante.paginasLidas << endl;
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
int edicaoSituacao(struct Usuario &usuario) {
    int retorno, situacao;

    struct Livro livro;
    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Mudar Status de Leitura  - " << endl << endl;
    livro.id = 0;
    escolheLivro(obtemLivrosEstante(usuario.estantes), livro);
    cout << "Digite o status de leitura do livro (Nao Lido[1], Lendo[2], Lido[3], Abandonei[4]): ";
    cin >> situacao;
    retorno = mudaSituacao(usuario.id, livro.id, situacao);

    if (!retorno)
        exibeMensagem("O status da leitura modificado com sucesso.");

    return retorno;
}

/**
 * Retorna a estante de acordo com o livro.
 *
 * @param estantes
 * @param livro
 * @return
 */
struct Estante obtemEstantePorLivro(vector<struct Estante> estantes, struct Livro &livro) {
    struct Estante estante;
    estante.idLivro = 0;

    for (size_t indice = 0; indice < estantes.size(); indice++) {
        if (estantes.at(indice).idLivro == livro.id) {
            return estantes.at(indice);
        }
    }

    return estante;
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

/**
 * Remove um livro da estante do usuario.
 *
 * @param usuario
 * @return 0 (sucesso) e 1 (erro)
 */
int remocaoLivroEstante(struct Usuario &usuario) {
    int retorno;
    struct Livro livro;
    livro.id = 0;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Remover Livro da Estante - " << endl << endl;
    escolheLivro(obtemLivrosEstante(usuario.estantes), livro);

    char confirmacao;
    cout << "Deseja realmente remover este livro da sua estante? (S/N) : ";
    cin >> confirmacao;
    cout << endl;

    if (confirmacao == 's' || confirmacao == 'S') {
        retorno = removeLivroEstante(usuario.id, livro.id);

        if (!retorno)
            exibeMensagem("Livro removido da estante com sucesso.");

        return retorno;
    }

    return retorno;
}