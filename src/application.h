#ifndef _APPLICATION_H
#define _APPLICATION_H

#include<string>
#include<iostream>
#include<bitset>
#include <cstring>
#include <sstream>

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(std::string mensagem);

void AplicacaoReceptora(std::string mensagem);
void CamadaDeAplicacaoReceptora(int quadro[]);

#endif