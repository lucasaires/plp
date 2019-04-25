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
int avaliaLivroMinhaEstante(int idUsuario);
void registroLeitura(idUsuario);
int listagemRegistroLeitura();
int editaRegistroLeitura(struct Usuario &usuario);



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
        linha = livros.at(i).at(indexIdLivro) + " - " + livros.at(i).at(indexNomeLivro);
        cout << linha << endl;
    }

}
int avaliaLivroMinhaEstante(int idUsuario){
    int idLivro, avaliacao;

    visualizarMinhaEstante(idUsuario);

    cout << "Qual livro será avaliado?" << endl;
    cin >> idLivro;

    cout << "Dê sua nota no intervalo de 1 a 5: " << endl;
    cin >> avaliacao;

    while(avaliacao < 0 || avaliacao > 5){
        cout << "Essa avaliação não é válida, informe outra nota:" << endl;
        cin >> avaliacao;
    }

    avaliaLivro(idUsuario, idLivro, avaliacao);

}

void registroLeitura(idUsuario){

int idLivro, numeroPaginas;
string comentario;

visualizarMinhaEstante(idUsuario);

cout << " Qual o livro será registrado?" << endl;
cin >> idLivro;
cout << "Quantas paginas foram lidas?" << endl;
cin >> numeroPaginas;
//tratamento de acordo com a quantidade de paginas do livro.
cout << "Deixe seu comentario sobre as páginas lidas: " << endl;
getline(cin, comentario);

registraLeitura(idUsuario,idLivro,numeroPaginas,comentario);

}

int listagemRegistroLeitura(){
    // listagem com dados ficticions do registro de determinado usuario e sua estante
    // : Nome do livro + numero de paginas lidas + comentario.
    // Dá um select no banco e fazer um for para percorrer o vetor

    cout >> "1. Luciola, 120 páginas, livro de José de alencar que é extremamente emocional e possui um final triste. " << endl;
    cout >> "2. Casa-Grande & Senzala, 30 páginas, livro de Gilberto Freyre, ele é de extrema importancia e deveria ser lido por todos os brasileiros." << endl;
    cout >> "3. Raizes do Brasil, 40 páginas, livro que faz refletir sobre individualismo e outros assuntos importantes. " << endl;
    cout >> "4. Formação de um pais Contemporaneo, 20 páginas, um livro bastante interessante, que conta a historia do brasil nos dias atuais." << endl;
    cout >> "5. O Estrangeiro, 50 páginas, A trama é centrada nas desventuras de Mersault, condenado à morte por matar um homem a troco de nada." << endl;
    cout >> "6. O Mundo se Despedaça, 20 páginas, Ele narra a história de Okonkwo, guerreiro da etnia Ibo" << endl;
    cout >> "7. A Época da Inocência, 80 páginas, o romance destaca a inquietação da sociedade aristocrata nova-iorquina do fim do século 19." << endl;

}


int editaRegistroLeitura(struct Usuario &usuario){

    int idLivro, opcao, novoNumPaginas;
    string novoComentario;
    listagemRegistroLeitura();

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Editar Meu Registro de Leitura - " << endl << endl;
    cout << "Qual registro deseja modificar?" << endl;
    cin >> idLivro;

    cout << "Qual campo deseja modificar?" << endl;
    cout << "(1) Numero de Páginas Lida " <<  endl;
    cout << "(2) Comentario " << endl;
    cout << "(3) Numero de Paginas e Comentario" << endl;
    
    bool condicao = false; 
    while(!condicao){
        cin >> opcao;

        if(opcao == 1){
        cout << "Qual novo número de páginas? " << endl;
        cin >> novoNumPaginas;
        condicao = true;
        editaPaginas(idUsuario, idLivro, novoNumeroPaginas);
        }
        else if(opcao == 2){
        cout << "Digite um novo comentario: " << endl;
        getline(cin, novoComentario);
        condicao = true;
        editaComentarios(idUsiario, idLivro, novoComentario);
        }
        else if(opcao == 3){
        cout << "Qual novo número de páginas? " << endl;
        cin >> novoNumPaginas;
        cout << "Digite um novo comentario: " << endl;
        getline(cin, novoComentario);
        condicao = true;
        editaRegistro(idUsuario, idLivro, novoNumeroPaginas, novoComentario);
        }
        else{
            cout << "Opção invalida, digite novamente: " << endl;

        }

    }
    
}
