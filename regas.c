#include "regas.h"
#include "plantas.h"
#include <stdio.h>
#include <string.h>

static Rega repositorio[MAX_REGAS];
static int  total      = 0;
static int  proximo_id = 1;

/* CORREÇÃO excerto 3: verificação de limites antes de escrever no array */
int regas_registar(int id_planta, int data, int quantidade) {
    if (total >= MAX_REGAS) {
        printf("Limite de regas atingido.\n");
        return 0;
    }
    /* Valida que a planta existe */
    if (plantas_encontrar_por_id(id_planta) < 0) {
        printf("Planta com ID %d nao encontrada.\n", id_planta);
        return 0;
    }
    repositorio[total].id_rega        = proximo_id++;
    repositorio[total].id_planta      = id_planta;
    repositorio[total].data_rega      = data;
    repositorio[total].quantidade_agua = quantidade;
    total++;

    /* Actualiza ultima_rega na planta correspondente */
    plantas_atualizar_rega(id_planta, data);
    return 1;
}

/* CORREÇÃO excerto 4: tipo de retorno alterado para int para permitir uso programático.
   A versão original era void, impossibilitando verificar se alguma planta precisa de rega. */
void regas_verificar_necessidade(int data_atual) {
    Planta *arr   = plantas_obter_array();
    int     n     = plantas_total();
    int     alguma = 0;

    printf("\n=== PLANTAS QUE PRECISAM DE REGA ===\n");
    for (int i = 0; i < n; i++) {
        int dias = data_atual - arr[i].ultima_rega;
        if (dias >= arr[i].intervalo_rega) {
            printf("  [!] %s (ID %d) — ultima rega ha %d dias (intervalo: %d)\n",
                   arr[i].nome, arr[i].id, dias, arr[i].intervalo_rega);
            alguma = 1;
        }
    }
    if (!alguma) printf("  Todas as plantas estao em dia.\n");
}

void regas_listar(void) {
    if (total == 0) { printf("Sem regas registadas.\n"); return; }
    printf("\n=== REGAS (%d) ===\n", total);
    for (int i = 0; i < total; i++) {
        printf("Rega %d | Planta ID: %d | Dia: %d | Qtd: %d ml\n",
               repositorio[i].id_rega, repositorio[i].id_planta,
               repositorio[i].data_rega, repositorio[i].quantidade_agua);
    }
}

int regas_carregar(const char *ficheiro) {
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL) return 0;

    Rega tmp;
    while (fscanf(f, "%d,%d,%d,%d\n",
                  &tmp.id_rega, &tmp.id_planta,
                  &tmp.data_rega, &tmp.quantidade_agua) == 4) {
        if (total >= MAX_REGAS) break;
        repositorio[total] = tmp;
        if (tmp.id_rega >= proximo_id) proximo_id = tmp.id_rega + 1;
        total++;
    }
    fclose(f);
    return 1;
}

int regas_guardar(const char *ficheiro) {
    FILE *f = fopen(ficheiro, "w");
    if (f == NULL) { printf("Erro ao guardar regas.\n"); return 0; }
    for (int i = 0; i < total; i++) {
        fprintf(f, "%d,%d,%d,%d\n",
                repositorio[i].id_rega, repositorio[i].id_planta,
                repositorio[i].data_rega, repositorio[i].quantidade_agua);
    }
    fclose(f);
    return 1;
}
