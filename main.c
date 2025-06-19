#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Necessário para a função isnan()
#include "expressao.h"

// Função para limpar o buffer de entrada, evitando problemas com scanf
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para limpar o terminal
void limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    char tipo[10];
    char buffer[512];
    char* resultado_conversao;
    float resultado_valor;

    while (1) {
        limpar_terminal();
        printf("--- Avaliador de Expressoes Matematicas ---\n");
        printf("Digite o tipo de expressao que deseja trabalhar ([infixa] ou [posfixa]):\n");
        printf("Digite 'sair' para encerrar o programa.\n> ");
        fgets(tipo, sizeof(tipo), stdin);
        tipo[strcspn(tipo, "\n")] = 0; // Remove o '\n'

        if (strcmp(tipo, "sair") == 0) {
            printf("Saindo do programa...\n");
            break;
        }

        if (strcmp(tipo, "infixa") == 0) {
            printf("Digite a expressao infixa:\n> ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0; // Remove o '\n'

            // Converter para pos-fixa
            resultado_conversao = getFormaPosFixa(buffer);
            if (resultado_conversao && strlen(resultado_conversao) > 0) {
                printf("Forma Pos-fixa: %s\n", resultado_conversao);
            } else {
                printf("Nao foi possivel converter a expressao.\n");
                continue;
            }

            // Avaliar valor da expressão infixa
            resultado_valor = getValorInFixa(buffer);
            if (!isnan(resultado_valor)) {
                printf("Valor (Infixa): %.2f\n", resultado_valor);
            } else {
                printf("Erro ao avaliar a expressao infixa.\n");
            }

        } else if (strcmp(tipo, "posfixa") == 0) {
            printf("Digite a expressao pos-fixa (com espacos):\n> ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0; // Remove o '\n'

            // Converter para infixa
            resultado_conversao = getFormaInFixa(buffer);
            if (resultado_conversao && strlen(resultado_conversao) > 0) {
                printf("Forma Infixa: %s\n", resultado_conversao);
            } else {
                printf("Nao foi possivel converter a expressao.\n");
                continue;
            }

            // Avaliar valor da expressão pos-fixa
            resultado_valor = getValorPosFixa(buffer);
            if (!isnan(resultado_valor)) {
                printf("Valor (Pos-fixa): %.2f\n", resultado_valor);
            } else {
                printf("Erro ao avaliar a expressao pos-fixa.\n");
            }
        } else {
            printf("Tipo invalido! Use 'infixa' ou 'posfixa'.\n");
        }

        printf("\nPressione qualquer tecla para continuar...");
        getchar(); // Aguarda o usuário pressionar uma tecla antes de reiniciar
    }

    return 0;
}
