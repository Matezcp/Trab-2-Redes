#include "application.h"

void AplicacaoTransmissora(void) {
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    std::cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(std::string mensagem) {
    //int quadro[] = mensagem //trabalhar com bits!!!
    //chama a proxima chamada
}
void CamadaDeAplicacaoReceptora(int quadro[]) {
    //string message = quadro []; //estava trabalhando com bits
    
    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(std::string mensagem) {
    std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
}