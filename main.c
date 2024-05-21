#include <stdio.h>
#include <stdlib.h>

// Guilherme de Abreu Guimarães
// 22.222.028-7

// Estrutura que representa um Aluno.
typedef struct {
  int matricula;  // Matrícula do aluno.
  char nome[50];  // Nome do aluno.
  float notas[2]; // Notas do aluno nas duas provas.
  float media;    // Média das notas do aluno.
} Aluno;




// Estrutura que representa um Professor.
typedef struct {
  int id;        // Identificador do professor.
  char nome[50]; // Nome do professor.
} Professor;




// Estrutura que representa uma Disciplina.
typedef struct {
  char codigo[10];      // Código da disciplina.
  char nome[50];        // Nome da disciplina.
  int pesos[2];         // Pesos das notas das provas.
  float mediaAprovacao; // Média necessária para aprovação na disciplina.
} Disciplina;




// Estrutura que representa uma Turma.
typedef struct {
  int id;                // Identificador da turma.
  Professor professor;   // Professor responsável pela turma.
  Disciplina disciplina; // Disciplina lecionada na turma.
  Aluno alunos[10]; // Array de alunos inscritos na turma (máximo de 10 alunos).
  int numAlunos;    // Número de alunos na turma.
} Turma;




// Função para escrever dados de um aluno em um arquivo.
void escreverAluno(Aluno aluno, FILE *fp) {
  fwrite(&aluno, sizeof(Aluno), 1,
         fp); // Escreve a estrutura Aluno no arquivo apontado por fp.
}




// Função para ler dados de um aluno de um arquivo.
Aluno lerAluno(FILE *fp) {
  Aluno aluno;
  fread(&aluno, sizeof(Aluno), 1,
        fp);    // Lê a estrutura Aluno do arquivo apontado por fp.
  return aluno; // Retorna a estrutura Aluno lida.
}




// Função para escrever dados de um professor em um arquivo.
void escreverProfessor(Professor professor, FILE *fp) {
  fwrite(&professor, sizeof(Professor), 1,
         fp); // Escreve a estrutura Professor no arquivo apontado por fp.
}




// Função para ler dados de um professor de um arquivo.
Professor lerProfessor(FILE *fp) {
  Professor professor;
  fread(&professor, sizeof(Professor), 1,
        fp);        // Lê a estrutura Professor do arquivo apontado por fp.
  return professor; // Retorna a estrutura Professor lida.
}




// Função para escrever dados de uma disciplina em um arquivo.
void escreverDisciplina(Disciplina disciplina, FILE *fp) {
  fwrite(&disciplina, sizeof(Disciplina), 1,
         fp); // Escreve a estrutura Disciplina no arquivo apontado por fp.
}




// Função para ler dados de uma disciplina de um arquivo.
Disciplina lerDisciplina(FILE *fp) {
  Disciplina disciplina;
  fread(&disciplina, sizeof(Disciplina), 1,
        fp);         // Lê a estrutura Disciplina do arquivo apontado por fp.
  return disciplina; // Retorna a estrutura Disciplina lida.
}




// Função para escrever dados de uma turma em um arquivo.
void escreverTurma(Turma turma, FILE *fp) {
  fwrite(&turma, sizeof(Turma), 1,
         fp); // Escreve a estrutura Turma no arquivo apontado por fp.
}




// Função para ler dados de uma turma de um arquivo.
Turma lerTurma(FILE *fp) {
  Turma turma;
  fread(&turma, sizeof(Turma), 1,
        fp);    // Lê a estrutura Turma do arquivo apontado por fp.
  return turma; // Retorna a estrutura Turma lida.
}




// Função para calcular a média de um aluno de acordo com as notas e pesos de
// uma disciplina.
float calcularMedia(Aluno aluno, Disciplina disciplina) {
  float media = 0;
  // Loop para somar o produto da nota pelo peso correspondente.
  for (int i = 0; i < 2; i++) {
    media += aluno.notas[i] * disciplina.pesos[i];
  }
  // Divide o total pela soma dos pesos para obter a média.
  media /= (disciplina.pesos[0] + disciplina.pesos[1]);
  return media; // Retorna a média calculada.
}

// Função para cadastrar um aluno no arquivo binário "alunos.bin".
void cadastrarAluno(Aluno aluno) {
  FILE *fp = fopen("alunos.bin", "ab"); // Abre o arquivo para adição ("ab").
  if (fp == NULL) { // Verifica se o arquivo foi aberto corretamente.
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
  escreverAluno(aluno, fp); // Chama a função para escrever o aluno no arquivo.
  printf("Aluno cadastrado com sucesso!\n");
  fclose(fp); // Fecha o arquivo.
}




// Função para buscar um aluno no arquivo binário "alunos.bin" pela matrícula.
Aluno buscarAluno(int matricula) {
  FILE *fp = fopen("alunos.bin", "rb"); // Abre o arquivo para leitura ("rb").
  if (fp == NULL) { // Verifica se o arquivo foi aberto corretamente.
    printf("Erro ao abrir o arquivo.\n");
    Aluno alunoVazio = {0, "", {0, 0}, 0}; // Cria um aluno vazio.
    return alunoVazio;                     // Retorna o aluno vazio.
  }
  Aluno aluno;
  // Loop para ler cada aluno no arquivo.
  while (fread(&aluno, sizeof(Aluno), 1, fp)) {
    if (aluno.matricula == matricula) { // Verifica se a matrícula do aluno é a
                                        // matrícula procurada.
      fclose(fp);   // Fecha o arquivo.
      return aluno; // Retorna o aluno encontrado.
    }
  }
  fclose(fp);                            // Fecha o arquivo.
  Aluno alunoVazio = {0, "", {0, 0}, 0}; // Cria um aluno vazio.
  return alunoVazio; // Retorna o aluno vazio se o aluno procurado não foi
                     // encontrado.
}




// Função para gerar um relatório de uma turma e salvar em um arquivo CSV.
char *nomeArquivo = "dados.csv";
void gerarRelatorio(Turma turma, char *nomeArquivo) {
  FILE *fp = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita.
  if (fp == NULL) { // Verifica se o arquivo foi aberto corretamente.
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  // Escreve a informação da disciplina no arquivo.
  fprintf(fp, "Disciplina: %s, %s, Pesos: %d, %d, Média para aprovação: %.2f\n",
          turma.disciplina.codigo, turma.disciplina.nome,
          turma.disciplina.pesos[0], turma.disciplina.pesos[1],
          turma.disciplina.mediaAprovacao);

  // Escreve a informação do professor no arquivo.
  fprintf(fp, "Professor: %d, %s\n", turma.professor.id, turma.professor.nome);

  // Loop para escrever a informação de cada aluno no arquivo.
  for (int i = 0; i < turma.numAlunos; i++) {
    Aluno aluno = turma.alunos[i];
    fprintf(fp, "Aluno: %d, %s, Notas: %.2f, %.2f, Média: %.2f\n",
            aluno.matricula, aluno.nome, aluno.notas[0], aluno.notas[1],
            aluno.media);
  }

  fclose(fp); // Fecha o arquivo.
}




// Função para alterar as informações de um aluno no arquivo binário
// "alunos.bin".
void alterarAluno(int matricula, Aluno novoAluno) {
  FILE *fp =
      fopen("alunos.bin", "r+b"); // Abre o arquivo para leitura e escrita.
  if (fp == NULL) { // Verifica se o arquivo foi aberto corretamente.
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
  Aluno aluno;
  // Loop para ler cada aluno no arquivo.
  while (fread(&aluno, sizeof(Aluno), 1, fp)) {
    if (aluno.matricula == matricula) { // Verifica se a matrícula do aluno é a
                                        // matrícula procurada.
      fseek(fp, -sizeof(Aluno),
            SEEK_CUR); // Move o cursor para o início das informações do aluno.
      fwrite(&novoAluno, sizeof(Aluno), 1,
             fp); // Sobrescreve as informações do aluno.
      printf("Aluno alterado com sucesso!\n");
      fclose(fp); // Fecha o arquivo.
      return;
    }
  }
  fclose(fp);                        // Fecha o arquivo.
  printf("Aluno não encontrado.\n"); // Exibe uma mensagem se o aluno não foi
                                     // encontrado.
}




// Função para excluir um aluno do arquivo binário "alunos.bin".
void excluirAluno(int matricula) {
  FILE *fp = fopen("alunos.bin", "rb"); // Abre o arquivo para leitura.
  FILE *fpTemp =
      fopen("temp.bin", "wb"); // Abre um arquivo temporário para escrita.

  // Verifica se os arquivos foram abertos corretamente.
  if (fp == NULL || fpTemp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
  Aluno aluno;
  int alunoExcluido = 0; // Variável de controle para confirmar a exclusão.

  // Loop para ler cada aluno no arquivo.
  while (fread(&aluno, sizeof(Aluno), 1, fp)) {
    // Se a matrícula do aluno for diferente da matrícula procurada, escreve o
    // aluno no arquivo temporário.
    if (aluno.matricula != matricula) {
      fwrite(&aluno, sizeof(Aluno), 1, fpTemp);
    } else {
      alunoExcluido = 1; // Marca que o aluno foi encontrado e removido.
    }
  }

  // Fecha os arquivos.
  fclose(fp);
  fclose(fpTemp);

  // Remove o arquivo original e renomeia o arquivo temporário para o nome do
  // arquivo original.
  remove("alunos.bin");
  rename("temp.bin", "alunos.bin");

  // Confirmação de exclusão.
  if (alunoExcluido) {
    printf("Aluno excluído com sucesso!\n");
  } else {
    printf("Aluno não encontrado.\n");
  }
}




// Função para cadastrar um professor no arquivo binário "professores.bin".
void cadastrarProfessor(Professor professor) {
  FILE *fp = fopen("professores.bin", "ab"); // Abre o arquivo para escrita.

  // Verifica se o arquivo foi aberto corretamente.
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  escreverProfessor(professor,
                    fp); // Escreve as informações do professor no arquivo.
  printf("Professor cadastrado com sucesso!\n");
  fclose(fp); // Fecha o arquivo.
}




// Função para buscar um professor no arquivo binário "professores.bin".
Professor buscarProfessor(int id) {
  FILE *fp = fopen("professores.bin", "rb"); // Abre o arquivo para leitura.

  // Verifica se o arquivo foi aberto corretamente.
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    Professor professorVazio = {0, ""};
    return professorVazio; // Retorna um professor vazio se o arquivo não pôde
                           // ser aberto.
  }
  Professor professor;

  // Loop para ler cada professor no arquivo.
  while (fread(&professor, sizeof(Professor), 1, fp)) {
    // Se o ID do professor for igual ao ID procurado, retorna o professor.
    if (professor.id == id) {
      fclose(fp);
      return professor;
    }
  }

  fclose(fp); // Fecha o arquivo.
  Professor professorVazio = {0, ""};
  return professorVazio; // Retorna um professor vazio se o professor não foi
                         // encontrado.
}




// Função para alterar as informações de um professor no arquivo binário
// "professores.bin".
void alterarProfessor(int id, Professor novoProfessor) {
  FILE *fp =
      fopen("professores.bin", "r+b"); // Abre o arquivo para leitura e escrita.

  // Verifica se o arquivo foi aberto corretamente.
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  Professor professor;

  // Loop para ler cada professor no arquivo.
  while (fread(&professor, sizeof(Professor), 1, fp)) {
    // Se o ID do professor for igual ao ID procurado, substitui as informações
    // do professor pelas novas informações.
    if (professor.id == id) {
      fseek(fp, -sizeof(Professor),
            SEEK_CUR); // Move o ponteiro do arquivo para o início do professor
                       // atual.
      fwrite(&novoProfessor, sizeof(Professor), 1,
             fp); // Escreve as novas informações do professor.
      printf("Professor alterado com sucesso!\n");
      fclose(fp); // Fecha o arquivo.
      return;
    }
  }

  fclose(fp); // Fecha o arquivo se o professor não foi encontrado.
  printf("Professor não encontrado.\n"); // Imprime uma mensagem de erro.
}




// Função para excluir um professor do arquivo binário "professores.bin".
void excluirProfessor(int id) {
  FILE *fp = fopen("professores.bin", "rb"); // Abre o arquivo para leitura.
  FILE *fpTemp =
      fopen("temp.bin", "wb"); // Abre um arquivo temporário para escrita.

  // Verifica se os arquivos foram abertos corretamente.
  if (fp == NULL || fpTemp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  Professor professor;
  int professorExcluido = 0; // Variável de controle para confirmar a exclusão.

  // Loop para ler cada professor no arquivo.
  while (fread(&professor, sizeof(Professor), 1, fp)) {
    // Se o ID do professor for diferente do ID procurado, escreve o professor
    // no arquivo temporário.
    if (professor.id != id) {
      fwrite(&professor, sizeof(Professor), 1, fpTemp);
    } else {
      professorExcluido = 1; // Marca que o professor foi encontrado e removido.
    }
  }

  // Fecha os arquivos.
  fclose(fp);
  fclose(fpTemp);

  // Remove o arquivo original e renomeia o arquivo temporário para o nome do
  // arquivo original.
  remove("professores.bin");
  rename("temp.bin", "professores.bin");

  // Confirmação de exclusão.
  if (professorExcluido) {
    printf("Professor excluído com sucesso!\n");
  } else {
    printf("Professor não encontrado.\n");
  }
}




// Função para cadastrar uma nova disciplina no arquivo binário
// "disciplinas.bin".
void cadastrarDisciplina(Disciplina disciplina) {
  FILE *fp = fopen("disciplinas.bin",
                   "ab"); // Abre o arquivo para adicionar informações ao final.

  // Verifica se o arquivo foi aberto corretamente.
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  escreverDisciplina(disciplina,
                     fp); // Chama a função 'escreverDisciplina' para escrever a
                          // nova disciplina no arquivo.
  printf("Disciplina cadastrada com sucesso!\n");
  fclose(fp); // Fecha o arquivo.
}




// Função para buscar uma disciplina pelo Código no arquivo binário
// "disciplinas.bin".
Disciplina buscarDisciplina(char *codigo) {
  FILE *fp = fopen("disciplinas.bin", "rb"); // Abre o arquivo para leitura.

  // Verifica se o arquivo foi aberto corretamente.
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");

    // Retorna uma disciplina vazia se o arquivo não puder ser aberto.
    Disciplina disciplinaVazia = {"", "", {0, 0}, 0};
    return disciplinaVazia;
  }

  Disciplina disciplina;

  // Loop para ler cada disciplina no arquivo.
  while (fread(&disciplina, sizeof(Disciplina), 1, fp)) {
    // Se o código da disciplina for igual ao código procurado, fecha o arquivo
    // e retorna a disciplina.
    if (strcmp(disciplina.codigo, codigo) == 0) {
      fclose(fp);
      return disciplina;
    }
  }

  fclose(fp); // Fecha o arquivo se a disciplina não foi encontrada.

  // Retorna uma disciplina vazia se a disciplina não foi encontrada.
  Disciplina disciplinaVazia = {"", "", {0, 0}, 0};
  return disciplinaVazia;
}




// Função para alterar os dados de uma disciplina existente no arquivo binário
// "disciplinas.bin".
void alterarDisciplina(char *codigo, Disciplina novaDisciplina) {
  FILE *fp =
      fopen("disciplinas.bin", "r+b"); // Abre o arquivo para leitura e escrita.

  // Verifica se o arquivo foi aberto corretamente.
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  Disciplina disciplina;

  // Loop para ler cada disciplina no arquivo.
  while (fread(&disciplina, sizeof(Disciplina), 1, fp)) {
    // Se o código da disciplina for igual ao código procurado, modifica os
    // dados da disciplina no arquivo.
    if (strcmp(disciplina.codigo, codigo) == 0) {
      fseek(fp, -sizeof(Disciplina),
            SEEK_CUR); // Retrocede a posição de leitura/escrita no arquivo para
                       // o início da disciplina que será alterada.
      fwrite(&novaDisciplina, sizeof(Disciplina), 1,
             fp); // Escreve a nova disciplina no lugar da antiga.
      printf("Disciplina alterada com sucesso!\n");
      fclose(fp); // Fecha o arquivo.
      return;
    }
  }

  fclose(fp); // Fecha o arquivo se a disciplina não foi encontrada.

  printf("Disciplina não encontrada.\n"); // Imprime uma mensagem se a
                                          // disciplina não foi encontrada.
}




// Função para excluir uma disciplina existente no arquivo binário
// "disciplinas.bin".
void excluirDisciplina(char *codigo) {
  FILE *fp =
      fopen("disciplinas.bin", "rb"); // Abre o arquivo original para leitura.
  FILE *fpTemp =
      fopen("temp.bin", "wb"); // Abre um arquivo temporário para escrita.

  // Verifica se os arquivos foram abertos corretamente.
  if (fp == NULL || fpTemp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  Disciplina disciplina;
  int disciplinaExcluida = 0; // Variável de controle para confirmar a exclusão.

  // Loop para ler cada disciplina no arquivo original.
  while (fread(&disciplina, sizeof(Disciplina), 1, fp)) {
    // Se o código da disciplina for diferente do código procurado, escreve a
    // disciplina no arquivo temporário.
    if (strcmp(disciplina.codigo, codigo) != 0) {
      fwrite(&disciplina, sizeof(Disciplina), 1, fpTemp);
    } else {
      disciplinaExcluida =
          1; // Marca que a disciplina foi encontrada e removida.
    }
  }

  // Fecha os arquivos.
  fclose(fp);
  fclose(fpTemp);

  // Remove o arquivo original e renomeia o arquivo temporário para o nome do
  // arquivo original.
  remove("disciplinas.bin");
  rename("temp.bin", "disciplinas.bin");

  // Confirmação de exclusão.
  if (disciplinaExcluida) {
    printf("Disciplina excluída com sucesso!\n");
  } else {
    printf("Disciplina não encontrada.\n");
  }
}




// Função para cadastrar uma turma no arquivo "turmas.bin".
void cadastrarTurma(Turma turma) {

  // Abre o arquivo "turmas.bin" em modo de acréscimo binário.
  FILE *fp = fopen("turmas.bin", "ab");

  // Verifica se o arquivo foi aberto corretamente.
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n"); // Imprime uma mensagem de erro se não
                                          // foi possível abrir o arquivo.
    return; // Retorna sem fazer mais nada se não foi possível abrir o arquivo.
  }

  // Chama a função 'escreverTurma' para escrever a turma no arquivo.
  escreverTurma(turma, fp);
  printf("Turma cadastrada com sucesso!\n");
  // Fecha o arquivo.
  fclose(fp);
}




// Esta função é responsável por buscar uma turma específica no arquivo
// "turmas.bin".
Turma buscarTurma(int id) {

  // Aqui, um ponteiro para um arquivo é criado para o arquivo "turmas.bin"
  FILE *fp = fopen("turmas.bin", "rb");

  // Se o arquivo não puder ser aberto, uma mensagem de erro é impressa e a
  // função retorna.
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
  }

  // Uma variável 'turma' do tipo Turma é criada para armazenar os dados lidos
  // do arquivo.
  Turma turma;

  // Neste loop, a função fread lê do arquivo 'fp' uma quantidade de bytes igual
  // ao tamanho de uma Turma e armazena os dados na variável 'turma'. A leitura
  // é feita até que o final do arquivo seja atingido (o que faz com que fread
  // retorne um valor menor que o número de elementos a serem lidos).
  while (fread(&turma, sizeof(Turma), 1, fp)) {

    // Se o id da turma lida do arquivo for igual ao id procurado, a função
    // fecha o arquivo e retorna a turma.
    if (turma.id == id) {
      fclose(fp);
      return turma;
    }
  }

  // Após a leitura, o arquivo é fechado.
  fclose(fp);
}




// Função para alterar os dados de uma turma específica
void alterarTurma(int id, Turma novaTurma) {

  // Abre o arquivo 'turmas.bin' no modo leitura e atualização (r+b)
  FILE *fp = fopen("turmas.bin", "r+b");

  // Verifica se o arquivo foi aberto corretamente
  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n"); // Imprime uma mensagem de erro se não
                                          // foi possível abrir o arquivo
    return; // Retorna sem fazer mais nada se não foi possível abrir o arquivo
  }

  Turma turma;

  // Lê cada turma do arquivo até encontrar a turma com o id específico
  while (fread(&turma, sizeof(Turma), 1, fp)) {
    if (turma.id == id) {
      // Retrocede o ponteiro do arquivo para o início da turma que será
      // alterada
      fseek(fp, -sizeof(Turma), SEEK_CUR);
      // Escreve a nova turma no lugar da antiga
      fwrite(&novaTurma, sizeof(Turma), 1, fp);
      printf("Turma alterada com sucesso!\n");
      // Fecha o arquivo e retorna
      fclose(fp);
      return;
    }
  }

  // Se a turma não foi encontrada, fecha o arquivo e imprime uma mensagem
  fclose(fp);
  printf("Turma não encontrada.\n");
}




// Função para excluir uma turma específica
void excluirTurma(int id) {
  // Abre o arquivo 'turmas.bin' no modo leitura (rb) e cria um arquivo
  // temporário 'temp.bin' no modo escrita (wb)
  FILE *fp = fopen("turmas.bin", "rb");
  FILE *fpTemp = fopen("temp.bin", "wb");

  // Verifica se os arquivos foram abertos corretamente
  if (fp == NULL || fpTemp == NULL) {
    printf("Erro ao abrir o arquivo.\n"); // Imprime uma mensagem de erro se não
                                          // foi possível abrir os arquivos
    return; // Retorna sem fazer mais nada se não foi possível abrir os arquivos
  }

  Turma turma;
  int turmaExcluida = 0; // Variável de controle para confirmar a exclusão.

  // Lê cada turma do arquivo 'turmas.bin'
  while (fread(&turma, sizeof(Turma), 1, fp)) {
    // Escreve a turma no arquivo temporário apenas se o id não for o que deve
    // ser excluído
    if (turma.id != id) {
      fwrite(&turma, sizeof(Turma), 1, fpTemp);
    } else {
      turmaExcluida = 1; // Marca que a turma foi encontrada e removida.
    }
  }

  // Fecha os arquivos
  fclose(fp);
  fclose(fpTemp);

  // Exclui o arquivo original 'turmas.bin' e renomeia o arquivo temporário
  // 'temp.bin' para 'turmas.bin'
  remove("turmas.bin");
  rename("temp.bin", "turmas.bin");

  // Confirmação de exclusão.
  if (turmaExcluida) {
    printf("Turma excluída com sucesso!\n");
  } else {
    printf("Turma não encontrada.\n");
  }
}




// Função que imprime uma mensagem quando o usuário decide sair do programa.
void sair() { printf("\nOperação Finalizada!\n"); }




// Função para exibir um menu de ações ao usuário e coletar a opção
// escolhida.
int exibirMenu() {
  // Variável para armazenar a opção escolhida pelo usuário.
  int option;

  // Imprimindo opções de menu.
  printf("\n1. Cadastrar Aluno\n");
  printf("2. Buscar Aluno\n");
  printf("3. Alterar Aluno\n");
  printf("4. Excluir Aluno\n");
  printf("\n5. Cadastrar Professor\n");
  printf("6. Buscar Professor\n");
  printf("7. Alterar Professor\n");
  printf("8. Excluir Professor\n");
  printf("\n9.  Cadastrar Disciplina\n");
  printf("10. Buscar Disciplina\n");
  printf("11. Alterar Disciplina\n");
  printf("12. Excluir Disciplina\n");
  printf("\n13. Cadastrar Turma\n");
  printf("14. Buscar Turma\n");
  printf("15. Alterar Turma\n");
  printf("16. Excluir Turma\n");
  printf("\n17. Gerar Relatório\n");
  printf("18. Sair\n");

  // Solicitando a opção do usuário.
  printf("\nSelecione uma opção: ");
  scanf("%d", &option);

  // Retornando a opção escolhida.
  return option;
}




// Função principal do programa.
int main() {
  // Variáveis para armazenar as opções do usuário e outras informações
  // necessárias.
  int option, matricula, id;
  char codigo[10];
  Aluno novoAluno;
  Professor professor;
  Disciplina disciplina;
  Turma turma;

  // Loop principal do programa. Continua até que o usuário decida sair.
  do {
    // Exibe o menu e obtém a opção escolhida pelo usuário.
    option = exibirMenu();

    // Processa a opção escolhida pelo usuário.
    switch (option) {
    case 1: // Opção para cadastrar um novo aluno.
      // Solicita as informações do aluno ao usuário.
      printf("Digite a matricula do aluno: ");
      scanf("%d", &novoAluno.matricula);

      printf("Digite o nome do aluno: ");
      scanf("%s", novoAluno.nome);

      printf("Digite a nota 1 do aluno: ");
      scanf("%f", &novoAluno.notas[0]);

      printf("Digite a nota 2 do aluno: ");
      scanf("%f", &novoAluno.notas[1]);

      // Calcula a média das notas do aluno.
      novoAluno.media = (novoAluno.notas[0] + novoAluno.notas[1]) / 2;

      // Chama a função para cadastrar o aluno.
      cadastrarAluno(novoAluno);
      break;

    case 2: // Opção para buscar um aluno.
      // Solicita a matricula do aluno que o usuário deseja buscar.
      printf("Insira a matricula do aluno que deseja buscar: ");
      scanf("%d", &matricula);

      // Busca o aluno e armazena as informações encontradas.
      Aluno alunoEncontrado = buscarAluno(matricula);

      // Verifica se o aluno foi encontrado.
      if (alunoEncontrado.matricula != 0) {
        // Se o aluno foi encontrado, imprime suas informações.
        printf("Aluno encontrado:\nNome: %s\nMatricula: %d\nNota 1: %.2f\nNota "
               "2: %.2f\nMedia: %.2f\n",
               alunoEncontrado.nome, alunoEncontrado.matricula,
               alunoEncontrado.notas[0], alunoEncontrado.notas[1],
               alunoEncontrado.media);
      } else {
        // Se o aluno não foi encontrado, imprime uma mensagem de erro.
        printf("Aluno não encontrado.\n");
      }
      break;

    case 3: // Opção para alterar um aluno existente.
      // Solicita a matricula do aluno a ser alterado e as novas informações.
      printf("Insira a matricula do aluno a ser alterado: ");
      scanf("%d", &matricula);
      printf("Insira a nova matricula: ");
      scanf("%d", &novoAluno.matricula);
      printf("Insira o novo nome: ");
      scanf("%s", novoAluno.nome);
      printf("Insira a primeira nota: ");
      scanf("%f", &novoAluno.notas[0]);
      printf("Insira a segunda nota: ");
      scanf("%f", &novoAluno.notas[1]);

      // Calcula a nova média do aluno.
      novoAluno.media = (novoAluno.notas[0] + novoAluno.notas[1]) / 2;

      // Chama a função para alterar o aluno.
      alterarAluno(matricula, novoAluno);
      break;

    case 4: // Opção para excluir um aluno.
      // Solicita a matricula do aluno a ser excluído.
      printf("Insira a matricula do aluno a ser excluído: ");
      scanf("%d", &matricula);

      // Chama a função para excluir o aluno.
      excluirAluno(matricula);
      break;

    case 5: // Opção para cadastrar um novo professor.
      // Solicita as informações do novo professor.
      printf("Insira o ID do novo professor: ");
      scanf("%d", &professor.id);
      printf("Insira o nome do novo professor: ");
      scanf("%s", professor.nome);

      // Chama a função para cadastrar o professor.
      cadastrarProfessor(professor);
      break;

    case 6: // Opção para buscar um professor.
      // Solicita o ID do professor que deseja buscar.
      printf("Insira o ID do professor que deseja buscar: ");
      scanf("%d", &id);

      // Busca o professor e armazena as informações encontradas.
      professor = buscarProfessor(id);

      // Verifica se o professor foi encontrado.
      if (professor.id == id) { // Caso o professor exista
        // Se o professor foi encontrado, imprime suas informações.
        printf("Professor encontrado:\nNome: %s\nID: %d\n", professor.nome,
               professor.id);
      } else {
        // Se o professor não foi encontrado, imprime uma mensagem de erro.
        printf("Professor com ID %d não encontrado.\n", id);
      }
      break;

    case 7: // Opção para alterar um professor existente.
      // Solicita o ID do professor a ser alterado e as novas informações.
      printf("Insira o ID do professor que deseja alterar: ");
      scanf("%d", &id);
      printf("Insira o novo ID do professor: ");
      scanf("%d", &professor.id);
      printf("Insira o novo nome do professor: ");
      scanf("%s", professor.nome);

      // Chama a função para alterar o professor.
      alterarProfessor(id, professor);
      break;

    case 8: // Opção para excluir um professor.
      // Solicita o ID do professor a ser excluído.
      printf("Insira o ID do professor que deseja excluir: ");
      scanf("%d", &id);

      // Chama a função para excluir o professor.
      excluirProfessor(id);
      break;

    case 9: // Opção para cadastrar uma nova disciplina.
      // Solicita as informações da nova disciplina.
      printf("Insira o código da disciplina: ");
      scanf("%s", disciplina.codigo);
      printf("Insira o nome da disciplina: ");
      scanf("%s", disciplina.nome);
      printf("Insira os pesos da nota 1 e 2 da disciplina:\n*Digite cada peso separadamente e apenas inteiros*\n");
      scanf("%d %d", &disciplina.pesos[0], &disciplina.pesos[1]);
      printf("Insira a média para aprovação: ");
      scanf("%f", &disciplina.mediaAprovacao);

      // Chama a função para cadastrar a disciplina.
      cadastrarDisciplina(disciplina);
      break;

    case 10: // Opção para buscar uma disciplina.
      // Solicita o código da disciplina a ser buscada.
      printf("Insira o código da disciplina: ");
      scanf("%s", codigo);

      // Busca a disciplina e armazena as informações encontradas.
      disciplina = buscarDisciplina(codigo);

      // Verifica se a disciplina foi encontrada.
      if (strcmp(disciplina.codigo, codigo) == 0) {
        // Se a disciplina foi encontrada, imprime suas informações.
        printf("Disciplina encontrada:\nCódigo: %s\nNome: %s\nPesos: %d, "
               "%d\nMédia para aprovação: %.2f\n",
               disciplina.codigo, disciplina.nome, disciplina.pesos[0],
               disciplina.pesos[1], disciplina.mediaAprovacao);
      } else {
        // Se a disciplina não foi encontrada, imprime uma mensagem de erro.
        printf("Disciplina não encontrada.\n");
      }
      break;

    case 11: // Opção para alterar uma disciplina existente.
      // Solicita o código da disciplina a ser alterada e as novas informações.
      printf("Insira o código da disciplina a ser alterada: ");
      scanf("%s", codigo);
      printf("Insira o novo código da disciplina: ");
      scanf("%s", disciplina.codigo);
      printf("Insira o novo nome da disciplina: ");
      scanf("%s", disciplina.nome);
      printf("Insira os novos pesos da nota 1 e 2 da disciplina:\n*Digite cada peso separadamente e apenas inteiros*\n");
      scanf("%d %d", &disciplina.pesos[0], &disciplina.pesos[1]);
      printf("Insira a nova média para aprovação: ");
      scanf("%f", &disciplina.mediaAprovacao);

      // Chama a função para alterar a disciplina.
      alterarDisciplina(codigo, disciplina);
      break;

    case 12: // Opção para excluir uma disciplina.
      // Solicita o código da disciplina a ser excluída.
      printf("Insira o código da disciplina a ser excluída: ");
      scanf("%s", codigo);

      // Chama a função para excluir a disciplina.
      excluirDisciplina(codigo);
      break;

    case 13: // Opção para cadastrar uma nova turma.
      // Solicita o ID da turma e do professor.
      printf("Insira o ID da turma: ");
      scanf("%d", &turma.id);

      printf("Insira o ID do professor: ");
      int idProfessor;
      scanf("%d", &idProfessor);

      // Busca o professor pelo ID e verifica se ele existe.
      turma.professor = buscarProfessor(idProfessor);
      if (turma.professor.id == 0) {
        printf("Professor não encontrado.\n");
        break;
      }

      // Solicita o código da disciplina, busca a disciplina e verifica se ela
      // existe.
      printf("Insira o código da disciplina: ");
      char codigoDisciplina[50];
      scanf("%s", codigoDisciplina);
      turma.disciplina = buscarDisciplina(codigoDisciplina);
      if (strcmp(turma.disciplina.codigo, "") == 0) {
        printf("Disciplina não encontrada.\n");
        break;
      }
      printf("Insira os pesos da nota 1 e 2 da disciplina:\n*Digite cada peso separadamente e apenas inteiros*\n");
      scanf("%d %d", &turma.disciplina.pesos[0], &turma.disciplina.pesos[1]);
      
      printf("Insira a média para aprovação na disciplina: ");
      scanf("%f", &turma.disciplina.mediaAprovacao);
      getchar();
      
      // Solicita o número de alunos e garante que seja 10 ou menos.
      printf("Insira o número de alunos: ");
      scanf("%d", &turma.numAlunos);
      while (turma.numAlunos > 10) {
        printf("O número de alunos deve ser 10 ou menos. Insira novamente: ");
        scanf("%d", &turma.numAlunos);
      }

      // Variável de controle para verificar se todos os alunos foram
      // encontrados.
      int allStudentsFound = 1;

      // Loop para solicitar a matrícula de cada aluno, buscar e validar se eles
      // existem.
      for (int i = 0; i < turma.numAlunos; i++) {
        printf("Insira a matrícula do aluno %d: ", i + 1);
        int matriculaAluno;
        scanf("%d", &matriculaAluno);
        turma.alunos[i] = buscarAluno(matriculaAluno);
        if (turma.alunos[i].matricula == 0) {
          printf("Aluno não encontrado.\n");
          allStudentsFound = 0; // Se algum aluno não for encontrado, a variável
                                // de controle é definida como 0.
          break;
        }
      }

      // Se todos os alunos foram encontrados, a turma é cadastrada.
      if (allStudentsFound) {
        cadastrarTurma(turma);
      } else {
        printf("Turma não foi cadastrada devido a erros.\n");
      }

      break;

    case 14: // Opção para buscar uma turma por seu ID.
      // Solicita o ID da turma.
      printf("Insira o ID da turma a ser buscada: ");
      scanf("%d", &id);

      // Busca a turma e verifica se ela existe.
      turma = buscarTurma(id);
      if (turma.id != 0) { // Se a turma existe, exibe suas informações.
        printf("ID da Turma: %d\n", turma.id);
        printf("ID do Professor: %d\n", turma.professor.id);
        printf("Nome do Professor: %s\n", turma.professor.nome);
        printf("Código da Disciplina: %s\n", turma.disciplina.codigo);
        printf("Nome da Disciplina: %s\n", turma.disciplina.nome);
        printf("Pesos da Disciplina: %d, %d\n", turma.disciplina.pesos[0], turma.disciplina.pesos[1]);
        printf("Média para Aprovação na Disciplina: %.2f\n", turma.disciplina.mediaAprovacao);
        printf("Número de Alunos: %d\n", turma.numAlunos);

        // Loop para exibir as informações de cada aluno na turma.
        for (int i = 0; i < turma.numAlunos; i++) {
          printf("Matricula do Aluno %d: %d\n", i + 1,
                 turma.alunos[i].matricula);
          printf("Nome do Aluno %d: %s\n", i + 1, turma.alunos[i].nome);
          printf("Notas do Aluno %d: %.2f %.2f\n", i + 1,
                 turma.alunos[i].notas[0], turma.alunos[i].notas[1]);
          printf("Média do Aluno %d: %.2f\n", i + 1, turma.alunos[i].media);
        }
      } else { // Se a turma não existe, exibe uma mensagem de erro.
        printf("Turma não encontrada.\n");
      }
      break;


    case 15: // Opção para alterar uma turma.
      // Solicita o ID da turma a ser alterada.
      printf("Insira o ID da turma que você quer alterar: ");
      scanf("%d", &id);
      getchar();
    
      Turma novaTurma;
    
      // Preenche os dados da nova turma.
      printf("Insira o novo ID da turma: ");
      scanf("%d", &novaTurma.id);
      getchar();
    
      printf("Insira o código da nova disciplina: ");
      fgets(novaTurma.disciplina.codigo, sizeof(novaTurma.disciplina.codigo),
            stdin);
      novaTurma.disciplina.codigo[strcspn(novaTurma.disciplina.codigo, "\n")] =
          0;
      printf("Insira o novo nome da disciplina: ");
      fgets(novaTurma.disciplina.nome, sizeof(novaTurma.disciplina.nome), stdin);
      novaTurma.disciplina.nome[strcspn(novaTurma.disciplina.nome, "\n")] = 0;

      printf("Insira os novos pesos da nota 1 e 2 da disciplina:\n*Digite cada peso separadamente e apenas inteiros*\n");
      scanf("%d %d", &novaTurma.disciplina.pesos[0], &novaTurma.disciplina.pesos[1]);
      
      printf("Insira a nova média para aprovação na disciplina: ");
      scanf("%f", &novaTurma.disciplina.mediaAprovacao);
      getchar();
      
      printf("Insira o ID do novo professor: ");
      scanf("%d", &novaTurma.professor.id);
      getchar();
      
      printf("Insira o novo nome do professor: ");
      fgets(novaTurma.professor.nome, sizeof(novaTurma.professor.nome), stdin);
      novaTurma.professor.nome[strcspn(novaTurma.professor.nome, "\n")] = 0;
    
      printf("Insira o novo número de alunos: ");
      scanf("%d", &novaTurma.numAlunos);
      getchar();
    
    // Loop para inserir os dados dos alunos.
    for (int i = 0; i < novaTurma.numAlunos; i++) {
      printf("Insira a nova matrícula do aluno %d: ", i + 1);
      scanf("%d", &novaTurma.alunos[i].matricula);
      getchar();
    
      printf("Insira o novo nome do aluno %d: ", i + 1);
      fgets(novaTurma.alunos[i].nome, sizeof(novaTurma.alunos[i].nome),
            stdin);
      novaTurma.alunos[i].nome[strcspn(novaTurma.alunos[i].nome, "\n")] = 0;
    
      printf("Insira a nova nota 1 do aluno %d: ", i + 1);
      scanf("%f", &novaTurma.alunos[i].notas[0]);
      getchar();
    
      printf("Insira a nova nota 2 do aluno %d: ", i + 1);
      scanf("%f", &novaTurma.alunos[i].notas[1]);
      getchar();
    
      printf("Insira a nova média do aluno %d: ", i + 1);
      scanf("%f", &novaTurma.alunos[i].media);
      getchar();
    }

      // Altera a turma com os novos dados.
      alterarTurma(id, novaTurma);
      break;
    
    case 16: // Opção para excluir uma turma.
      // Solicita o ID da turma a ser excluída.
      printf("Insira o ID da turma que você quer excluir: ");
      scanf("%d", &id);
      excluirTurma(id);
      break;
    case 17: // Opção para gerar relatório de uma turma.
      // Solicita o ID da turma para gerar o relatório.
      printf("Insira o ID da turma para gerar relatório: ");
      scanf("%d", &id);
      turma = buscarTurma(id);
      gerarRelatorio(turma, nomeArquivo);
      printf("Relatório gerado com sucesso.\n");
      break;
    case 18: // Opção para sair do programa.
      sair();
      break;
    default: // Caso a opção escolhida não seja válida.
      printf("\nOpção inválida!\n");
    }
  } while (option != 18);

  return 0;
}