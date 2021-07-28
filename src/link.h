#ifndef _LINK_H
#define _LINK_H

#define ERROR_CHECK_LEN 32
#define FRAME_BEGIN_LEN 8
#define FRAME_END_LEN 8
#define FRAME_LEN (FRAME_BEGIN_LEN + ERROR_CHECK_LEN + FRAME_END_LEN)

void CamadaEnlaceDadosTransmissora(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]);
void CamadaEnlaceDadosReceptora(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[], int tamanho);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[], int tamanho);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[], int tamanho);
void CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[], int tamanho);

#endif