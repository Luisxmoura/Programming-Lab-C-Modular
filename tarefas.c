#include "tarefas.h"
#include <stdio.h>
#include <string.h>

static Tarefa repositorio[MAX_TAREFAS];
static int    total      = 0;
static int    proximo_id = 1;

/* CORREÇÃO excerto 5: verificação de limite antes de escrever */
int tarefas_criar(const char *descricao, int data_prevista) {
    if (total >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido.\n");
        return 0;
    }
    Tarefa *t     = &repositorio[total];
    t->id_tarefa  = proximo_id++;
    strncpy(t->descricao, descricao, sizeof(t->descricao) - 1);
    t->descricao[sizeof(t->descricao) - 1] = '\0';
    t->data_prevista = data_prevista;
    t->concluida     = 0;
    total++;
    return 1;
}

/* CORREÇÃO excerto 7: substituído = por == na condição do if.
   O código original fazia atribuição (tarefas[i].id_tarefa = id),
   o que tornava a condição sempre verdadeira para id != 0. */
int tarefas_concluir(int id) {
    for (int i = 0; i < total; i++) {
        if (repositorio[i].id_tarefa == id) {
            repositorio[i].concluida = 1;
            printf("Tarefa %d concluida.\n", id);
            return 1;
        }
    }
    printf("Tarefa com ID %d nao encontrada.\n", id);
    return 0;
}

/* CORREÇÃO excerto 6: substituído = por == na condição do if.
   O código original atribuía 0 a concluida em cada iteração,
   tornando a condição sempre falsa e nunca imprimindo nada. */
void tarefas_listar_pendentes(void) {
    int alguma = 0;
    printf("\n=== TAREFAS PENDENTES ===\n");
    for (int i = 0; i < total; i++) {
        if (repositorio[i].concluida == 0) {
            printf("  [%d] %s (prevista: dia %d)\n",
                   repositorio[i].id_tarefa,
                   repositorio[i].descricao,
                   repositorio[i].data_prevista);
            alguma = 1;
        }
    }
    if (!alguma) printf("  Sem tarefas pendentes.\n");
}

void tarefas_listar_todas(void) {
    if (total == 0) { printf("Sem tarefas registadas.\n"); return; }
    printf("\n=== TODAS AS TAREFAS (%d) ===\n", total);
    for (int i = 0; i < total; i++) {
        printf("  [%d] %s | Dia: %d | %s\n",
               repositorio[i].id_tarefa,
               repositorio[i].descricao,
               repositorio[i].data_prevista,
               repositorio[i].concluida ? "Concluida" : "Pendente");
    }
}

int tarefas_carregar(const char *ficheiro) {
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL) return 0;

    Tarefa tmp;
    while (fscanf(f, "%d,%99[^,],%d,%d\n",
                  &tmp.id_tarefa, tmp.descricao,
                  &tmp.data_prevista, &tmp.concluida) == 4) {
        if (total >= MAX_TAREFAS) break;
        repositorio[total] = tmp;
        if (tmp.id_tarefa >= proximo_id) proximo_id = tmp.id_tarefa + 1;
        total++;
    }
    fclose(f);
    return 1;
}

int tarefas_guardar(const char *ficheiro) {
    FILE *f = fopen(ficheiro, "w");
    if (f == NULL) { printf("Erro ao guardar tarefas.\n"); return 0; }
    for (int i = 0; i < total; i++) {
        fprintf(f, "%d,%s,%d,%d\n",
                repositorio[i].id_tarefa, repositorio[i].descricao,
                repositorio[i].data_prevista, repositorio[i].concluida);
    }
    fclose(f);
    return 1;
}
