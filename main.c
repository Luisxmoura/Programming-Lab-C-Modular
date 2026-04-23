#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plantas.h"
#include "regas.h"
#include "tarefas.h"

#define CSV_PLANTAS  "plantas.csv"
#define CSV_REGAS    "regas.csv"
#define CSV_TAREFAS  "tarefas.csv"

/* Persistência imediata após cada escrita */
static void guardar_tudo(void) {
    plantas_guardar(CSV_PLANTAS);
    regas_guardar(CSV_REGAS);
    tarefas_guardar(CSV_TAREFAS);
}

/* CORREÇÃO excerto 10: leitura de strings com espaços via fgets em vez de scanf("%s").
   scanf("%s") pára no primeiro espaço — inaceitável para nomes e descrições. */
static void ler_string(const char *prompt, char *dest, int tamanho) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(dest, tamanho, stdin) == NULL) { dest[0] = '\0'; return; }
    /* Remove \n final */
    char *nl = strchr(dest, '\n');
    if (nl) *nl = '\0';
}

static void menu_plantas(void) {
    char nome[50], especie[50], data[11];
    int intervalo;

    ler_string("Nome: ",          nome,    sizeof(nome));
    ler_string("Especie: ",       especie, sizeof(especie));
    ler_string("Data (DD/MM/AAAA): ", data, sizeof(data));
    printf("Intervalo de rega (dias): ");
    scanf("%d", &intervalo);
    getchar(); /* consome \n deixado pelo scanf */

    if (plantas_adicionar(nome, especie, data, intervalo))
        guardar_tudo();
}

static void menu_rega(void) {
    int id, data, qtd;
    printf("ID da planta: ");    scanf("%d", &id);
    printf("Dia (timestamp): "); scanf("%d", &data);
    printf("Quantidade (ml): "); scanf("%d", &qtd);
    getchar();

    if (regas_registar(id, data, qtd))
        guardar_tudo();
}

static void menu_tarefa(void) {
    char descricao[100];
    int data;

    /* CORREÇÃO excerto 10: fgets em vez de scanf("%s") */
    ler_string("Descricao: ", descricao, sizeof(descricao));
    printf("Dia previsto (timestamp): ");
    scanf("%d", &data);
    getchar();

    if (tarefas_criar(descricao, data))
        guardar_tudo();
}

static void menu_concluir_tarefa(void) {
    int id;
    printf("ID da tarefa: "); scanf("%d", &id); getchar();
    if (tarefas_concluir(id))
        guardar_tudo();
}

static void imprimir_menu(void) {
    // Adiciona espaço antes do menu para não colar ao resultado anterior
    printf("\n\n==========================================\n");
    printf("      GreenTrack - Menu Principal       \n");
    printf("==========================================\n");
    printf(" 1. Listar plantas\n");
    printf(" 2. Adicionar planta\n");
    printf(" 3. Registar rega\n");
    printf(" 4. Verificar necessidade\n");
    printf(" 5. Listar regas\n");
    printf(" 6. Criar tarefa\n");
    printf(" 7. Concluir tarefa\n");
    printf(" 8. Listar tarefas pendentes\n");
    printf(" 9. Listar todas as tarefas\n");
    printf(" 0. Sair\n");
    printf("------------------------------------------\n");
    printf("Opcao: ");

}

int main(void) {
    /* Carrega dados persistidos (falha silenciosa se CSV não existir) */
    plantas_carregar(CSV_PLANTAS);
    regas_carregar(CSV_REGAS);
    tarefas_carregar(CSV_TAREFAS);

    int opcao;
    do {
        imprimir_menu();
        if (scanf("%d", &opcao) != 1) { 
            while(getchar() != '\n'); // Limpa buffer de erro
            continue;
        }

        getchar();

        switch (opcao) {
            case 1: plantas_listar();              break;
            case 2: menu_plantas();                break;
            case 3: menu_rega();                   break;
            case 4: {
                int dia;
                printf("Dia atual (timestamp): "); scanf("%d", &dia); getchar();
                regas_verificar_necessidade(dia);
                break;
            }
            case 5: regas_listar();                break;
            case 6: menu_tarefa();                 break;
            case 7: menu_concluir_tarefa();        break;
            case 8: tarefas_listar_pendentes();    break;
            case 9: tarefas_listar_todas();        break;
            case 0: printf("A sair...\n");         break;
            default: printf("Opcao invalida.\n");  break;
        }
    } while (opcao != 0);

    return 0;
}
