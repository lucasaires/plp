#include <iostream>
#include <string>
#include <vector>

using namespace std;

void exibeMensagem(string mensagem);
void exibeMensagemErro(string mensagem);
void exibeMensagemErroBancoDados(string mensagem, const char * erroBancoDados);

void exibeMensagem(string mensagem) {
    cout << "\033[1;32m" << "--- " << mensagem << " ---" << "\033[0m\n\n";
}

void exibeMensagemErro(string mensagem) {
    cout << "\033[1;31m" << "--- " << mensagem << " ---" << "\033[0m\n\n";
}

void exibeMensagemErroBancoDados(string mensagem, const char * erroBancoDados) {
    cout << "\033[1;31m" << "--- " << mensagem << erroBancoDados << " ---" << "\033[0m\n\n";
}