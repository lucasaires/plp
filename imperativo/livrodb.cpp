#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "constantes.cpp"
#include "utilitario.cpp"

using namespace std;

void criaTabelaLivro();
int insereLivro(struct Livro &livro);
int geraIDLivro();

void criaTabelaLivro() {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao criar a tabela de livro: ";

    if (retorno) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
    }

    string sql = "CREATE TABLE IF NOT EXISTS livro("
                 "id INT PRIMARY KEY NOT NULL, "
                 "nome TEXT NOT NULL, "
                 "autor TEXT NOT NULL, "
                 "paginas INT NOT NULL, "
                 "ficcao INT, "
                 "nao_ficcao INT, "
                 "romance INT, "
                 "horror INT, "
                 "biografia INT);";

    retorno = sqlite3_exec(bancoDados, sql.c_str(), NULL, 0, &erroBanco);

    if (retorno != SQLITE_OK) {
        cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_free(erroBanco);
    }

    sqlite3_close(bancoDados);
}

/**
 * Insere as informacoes de livro.
 *
 * @param livro
 * @return 0 (sucesso) e 1 (erro)
 */
int insereLivro(struct Livro &livro) {
    criaTabelaLivro();
    livro.id = geraIDLivro();

    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao inserir livro: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "INSERT INTO livro(id, nome, autor, paginas, ficcao, nao_ficcao, romance, horror, biografia) "
                 "VALUES('" + to_string(livro.id) + "', '" + livro.nome + "', '" + livro.autor + "', '" +
                 to_string(livro.paginas) + "', '" + to_string(livro.ficcao) + "', '" + to_string(livro.naoFiccao) +
                 "', '" + to_string(livro.romance) + "', '" + to_string(livro.horror) + "', '" +
                 to_string(livro.biografia) + "');";

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
 * Gera o proximo ID.
 * @param id
 * @return ultimo id (sucesso) e -1 (erro)
 */
int geraIDLivro() {
    int id = 1;
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao consultar o último ID do livro: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return -1;
    }

    string sql = "SELECT id FROM livro ORDER BY id DESC LIMIT 1;";
    retorno = sqlite3_prepare(bancoDados, sql.c_str(), -1, &stmt, NULL);

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return -1;
    }

    while (true) {
        retorno = sqlite3_step(stmt);

        if (retorno == SQLITE_DONE) break;

        if (retorno != SQLITE_ROW) {
            exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
            sqlite3_finalize(stmt);
            sqlite3_close(bancoDados);

            return -1;
        }
        id = sqlite3_column_int(stmt, 0);
        id += 1;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return id;
}

/**
 * Lista todos os livros.
 *
 * @param livros
 * @return 0 (sucesso) e 1 (erro)
 */
int listaLivros(vector<struct Livro> &livros) {
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao listar livros: ";

    if (retorno != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT * FROM livro;";
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

        struct Livro livro;
        livro.id = sqlite3_column_int(stmt, 0);
        livro.nome = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        livro.autor = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        livro.paginas = sqlite3_column_int(stmt, 3);
        livro.ficcao = sqlite3_column_int(stmt, 4);
        livro.naoFiccao = sqlite3_column_int(stmt, 5);
        livro.romance = sqlite3_column_int(stmt, 6);
        livro.horror = sqlite3_column_int(stmt, 7);
        livro.biografia = sqlite3_column_int(stmt, 8);
        livros.push_back(livro);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}