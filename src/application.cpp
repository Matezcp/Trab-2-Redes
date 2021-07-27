#include "application.h"
#include "link.h"

#include <iostream>
#include <bitset>
#include <cstring>
#include <sstream>

#define MAX_MSG_LEN 46
#define ERROR_CHECK_LEN 33
#define FRAME_BEGIN_LEN 8
#define FRAME_END_LEN 8
#define FRAME_LEN (FRAME_BEGIN_LEN + ERROR_CHECK_LEN + FRAME_END_LEN)
#define APP_HEADER_LEN 8

void AplicacaoTransmissora(void) {
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    //std::cin >> mensagem;
    std::getline(std::cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(std::string mensagem) {
    //Aceito até 46 caracteres + 33 espaços para o CRC
    int quadro[8*MAX_MSG_LEN + FRAME_LEN];

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