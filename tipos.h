#ifndef TIPOS_H
#define TIPOS_H

#define MAX_PLANTAS  100
#define MAX_REGAS    500
#define MAX_TAREFAS  200

typedef struct {
    int  id;
    char nome[50];
    char especie[50];
    char data_plantio[11]; /* DD/MM/AAAA */
    int  intervalo_rega;   /* dias */
    int  ultima_rega;      /* dias desde 01/01/2026 */
} Planta;

typedef struct {
    int id_rega;
    int id_planta;
    int data_rega;         /* dias desde 01/01/2026 */
    int quantidade_agua;   /* ml */
} Rega;

typedef struct {
    int  id_tarefa;
    char descricao[100];
    int  data_prevista;    /* dias desde 01/01/2026 */
    int  concluida;        /* 0 = pendente | 1 = concluida */
} Tarefa;

#endif /* TIPOS_H */
