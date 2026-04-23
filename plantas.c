#include "plantas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Planta repositorio[MAX_PLANTAS];
static int    total = 0;
static int    proximo_id = 1;

Planta *plantas_obter_array(void) { return repositorio; }
int     plantas_total(void)       { return total; }

int plantas_encontrar_por_id(int id) {
    for (int i = 0; i < total; i++)
        if (repositorio[i].id == id) return i;
    return -1;
}

int plantas_adicionar(const char *nome, const char *especie,
                      const char *data_plantio, int intervalo) {
    if (total >= MAX_PLANTAS) {
        printf("Limite de plantas atingido.\n");
        return 0;
    }
    Planta *p = &repositorio[total];
    p->id = proximo_id++;
    strncpy(p->nome,         nome,         sizeof(p->nome)         - 1);
    strncpy(p->especie,      especie,      sizeof(p->especie)      - 1);
    strncpy(p->data_plantio, data_plantio, sizeof(p->data_plantio) - 1);
    p->nome[sizeof(p->nome)-1]                 = '\0';
    p->especie[sizeof(p->especie)-1]           = '\0';
    p->data_plantio[sizeof(p->data_plantio)-1] = '\0';
    p->intervalo_rega = intervalo;
    p->ultima_rega    = 0;
    total++;
    return 1;
}

void plantas_listar(void) {
    if (total == 0) { printf("Sem plantas registadas.\n"); return; }
    printf("\n=== PLANTAS (%d) ===\n", total);
    /* CORREÇÃO excerto 2: i < total, não i <= total */
    for (int i = 0; i < total; i++) {
        printf("ID: %d | Nome: %-20s | Especie: %-20s | Plantio: %s | Rega cada %d dias\n",
               repositorio[i].id, repositorio[i].nome,
               repositorio[i].especie, repositorio[i].data_plantio,
               repositorio[i].intervalo_rega);
    }
}

int plantas_atualizar_rega(int id_planta, int data_rega) {
    int idx = plantas_encontrar_por_id(id_planta);
    if (idx < 0) return 0;
    repositorio[idx].ultima_rega = data_rega;
    return 1;
}

/* CORREÇÃO excerto 1:
   - Substituído !feof() por verificar o retorno de fscanf (evita leitura duplicada no EOF)
   - Adicionada verificação de NULL em f_plantas antes de usar */
int plantas_carregar(const char *ficheiro) {
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL) return 0; /* ficheiro ainda não existe — OK na primeira execução */

    Planta tmp;
    int lidos;
    while ((lidos = fscanf(f, "%d,%49[^,],%49[^,],%10[^,],%d,%d\n",
                           &tmp.id, tmp.nome, tmp.especie,
                           tmp.data_plantio, &tmp.intervalo_rega,
                           &tmp.ultima_rega)) == 6) {
        if (total >= MAX_PLANTAS) break;
        repositorio[total] = tmp;
        if (tmp.id >= proximo_id) proximo_id = tmp.id + 1;
        total++;
    }
    fclose(f);
    return 1;
}

int plantas_guardar(const char *ficheiro) {
    FILE *f = fopen(ficheiro, "w");
    if (f == NULL) { printf("Erro ao guardar plantas.\n"); return 0; }
    for (int i = 0; i < total; i++) {
        fprintf(f, "%d,%s,%s,%s,%d,%d\n",
                repositorio[i].id, repositorio[i].nome,
                repositorio[i].especie, repositorio[i].data_plantio,
                repositorio[i].intervalo_rega, repositorio[i].ultima_rega);
    }
    fclose(f);
    return 1;
}
