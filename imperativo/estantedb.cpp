#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "constantes.cpp"
#include "utilitario.cpp"

using namespace std;

int adicionaLivroEstante(int idUsuario, int idLivro);
void criaTabelaEstante();

void criaTabelaEstante() {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao criar a tabela de estante: ";

    if (retorno)
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;

    string sql = "CREATE TABLE IF NOT EXISTS estante("
                 "id_usuario INT NOT NULL, "
                 "id_livro INT NOT NULL, "
                 "nota INT NOT NULL, "
                 "situacao INT NOT NULL, "
                 "FOREIGN KEY (id_usuario) REFERENCES usuario(id) ON UPDATE CASCADE ON DELETE CASCADE, "
                 "FOREIGN KEY (id_livro) REFERENCES livro(id) ON UPDATE CASCADE ON DELETE CASCADE, "
                 "UNIQUE(id_usuario, id_livro));";

    retorno = sqlite3_exec(bancoDados, sql.c_str(), NULL, 0, &erroBanco);

    if (retorno != SQLITE_OK) {
        cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_free(erroBanco);
    }

    sqlite3_close(bancoDados);
}

/**
 * Adiciona um livro na estante.
 *
 * @param idUsuario
 * @param idLivro
 * @return 0 (sucesso) e 1 (erro)
 */
int adicionaLivroEstante(int idUsuario, int idLivro) {
    criaTabelaEstante();

    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao adicionar livro na estante: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "INSERT INTO estante(id_usuario, id_livro, nota, situacao) VALUES(" + to_string(idUsuario) + ", " +
                 to_string(idLivro) + ", 0, " + to_string(NAO_LIDO) + ");";

    retorno = sqlite3_exec(bancoDados, sql.c_str(), NULL, 0, &erroBanco);

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
        sqlite3_free(erroBanco);
        sqlite3_close(bancoDados);

        return 1;
    }

    sqlite3_close(bancoDados);

    return 0;
}
