#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "estante.struct.cpp"

using namespace std;

int adicionaLivroEstante(int idUsuario, int idLivro);
int avaliaLivro(int idUsuario, int idLivro, int nota);
void criaTabelaEstante();
int listaLivrosEstante(struct Usuario &usuario);
int mudaSituacao(int idUsuario, int idLivro, int situacao);
int registraLeitura(struct Estante &estante);
int removeLivroEstante(int idUsuario, int idLivro);

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
                 "nota REAL NOT NULL, "
                 "situacao INT NOT NULL, "
                 "paginas_lidas INT, "
                 "comentario TEXT, "
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
 * Avalia um livro da estante.
 *
 * @param idUsuario
 * @param idLivro
 * @param nota
 * @return 0 (sucesso) e 1 (error)
 */
int avaliaLivro(int idUsuario, int idLivro, int nota) {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao avaliar o livro da estante: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "UPDATE estante SET nota = " + to_string(nota) + " WHERE id_livro = " + to_string(idLivro) +
                 " AND id_usuario = " + to_string(idUsuario) + ";";

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
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql =
            "SELECT id_livro, nome, autor, paginas, nota, situacao, paginas_lidas, comentario, COUNT(id_livro) AS "
            "leitores, (SELECT AVG(nota) FROM estante WHERE livro.id = id_livro) AS nota_geral FROM estante INNER "
            "JOIN livro ON livro.id = id_livro WHERE id_usuario = " + to_string(usuario.id) + " ;";

    retorno = sqlite3_prepare(bancoDados, sql.c_str(), -1, &stmt, NULL);

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    while (true) {
        retorno = sqlite3_step(stmt);

        if (retorno == SQLITE_DONE) break;

        if (retorno != SQLITE_ROW) {
            cout << "erro sqlite" << endl;
            exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
            sqlite3_finalize(stmt);
            sqlite3_close(bancoDados);

            return 1;
        }

        if (sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
            struct Estante estante;
            estante.livro.id = sqlite3_column_int(stmt, 0);
            estante.idLivro = sqlite3_column_int(stmt, 0);
            estante.idUsuario = usuario.id;
            estante.livro.nome = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            estante.livro.autor = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            estante.livro.paginas = sqlite3_column_int(stmt, 3);
            estante.nota = sqlite3_column_double(stmt, 4);
            estante.situacao = sqlite3_column_int(stmt, 5);
            estante.paginasLidas = sqlite3_column_int(stmt, 6);
            estante.comentario = "";

            if (sqlite3_column_type(stmt, 7) != SQLITE_NULL)
               estante.comentario = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));

            estante.livro.leitores = sqlite3_column_int(stmt, 8);
            estante.livro.notaGeral = sqlite3_column_double(stmt, 9);
            usuario.estantes.push_back(estante);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}

/**
 * Muda a situacao do livro.
 *
 * @param idUsuario
 * @param idLivro
 * @param situacao
 * @return 0 (sucesso) e 1 (error)
 */
int mudaSituacao(int idUsuario, int idLivro, int situacao) {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao modificar situacao do livro: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "UPDATE estante SET situacao = " + to_string(situacao) + " WHERE id_livro = " + to_string(idLivro) +
                 " AND id_usuario = " + to_string(idUsuario) + ";";

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
 * Registra a leitura de um livro da estante.
 *
 * @param estante
 * @return 0 (sucesso) e 1 (error)
 */
int registraLeitura(struct Estante &estante) {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao registrar a leitura do livro da estante: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "UPDATE estante SET paginas_lidas = " + to_string(estante.paginasLidas) + ", comentario = '" +
                 estante.comentario + "' WHERE id_livro = " + to_string(estante.idLivro) + " AND id_usuario = " +
                 to_string(estante.idUsuario) + ";";

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
 * Remove o livro da estante do usuario.
 *
 * @param idUsuario
 * @param idLivro
 * @return 0 (sucesso) e 1 (erro)
 */
int removeLivroEstante(int idUsuario, int idLivro) {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao remover livro da minha estante: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "DELETE FROM estante WHERE id_usuario = " + to_string(idUsuario) + " AND id_livro = "
                 + to_string(idLivro) + ";";

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