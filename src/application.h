#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <string>

#define MAX_MSG_LEN 46
#define APP_HEADER_LEN 8
#define APP_LEN (APP_HEADER_LEN + MAX_MSG_LEN)

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(std::string mensagem);

void AplicacaoReceptora(std::string mensagem);
void CamadaDeAplicacaoReceptora(int quadro[]);

#endif