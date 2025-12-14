#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARQ_MEDICO "medicos.bin"
#define ARQ_PACIENTE "pacientes.bin"
#define ARQ_CONSULTA "consultas.bin"

typedef struct Medico {
    int ID;
    char nome[55];
    char especialidade[55];
} Medico;

typedef struct Paciente {
    int ID;
    char nome[55];
    char identidade[20];
    char endereco[100];
    char telefone[20];
    char sexo[20]
} Paciente;

typedef struct Consulta {
    int ID;
    int idMedico;
    int idPaciente;
    char horario[10];
    char data[15];
    char duracao[10];
} Consulta;

int subMenu(char str[]);
int subMenuRelatorios();

void carregar_medicos(Medico **medico, int *tamMedico, int *idMedico);
void incluir_medico(Medico **medico, int *tamMedico, int *idMedico);
void listar_todos_medicos(Medico *medico, int tamMedico);
void pesquisar_medico(Medico *medico, int tamMedico);
void alterar_medico(Medico **medico, int tamMedico);
void excluir_medico(Medico **medico, int *tamMedico);

void carregar_pacientes(Paciente **paciente, int *tamPaciente, int *idPaciente);
void incluir_paciente(Paciente **paciente, int *tamPaciente, int *idPaciente);
void listar_todos_pacientes(Paciente *paciente, int tamPaciente);
void pesquisar_paciente(Paciente *paciente, int tamPaciente);
void alterar_paciente(Paciente **paciente, int tamPaciente);
void excluir_paciente(Paciente **paciente, int *tamPaciente);


int main() {
    int opcao;
    Medico *medico = NULL;
    int tamMedico = 0, idMedico = 0;

    Paciente *paciente = NULL;
    int tamPaciente = 0, idPaciente = 0;

    carregar_medicos(&medico, &tamMedico, &idMedico);
    carregar_pacientes(&paciente, &tamPaciente, &idPaciente);

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
                            incluir_paciente(&paciente, &tamPaciente, &idPaciente);
                            break;
                        case 2:
                            alterar_paciente(&paciente, tamPaciente);
                            break;
                        case 3:
                            excluir_paciente(&paciente, &tamPaciente);
                            break;
                        case 4:
                            pesquisar_paciente(paciente, tamPaciente);
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

void excluir_consultas_por_medico(int idMedico) {
    FILE *fp = fopen(ARQ_CONSULTA, "rb");
    FILE *temp = fopen("temp_consulta.bin", "wb");
    Consulta aux;

    if(fp == NULL || temp == NULL) {
        if(fp) fclose(fp);
        if(temp) fclose(temp);
        return;
    }

    while(fread(&aux, sizeof(Consulta), 1, fp) == 1) {
        if(aux.idMedico != idMedico) {
            fwrite(&aux, sizeof(Consulta), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(ARQ_CONSULTA);
    rename("temp_consulta.bin", ARQ_CONSULTA);
}

void excluir_medico(Medico **medico, int *tamMedico) {
    FILE *fp = fopen(ARQ_MEDICO, "rb");
    FILE *temp = fopen("temp_medico.bin", "wb");
    Medico aux;
    int idExcluir, achado = 0;

    if(fp == NULL || temp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        return;
    }

    listar_todos_medicos(*medico, *tamMedico);

    printf("\n--- digite o ID do medico que deseja excluir: ");
    scanf("%d", &idExcluir);
    getchar();

    while(fread(&aux, sizeof(Medico), 1, fp) == 1) {
        if(aux.ID == idExcluir) {
            achado = 1;
        } else {
            fwrite(&aux, sizeof(Medico), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if(!achado) {
        printf("\n--- medico nao encontrado ---\n");
        remove("temp_medico.bin");
        return;
    }

    excluir_consultas_por_medico(idExcluir);
    remove(ARQ_MEDICO);
    rename("temp_medico.bin", ARQ_MEDICO);

    free(*medico);
    *medico = NULL;
    *tamMedico = 0;
    int idAux = 0;

    carregar_medicos(medico, tamMedico, &idAux);

    printf("\n--- medico excluido com sucesso ---\n");
}

//pacientes
void carregar_pacientes(Paciente **paciente, int *tamPaciente, int *idPaciente) {
    FILE *fp = fopen(ARQ_PACIENTE, "rb");
    Paciente aux;

    if(fp == NULL) return;

    *tamPaciente = 0;
    *idPaciente = 0;

    while(fread(&aux, sizeof(Paciente), 1, fp) == 1) {
        Paciente *temp = realloc(*paciente, (*tamPaciente + 1) * sizeof(Paciente));
        if(temp == NULL) {
            fclose(fp);
            return;
        }
        *paciente = temp;

        (*paciente)[*tamPaciente] = aux;
        (*tamPaciente)++;

        if(aux.ID > *idPaciente)
            *idPaciente = aux.ID;
    }

    fclose(fp);
}

void incluir_paciente(Paciente **paciente, int *tamPaciente, int *idPaciente) {
    FILE *fp = fopen(ARQ_PACIENTE, "ab");
    Paciente novo;

    if(fp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        return;
    }

    (*idPaciente)++;
    novo.ID = *idPaciente;

    printf("\n--- digite o nome do paciente: ");
    fgets(novo.nome, 55, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("--- digite a identidade: ");
    fgets(novo.identidade, 20, stdin);
    novo.identidade[strcspn(novo.identidade, "\n")] = '\0';

    printf("--- digite o endereco: ");
    fgets(novo.endereco, 100, stdin);
    novo.endereco[strcspn(novo.endereco, "\n")] = '\0';

    printf("--- digite o telefone: ");
    fgets(novo.telefone, 20, stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = '\0';

    printf("--- digite o sexo: ");
    fgets(novo.sexo, 20, stdin);
    novo.sexo[strcspn(novo.sexo, "\n")] = '\0';

    fwrite(&novo, sizeof(Paciente), 1, fp);
    fclose(fp);

    Paciente *temp = realloc(*paciente, (*tamPaciente + 1) * sizeof(Paciente));
    if(temp == NULL) {
        printf("\n--- erro de memoria ---\n");
        return;
    }

    *paciente = temp;
    (*paciente)[*tamPaciente] = novo;
    (*tamPaciente)++;

    printf("\n--- paciente incluído com sucesso ---\n");
}

void pesquisar_paciente(Paciente *paciente, int tamPaciente) {
    FILE *fp = fopen(ARQ_PACIENTE, "rb");
    Paciente aux;
    char nome[55];
    int achado = 0;

    if(fp == NULL) {
        printf("\n--- nao ha pacientes cadastrados ---\n");
        return;
    }

    printf("\n--- digite o nome do paciente: ");
    fgets(nome, 55, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while(fread(&aux, sizeof(Paciente), 1, fp) == 1) {
        if(strcmp(aux.nome, nome) == 0) {
            printf("ID: %d | Nome: %s | Identidade: %s | Endereco: %s | Telefone: %s | Sexo: %s\n",
                aux.ID, aux.nome, aux.identidade, aux.endereco, aux.telefone, aux.sexo);
            achado = 1;
        }
    }

    fclose(fp);

    if(!achado) {
        printf("\n--- paciente nao encontrado ---\n");
    }
}

void alterar_paciente(Paciente **paciente, int tamPaciente) {
    FILE *fp = fopen(ARQ_PACIENTE, "rb+");
    Paciente aux;
    int idAlterar, achado = 0;

    if(fp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        return;
    }

    listar_todos_pacientes(*paciente, tamPaciente);

    printf("\n--- digite o ID do paciente que deseja alterar: ");
    scanf("%d", &idAlterar);
    getchar();

    while(fread(&aux, sizeof(Paciente), 1, fp) == 1) {
        if(aux.ID == idAlterar) {
            achado = 1;

            printf("\n--- digite o novo nome: ");
            fgets(aux.nome, 55, stdin);
            aux.nome[strcspn(aux.nome, "\n")] = '\0';

            printf("--- digite a nova identidade: ");
            fgets(aux.identidade, 20, stdin);
            aux.identidade[strcspn(aux.identidade, "\n")] = '\0';

            printf("--- digite o novo endereco: ");
            fgets(aux.endereco, 100, stdin);
            aux.endereco[strcspn(aux.endereco, "\n")] = '\0';

            printf("--- digite o novo telefone: ");
            fgets(aux.telefone, 20, stdin);
            aux.telefone[strcspn(aux.telefone, "\n")] = '\0';

            printf("--- digite o novo sexo: ");
            fgets(aux.sexo, 20, stdin);
            aux.sexo[strcspn(aux.sexo, "\n")] = '\0';

            fseek(fp, -sizeof(Paciente), SEEK_CUR);
            fwrite(&aux, sizeof(Paciente), 1, fp);
            break;
        }
    }

    fclose(fp);

    if(!achado)
        printf("\n--- paciente nao encontrado ---\n");
    else
        printf("\n--- paciente alterado com sucesso ---\n");
}

void excluir_paciente(Paciente **paciente, int *tamPaciente) {
    FILE *fp = fopen(ARQ_PACIENTE, "rb");
    FILE *temp = fopen("temp_paciente.bin", "wb");
    Paciente aux;
    int idExcluir, achado = 0;

    if(fp == NULL || temp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        return;
    }

    listar_todos_pacientes(*paciente, *tamPaciente);

    printf("\n--- digite o ID do paciente que deseja excluir: ");
    scanf("%d", &idExcluir);
    getchar();

    while(fread(&aux, sizeof(Paciente), 1, fp) == 1) {
        if(aux.ID == idExcluir) {
            achado = 1;
        } else {
            fwrite(&aux, sizeof(Paciente), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if(!achado) {
        printf("\n--- paciente nao encontrado ---\n");
        remove("temp_paciente.bin");
        return;
    }

    remove(ARQ_PACIENTE);
    rename("temp_paciente.bin", ARQ_PACIENTE);

    free(*paciente);
    *paciente = NULL;
    *tamPaciente = 0;
    int idAux = 0;

    carregar_pacientes(paciente, tamPaciente, &idAux);

    printf("\n--- paciente excluido com sucesso ---\n");
}

