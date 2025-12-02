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
                    break;
                }
            break;

            case 2:
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
                        break;
                }
            break;

            case 3:
                switch (subMenu("Medico")) {
                    case 1:
                       incluir_medico(&medico, &tamMedico, &idMedico);
                        break;
                    case 2:
                       alterar_medico();
                        break;
                    case 3:
                       excluir_medico();
                        break;
                    case 4:
                        pesquisar_medico(medico, tamMedico);
                        break;
                    case 5:
                        break;
                }
            break;

            case 4:
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
                        break;
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
    return subOpcao;
}

void incluir_medico(Medico **medico, int *tamMedico, int *idMedico) {
    Medico *temp = realloc(*medico, (*tamMedico + 1) * sizeof(Medico));
    if(temp == NULL) {
        printf("nao foi possivel incluir o medico, tente novamente.\n");
        return;
    }
    *medico = temp;

    (*idMedico)++;
    (*medico)[*tamMedico].ID = *idMedico;

    printf("digite o nome do medico: ");
    fgets((*medico)[*tamMedico].nome, 55, stdin);
    (*medico)[*tamMedico].nome[strcspn((*medico)[*tamMedico].nome, "\n")] = '\0';

    printf("digite a especialidade do medico: ");
    fgets((*medico)[*tamMedico].especialidade, 55, stdin);
    (*medico)[*tamMedico].especialidade[strcspn((*medico)[*tamMedico].especialidade, "\n")] = '\0';

    (*tamMedico)++;
    printf("medico incluido com sucesso !\n");
}

void pesquisar_medico(Medico *medico, int tamMedico) {
    char nome[55];
    int achado = 0;
    if(tamMedico == 0) {
        printf("nao ha medicos cadastrados.\n");
        return;
    }

    printf("digite o nome do medico: ");
    fgets(nome, 55, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(int i = 0; i < tamMedico; i++) {
        if(!strcmp(medico->nome, nome)) {
            achado = 1;
            printf("medico %d encontrado(a):\n", i);
            printf("id: %d\n", medico[i].ID);
            printf("nome: %s\n", medico[i].nome);
            printf("especialidade: %s\n", medico[i].especialidade);
        }
    }

    if(!achado) {
        printf("nao ha nenhum(a) medico(a) com esse nome\n");
    }

}
