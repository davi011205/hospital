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
    char sexo[20];
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
void alterar_medico(Medico **medico, int tamMedico, int *idMedico);
void excluir_medico(Medico **medico, int *tamMedico);

void carregar_pacientes(Paciente **paciente, int *tamPaciente, int *idPaciente);
void incluir_paciente(Paciente **paciente, int *tamPaciente, int *idPaciente);
void listar_todos_pacientes(Paciente *paciente, int tamPaciente);
void pesquisar_paciente(Paciente *paciente, int tamPaciente);
void alterar_paciente(Paciente **paciente, int tamPaciente, int *idPaciente);
void excluir_paciente(Paciente **paciente, int *tamPaciente);

void carregar_consultas(Consulta **consulta, int *tamConsulta, int *idConsulta);
void incluir_consulta(Consulta **consulta, int *tamConsulta, int *idConsulta, Medico *medico, int tamMedico, Paciente *paciente, int tamPaciente);
void listar_todas_consultas(Consulta *consulta, int tamConsulta);
void pesquisar_consulta(Consulta *consulta, int tamConsulta);
void excluir_consulta(Consulta **consulta, int *tamConsulta, int *idConsulta);
void alterar_consulta(Consulta **consulta, int tamConsulta, int *idConsulta, Medico *medico, int tamMedico, Paciente *paciente, int tamPaciente);
void listar_consulta_paciente(Consulta *consulta, int tamConsulta, Paciente *paciente, int tamPaciente);
void listar_consulta_medico(Consulta *consulta, int tamConsulta, Medico *medico, int tamMedico);
void listar_paciente_especialidade(Consulta *consulta, int tamConsulta, Medico *medico, int tamMedico, Paciente *paciente, int tamPaciente);

int main() {
    int opcao;
    Medico *medico = NULL;
    int tamMedico = 0, idMedico = 0;

    Paciente *paciente = NULL;
    int tamPaciente = 0, idPaciente = 0;

    Consulta *consulta = NULL;   
    int tamConsulta = 0;         
    int idConsulta = 0;

    carregar_medicos(&medico, &tamMedico, &idMedico);
    carregar_pacientes(&paciente, &tamPaciente, &idPaciente);
    carregar_consultas(&consulta, &tamConsulta, &idConsulta);

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
            case 1: ;
                int loop = 1;
                while (loop) {
                    switch (subMenu("Consulta")) {
                        case 1:
                            incluir_consulta(&consulta, &tamConsulta, &idConsulta, medico, tamMedico, paciente, tamPaciente);
                            break;
                        case 2:
                            alterar_consulta(&consulta, tamConsulta, &idConsulta, medico, tamMedico, paciente, tamPaciente);
                            break;
                        case 3:
                            excluir_consulta(&consulta, &tamConsulta, &idConsulta);
                            break;
                        case 4:
                            pesquisar_consulta(consulta, tamConsulta);
                            break;
                        case 5:
                            listar_todas_consultas(consulta, tamConsulta);
                            break;
                        case 6:
                            loop = 0;
                            break;
                    }
                }
            break;

            case 2:
                loop = 1;
                while (loop) {
                    switch (subMenu("Paciente")) {
                        case 1:
                            incluir_paciente(&paciente, &tamPaciente, &idPaciente);
                            break;
                        case 2:
                            alterar_paciente(&paciente, tamPaciente, &idPaciente);
                            break;
                        case 3:
                            excluir_paciente(&paciente, &tamPaciente);
                            break;
                        case 4:
                            pesquisar_paciente(paciente, tamPaciente);
                            break;
                        case 5:
                            listar_todos_pacientes(paciente, tamPaciente);
                            break;
                        case 6:
                            loop = 0;
                            break;
                    }
                }
            break;

            case 3:
                loop = 1;
                while (loop) {
                    switch (subMenu("Medico")) {
                        case 1:
                            incluir_medico(&medico, &tamMedico, &idMedico);
                            break;
                        case 2:
                            alterar_medico(&medico, tamMedico, &idMedico);
                            break;
                        case 3:
                            excluir_medico(&medico, &tamMedico);
                            free(consulta);
                            consulta = NULL;
                            carregar_consultas(&consulta, &tamConsulta, &idConsulta);
                            break;
                        case 4:
                            pesquisar_medico(medico, tamMedico);
                            break;
                        case 5:
                            listar_todos_medicos(medico, tamMedico);
                            break;
                        case 6:
                            loop = 0;
                            break;
                    }
                }
            break;

            case 4:
                loop = 1;
                while (loop) {
                    switch (subMenuRelatorios()) {
                        case 1:
                            listar_consulta_paciente(consulta, tamConsulta, paciente, tamPaciente);
                            break;
                        case 2:
                            listar_consulta_medico(consulta, tamConsulta, medico, tamMedico);
                            break;
                        case 3:
                            listar_paciente_especialidade(consulta, tamConsulta, medico, tamMedico, paciente, tamPaciente);
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
    free(consulta);
    free(paciente);
    return 0;
}

int subMenu(char str[]) {
    int subOpcao;
    printf("--- %s - O que deseja fazer ---\n", str);
    printf("1 - Incluir %s\n", str);
    printf("2 - Alterar %s\n", str);
    printf("3 - Excluir %s\n", str);
    printf("4 - Pesquisar %s\n", str);
    printf("5 - Listar %s\n", str);
    printf("6 - Voltar\n");
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
        return;
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


void alterar_medico(Medico **medico, int tamMedico, int *idMaior) {
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
        free(*medico);
        *medico = NULL;
        carregar_medicos(medico, &tamMedico, idMaior);
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

void listar_todos_pacientes(Paciente *paciente, int tamPaciente) {
    FILE *fp = fopen(ARQ_PACIENTE, "rb");
    Paciente aux;

    if(fp == NULL) {
        printf("\n--- nao ha pacientes cadastrados ---\n");
        return;
    }

    printf("\n--- pacientes cadastrados ---\n");
    while(fread(&aux, sizeof(Paciente), 1, fp) == 1) {
        printf("ID: %d | Nome: %s | Identidade: %s | Endereco: %s | Telefone: %s | Sexo: %s\n",
            aux.ID, aux.nome, aux.identidade, aux.endereco, aux.telefone, aux.sexo);
    }

    fclose(fp);
}

void alterar_paciente(Paciente **paciente, int tamPaciente, int *idMaior) {
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
    else{
    free(*paciente);
    *paciente = NULL;
    int tamTemp = 0;
    carregar_pacientes(paciente, &tamTemp, idMaior);
        printf("\n--- paciente alterado com sucesso ---\n");
    }
}

void excluir_consultas_por_paciente(int idPaciente) {
    FILE *fp = fopen(ARQ_CONSULTA, "rb");
    FILE *temp = fopen("temp_consulta.bin", "wb");
    Consulta aux;

    if(fp == NULL || temp == NULL) {
        if(fp) fclose(fp);
        if(temp) fclose(temp);
        return;
    }

    while(fread(&aux, sizeof(Consulta), 1, fp) == 1) {
        if(aux.idPaciente != idPaciente) {
            fwrite(&aux, sizeof(Consulta), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(ARQ_CONSULTA);
    rename("temp_consulta.bin", ARQ_CONSULTA);
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

    excluir_consultas_por_paciente(idExcluir);
    remove(ARQ_PACIENTE);
    rename("temp_paciente.bin", ARQ_PACIENTE);

    free(*paciente);
    *paciente = NULL;
    *tamPaciente = 0;
    int idAux = 0;

    carregar_pacientes(paciente, tamPaciente, &idAux);

    printf("\n--- paciente excluido com sucesso ---\n");
}

void carregar_consultas(Consulta **consulta, int *tamConsulta, int *idConsulta) {
    FILE *fp = fopen(ARQ_CONSULTA, "rb");
    Consulta aux;

    if(fp == NULL) return;

    *tamConsulta = 0;
    *idConsulta = 0;

    while(fread(&aux, sizeof(Consulta), 1, fp) == 1) {
        Consulta *temp = realloc(*consulta, (*tamConsulta + 1) * sizeof(Consulta));
        if(temp == NULL) {
            fclose(fp);
            return;
        }
        *consulta = temp;

        (*consulta)[*tamConsulta] = aux;
        (*tamConsulta)++;

        if(aux.ID > *idConsulta)
            *idConsulta = aux.ID;
    }
    fclose(fp);
}

void incluir_consulta(Consulta **consulta, int *tamConsulta, int *idConsulta, Medico *medico, int tamMedico, Paciente *paciente, int tamPaciente) {

    if (tamMedico == 0) {
        printf("\n--- Erro: Nenhum medico cadastrado. Cadastre um medico antes. ---\n");
        return;
    }
    if (tamPaciente == 0) {
        printf("\n--- Erro: Nenhum paciente cadastrado. Cadastre um paciente antes. ---\n");
        return;
    }

    FILE *fp = fopen(ARQ_CONSULTA, "ab");
    if(fp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        return;
    }

    Consulta novo;
    int idBusca, encontrado;

    listar_todos_medicos(medico, tamMedico);
    printf("\n--- Digite o ID do Medico para a consulta: ");
    scanf("%d", &idBusca);
    getchar();

    encontrado = 0;
    for(int i = 0; i < tamMedico; i++) {
        if(medico[i].ID == idBusca) {
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) {
        printf("\n--- Erro: ID de Medico nao encontrado! Cancelando operacao. ---\n");
        fclose(fp);
        return;
    }
    novo.idMedico = idBusca;

    listar_todos_pacientes(paciente, tamPaciente);
    printf("\n--- Digite o ID do Paciente para a consulta: ");
    scanf("%d", &idBusca);
    getchar();

    encontrado = 0;
    for(int i = 0; i < tamPaciente; i++) {
        if(paciente[i].ID == idBusca) {
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) {
        printf("\n--- Erro: ID de Paciente nao encontrado! Cancelando operacao. ---\n");
        fclose(fp);
        return;
    }
    novo.idPaciente = idBusca;

    (*idConsulta)++;
    novo.ID = *idConsulta;

    printf("--- Digite a Data (dd/mm/aaaa): ");
    fgets(novo.data, 15, stdin);
    novo.data[strcspn(novo.data, "\n")] = '\0';

    printf("--- Digite o Horario (hh:mm): ");
    fgets(novo.horario, 10, stdin);
    novo.horario[strcspn(novo.horario, "\n")] = '\0';

    printf("--- Digite a Duracao (ex: 30min): ");
    fgets(novo.duracao, 10, stdin);
    novo.duracao[strcspn(novo.duracao, "\n")] = '\0';

    fwrite(&novo, sizeof(Consulta), 1, fp);
    fclose(fp);


    Consulta *temp = realloc(*consulta, (*tamConsulta + 1) * sizeof(Consulta));
    if(temp == NULL) {
        printf("\n--- erro de memoria ---\n");
        return;
    }

    *consulta = temp;
    (*consulta)[*tamConsulta] = novo;
    (*tamConsulta)++;

    printf("\n--- Consulta agendada com sucesso! (ID: %d) ---\n", novo.ID);
}

void listar_todas_consultas(Consulta *consulta, int tamConsulta) {
    FILE *fp = fopen(ARQ_CONSULTA, "rb");
    Consulta aux;

    if(fp == NULL) {
        printf("\n--- nao ha consultas agendadas ---\n");
        return;
    }

    printf("\n--- Consultas Agendadas: ---\n");
    printf("%-5s | %-12s | %-8s | %-10s | %-10s | %-10s\n", "ID", "Data", "Hora", "Duracao", "ID Medico", "ID Paciente");
    printf("--------------------------------------------------------------------------\n");

    while(fread(&aux, sizeof(Consulta), 1, fp) == 1) {
        printf("%-5d | %-12s | %-8s | %-10s | %-10d | %-10d\n", 
            aux.ID, aux.data, aux.horario, aux.duracao, aux.idMedico, aux.idPaciente);
    }

    fclose(fp);
}

void pesquisar_consulta(Consulta *consulta, int tamConsulta) {
    FILE *fp = fopen(ARQ_CONSULTA, "rb");
    Consulta aux;
    int idBusca, achado = 0;

    if(fp == NULL) {
        printf("\n--- nao ha consultas agendadas ---\n");
        return;
    }

    printf("\n--- Digite o ID da consulta que deseja buscar: ");
    scanf("%d", &idBusca);
    getchar();

    while(fread(&aux, sizeof(Consulta), 1, fp) == 1) {
        if(aux.ID == idBusca) {
            printf("\n--- CONSULTA ENCONTRADA ---\n");
            printf("ID: %d\nData: %s - Hora: %s\nDuracao: %s\nID Medico: %d\nID Paciente: %d\n", 
                aux.ID, aux.data, aux.horario, aux.duracao, aux.idMedico, aux.idPaciente);
            achado = 1;
            break; 
        }
    }

    fclose(fp);

    if(!achado) {
        printf("\n--- consulta nao encontrada ---\n");
    }
}

void excluir_consulta(Consulta **consulta, int *tamConsulta, int *idConsulta) {
    FILE *fp = fopen(ARQ_CONSULTA, "rb");
    FILE *temp = fopen("temp_consulta.bin", "wb");
    Consulta aux;
    int idExcluir, achado = 0;

    if(fp == NULL || temp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        if(fp) fclose(fp);
        if(temp) fclose(temp);
        return;
    }

    listar_todas_consultas(*consulta, *tamConsulta);

    printf("\n--- Digite o ID da consulta que deseja cancelar/excluir: ");
    scanf("%d", &idExcluir);
    getchar();

    while(fread(&aux, sizeof(Consulta), 1, fp) == 1) {
        if(aux.ID == idExcluir) {
            achado = 1;
        } else {
            fwrite(&aux, sizeof(Consulta), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if(!achado) {
        printf("\n--- consulta nao encontrada ---\n");
        remove("temp_consulta.bin");
        return;
    }

    remove(ARQ_CONSULTA);
    rename("temp_consulta.bin", ARQ_CONSULTA);

    free(*consulta);
    *consulta = NULL;

    carregar_consultas(consulta, tamConsulta, idConsulta);

    printf("\n--- consulta excluida com sucesso ---\n");
}

void alterar_consulta(Consulta **consulta, int tamConsulta, int *idConsulta, Medico *medico, int tamMedico, Paciente *paciente, int tamPaciente) {
    FILE *fp = fopen(ARQ_CONSULTA, "rb+");
    Consulta aux;
    int idAlterar, achado = 0;
    int idBusca, encontrado;

    if(fp == NULL) {
        printf("\n--- erro ao abrir arquivo ---\n");
        return;
    }

    listar_todas_consultas(*consulta, tamConsulta);

    printf("\n--- Digite o ID da consulta que deseja alterar: ");
    scanf("%d", &idAlterar);
    getchar();

    while(fread(&aux, sizeof(Consulta), 1, fp) == 1) {
        if(aux.ID == idAlterar) {
            achado = 1;

            printf("\n--- ALTERANDO DADOS (ID: %d) ---\n", aux.ID);
            
            listar_todos_medicos(medico, tamMedico);
            printf("Novo ID do Medico (Atual: %d): ", aux.idMedico);
            scanf("%d", &idBusca);
            getchar();
            
            encontrado = 0;
            for(int i=0; i<tamMedico; i++) {
                if(medico[i].ID == idBusca) encontrado = 1;
            }
            if(!encontrado) {
                printf("Erro: Medico nao encontrado. Alteracao cancelada.\n");
                fclose(fp);
                return;
            }
            aux.idMedico = idBusca;

            listar_todos_pacientes(paciente, tamPaciente);
            printf("Novo ID do Paciente (Atual: %d): ", aux.idPaciente);
            scanf("%d", &idBusca);
            getchar();

            encontrado = 0;
            for(int i=0; i<tamPaciente; i++) {
                if(paciente[i].ID == idBusca) encontrado = 1;
            }
            if(!encontrado) {
                printf("Erro: Paciente nao encontrado. Alteracao cancelada.\n");
                fclose(fp);
                return;
            }
            aux.idPaciente = idBusca;

            printf("Nova Data (dd/mm/aaaa) [Atual: %s]: ", aux.data);
            fgets(aux.data, 15, stdin);
            aux.data[strcspn(aux.data, "\n")] = '\0';

            printf("Novo Horario (hh:mm) [Atual: %s]: ", aux.horario);
            fgets(aux.horario, 10, stdin);
            aux.horario[strcspn(aux.horario, "\n")] = '\0';

            printf("Nova Duracao [Atual: %s]: ", aux.duracao);
            fgets(aux.duracao, 10, stdin);
            aux.duracao[strcspn(aux.duracao, "\n")] = '\0';

            fseek(fp, -(long)sizeof(Consulta), SEEK_CUR);
            fwrite(&aux, sizeof(Consulta), 1, fp);
            break;
        }
    }

    fclose(fp);

    if(!achado) {
        printf("\n--- consulta nao encontrada ---\n");
    } else {
        free(*consulta);
        *consulta = NULL;
        carregar_consultas(consulta, &tamConsulta, idConsulta);
        printf("\n--- consulta alterada com sucesso ---\n");
    }
}

void listar_consulta_paciente(Consulta *consulta, int tamConsulta, Paciente *paciente, int tamPaciente) {
    int idBusca;
    int encontrou_paciente = 0;
    int encontrou_consulta = 0;
    char nomePaciente[55] = "Desconhecido";

    if (tamPaciente == 0) {
        printf("\n--- Nao ha pacientes cadastrados ---\n");
        return;
    }

    listar_todos_pacientes(paciente, tamPaciente);
    printf("\n--- Digite o ID do Paciente para ver o historico: ");
    scanf("%d", &idBusca);
    getchar();

    for(int i = 0; i < tamPaciente; i++) {
        if(paciente[i].ID == idBusca) {
            strcpy(nomePaciente, paciente[i].nome);
            encontrou_paciente = 1;
            break;
        }
    }

    if(!encontrou_paciente) {
        printf("\n--- Paciente nao encontrado ---\n");
        return;
    }

    printf("\n--- Consultas de: %s (ID: %d) ---\n", nomePaciente, idBusca);
    printf("%-5s | %-12s | %-8s | %-10s | %-10s\n", "ID", "Data", "Hora", "Duracao", "ID Medico");
    printf("-----------------------------------------------------------\n");


    for(int i = 0; i < tamConsulta; i++) {
        if(consulta[i].idPaciente == idBusca) {
            printf("%-5d | %-12s | %-8s | %-10s | %-10d\n", 
                consulta[i].ID, consulta[i].data, consulta[i].horario, consulta[i].duracao, consulta[i].idMedico);
            encontrou_consulta = 1;
        }
    }

    if(!encontrou_consulta) {
        printf("\n--- Nenhuma consulta encontrada para este paciente ---\n");
    }
}

void listar_consulta_medico(Consulta *consulta, int tamConsulta, Medico *medico, int tamMedico) {
    int idBusca;
    int encontrou_medico = 0;
    int encontrou_consulta = 0;
    char nomeMedico[55] = "Desconhecido";

    if (tamMedico == 0) {
        printf("\n--- Nao ha medicos cadastrados ---\n");
        return;
    }

    listar_todos_medicos(medico, tamMedico);
    printf("\n--- Digite o ID do Medico para ver a agenda: ");
    scanf("%d", &idBusca);
    getchar();


    for(int i = 0; i < tamMedico; i++) {
        if(medico[i].ID == idBusca) {
            strcpy(nomeMedico, medico[i].nome);
            encontrou_medico = 1;
            break;
        }
    }

    if(!encontrou_medico) {
        printf("\n--- Medico nao encontrado ---\n");
        return;
    }

    printf("\n--- Agenda do Dr(a). %s (ID: %d) ---\n", nomeMedico, idBusca);
    printf("%-5s | %-12s | %-8s | %-10s | %-10s\n", "ID", "Data", "Hora", "Duracao", "ID Paciente");
    printf("------------------------------------------------------------\n");


    for(int i = 0; i < tamConsulta; i++) {
        if(consulta[i].idMedico == idBusca) {
            printf("%-5d | %-12s | %-8s | %-10s | %-10d\n", 
                consulta[i].ID, consulta[i].data, consulta[i].horario, consulta[i].duracao, consulta[i].idPaciente);
            encontrou_consulta = 1;
        }
    }

    if(!encontrou_consulta) {
        printf("\n--- Nenhuma consulta agendada para este medico ---\n");
    }
}

void listar_paciente_especialidade(Consulta *consulta, int tamConsulta, Medico *medico, int tamMedico, Paciente *paciente, int tamPaciente) {
    char especialidadeBusca[55];
    int encontrou = 0;

    printf("\n--- Digite a especialidade (ex: Cardiologia): ");
    fgets(especialidadeBusca, 55, stdin);
    especialidadeBusca[strcspn(especialidadeBusca, "\n")] = '\0';

    printf("\n--- Pacientes que consultaram com [%s] ---\n", especialidadeBusca);
    printf("%-5s | %-20s | %-15s | %-12s\n", "ID", "Nome Paciente", "Medico", "Data Cons.");
    printf("--------------------------------------------------------------\n");

    for(int i = 0; i < tamConsulta; i++) {
        
        for(int m = 0; m < tamMedico; m++) {
            if(consulta[i].idMedico == medico[m].ID) {
                
                if(strcmp(medico[m].especialidade, especialidadeBusca) == 0) {
                    

                    for(int p = 0; p < tamPaciente; p++) {
                        if(consulta[i].idPaciente == paciente[p].ID) {
                            printf("%-5d | %-20s | %-15s | %-12s\n", 
                                paciente[p].ID, paciente[p].nome, medico[m].nome, consulta[i].data);
                            encontrou = 1;
                            break; 
                        }
                    }
                }
                break; 
            }
        }
    }

    if(!encontrou) {
        printf("\n--- Nenhum registro encontrado para essa especialidade ---\n");
    }
}