#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "constantes.cpp"

using namespace std;

void criaTabelaLivros()
{
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao criar a tabela de livros: ";

    if (retorno) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
    }

    string sql = "CREATE TABLE IF NOT EXISTS livros("
                 "id INT PRIMARY KEY NOT NULL, "
                 "nome TEXT NOT NULL, "
                 "escritor TEXT NOT NULL, "
                 "paginas INT NOT NULL, "
                 "qnt_leitores INT NOT NULL, "
                 "nota REAL NOT NULL, "
                 "genero INT NOT NULL);";

    retorno = sqlite3_exec(bancoDados, sql.c_str(), NULL, 0, &erroBanco);

    if (retorno != SQLITE_OK) {
        cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_free(erroBanco);
    }

    sqlite3_close(bancoDados);
}


/**
 * Consulta um livro.
 * @param id
 * @return 0 (sucesso) e 1 (erro)
 */
int consultaLivro(vector<string> &livros, int id)
{
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao consultar o livro: ";

    if (retorno != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT * FROM livros WHERE id = " + to_string(id) + ";";
    retorno = sqlite3_prepare(bancoDados, sql.c_str(), -1, &stmt, NULL);

    if (retorno != SQLITE_OK) {
        cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    while(true) {
        retorno = sqlite3_step(stmt);

        if (retorno == SQLITE_DONE) break;

        if (retorno != SQLITE_ROW) {
            cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bancoDados);

            return 1;
        }

        const char *idLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        const char *nomeLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        const char *escritorLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        const char *paginasLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        const char *qnt_leitoresLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        const char *notaLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
        const char *generoLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));

        livros.push_back(idLivros);
        livros.push_back(nomeLivros);
        livros.push_back(escritorLivros);
        livros.push_back(paginasLivros);
        livros.push_back(qnt_leitoresLivros);
        livros.push_back(notaLivros);
        livros.push_back(generoLivros);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}

/**
 * Insere as informacoes de livro.
 * @param id
 * @param nome
 * @param escritor
 * @param paginas
 * @param genero
 * @return 0 (sucesso) e 1 (erro)
 */
int insereLivro(int id, string nome, string escritor, int paginas, int genero)
{
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao inserir livros: ";

    if (retorno != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "INSERT INTO livros(id, nome, escritor, paginas, qnt_leitores, nota, genero) "
                 "VALUES('" + to_string(id) + "', '" + nome + "', '" + escritor + "', '" + to_string(paginas) + "', '" +
                 to_string(0) + "', '" + to_string(0.0) + "', '" + to_string(genero) +"');";
    retorno = sqlite3_exec(bancoDados, sql.c_str(), NULL, 0, &erroBanco);

    if (retorno != SQLITE_OK) {
        cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_free(erroBanco);
        sqlite3_close(bancoDados);

        return 1;
    }

    sqlite3_close(bancoDados);

    return 0;
}

int removeLivro(int id)
{
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao remover livros: ";

    if (retorno != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "DELETE FROM livros WHERE id = " + to_string(id) + ";";

    retorno = sqlite3_exec(bancoDados, sql.c_str(), NULL, 0, &erroBanco);

    if (retorno != SQLITE_OK) {
        cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_free(erroBanco);
        sqlite3_close(bancoDados);

        return 1;
    }

    sqlite3_close(bancoDados);

    return 0;
}

/**
 * Lista todos os Livros.
 * @param livros
 * @return 0 (sucesso) e 1 (erro)
 */
int listaTodosLivros(vector<vector<string> > &livros)
{
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

    string sql = "SELECT * FROM livros;";
    retorno = sqlite3_prepare(bancoDados, sql.c_str(), -1, &stmt, NULL);

    if (retorno != SQLITE_OK) {
        cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    while(true) {
        retorno = sqlite3_step(stmt);

        if (retorno == SQLITE_DONE) break;

        if (retorno != SQLITE_ROW) {
            cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bancoDados);

            return 1;
        }

        const char *idLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        const char *nomeLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        const char *escritorLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        const char *paginasLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        const char *qnt_leitoresLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        const char *notaLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
        const char *generoLivros = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));

        vector<string> livro;
        livro.push_back(idLivros);
        livro.push_back(nomeLivros);
        livro.push_back(escritorLivros);
        livro.push_back(paginasLivros);
        livro.push_back(qnt_leitoresLivros);
        livro.push_back(notaLivros);
        livro.push_back(generoLivros);

        livros.push_back(livro);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}