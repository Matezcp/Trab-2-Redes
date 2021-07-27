#include "application.h"
#include "link.h"

#include <iostream>

void AplicacaoTransmissora(void) {
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    //std::cin >> mensagem;
    std::getline(std::cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(std::string mensagem) {
    //Aceito até 46 caracteres + 33 espaços para o CRC
    int quadro[MAX_FRAME_LEN];

    //Insere o tamanho da mensagem como header
    size_t tamanho = (mensagem.length() <= MAX_MSG_LEN) ? mensagem.length() : 46;
    for(int i = 0; i < APP_HEADER_LEN; i++) {
        quadro[i] = (tamanho >> (7-i)) & 1;
    }

    //Transforma a mensagem em binário
    for (int i = 0; i < MAX_MSG_LEN; ++i) {
        for(int j = 0; j < 8; ++j) {
            quadro[APP_HEADER_LEN + (i*8+j)] = (mensagem[i] >> (7-j)) & 1;
        }
    }

    //chama a proxima chamada
    CamadaEnlaceDadosTransmissora(quadro);
}

void CamadaDeAplicacaoReceptora(int quadro[]) {
    std::string mensagem; //estava trabalhando com bits

    
    //TODO
    

    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(std::string mensagem) {
    std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
}