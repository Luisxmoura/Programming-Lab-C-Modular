#ifndef PLANTAS_H
#define PLANTAS_H

#include "tipos.h"

/* Acesso ao repositório interno */
Planta *plantas_obter_array(void);
int     plantas_total(void);

/* Operações */
int  plantas_adicionar(const char *nome, const char *especie,
                       const char *data_plantio, int intervalo);
void plantas_listar(void);
int  plantas_atualizar_rega(int id_planta, int data_rega);
int  plantas_encontrar_por_id(int id); /* devolve índice ou -1 */

/* Persistência */
int  plantas_carregar(const char *ficheiro);
int  plantas_guardar(const char *ficheiro);

#endif /* PLANTAS_H */
