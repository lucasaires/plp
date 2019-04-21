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
		cerr << "Não foi possível abir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
	}
	
	string sql = "CREATE TABLE IF NOT EXISTS estantes("
                 "isbn INT PRIMARY KEY NOT NULL, "
                 "nome TEXT NOT NULL, "
                 "escritor TEXT NOT NULL, "
                 "paginas INT NOT NULL, "
                 "paginasLidas INT NOT NULL, "
				 "genero INT NOT NULL);";
				 
    retorno = sqlite3_exec(bancoDados, sql.c_str(), NULL, 0, &erroBanco);
    
    if(retorno != SQLITE_OK){
		cerr << mensagemErro << sqlite3_errmsg(bancoDados) << endl;
		sqlite3_free(erroBanco);
	}
	
	sqlite3_close(bancoDados);
}

int consultaEstante(vector<Livro> &estante, int id){
    sqlite3 *bancoDados;
    sqlite3_stmt *stmt;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao consultar a estante: ";

    if (retorno != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "SELECT * FROM estante WHERE id = " + to_string(id) + ";";
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

        const char *idEstante = reinterpret_cast<const char *>(sqlite3_column_text(stmt, E_ID));
        

        livros.push_back(idEstantes);

    }

    sqlite3_finalize(stmt);
    sqlite3_close(bancoDados);

    return 0;
}

int insereEstante(int id, vector<Livros> estante){
    sqlite3 *bancoDados;
    char *erroBanco;
    int retorno = sqlite3_open(BANCO_DADOS, &bancoDados);
    string mensagemErro = "Ocorreu um erro ao inserir estante: ";
    //string interessesFormatado = formataInteresses(interesses);

    if (retorno != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
        sqlite3_close(bancoDados);

        return 1;
    }

    string sql = "INSERT INTO estante(id, estantes) "
                 "VALUES('" + to_string(id) + "', '" + estante + "');";

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
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(bancoDados) << endl;
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

