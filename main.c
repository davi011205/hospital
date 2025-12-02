#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int subMenu();
int subMenuRelatorios();

typedef struct Medico {
    int ID;
    char nome[55];
    char especialidade[55];
} Medico;

void incluir_medico(Medico **Medico, int *tamMedico, int *idMedico);
void pesquisar_medico(Medico *Medico, int tamMedico);
void listar_todos_medicos(Medico *Medico, int tamMedico);
void alterar_medico(Medico **Medico, int tamMedico);

int main() {
    int opcao;
    Medico *medico = NULL;
    int tamMedico = 0, idMedico = 0;

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
                            excluir_medico();
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

void incluir_medico(Medico **medico, int *tamMedico, int *idMedico) {
    Medico *temp = realloc(*medico, (*tamMedico + 1) * sizeof(Medico));
    if(temp == NULL) {
        printf("\n--- nao foi possivel incluir o medico, tente novamente ---\n");
        return;
    }
    *medico = temp;

    (*idMedico)++;
    (*medico)[*tamMedico].ID = *idMedico;

    printf("\n--- digite o nome do medico: ");
    fgets((*medico)[*tamMedico].nome, 55, stdin);
    (*medico)[*tamMedico].nome[strcspn((*medico)[*tamMedico].nome, "\n")] = '\0';

    printf("--- digite a especialidade do medico: ");
    fgets((*medico)[*tamMedico].especialidade, 55, stdin);
    (*medico)[*tamMedico].especialidade[strcspn((*medico)[*tamMedico].especialidade, "\n")] = '\0';

    (*tamMedico)++;
    printf("--- medico incluido com sucesso ---\n");
}

void pesquisar_medico(Medico *medico, int tamMedico) {
    char nome[55];
    int achado = 0;
    if(tamMedico == 0) {
        printf("\n--- nao ha medicos cadastrados ---\n");
        return;
    }

    printf("\n--- digite o nome do medico que deseja encontrar: ");
    fgets(nome, 55, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(int i = 0; i < tamMedico; i++) {
        if(!strcmp(medico[i].nome, nome)) {
            achado = 1;
            printf("--- ID: %d | Nome: %s | Especialidade: %s\n", medico[i].ID, medico[i].nome, medico[i].especialidade);
        }
    }

    if(!achado) {
        printf("\n--- nao ha nenhum(a) medico(a) com esse nome ---\n");
    }
    printf("\n");
}

void listar_todos_medicos(Medico *medico, int tamMedico) {
    if(tamMedico == 0) {
        printf("\n--- nao ha medicos cadastrados ---\n");
        return;
    }

    printf("\n--- medicos cadastrados: \n");
    for(int i = 0; i < tamMedico; i++) {
        printf("ID: %d | Nome: %s | Especialidade: %s\n", medico[i].ID, medico[i].nome, medico[i].especialidade);
    }
}

void alterar_medico(Medico **medico, int tamMedico) {
    int idAlterar, achado = 0;
    listar_todos_medicos(*medico, tamMedico);

    printf("\n--- digite o id referente ao medico que deseja alterar: ");
    scanf("%d", &idAlterar);
    getchar();

    for(int i = 0; i < tamMedico; i++) {
        if((*medico)[i].ID == idAlterar) {
            achado = 1;
            printf("\n--- medico(a) selecionado(a):\n");
            printf("--- ID: %d | Nome: %s | Especialidade: %s", (*medico)[i].ID, (*medico)[i].nome, (*medico)[i].especialidade);

            printf("\n--------Alterando--------\n");

            printf("--- digite o novo nome: ");
            fgets((*medico)[i].nome, 55, stdin);
            (*medico)[i].nome[strcspn((*medico)[i].nome, "\n")] = '\0';

            printf("--- digite a nova especialidade: ");
            fgets((*medico)[i].especialidade, 55, stdin);
            (*medico)[i].especialidade[strcspn((*medico)[i].especialidade, "\n")] = '\0';

            printf("\n--- medico(a) alterado(a) com sucesso! Confira os novos dados:\n");
            printf("--- ID: %d | Nome: %s | Especialidade: %s\n\n", (*medico)[i].ID, (*medico)[i].nome, (*medico)[i].especialidade);
            return;
        }
    }

    if(!achado) {
        printf("\n---nao ha nenhum(a) medico(a) referente ao ID %d---\n", idAlterar);
    }
}