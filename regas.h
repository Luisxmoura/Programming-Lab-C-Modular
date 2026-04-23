#ifndef REGAS_H
#define REGAS_H

#include "tipos.h"

/* Operações */
int  regas_registar(int id_planta, int data, int quantidade);
void regas_verificar_necessidade(int data_atual);
void regas_listar(void);

/* Persistência */
int  regas_carregar(const char *ficheiro);
int  regas_guardar(const char *ficheiro);

#endif /* REGAS_H */
