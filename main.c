#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "merge_sort.h"
#include "heap_sort.h"
#include "quick_sort.h"

#define EXECUCOES 3

typedef struct
{
    double tempos[EXECUCOES];
    double media;
    double desvioPadrao;
    long long movimentacoes;
} Resultado;

void gerarVetorAleatorio(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = rand();
    }
}

void copiarVetor(int origem[], int destino[], int tamanho)
{
    memcpy(destino, origem, tamanho * sizeof(int));
}

double calcularMedia(double valores[], int n)
{
    double soma = 0.0;

    for (int i = 0; i < n; i++)
        soma += valores[i];

    return soma / n;
}

double calcularDesvioPadrao(double valores[], int n, double media)
{
    double soma = 0.0;

    for (int i = 0; i < n; i++)
    {
        soma += pow(valores[i] - media, 2);
    }

    return sqrt(soma / n);
}

void executarMergeSort(
    int vetorOriginal[],
    int tamanho,
    Resultado *resultado)
{
    int *vetor = (int *)malloc(tamanho * sizeof(int));

    resultado->movimentacoes = 0;

    for (int exec = 0; exec < EXECUCOES; exec++)
    {
        copiarVetor(vetorOriginal, vetor, tamanho);

        long long movs = 0;

        clock_t inicio = clock();

        mergeSort(vetor, 0, tamanho - 1, &movs);

        clock_t fim = clock();

        resultado->tempos[exec] =
            ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        resultado->movimentacoes = movs;
    }

    resultado->media =
        calcularMedia(resultado->tempos, EXECUCOES);

    resultado->desvioPadrao =
        calcularDesvioPadrao(
            resultado->tempos,
            EXECUCOES,
            resultado->media);

    free(vetor);
}

void executarHeapSort(
    int vetorOriginal[],
    int tamanho,
    Resultado *resultado)
{
    int *vetor = (int *)malloc(tamanho * sizeof(int));

    resultado->movimentacoes = 0;

    for (int exec = 0; exec < EXECUCOES; exec++)
    {
        copiarVetor(vetorOriginal, vetor, tamanho);

        long long movs = 0;

        clock_t inicio = clock();

        heapSort(vetor, tamanho, &movs);

        clock_t fim = clock();

        resultado->tempos[exec] =
            ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        resultado->movimentacoes = movs;
    }

    resultado->media =
        calcularMedia(resultado->tempos, EXECUCOES);

    resultado->desvioPadrao =
        calcularDesvioPadrao(
            resultado->tempos,
            EXECUCOES,
            resultado->media);

    free(vetor);
}

void executarQuickSort(
    int vetorOriginal[],
    int tamanho,
    Resultado *resultado)
{
    int *vetor = (int *)malloc(tamanho * sizeof(int));

    resultado->movimentacoes = 0;

    for (int exec = 0; exec < EXECUCOES; exec++)
    {
        copiarVetor(vetorOriginal, vetor, tamanho);

        long long movs = 0;

        clock_t inicio = clock();

        quickSort(vetor, 0, tamanho - 1, &movs);

        clock_t fim = clock();

        resultado->tempos[exec] =
            ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        resultado->movimentacoes = movs;
    }

    resultado->media =
        calcularMedia(resultado->tempos, EXECUCOES);

    resultado->desvioPadrao =
        calcularDesvioPadrao(
            resultado->tempos,
            EXECUCOES,
            resultado->media);

    free(vetor);
}

void salvarResultadoDetalhado(
    FILE *arquivo,
    const char *algoritmo,
    int tamanho,
    Resultado resultado)
{
    for (int i = 0; i < EXECUCOES; i++)
    {
        fprintf(
            arquivo,
            "%s,%d,%d,%.6f,%lld\n",
            algoritmo,
            tamanho,
            i + 1,
            resultado.tempos[i],
            resultado.movimentacoes);
    }
}

void salvarResumo(
    FILE *arquivo,
    const char *algoritmo,
    int tamanho,
    Resultado resultado)
{
    fprintf(
        arquivo,
        "%s,%d,%.6f,%.6f,%lld\n",
        algoritmo,
        tamanho,
        resultado.media,
        resultado.desvioPadrao,
        resultado.movimentacoes);
}

int main()
{
    srand(time(NULL));

    int tamanhos[] = {1000, 10000, 100000};

    FILE *detalhado =
        fopen("resultados_execucoes.csv", "w");

    FILE *resumo =
        fopen("resultados_resumo.csv", "w");

    fprintf(
        detalhado,
        "Algoritmo,Tamanho,Execucao,Tempo,Movimentacoes\n");

    fprintf(
        resumo,
        "Algoritmo,Tamanho,Media,DesvioPadrao,Movimentacoes\n");

    for (int t = 0; t < 3; t++)
    {
        int tamanho = tamanhos[t];

        printf("\n=====================================\n");
        printf("Tamanho: %d\n", tamanho);
        printf("=====================================\n");

        int *vetorOriginal =
            (int *)malloc(tamanho * sizeof(int));

        gerarVetorAleatorio(vetorOriginal, tamanho);

        Resultado mergeResultado;
        Resultado heapResultado;
        Resultado quickResultado;

        printf("Executando Merge Sort...\n");
        executarMergeSort(
            vetorOriginal,
            tamanho,
            &mergeResultado);

        printf("Executando Heap Sort...\n");
        executarHeapSort(
            vetorOriginal,
            tamanho,
            &heapResultado);

        printf("Executando Quick Sort...\n");
        executarQuickSort(
            vetorOriginal,
            tamanho,
            &quickResultado);

        salvarResultadoDetalhado(
            detalhado,
            "MergeSort",
            tamanho,
            mergeResultado);

        salvarResultadoDetalhado(
            detalhado,
            "HeapSort",
            tamanho,
            heapResultado);

        salvarResultadoDetalhado(
            detalhado,
            "QuickSort",
            tamanho,
            quickResultado);

        salvarResumo(
            resumo,
            "MergeSort",
            tamanho,
            mergeResultado);

        salvarResumo(
            resumo,
            "HeapSort",
            tamanho,
            heapResultado);

        salvarResumo(
            resumo,
            "QuickSort",
            tamanho,
            quickResultado);

        printf("\nResultados (%d elementos)\n", tamanho);

        printf(
            "Merge Sort -> Media: %.6f s | Desvio: %.6f | Movs: %lld\n",
            mergeResultado.media,
            mergeResultado.desvioPadrao,
            mergeResultado.movimentacoes);

        printf(
            "Heap Sort  -> Media: %.6f s | Desvio: %.6f | Movs: %lld\n",
            heapResultado.media,
            heapResultado.desvioPadrao,
            heapResultado.movimentacoes);

        printf(
            "Quick Sort -> Media: %.6f s | Desvio: %.6f | Movs: %lld\n",
            quickResultado.media,
            quickResultado.desvioPadrao,
            quickResultado.movimentacoes);

        free(vetorOriginal);
    }

    fclose(detalhado);
    fclose(resumo);

    printf("\nArquivos gerados:\n");
    printf(" - resultados_execucoes.csv\n");
    printf(" - resultados_resumo.csv\n");

    return 0;
}