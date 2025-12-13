#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARQ_MEDICO "medicos.bin"

typedef struct Medico {
    int ID;
    char nome[55];
    char especialidade[55];
} Medico;

int subMenu(char str[]);
int subMenuRelatorios();

void carregar_medicos(Medico **medico, int *tamMedico, int *idMedico);
void incluir_medico(Medico **medico, int *tamMedico, int *idMedico);
void listar_todos_medicos(Medico *medico, int tamMedico);
void pesquisar_medico(Medico *medico, int tamMedico);
void alterar_medico(Medico **medico, int tamMedico);
void excluir_medico(Medico **medico, int *tamMedico);

int main() {
    int opcao;
    Medico *medico = NULL;
    int tamMedico = 0, idMedico = 0;

    carregar_medicos(&medico, &tamMedico, &idMedico);

    do {
        printf("--- BEM VINDO AO SISTEMA HOSPITALAR ---\n");
        printf("1 - Consulta\n");
        printf("2 - Paciente\n");
        printf("3 - Medico\n");
        printf("4 - Relatorios\n");
        printf("5 - Sair\n");
        printf("digite a opcao desejada: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                int loop = 1;
                while (loop) {
                    switch (subMenu("Consulta")) {
                        case 1:
                            incluir_consulta();
                            break;
                        case 2:
                            alterar_consulta();
                            break;
                        case 3:
                            excluir_consulta();
                            break;
                        case 4:
                            pesquisar_consulta();
                            break;
                        case 5:
                            loop = 0;
                            break;
                    }
                }
            break;

            case 2:
                int loop = 1;
                while (loop) {
                    switch (subMenu("Paciente")) {
                        case 1:
                            incluir_paciente();
                            break;
                        case 2:
                            alterar_paciente();
                            break;
                        case 3:
                            excluir_paciente();
                            break;
                        case 4:
                            pesquisar_paciente();
                            break;
                        case 5:
                            loop = 0;
                            break;
                    }
                }
            break;

            case 3:
                int loop = 1;
                while (loop) {
                    switch (subMenu("Medico")) {
                        case 1:
                            incluir_medico(&medico, &tamMedico, &idMedico);
                            break;
                        case 2:
                            alterar_medico(&medico, tamMedico);
                            break;
                        case 3:
                            excluir_medico(&medico, &tamMedico);
                            break;
                        case 4:
                            pesquisar_medico(medico, tamMedico);
                            break;
                        case 5:
                            loop = 0;
                            break;
                    }
                }
            break;

            case 4:
                int loop = 1;
                while (loop) {
                    switch (subMenuRelatorios()) {
                        case 1:
                            listar_consulta_paciente();
                            break;
                        case 2:
                            listar_consulta_medico();
                            break;
                        case 3:
                            listar_paciente_especialidade();
                            break;
                        case 4:
                            loop = 0;
                            break;
                    }
                }
            break;

            
        }
    } while(opcao != 5);

    free(medico);
    return 0;
}

int subMenu(char str[]) {
    int subOpcao;
    printf("--- %s - O que deseja fazer ---\n", str);
    printf("1 - Incluir %s\n", str);
    printf("2 - Alterar %s\n", str);
    printf("3 - Excluir %s\n", str);
    printf("4 - Pesquisar %s\n", str);
    printf("5 - Voltar\n");
    printf("digite a opcao desejada: ");
    scanf("%d", &subOpcao);
    getchar();
    return subOpcao;
}

int subMenuRelatorios() {
    int subOpcao;
    printf("--- O que deseja fazer ---\n");
    printf("1 - Listar consultas agendadas para o paciente\n");
    printf("2 - Listar consultas agendadas para o médico\n");
    printf("3 - Listar pacientes por especialidade\n");
    printf("4 - Voltar\n");
    printf("digite a opcao desejada: ");
    scanf("%d", &subOpcao);
    getchar();
    return subOpcao;
}

void carregar_medicos(Medico **medico, int *tamMedico, int *idMedico) {
    FILE *fp = fopen(ARQ_MEDICO, "rb");
    Medico aux;

    if(fp == NULL) {
        return; // arquivo ainda não existe
    }

    *tamMedico = 0;
    *idMedico = 0;

    while(fread(&aux, sizeof(Medico), 1, fp) == 1) {
        Medico *temp = realloc(*medico, (*tamMedico + 1) * sizeof(Medico));
        if(temp == NULL) {
            fclose(fp);
            return;
        }
        *medico = temp;

        (*medico)[*tamMedico] = aux;
        (*tamMedico)++;

        if(aux.ID > *idMedico)
            *idMedico = aux.ID;
    }

    fclose(fp);
}


void incluir_medico(Medico **medico, int *tamMedico, int *idMedico) {
    FILE *fp = fopen(ARQ_MEDICO, "ab");

    if(fp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        return;
    }

    Medico novo;

    (*idMedico)++;
    novo.ID = *idMedico;

    printf("\n--- digite o nome do medico: ");
    fgets(novo.nome, 55, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("--- digite a especialidade do medico: ");
    fgets(novo.especialidade, 55, stdin);
    novo.especialidade[strcspn(novo.especialidade, "\n")] = '\0';

    fwrite(&novo, sizeof(Medico), 1, fp);
    fclose(fp);

    Medico *temp = realloc(*medico, (*tamMedico + 1) * sizeof(Medico));
    if(temp == NULL) {
        printf("\n--- erro de memoria ---\n");
        return;
    }

    *medico = temp;
    (*medico)[*tamMedico] = novo;
    (*tamMedico)++;

    printf("\n--- medico incluido com sucesso ---\n");
}

void pesquisar_medico(Medico *medico, int tamMedico) {
    FILE *fp = fopen(ARQ_MEDICO, "rb");
    Medico aux;
    
    char nome[55];
    int achado = 0;

    if(fp == NULL) {
        printf("\n--- nao ha medicos cadastrados ---\n");
        return;
    }

    printf("\n--- digite o nome do medico: ");
    fgets(nome, 55, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while(fread(&aux, sizeof(Medico), 1, fp) == 1) {
        if(strcmp(aux.nome, nome) == 0) {
            printf("--- ID: %d | Nome: %s | Especialidade: %s\n", aux.ID, aux.nome, aux.especialidade);
            achado = 1;
        }
    }

    fclose(fp);

    if(!achado) {
        printf("\n--- medico nao encontrado ---\n");
    }
}

void listar_todos_medicos(Medico *medico, int tamMedico) {
    FILE *fp = fopen(ARQ_MEDICO, "rb");
    Medico aux;

    if(fp == NULL) {
        printf("\n--- nao ha medicos cadastrados ---\n");
        return;
    }

    printf("\n--- medicos cadastrados: \n");
    while(fread(&aux, sizeof(Medico), 1, fp) == 1) {
        printf("ID: %d | Nome: %s | Especialidade: %s\n", aux.ID, aux.nome, aux.especialidade);
    }

    fclose(fp);
}


void alterar_medico(Medico **medico, int tamMedico) {
    FILE *fp = fopen(ARQ_MEDICO, "rb+");
    Medico aux;

    int idAlterar, achado = 0;

    if(fp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        return;
    }

    listar_todos_medicos(*medico, tamMedico);

    printf("\n--- digite o ID do medico que deseja alterar: ");
    scanf("%d", &idAlterar);
    getchar();

    while(fread(&aux, sizeof(Medico), 1, fp) == 1) {
        if(aux.ID == idAlterar) {
            achado = 1;

            printf("\n--- digite o novo nome: ");
            fgets(aux.nome, 55, stdin);
            aux.nome[strcspn(aux.nome, "\n")] = '\0';

            printf("--- digite a nova especialidade: ");
            fgets(aux.especialidade, 55, stdin);
            aux.especialidade[strcspn(aux.especialidade, "\n")] = '\0';

            fseek(fp, -sizeof(Medico), SEEK_CUR);
            fwrite(&aux, sizeof(Medico), 1, fp);
            break;
        }
    }

    fclose(fp);

    if(!achado) {
        printf("\n--- medico nao encontrado ---\n");
    } else {
        carregar_medicos(medico, &tamMedico, &(int){0});
        printf("\n--- medico alterado com sucesso ---\n");
    }
}