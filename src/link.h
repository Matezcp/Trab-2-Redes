#ifndef _LINK_H
#define _LINK_H

#define ERROR_CHECK_LEN 33
#define FRAME_BEGIN_LEN 8
#define FRAME_END_LEN 8
#define FRAME_LEN (FRAME_BEGIN_LEN + ERROR_CHECK_LEN + FRAME_END_LEN)

void CamadaEnlaceDadosTransmissora(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]);
void CamadaEnlaceDadosReceptora(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[]);

#endif