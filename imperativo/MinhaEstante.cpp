#include <iostream>
#include <vector>
#include "livrosdb.cpp"
#include "pesquisas.cpp"
#include "usuariodb.cpp"
#include "constantes.cpp"

using namespace std;

void visualizarMinhaEstante(int idUsuario);
int removerLivroMinhaEst(int idUsuario);
int adicionaLivroMinhaEst(int idUsuario);
int mudarStatusLeitura(int idUsuario);
void printandoLivros(vector<vector<string>> livros);

int adicionaLivroMinhaEst(int idUsuario){
    int idLivro;
    int retorno;
    int opcao; 

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Adicionando livros a minha estante - " << endl << endl;

    cout << "Digite a opção de Pesquisa de sua preferência: " << endl;
    cout << "Pesquisa por Autor[1]: " << endl;
    cout << "Pesquisa por Titulo[2]: " << endl;
    cout << "Pesquisa por Gênero[3]: " << endl;
    cout << "Listar todos os Livros[4]: " << endl;
    cin >> opcao;

    switch (opcao){
        case 1:
            pesquisasAutor();
            break;
        
        case 2:
            pesquisasTitulo();
            break;
        
        case 3:
            pesquisasGenero();
            break;

        case 4:
            cout << "Livros cadastrados na biblioteca do PrompSkoob: " << endl << "id - titulo";
           
            visualizarMinhaEstante(idUsuario);
    
        default:
            cout << "Opcao inválida" << endl;
            break;
    }

    cout << "insira o id do livro que você quer cadastrar na sua estante: ";
    cin >> idLivro;

    insereEstante(idUsuario, idLivro);

    return 0;
}

int removerLivroMinhaEst(int idUsuario){
    int idLivro;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Removendo livros da minha estante - " << endl << endl;

    cout << "Livros da sua estante:" << endl;
    
    visualizarMinhaEstante(idUsuario);

    cout << "insira o id do livro que voce quer remover da sua estante: ";
    cin >> idLivro;

    removeEstante(idUsuario, idLivro);

    return 0;
}

int mudarStatusLeitura(int idUsuario){
    int idLivro;
    int opcao;

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - mudando status de leitura - " << endl << endl;

    visualizarMinhaEstante(idUsuario);

    cout << "insira o id do livro que voce deseja mudar o status: ";
    cin >> idLivro;

    cout << "Digite o status de leitura do livro: " << endl;
    cout << "Nao lido[1]: " << endl;
    cout << "Lendo[2]: " << endl;
    cout << "Lido[3]: " << endl;
    cin >> opcao;

    switch (opcao){
        case N_LIDO:
            mudarStatus(idUsuario, idLivro, "n_lido");
            break;
        
        case LENDO:
            mudarStatus(idUsuario, idLivro, "lendo");
            break;
        
        case LIDO:
            mudarStatus(idUsuario, idLivro, "lido");
            break;
    
        default:
            cout << "Opcao inválida" << endl;
            break;

    return 0;
}

void visualizarMinhaEstante(int idUsuario){
    vector<vector<string>> livros;
    listaTodosLivrosMinhaESt(idUsuario, livros);

    if(livros.size() == 0){
        cout << "Estante vazia." << endl;
    }
    
    printandoLivros(livros);
}

void printandoLivros(vector<vector<string>> livros){
    int indexIdLivro = 0;
    int indexNomeLivro = 2;
    string linha = "";

    for(size_t i = 0; i < livros.size(); i++){
        linha = livros.at(i).at(indexIdLivro) + " - " + livros.at(i).at(indexNomeLivro)
        cout << linha << endl;
    }

}