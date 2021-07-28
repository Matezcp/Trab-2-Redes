#include "link.h"
#include "physical.h"
#include "application.h"

#include <iostream>
#include <string>

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
        tamanho |= quadro[i] << (7-i);
    }

    return tamanho;
}

void AdicionaFrame(int quadro[]) {
    int buffer[MAX_FRAME_LEN];
    size_t tamanho = LerTamanho(quadro);

    std::cout << "Tamanho enlace out: " << 8 + tamanho << " - Mensagem: " << tamanho << std::endl;

    std::cout << "Quadro enlace out: ";
    for(int i = 0; i < MAX_MSG_LEN; ++i) {
        std::cout << quadro[i] << ' ';
    }
    std::cout << std::endl;

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
            //Reinicia para 0 se o primeiro bit for diferente ou 1 se for igual
            indiceBusca1 = (limitador[0] == quadro[i]);
        }
        
        //Procura pelo byte de escape
        if(escape[indiceBusca2] == quadro[i]) {
            indiceBusca2++;
        }
        else {
            //Reinicia para 0 se o primeiro bit for diferente ou 1 se for igual
            indiceBusca2 = (escape[0] == quadro[i]);
        }
        
        //Substitui por uma sequencia de escape se achou
        if(indiceBusca1 == 8 || indiceBusca2 == 8) {
            EscapaByte(buffer, FRAME_BEGIN_LEN + i + quantEscapes*8 - 8, quadro+i);
            //Reinicia os indices de busca
            indiceBusca1 = 0;
            indiceBusca2 = 0;
        }
        else {
            buffer[FRAME_BEGIN_LEN + i + quantEscapes*8] = quadro[i];
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

/**
 * Realiza a subtracao de dois valores binarios utilizando xor
*/
std::string completeXor(std::string a, std::string b){
    std::string result = "";
    for(int i = 1; i < b.length(); i++){
        if (a[i] == b[i]){
            result += "0";
        }else{
            result += "1";
        }
    }
    return result;
}

/**
 * Faz a divisao de dois valores binariosutilizando xor
 * 
*/
std::string mod2div(std::string divident, std::string divisor){
    int pick = divisor.length();
     
    // primeiro valor na subtracao da divisao deve ser do mesmo tamanho que o divisor
    std::string remainder = divident.substr(0, pick);
     
    int n = divident.length();
    while(pick < n){
        if(remainder[0] == '1'){
            // faz subtracao utilizando xor
            remainder = completeXor(divisor, remainder);
            // adiciona proximo bit do dividendo no resto
            remainder += divident[pick];
        }else{
            // faz subtracao com zeros
            remainder = completeXor(std::string(pick, '0'), remainder);
            // adiciona proximo bit do dividendo
            remainder += divident[pick];
        }          
        // vai para o proximo bit do dividendo no resto
        pick += 1;
    }

    // verifica o ultimo bit
    if (remainder[0] == '1'){
        remainder = completeXor(divisor, remainder);
    }
    else{
        remainder = completeXor(std::string(pick, '0'), remainder);
    }
         
    return remainder;
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
    // Gerador polinominal x^16 x^15 x^2 + 1 de acordo com CRC-32(IEEE 802)
    std::string generator = "100000100110000010001110110110111";
    // Salva o quadro como string
    std::string data;
    for(int i = 0; i < MAX_MSG_LEN; ++i) {
        data.push_back(quadro[i] + '0');
    }
    // Adiciona no fim da mensagem o numero de bits do gerador-1 com 0
    for(int i = 0; i < (int)generator.size() - 1; ++i) {
        data.push_back('0');
    }
    std::string remainder = mod2div(data,generator);
    // Adiciona resto no final da mensagem
    for(int i = 0; i < (int)remainder.size(); ++i){
        quadro[MAX_MSG_LEN + i] = remainder[i] - '0';
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]) {
    int tipoDeControleDeErro = 2; //alterar de acordo com o teste
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

///////////////////////////////////////////////////////////////////////////////////

void RestauraByteEscapado(int quadro[], int indice, int* caracter) {
    //Restaura o byte escapado com o bit 5 invertido
    for(int i = 0; i < 8; ++i) {
        quadro[indice+i] = (i != 5) ? caracter[i] : !caracter[i];
    }
}

bool RemoveFrame(int quadro[]) {
    int estado = 0; //Assume valores 0 (nao iniciado), 1 (lendo), 2 (terminado com sucesso)
    int indiceBusca1 = 0;
    int indiceBusca2 = 0;
    size_t tamanho = 0;

    /////////////[DEBUG]/////////////
    std::cout << "\nFrame original in: ";
    int indiceBusca3 = 0;
    for(int i = 0; i < MAX_FRAME_LEN; ++i) {
        if(i > 7) {
            if(limitador[indiceBusca3] == quadro[i]) {
                indiceBusca3++;
            }
            else {
                indiceBusca3 = (limitador[0] == quadro[i]);
            }
            if(indiceBusca3 == 8) {
                std::cout << quadro[i];
                break;
            }
        }
        std::cout << quadro[i] << ' ';
    }
    std::cout << '\n' << std::endl;
    ////////////////////////////////

    for(int i = 0; i < MAX_FRAME_LEN; ++i) {
        if(estado == 2) {
            break;
        }

        //Procura pelo byte de limite
        if(limitador[indiceBusca1] == quadro[i]) {
            indiceBusca1++;
        }
        else {
            //Reinicia para 0 se o primeiro bit for diferente ou 1 se for igual
            indiceBusca1 = (limitador[0] == quadro[i]);
        }
        
        //Procura pelo byte de escape
        if(escape[indiceBusca2] == quadro[i]) {
            indiceBusca2++;
        }
        else {
            //Reinicia para 0 se o primeiro bit for diferente ou 1 se for igual
            indiceBusca2 = (escape[0] == quadro[i]);
        }

        if(indiceBusca1 == 8) {
            //Avanca para o proximo estado
            estado++;
            //Remove do quadro o ultimo byte lido
            tamanho -= 7;
            //Reinicia os indices de busca
            indiceBusca1 = 0;
            indiceBusca2 = 0;
        }
        else if(indiceBusca2 == 8) {
            //Restaura uma sequencia de escape se achou
            RestauraByteEscapado(&quadro[tamanho], i-8, &quadro[i]);
            //Reinicia os indices de busca
            indiceBusca1 = 0;
            indiceBusca2 = 0;
        }
        else {
            quadro[tamanho] = quadro[i];
            tamanho++;
        }
    }

    std::cout << "Tamanho enlace in: " << tamanho << " - Mensagem: " << (int)tamanho - 8 << std::endl;

    std::cout << "Quadro enlace in: ";
    for(int i = 0; i < MAX_MSG_LEN; ++i) {
        std::cout << quadro[i] << ' ';
    }
    std::cout << '\n' << std::endl;

    return (estado == 2); // Checa se terminou com sucesso
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]) {
    if(NumOfOnes(quadro) % 2 == 0){ //Número par de 1's
        std::cout << "Mensagem Recebida com Sucesso" << std::endl;
        CamadaDeAplicacaoReceptora(quadro);
    }
    else{                           //Número impar de 1's
        std::cout << "Processo abortado, pois um erro na paridade foi encontrado" << std::endl;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]) {
    if(NumOfOnes(quadro) % 2 != 0){ //Número Impar de 1's
        std::cout << "Mensagem Recebida com Sucesso" << std::endl;
        CamadaDeAplicacaoReceptora(quadro);
    }
    else{                           //Número Par de 1's
        std::cout << "Processo abortado, pois um erro na paridade foi encontrado" << std::endl;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[]) {
    //implementacao do algoritmo
    //usar polinomio CRC-32(IEEE 802)
    // Gerador polinominal x^16 x^15 x^2 + 1 de acordo com CRC-32(IEEE 802)
    std::string generator = "100000100110000010001110110110111";
    // Salva o quadro como string
    std::string data;
    for(int i = 0; i < MAX_MSG_LEN; ++i) {
        data.push_back(quadro[i] + '0');
    }
    std::string remainder = mod2div(data,generator);
    // Verifica se o resto foi diferente de 0
    if(remainder.find('1') != std::string::npos){
        std::cout << "Processo abortado, pois um erro no frame foi encontrado" << std::endl;
    }else{
        std::cout << "Mensagem Recebida com Sucesso" << std::endl;
        CamadaDeAplicacaoReceptora(quadro);
    }
}

void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[]) {
    int tipoDeControleDeErro = 2; //alterar de acordo com o teste
    switch (tipoDeControleDeErro) {
        case 0: //bit de paridade par
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
            break;
        case 1: //bit de paridade impar
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2: //CRC
            //codigo
            CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
            //codigo
            break;
    }
}

void CamadaEnlaceDadosReceptora(int quadro[]) {
    if(RemoveFrame(quadro)) {
        CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    }
    else {
        std::cout << "Processo abortado, pois um erro no frame foi encontrado" << std::endl;
    }
}
