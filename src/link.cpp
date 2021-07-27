#include "link.h"
#include "physical.h"
#include "application.h"

using namespace std;

int numOfOnes(int quadro[]){
    int count = 0;

    for(int i =0; i <= 46 ; ++i){
        if(quadro[i] == 1)
            count++;
    }

    return count;
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]) {
    //implementacao do algoritmo
    if(numOfOnes(quadro) % 2 == 0){ //Número par de 1's
        quadro[8*46] = 0;
    }
    else{                           //Número impar de 1's
        quadro[8*46] = 1;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]) {
    //implementacao do algoritmo
    if(numOfOnes(quadro) % 2 == 0){ //Número par de 1's
        quadro[8*46] = 1;
    }
    else{                           //Número impar de 1's
        quadro[8*46] = 0;
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
    
    /*for(int i=0;i<8*46;i++){
        cout << quadro[i] << endl;
    }*/

    //chama a proxima camada
    MeioDeComunicacao(quadro);
}


bool CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]) {
    if(numOfOnes(quadro) % 2 == 0){ //Número par de 1's
        cout << "Mensagem Válida" << endl;
        return true;
    }
    else{                           //Número impar de 1's
        cout << "Erro encontrado" << endl;
        return false;
    }
}

bool CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]) {
    if(numOfOnes(quadro) % 2 != 0){ //Número Impar de 1's
        cout << "Mensagem Válida" << endl;
        return true;
    }
    else{                           //Número Par de 1's
        cout << "Erro encontrado" << endl;
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
        cout << "Mensagem Recebida com Sucesso" << endl;
        CamadaDeAplicacaoReceptora(quadro);
    }
    else
        cout << "Processo abortado, pois um erro foi encontrado" << endl;
}
