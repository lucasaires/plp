#include <iostream>
#include <sqlite3.h>
#include <vector>
#import "constantes.cpp"
#import "utilitario.cpp"

using namespace std;

int autenticaUsuario(struct Usuario &usuario);
void criaTabelaUsuario();
int editaUsuario(struct Usuario &usuario);
int insereUsuario(struct Usuario &usuario);
int geraIDUsuario();
int removeUsuario(int id);

/**
 * Autentica o usuario atraves do email e senha.
 *
 * @param usuario
 * @return 0 (sucesso) e 1 (erro)
 */
int autenticaUsuario(struct Usuario &usuario) {
    criaTabelaUsuario();

    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao autenticar usuario: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Nao foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT id, nome, ficcao, nao_ficcao, romance, horror, biografia "
                 "FROM usuario "
                 "WHERE email = '" + usuario.email + "' AND senha = '" + usuario.senha + "' "
                 "LIMIT 1;";

    retorno = sqlite3_prepare(bancoDados, sql.c_str(), -1, &stmt, NULL);

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    while (true) {
        retorno = sqlite3_step(stmt);

        if (retorno == SQLITE_DONE)
            break;

        if (retorno != SQLITE_ROW) {
            exibeMensagemErroBancoDados(mensagemErro, sqlite3_errmsg(bancoDados));
            sqlite3_finalize(stmt);
            sqlite3_close(bancoDados);

            return 1;
        }

        usuario.id = sqlite3_column_int(stmt, 0);
        usuario.nome = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        usuario.ficcao = sqlite3_column_int(stmt, 2);
        usuario.naoFiccao = sqlite3_column_int(stmt, 3);
        usuario.romance = sqlite3_column_int(stmt, 4);
        usuario.horror = sqlite3_column_int(stmt, 5);
        usuario.biografia = sqlite3_column_int(stmt, 6);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}

void criaTabelaUsuario() {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao criar a tabela de usuario: ";

    if (retorno) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
    }

    string sql = "CREATE TABLE IF NOT EXISTS usuario("
                 "id INT PRIMARY KEY NOT NULL, "
                 "nome TEXT NOT NULL, "
                 "email TEXT NOT NULL UNIQUE, "
                 "senha INT NOT NULL, "
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
 * Edita as informacoes de usuario.
 *
 * @param usuario
 * @return 0 (sucesso) e 1 (erro)
 */
int editaUsuario(struct Usuario &usuario) {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao editar as informaçéos do usuário: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "UPDATE usuario "
                 "SET nome = '" + usuario.nome + "', "
                     "email = '" + usuario.email + "', "
                     "senha = '" + usuario.senha + "', "
                     "ficcao = '" + to_string(usuario.ficcao) + "', "
                     "nao_ficcao = '" + to_string(usuario.naoFiccao) + "', "
                     "romance = '" + to_string(usuario.romance) + "', "
                     "horror = '" + to_string(usuario.horror) + "', "
                     "biografia = '" + to_string(usuario.biografia) + "'"
                 "WHERE id = " + to_string(usuario.id) + ";";

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
 * Consulta um usuario.
 * @param id
 * @return ultimo id (sucesso) e -1 (erro)
 */
int geraIDUsuario() {
    int id = 1;
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao consultar usuário: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return -1;
    }

    string sql = "SELECT id FROM usuario ORDER BY id DESC LIMIT 1;";
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
 * Insere as informacoes de usuario.
 *
 * @param usuario
 * @return 0 (sucesso) e 1 (erro)
 */
int insereUsuario(struct Usuario &usuario) {
    criaTabelaUsuario();
    usuario.id = geraIDUsuario();

    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao inserir usuário: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "INSERT INTO usuario(id, nome, email, senha, ficcao, nao_ficcao, romance, horror, biografia) "
                 "VALUES('" + to_string(usuario.id) + "', '" + usuario.nome + "', '" + usuario.email + "', '" +
                 usuario.senha + "', '" + to_string(usuario.ficcao) + "', '" + to_string(usuario.naoFiccao) + "', '" +
                 to_string(usuario.romance) + "', '" + to_string(usuario.horror) + "', '" +
                 to_string(usuario.biografia) + "');";

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
 * Remove o usuario pelo id.
 *
 * @param id
 * @return 0 (sucesso) e 1 (erro)
 */
int removeUsuario(int id) {
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao remover usuário: ";

    if (retorno != SQLITE_OK) {
        exibeMensagemErroBancoDados("Não foi possível abrir o banco de dados: ", sqlite3_errmsg(bancoDados));
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "DELETE FROM usuario "
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