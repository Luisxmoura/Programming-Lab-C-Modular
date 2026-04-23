#ifndef TAREFAS_H
#define TAREFAS_H

#include "tipos.h"

/* Operações */
int  tarefas_criar(const char *descricao, int data_prevista);
int  tarefas_concluir(int id);
void tarefas_listar_pendentes(void);
void tarefas_listar_todas(void);

/* Persistência */
int  tarefas_carregar(const char *ficheiro);
int  tarefas_guardar(const char *ficheiro);

#endif /* TAREFAS_H */
