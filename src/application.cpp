#include "application.h"
#include "link.h"

using namespace std;

void AplicacaoTransmissora(void) {
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    //std::cin >> mensagem;
    std::getline(std::cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(std::string mensagem) {
    //int quadro[] = mensagem //trabalhar com bits!!!
    string binary = "";
    //Aceito até 256 caracteres
    int quadro[8*256];
    //Inializa tudo com -1 para controle de dados
    memset (quadro,-1,8*256);
    //Transforma a palavra em binário
    for (int i = 0; i < mensagem.size(); ++i)
    {
        //É pego 8 bits para cada letra
        binary += bitset<8>(mensagem.c_str()[i]).to_string();
    }

    cout << "Mensagem em bits: ";

    //Coloca o binário no vetor quadro
    for (int i = 0; i < binary.size(); ++i)
    {
        //Se chegarmos no valor máximo, a mensagem é truncada
        if(i == 256){
            break;
        }
        //Transforma em número o char
        quadro[i] = int(binary[i]) - 48;
        cout << quadro[i];
    }
    
    cout << endl;

    //chama a proxima chamada
    CamadaEnlaceDadosTransmissora(quadro);
    
    
}
void CamadaDeAplicacaoReceptora(int quadro[]) {
    //string message = quadro []; //estava trabalhando com bits
    
    //AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(std::string mensagem) {
    std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
}