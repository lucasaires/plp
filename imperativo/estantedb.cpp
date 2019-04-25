#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "constantes.cpp"
#include "estante.struct.cpp"
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

/**
 * Lista todos os livros da estante do usuario.
 *
 * @param livros
 * @return 0 (sucesso) e 1 (erro)
 */
int listaLivrosEstante(struct Usuario &usuario) {
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao listar livros da estante: ";
    usuario.estantes.clear();

    if (retorno != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT id_livro, nome, autor, paginas, nota, situacao FROM estante INNER JOIN livro ON "
                 "livro.id = id_livro WHERE id_usuario = " + to_string(usuario.id) + " ;";
    retorno = sqlite3_prepare(bancoDados, sql.c_str(), -1, &stmt, NULL);

    if (retorno != SQLITE_OK) {
        cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    while (true) {
        retorno = sqlite3_step(stmt);

        if (retorno == SQLITE_DONE) break;

        if (retorno != SQLITE_ROW) {
            cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bancoDados);

            return 1;
        }

        struct Estante estante;
        estante.livro.id = sqlite3_column_int(stmt, 0);
        estante.livro.nome = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        estante.livro.autor = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        estante.livro.paginas = sqlite3_column_int(stmt, 3);
        estante.nota = sqlite3_column_int(stmt, 4);
        estante.situacao = sqlite3_column_int(stmt, 5);
        usuario.estantes.push_back(estante);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}
