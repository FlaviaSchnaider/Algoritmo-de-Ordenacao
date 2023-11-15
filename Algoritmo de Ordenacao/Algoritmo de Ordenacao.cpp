
/*
	O objetivo deste trabalho é a implementação do conjunto de algoritmos de ordenação listado a
	seguir. Nele deverá ser solicitado ao usuário o tamanho do vetor de inteiros a ser ordenado e a
	quantidade de casos desejados. Destes casos, dois devem ser o melhor e o pior caso. Os demais
	devem ser produzidos de forma aleatória. O usuário também poderá escolher a quantidade de
	vezes que cada caso deve ser executado de forma a produzir uma média de tempo de execução.
	Uma vez coletados os dados e gerados os vetores de teste, cada um dos algoritmos de ordenação
	deve ser executado por sobre os dados a quantidade de vezes determina e o tempo que ele levou
	para produzir a resposta deve ser controlado. Ao final, devem ser produzidas estatísticas que
	serão utilizadas para a produção do relatório de análise.

	Os algoritmos com seus casos de análise são os seguintes:
	a) Método quicksort com a seleção do pivô com as seguintes alternativas:
	- primeiro elemento;
	- último elemento;
	- elemento do meio;
	- mediana entre o primeiro, o último e o elemento do meio;

	b) Método do Shellsort com as seguintes particionamentos:
	- Iniciando em 4 grupos;
	- Iniciando em 6 grupos;
	- Iniciando em 8 grupos;

	Com os dados dessas execuções, cada grupo deverá produzir um relatório técnico, dentro das
	normas da ABNT, contendo a apresentação dos resultados das execuções em forma de tabela e
	gráfica para cada algoritmos bem como uma análise com embasamento técnico comparando e
	explicando as diferenças existentes nos desempenhos de um mesmo algoritmo com as diferentes
	implementações. Para essa análise devem estar presentes detalhes técnicos relativos a
	implementação que corroborem e justifiquem as conclusões estabelecidas.
	Cada um dos algoritmos implementados deve ser apresentado e detalhado no seu relatório. Ele
	também deve incluir uma comparação entre o desempenho médio das implementações do
	quicksort e shellsort para os casos: pior, melhor e médio.
	Na confecção dos testes, as escolhas deverão ser as seguintes, para ambos os casos:

	1) Tamanho do vetor: 5000, 10000 e 15000 elementos
	2) Além dos casos pior e melhor, devem ser testados, pelo menos, 30 casos médios
	3) Cada caso deve ser executado, no mínimo, 20 vezes para fazer a média dos tempos.
*/

#include <iostream>
#include <time.h>
#include <math.h>
#include <ctime>
using namespace std;


void preencherVetor(int v[], int tam, int limite = 100) {
	for (int i = 0; i < tam; i++) {
		v[i] = rand() % limite;
	}
}

void mostrarVetor(int v[], int tam) {
	for (int i = 0; i < tam; i++) {
		cout << v[i] << " ";
	}
}

int escolherPrimeiroPivo(int v[], int esq, int dir) {
	return v[esq];
}

int escolherPivoMeio(int v[], int esq, int dir) {
	int meio = (esq + dir) / 2;
	return v[meio];
}

int escolherUltimoPivo(int v[], int esq, int dir) {
	return v[dir];
}


void quicksort(int v[], int esq, int dir, int (*escolherPivo)(int[], int, int)) {
	int aux, i = esq, j = dir;
	int x = escolherPivo(v, esq, dir);

	do {
		while (x > v[i]) i++;
		while (x < v[j]) j--;
		if (i <= j) {
			aux = v[i];
			v[i] = v[j];
			v[j] = aux;
			i++;
			j--;
		}
	} while (i <= j);
	if (esq < j) quicksort(v, esq, j, escolherPivo);
	if (dir > i) quicksort(v, i, dir, escolherPivo);
}


void shell(int v[], int r, int s, int n) {
	int i, j, k, temp;
	bool achei;

	for (i = s + r; i < n; i += r) {
		j = s;
		achei = false;
		while (j < i && !achei) {
			if (v[i] < v[j]) achei = true;
			else j = j + r;
		}
		if (achei) {
			temp = v[i];
			k = i - r;
			while (k > j - r) {
				v[k + r] = v[k];
				k = k - r;
			}
			v[j] = temp;
		}
	}
}

void shellsort(int v[], int tam) {
	for (int i = 2; i >= 0; i--) {
		int inc = pow(2, i);
		for (int j = 0; j <= inc; j++) {
			shell(v, inc, j, tam);
		}
	}
}

void gerarMelhorCaso(int v[], int tam) { // vetor já ordenado
	for (int i = 0; i < tam; ++i) {
		v[i] = i;
	}
}

void gerarPiorCaso(int v[], int tam) { // vetor ordenado ao contrário
	for (int i = 0; i < tam; ++i) {
		v[i] = tam - i - 1;
	}
}

void gerarCasoMediano(int v[], int tam) { // preencher o vetor com valores aleatórios
	preencherVetor(v, tam);
}


int main()
{
	srand(time(NULL));
	const int tam = 15;
	int vetor[tam];
	int numCasos, numExecucoes;

	/*
	cout << "Digite a quantidade de casos desejados: ";
	cin >> numCasos;

	cout << "Digite a quantidade de execucoes para cada caso: ";
	cin >> numExecucoes;

	for (int caso = 0; caso < numCasos; ++caso) {
		if (caso == 0) {
			gerarMelhorCaso(vetor, tam);
		}
		else if (caso == 1) {
			gerarPiorCaso(vetor, tam);
		}
		else {
			gerarCasoMediano(vetor, tam);
		}

		// Executar e medir o tempo para o Quicksort com diferentes escolhas de pivô


		// Executar e medir o tempo para o Shellsort com diferentes particionamentos
	}
	*/
	
	preencherVetor(vetor, tam);
	cout << "Vetor Antes: ";
	mostrarVetor(vetor, tam);
	cout << endl;

	int vetorNormal[tam];
	for (int i = 0; i < tam; i++) {
		vetorNormal[i] = vetor[i];
	}

	quicksort(vetorNormal, 0, tam - 1, escolherPrimeiroPivo);

	cout << "Vetor QuickSort normal: ";
	mostrarVetor(vetorNormal, tam);
	cout << endl << endl;

	int vetorPrimeiroPivo[tam];
	int vetorMeioPivo[tam];
	int vetorUltimoPivo[tam];

	for (int i = 0; i < tam; i++) {
		vetorPrimeiroPivo[i] = vetor[i];
		vetorMeioPivo[i] = vetor[i];
		vetorUltimoPivo[i] = vetor[i];
	}

	quicksort(vetorPrimeiroPivo, 0, tam - 1, escolherPrimeiroPivo);
	quicksort(vetorMeioPivo, 0, tam - 1, escolherPivoMeio);
	quicksort(vetorUltimoPivo, 0, tam - 1, escolherUltimoPivo);

	cout << "Vetor Quicksort (Primeiro pivo): ";
	mostrarVetor(vetorPrimeiroPivo, tam);
	cout << endl << endl;

	cout << "Vetor Quicksort (Pivo do meio): ";
	mostrarVetor(vetorMeioPivo, tam);
	cout << endl << endl;

	cout << "Vetor Quicksort (Ultimo pivo): ";
	mostrarVetor(vetorUltimoPivo, tam);
	cout << endl << endl;

	preencherVetor(vetor, 15);
	cout << "Vetor Antes: ";
	mostrarVetor(vetor, 15);

	shellsort(vetor, 15);

	cout << endl << "Vetor ShellSort: ";
	mostrarVetor(vetor, 15);
	cout << endl << endl;
}
