#include <iostream>
#include "sqlite3.h"
#include <vector>
#include "MinhaEstante.cpp"

using namespace std;

void criaTabelaEstantes(){
	sqlite3 *bancoDados;
	char *erroBanco;
	int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
	string mensagemErro = "Ocorreu um erro ao criar a tabela de Estantes: ";
	
	if (retorno) {
		cerr << "N�o foi poss�vel abir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
	}
	
	string sql = "CREATE TABLE IF NOT EXISTS estantes("
                 "idUsuario INT FOREIGN KEY NOT NULL, "
                 "idLivro INT );";
				 
    retorno = sqlite3_exec(bancoDados, sql.c_str(), NULL, 0, &erroBanco);
    
    if(retorno != SQLITE_OK){
		cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
		sqlite3_free(erroBanco);
	}
	
	sqlite3_close(bancoDados);
}

int consultaEstante(int idUsuario){
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao consultar a estante: ";

    if (retorno != SQLITE_OK) {
        cerr << "N�o foi poss�vel abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT idLivro FROM estantes WHERE idUsuario = " + to_string(idUsuario) + ";";
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

        const char *idLivro = reinterpret_cast<const char *>(sqlite3_column_text(stmt, E_LIVRO));
        

        livros.push_back(idEstante);

    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}

int insereEstante(int idUsuario, int idLivro){
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao inserir estante: ";

    if (retorno != SQLITE_OK) {
        cerr << "N�o foi poss�vel abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "INSERT INTO estante(idEstante, idUsuario, idLivro) "
                 "VALUES('" + to_string(idUsuario) + "', '" + to_string(idLivro) + "');";

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

int removeEstante(int id)
{
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao remover estante: ";

    if (retorno != SQLITE_OK) {
        cerr << "N�o foi poss�vel abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "DELETE FROM estantes WHERE id = " + to_string(id) + ";";

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

