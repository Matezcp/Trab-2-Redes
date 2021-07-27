#include "link.h"
#include "physical.h"
#include "application.h"

#include <iostream>

const int limitador[8] = {0, 1, 1, 1, 1, 1, 1, 0};
const int escape[8] = {1, 0, 1, 1, 1, 1, 1, 0};

int NumOfOnes(int quadro[]){
    int count = 0;

    for(int i = 0; i <= 46 ; ++i){
        if(quadro[i] == 1)
            count++;
    }

    return count;
}

void EscapaByte(int quadro[], int indice, int* caracter) {
    //Adiciona o byte de escape
    for(int i = 0; i < 8; ++i) {
        quadro[indice+i] = escape[i];
    }
    //Adiciona o byte escapado com o bit 5 invertido
    for(int i = 0; i < 8; ++i) {
        quadro[indice+8+i] = (i != 5) ? caracter[i] : !caracter[i];
    }
}

size_t LerTamanho(int quadro[]) {
    size_t tamanho = 0;
    
    //Lê o tamanho da mensagem
    for(int i = 0; i < 8; ++i) {
        tamanho = quadro[i] << (7-i);
    }

    return tamanho;
}

void AdicionaFrame(int quadro[]) {
    int buffer[2*8*MAX_MSG_LEN + FRAME_LEN];
    size_t tamanho = LerTamanho(quadro);

    //Insere o inicio do frame no buffer
    for(int i = 0; i < 8; ++i) {
        buffer[i] = limitador[i];
    }

    //Faz um shift de todos os bits para frente para colocar a marcacao de inicio do frame
    //e escapa os bytes identicos aos de limite do frame e aos de escape
    int indiceBusca1 = 0;
    int indiceBusca2 = 0;
    int quantEscapes = 0;
    for(int i = 0; i < tamanho; ++i) {
        //Procura pelo byte de limite
        if(limitador[indiceBusca1] == quadro[i]) {
            indiceBusca1++;
        }
        else {
            indiceBusca1 = 0;
        }
        
        //Procura pelo byte de escape
        if(limitador[indiceBusca2] == quadro[i]) {
            indiceBusca2++;
        }
        else {
            indiceBusca2 = 0;
        }
        
        //Substitui por uma sequencia de escape se achou
        if(indiceBusca1 == 8 || indiceBusca2 == 8) {
            EscapaByte(buffer-8, FRAME_BEGIN_LEN+i+quantEscapes*8, quadro+i);
            indiceBusca1 = 0;
            indiceBusca2 = 0;
        }
        else {
            quadro[FRAME_BEGIN_LEN + i + quantEscapes*8] = quadro[i];
        }
    }

    //Insere o fim do frame no buffer
    for(int i = 0; i < 8; ++i) {
        buffer[FRAME_BEGIN_LEN + tamanho + quantEscapes*8 + i] = limitador[i];
    }

    //Copia o buffer para o quadro
    for(int i = 0; i < FRAME_BEGIN_LEN + tamanho + quantEscapes*8 + FRAME_END_LEN; ++i) {
        quadro[i] = buffer[i];
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]) {
    //implementacao do algoritmo
    size_t tamanho = LerTamanho(quadro);

    if(NumOfOnes(quadro) % 2 == 0){ //Número par de 1's
        quadro[8*(tamanho+1)] = 0;
    }
    else{                           //Número impar de 1's
        quadro[8*(tamanho+1)] = 1;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]) {
    //implementacao do algoritmo
    size_t tamanho = 0;
    
    //Lê o tamanho da mensagem
    for(int i = 0; i < 8; ++i) {
        tamanho = quadro[i] << (7-i);
    }

    if(NumOfOnes(quadro) % 2 == 0){ //Número par de 1's
        quadro[8*(tamanho+1)] = 1;
    }
    else{                           //Número impar de 1's
        quadro[8*(tamanho+1)] = 0;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]) {
    //implementacao do algoritmo
    //usar polinomio CRC-32(IEEE 802)
}

void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]) {
    int tipoDeControleDeErro = 0; //alterar de acordo com o teste
    switch (tipoDeControleDeErro) {
        case 0: //bit de paridade par
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break;
        case 1: //bit de paridade impar
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2: //CRC
            //codigo
            CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            //codigo
            break;
    }
}

void CamadaEnlaceDadosTransmissora(int quadro[]) {
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    
    AdicionaFrame(quadro);

    //chama a proxima camada
    MeioDeComunicacao(quadro);
}


bool CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]) {
    if(NumOfOnes(quadro) % 2 == 0){ //Número par de 1's
        std::cout << "Mensagem Válida" << std::endl;
        return true;
    }
    else{                           //Número impar de 1's
        std::cout << "Erro encontrado" << std::endl;
        return false;
    }
}

bool CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]) {
    if(NumOfOnes(quadro) % 2 != 0){ //Número Impar de 1's
        std::cout << "Mensagem Válida" << std::endl;
        return true;
    }
    else{                           //Número Par de 1's
        std::cout << "Erro encontrado" << std::endl;
        return false;
    }
}

bool CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[]) {
    //implementacao do algoritmo
    //usar polinomio CRC-32(IEEE 802)
}

bool CamadaEnlaceDadosReceptoraControleDeErro(int quadro[]) {
    int tipoDeControleDeErro = 0; //alterar de acordo com o teste
    switch (tipoDeControleDeErro) {
        case 0: //bit de paridade par
            if(CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro))
                return true;
            return false;
            break;
        case 1: //bit de paridade impar
            if(CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro))
                return true;
            return false;
            break;
        case 2: //CRC
            //codigo
            if(CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro))
                return true;
            return false;
            //codigo
            break;
    }

    return false;
}

void CamadaEnlaceDadosReceptora(int quadro[]) {

    if(CamadaEnlaceDadosReceptoraControleDeErro(quadro)){
        //chama a proxima camada
        std::cout << "Mensagem Recebida com Sucesso" << std::endl;
        CamadaDeAplicacaoReceptora(quadro);
    }
    else
        std::cout << "Processo abortado, pois um erro foi encontrado" << std::endl;
}
