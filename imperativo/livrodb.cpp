#include <iostream>
#include <sqlite3.h>
#include <vector>

using namespace std;

void criaTabelaLivro();
int editaLivro(struct Livro &livro);
int insereLivro(struct Livro &livro);
int geraIDLivro();

int listaLivros(vector<struct Livro> &livros);

int recomendaLivros(vector<struct Livro> &livros, struct Usuario &usuario);

int removeLivro(int id);

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
 * Edita as informacoes de livro.
 *
 * @param livro
 * @return 0 (sucesso) e 1 (erro)
 */
int editaLivro(struct Livro &livro) {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao editar as informaçéos do livro: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "UPDATE livro "
                 "SET nome = '" + livro.nome + "', autor = '" + livro.autor + "', paginas = " +
                 to_string(livro.paginas) + ", ficcao = " + to_string(livro.ficcao) + ", nao_ficcao = " +
                 to_string(livro.naoFiccao) + ", romance = " + to_string(livro.romance) + ", horror = " +
                 to_string(livro.horror) + ", biografia = " + to_string(livro.biografia) + " WHERE id = " +
                 to_string(livro.id) + ";";

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
 * Insere as informacoes de livro.
 *
 * @param livro
 * @return 0 (sucesso) e 1 (erro)
 */
int insereLivro(struct Livro &livro) {
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
    livros.clear();

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT *, (SELECT COUNT(id_livro) FROM estante WHERE id_livro = id) AS leitores, "
                 "(SELECT AVG(nota) FROM estante WHERE id_livro = id) AS nota_geral FROM livro;";

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
            exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
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
        livro.leitores = sqlite3_column_int(stmt, 9);
        livro.notaGeral = sqlite3_column_double(stmt, 10);
        livros.push_back(livro);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}

 /**
  * Pesquisa livros por titulo.
  *
  * @param livros
  * @param titulo
  * @return 0 (sucesso) e 1 (erro)
  */
int pesquisaLivros(vector<struct Livro> &livros, string titulo) {
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao pesquisar livros por titulo: ";
    livros.clear();

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT *, (SELECT COUNT(id_livro) FROM estante WHERE id_livro = id) AS leitores, "
                 "(SELECT AVG(nota) FROM estante WHERE id_livro = id) AS nota_geral FROM livro WHERE nome like '%" +
                 titulo +"%';";

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
            exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
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
        livro.leitores = sqlite3_column_int(stmt, 9);
        livro.notaGeral = sqlite3_column_double(stmt, 10);
        livros.push_back(livro);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}

/**
 * Retorna os livros a serem recomendados para o usuario logado.
 *
 * @param livros
 * @param usuario
 * @return
 */
int recomendaLivros(vector<struct Livro> &livros, struct Usuario &usuario) {
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao recomendar livros para usuario: ";
    livros.clear();

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT *, (SELECT COUNT(id_livro) FROM estante WHERE id_livro = id) AS leitores, "
                 "(SELECT AVG(nota) FROM estante WHERE id_livro = id) AS nota_geral FROM livro ";

    string where = "WHERE ";
    where += (usuario.ficcao) ? "ficcao = 1 OR " : "";
    where += (usuario.naoFiccao) ? "nao_ficcao = 1 OR " : "";
    where += (usuario.romance) ? "romance = 1 OR " : "";
    where += (usuario.horror) ? "horror = 1 OR " : "";
    where += (usuario.biografia) ? "biografia = 1 OR " : "";
    where += "FALSE;";
    sql += where;

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
            exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
            sqlite3_finalize(stmt);
            sqlite3_close(bancoDados);

            return 1;
        }

        if (sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
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
            livro.leitores = sqlite3_column_int(stmt, 9);
            livro.notaGeral = sqlite3_column_double(stmt, 10);
            livros.push_back(livro);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}

/**
 * Remove o livro pelo id.
 *
 * @param id
 * @return 0 (sucesso) e 1 (erro)
 */
int removeLivro(int id) {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao remover livro: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "DELETE FROM livro "
                 "WHERE id = " + to_string(id) + ";";

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