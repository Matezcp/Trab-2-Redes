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
    //Aceito até 46 caracteres + 33 espaços para o CRC
    int quadro[8*46+33];
    //Inializa tudo com -1 para controle de dados
    memset (quadro,0,8*46+33);
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
        if(i == 46){
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
    string mensagem = ""; //estava trabalhando com bits

    
    //TODO
    

    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(std::string mensagem) {
    std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
}