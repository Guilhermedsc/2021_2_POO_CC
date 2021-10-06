## Algorítmos mais importantes de FUP

![](fila.png)

## Fila dos estressados


- Na entrada de um evento de um experimento social, os participantes ganhavam uma pulseira especial que precisavam ficar utilizando.
- A pulseira informava, num pequeno visor, um número inteiro que representava o nível de stress daquele participante.
- Nenhum participante sabia o que aquele número significava.
- O número 1 significava totalmente tranquilo e ia aumentando conforme o stress do participante aumentava a´té o valor máximo de 99.
- Para fazer uma representação lógica, os números positivos representam homens e os números negativos representam mulheres em um vetor de inteiros.
- Precisamos escrever os algorítmos que identifiquem informações importantes sobre os participantes da fila.

**Exemplos:** 
- `{]` equivale a uma fila vazia.
- `{-1, -50, -99}` equivale a uma mulher totalmente tranquila, uma mulher médio estressada e uma mulher extremamente estressada.
- `{80, 70, 90, -4}` equivale a três homens estressados e uma mulher tranquila. 
---

<!--TOC_BEGIN-->
- [Algorítmos mais importantes de FUP](#algorítmos-mais-importantes-de-fup)
- [Fila dos estressados](#fila-dos-estressados)
- [Exercícios](#exercícios)
- [BLOCO I](#bloco-i)
    - [**Busca**: 4 funções](#busca-4-funções)
    - [**Melhor caso**: 4 funções](#melhor-caso-4-funções)
    - [**Contagem**: 4 funções](#contagem-4-funções)
- [BLOCO II](#bloco-ii)
    - [**Filter - Operações de Filtragem**: 4 funções](#filter---operações-de-filtragem-4-funções)
    - [**Acesso**: 5 funções](#acesso-5-funções)
    - [**Conjuntos**: 3 funções](#conjuntos-3-funções)
- [BLOCO III](#bloco-iii)
    - [**Map - Manipulação**: 3 funções](#map---manipulação-3-funções)
    - [**Proximidade**: 2 funções](#proximidade-2-funções)
    - [**Sequências**: 3 funções](#sequências-3-funções)
    - [**Grupos**: 2 funções](#grupos-2-funções)
    - [**Alteração**: 3 funções](#alteração-3-funções)
<!--TOC_END-->


## Exercícios

## BLOCO I

### **Busca**: 4 funções
- **existe**: Alguém com o valor X está na fila?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

bool existe(std::vector<int> vet, int valor) {
    for (int i = 0; i < vet.size(); i++)
        if(vet[i] == valor)
            return true;
    return false;
}

int main() {
    std::cout << existe({1, 2, 3, 4, 5}, 5) << '\n';
    std::cout << existe({1, 2, 3, 4, 5}, 0) << '\n';
}
```

- **contar**: Quantas vezes o valor X apareceu na fila?

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int contar(std::vector<int> vet, int valor) {
    int cont=0;

    for (int i = 0; i < vet.size(); i++)
        if(vet[i] == valor)
            cont++;
    return cont;
}

int main() {
    std::cout << contar({1, 2, 3, 5, 5, 4, 5}, 5) << '\n';
    std::cout << contar({1, 2, 3, 4, 5}, 0) << '\n';
}
```

- **procurar_valor**: Em que posição da fila aparece X pela primeira vez?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int procura(std::vector<int> vet, int valor) {
    for (int i = 0; i < vet.size(); i++)
        if(vet[i] == valor)
            return i;
    return -1;
}

int main() {
    std::cout << procura({1, 2, 3, 4, 5}, 5) << '\n';
    std::cout << procura({1, 2, 3, 4, 5}, 0) << '\n';
}
```

- **procurar_valor_apartir**: Dada a posição para iniciar a busca, qual a próxima posição em que aparece X?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int procura_apos(std::vector<int> vet, int valor, int posicao) {
    for (int i = posicao; i < vet.size(); i++)
        if(vet[i] == valor)
            return i;
    return -1;
}

int main() {
    int posicao=0;
    std::cin >> posicao;
    std::cout << procura_apos({1, 2, 5, 4, 5}, 5, posicao) << '\n';
    std::cout << procura_apos({1, 2, 3, 4, 5}, 0, posicao) << '\n';
}
```

### **Melhor caso**: 4 funções
- **procurar_menor**: qual o menor valor da lista?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int procura_menor(std::vector<int> vet) {
    int menor=0;

    for (int i = 0; i < vet.size(); i++)
        if(vet[i] < menor){
            menor=vet[i];
        }
    return menor;
}

int procura_maior(std::vector<int> vet) {
    int maior=0;

    for (int i = 0; i < vet.size(); i++)
        if(vet[i] > maior){
            maior=vet[i];
        }
    return maior;
}

int main() {
    std::cout << procura_menor({-1, 0, 1, 2, 5, 4, 5}) << '\n';
    std::cout << procura_maior({-1, 0, 1, 2, 5, 4, 5}) << '\n';
}
```

- **procurar_menor_pos**: qual a posição do menor valor da lista?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int procura_menor_pos(std::vector<int> vet) {
    int menor=0;

    for (int i = 0; i < vet.size(); i++){
        if(vet[i] < menor){
            menor=vet[i];
        }
    }

    for (int i = 0; i < vet.size(); i++){
        if(vet[i] == menor){
            return i;
        }
    return -1;
    }
}

int main() {
    int posicao=0;
    std::cin >> posicao;
    std::cout << procura_menor_pos({-1, 0, 1, 2, 5, 4, 5}) << '\n';
}
```

- **procurar_menor_pos_apartir**: Dada a posição para iniciar a busca, qual a posição do menor valor da lista?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int procura_menor_apos_apartir(std::vector<int> vet, int posicao) {
    int menor=0;

    for (int i = posicao; i < vet.size(); i++){
        if(vet[i] < menor){
            menor=vet[i];
        }
    }

    for (int i = 0; i < vet.size(); i++){
        if(vet[i] == menor){
            return i;
        }
    }
}

int main() {
    int posicao=0;
    std::cin >> posicao;
    std::cout << procura_menor_apos_apartir({-3, -2, -1, 0, 1, 2, -4, 5}, posicao) << '\n';
}
```

- **procurar_melhor_se**: qual a posição do HOMEM mais calmo? (menor valor maior que 0)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int procura_hcalmo(std::vector<int> vet) {
    int menor=vet[0];
    
    for (int i = 0; i < vet.size(); i++){
        if(vet[i] < menor && vet[i] > 0){
            menor=vet[i];
        }
    }

    for (int i = 0; i < vet.size(); i++){
        if(vet[i] == menor){
            return i;
        }
    }
}

int main() {
    std::cout << procura_hcalmo({30, -43, 17, -96, 13}) << '\n';
}
```


### **Contagem**: 4 funções
- **calcular_stress_medio**: qual a média de stress da fila? (abs)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

float calcular_stress_medio(std::vector<int> vet) {
    int i=0, soma=0;
    float media=0;

    for( i; i < vet.size(); i++){
        if(vet[i] < 0){
            vet[i]=std::abs(vet[i]);
        }
        soma+=vet[i];
    }
    media=(float)soma/i;
    return media;
}

int main() {
    std::cout << calcular_stress_medio({28, -44, 18, -96, 12, 24}) << '\n';

    return 0;
}
```

- **mais_homens_ou_mulheres**: Na fila existem mais homens ou mulheres?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::string mais_homens_ou_mulheres(std::vector<int> vet) {
    int contH=0, contM=0;

    for(int i=0; i < vet.size(); i++){
        if(vet[i] > 0){
            contH++;
        }else{
            contM++;
        }
    }

    if(contH > contM){
        return "Homens";
    }else {
        return "Mulheres";
    }
}

int main() {
    std::cout << mais_homens_ou_mulheres({30, -43, 17, -96, 13}) << '\n';
    std::cout << mais_homens_ou_mulheres({30, -43, -17, 96, -13}) << '\n';

    return 0;
}
```

- **qual_metade_eh_mais_estressada**: O nível de stress somado de todas as pessoas da primeira metade é maior que o nível de stress somado das pessoas da segunda metade da fila? (abs)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::string cqual_metade_eh_mais_estressada(std::vector<int> vet) {
    int soma1=0, soma2=0;
    float media1=0, media2=0;

    for( int i=0; i < 3; i++){
        if(vet[i] < 0){
            vet[i]=std::abs(vet[i]);
        }
        soma1+=vet[i];
    }
    media1=(float)soma1/3;

    for( int i=3; i < 6; i++){
        if(vet[i] < 0){
            vet[i]=std::abs(vet[i]);
        }
        soma2+=vet[i];
    }
    media2=(float)soma2/3;

    if (media1 > media2){
        return "Sim";
    }else{
        return "Nao";
    }
        
}

int main() {
    std::cout << cqual_metade_eh_mais_estressada({28, -44, 18, -96, 12, 24}) << '\n';

    return 0;
}
```

- **homens_sao_mais_estressados_que_mulheres**: a média do stress dos homens é maior que a das mulheres?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::string homens_sao_mais_estressados_que_mulheres(std::vector<int> vet) {
    int somaH=0, somaM=0, contH=0, contM=0;
    float mediaH=0, mediaM=0;

    for( int i=0; i < vet.size(); i++){
        if(vet[i] > 0){
            contH++;
            somaH+=vet[i];
        }        
    }
    for( int i=0; i < vet.size(); i++){
        if(vet[i] < 0){
            vet[i]=std::abs(vet[i]);
            contM++;
            somaM+=vet[i];
        }        
    }
    mediaH=(float)somaH/contH;
    mediaM=(float)somaM/contM;

    if (mediaH > mediaM){
        return "Sim";
    }else{
        return "Nao";
    }
}

int main() {
    std::cout << homens_sao_mais_estressados_que_mulheres({28, -44, 18, -96, 12, 24}) << '\n';

    return 0;
}
```

## BLOCO II

### **Filter - Operações de Filtragem**: 4 funções
- **clonar**: retorna um novo vetor copiando os valores do vetor de entrada
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> clonar(const std::vector<int>& vet) {
    std::vector<int> vetcopy;
    for( int i=0; i < (int) vet.size(); i++){
        vetcopy.push_back(vet[i]);
    }
    return vetcopy;
}

int main() {
    std::vector<int> vetcopy = { clonar({28, -44, 18, 96, 12, -24}) };

    for(int i=0; i < (int) vetcopy.size(); i++){
        std::cout << vetcopy[i] << " ";
    }

    return 0;
}
```

- **pegar_homens**: retorne uma lista com os homens (valores positivos)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> pegar_h(const std::vector<int>& vet) {
    std::vector<int> listah;
    for( int i=0; i < (int) vet.size(); i++){
        if(vet[i] > 0){
            listah.push_back(vet[i]);
        }
    }
    return listah;
}

int main() {
    std::vector<int> listah = { pegar_h({28, -44, 18, 96, 12, -24}) };

    for(int i=0; i < (int) listah.size(); i++){
        std::cout << listah[i] << " ";
    }

    return 0;
}
```

- **pegar_calmos**: retorne uma lista com as pessoas com stress menor que 10 (positivos menor que 10) (abs)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> pegar_calmos(std::vector<int> vet) {
    std::vector<int> vetcopy;
    for( int i=0; i < (int) vet.size(); i++){     
        if(vet[i] < 0){
            vet[i]=std::abs(vet[i]);
        }

        if(vet[i] < 10 && vet[i] > 0){         // || (vet[i] > -10 && vet[i] < -1))
            vetcopy.push_back(vet[i]);
        }
    }
    return vetcopy;
}

int main() {
    std::vector<int> vetcopy = { pegar_calmos({10, -9, 18, 7, -2, -4}) };

    for(int i=0; i < (int) vetcopy.size(); i++){
        std::cout << vetcopy[i] << " ";
    }

    return 0;
}
```

- **pegar_mulheres_calmas**: retorne uma lista com as mulheres com nível de stress menor que 10.(negativos menor que 10)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> pegar_mulheres_calmas(const std::vector<int>& vet) {
    std::vector<int> vetcopy;
    for( int i=0; i < (int) vet.size(); i++){     
        if(vet[i] > -10 && vet[i] < -1){
            vetcopy.push_back(vet[i]);
        }
    }
    return vetcopy;
}

int main() {
    std::vector<int> vetcopy = { pegar_mulheres_calmas({10, -9, 18, 7, -2, -4}) };

    for(int i=0; i < (int) vetcopy.size(); i++){
        std::cout << vetcopy[i] << " ";
    }

    return 0;
}
```

### **Acesso**: 5 funções
- **inverter_com_copia**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> inverter_com_copia(std::vector<int> vet) {
    std::vector<int> vetcopy;
    
    for(int i=0; i < (int) vet.size(); i++){     
        vetcopy.push_back(vet[i]);
    }
    std::reverse(vetcopy.begin(),vetcopy.end());
    return vetcopy;
}

int main() {
    std::vector<int> vetcopy = { inverter_com_copia({1, 2, 3, 4, 5, 6}) };

    for(int i=0; i < (int) vetcopy.size(); i++){
        std::cout << vetcopy[i] << " ";
    }

    return 0;
}
```

- **reverter_inplace**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> inverter_inplace(std::vector<int> vet) {
    std::reverse(vet.begin(),vet.end());
    return vet;
}

int main() {
    //vetcopy auxilia na impressão
    std::vector<int> vetcopy = { inverter_inplace({1, 2, 3, 4, 5, 6}) };

    for(int i=0; i < (int) vetcopy.size(); i++){
        std::cout << vetcopy[i] << " ";
    }

    return 0;
}
```

- **sortear**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

int sortear(std::vector<int> vet) {
    srand(time(NULL));
    int n;
    
    n=0+(rand()%5);

    return vet[n];
}

int main() {
    std::cout << sortear({1, 2, 3, 4, 5, 6}) << '\n';

    return 0;
}
```

- **embaralhar**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

void embaralhar(std::vector<int>& vet) {
    srand(time(NULL));
    for (int i = 0; i < vet.size(); i++){
	int r = rand() % vet.size();

	int temp = vet[i];
	vet[i] = vet[r];
	vet[r] = temp;
    }
}

int main() {
    std::vector<int> vet = {1, 2, 3, 4, 5, 6};
    embaralhar(vet);

    for(int i=0; i < (int) vet.size(); i++){
        std::cout << vet[i] << " ";
    }

    return 0;
}
```

- **ordenar** - selection sort utilizando 
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

void ordenar(std::vector<int>& vet) {
    int aux=0;

    for (int i = 0; i < vet.size(); i++){
        for (int j = i+1; j < vet.size(); j++){
            if(vet[i] > vet[j]){
                aux=vet[i];
                vet[i]=vet[j];
                vet[j]=aux;
            }
        }
	}
}

int main() {
    std::vector<int> vet = {10, 6, 7, 12, 3, 9};
    ordenar(vet);

    for(int i=0; i < (int) vet.size(); i++){
        std::cout << vet[i] << " ";
    }

    return 0;
}
```

### **Conjuntos**: 3 funções
- **exclusivos**: O fiscal permitiu a entrada de um único representante de cada valor, ou seja, uma lista dos valores que aparecem na fila sem repetição. Que conjunto foi formado?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> exclusivos(std::vector<int> vet) {
    std::vector<int> vetaux;
    
    for(int i=0; i < (int) vet.size(); i++){ 
        int cont=0;

        for(int j=0; j < (int) vet.size(); j++){    
              if(vet[i] == vet[j]){                     
                cont++;
              }
        }

        if(cont > 1){
            vet.erase(std::remove(vet.begin(), vet.end(), vet[i]), vet.end());
        }
        vetaux.push_back(vet[i]);
    }
    return vetaux;
}

int main() {
    std::vector<int> vetaux = { exclusivos({1, 3, 4, 3, -1, -3, -3}) };

    for(int i=0; i < (int) vetaux.size(); i++){
        std::cout << vetaux[i] << " ";
    }

    return 0;
}
```

- **diferentes**: Qual a lista dos diferentes níveis de stress que aparecem?
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> exclusivos(std::vector<int> vet) {
    std::vector<int> vetaux;
    
    for(int i=0; i < (int) vet.size() - 1; i++){ 
        vet[i]=std::abs(vet[i]);
    }

    for(int i=0; i < (int) vet.size() - 1; i++){ 
        for(int j=i+1; j < (int) vet.size(); j++){    
              if(vet[i] == vet[j]){                     
                vet.erase(std::remove(vet.begin(), vet.end(), vet[i]), vet.end());
              }
        }
        vetaux.push_back(vet[i]);
    }
    return vetaux;
}

int main() {
    std::vector<int> vetaux = { exclusivos({1, 3, 4, 3, -1, -3, -3}) };

    for(int i=0; i < (int) vetaux.size(); i++){
        std::cout << vetaux[i] << " ";
    }

    return 0;
}
```

- **abandonados**: quais pessoas ficaram na fila após remover um exemplar de cada valor?
```cpp
//{1, 3, 4, 3, -1, -2, -2} -> {3, -2}
vector<int> abandonados(const vector<int>& v);
```

## BLOCO III

### **Map - Manipulação**: 3 funções
- **sozinhos**: Quais PESSOAS eram as únicas representantes do seu nível de stress na fila? (abs)
```cpp
//{1, 3, 4, 3, -1, -3, -3} -> {4}
vector<int> sozinhos(const vector<int>& v);
```

{1, 3, 4, 3, -1, -2, -2} -> {3, -2}
- **mais_ocorrencias**: Qual a maior quantidade de ocorrências do mesmo nível de stress. (abs)
    - ```{1, 3, 4, 5, -1, -5, -5} -> 3```
- **mais_recorrentes**: Quais os níveis de stress mais recorrentes. (abs)
    - ```{1, 3, 4, 5, -1, -5, -5, 3, -3} -> {5, 3}```

### **Proximidade**: 2 funções
- **briga**: Quando alguém super estressado(>50) está ao lado de duas pessoas muito estressadas(>30) pode dar briga. Quantas vezes essa situação acontece?
- **apaziguado**: Se alguém hiper estressado(>80) estiver ao lado de pelo menos uma pessoa bem tranquila (<10) ela vai ser apaziguada. Em que posições estão esses que serão apaziguados?


### **Sequências**: 3 funções
- **quantos_times**: Duas ou mais pessoas do mesmo sexo seguidas podem formar um time. Quantos times existem na fila?
- **maior_time**: Qual o maior time que apareceu na fila?
- **sozinhos**: Quantas pessoas não estavam em um time?

### **Grupos**: 2 funções
- **casais**: Casais são formados quando quando um homem e uma mulher com o mesmo nível de stress são formados. O 3 e o -3 formam um casal. Os participantes fossem orientados a sair da fila e procurar seu par. Quantos casais poderiam ser formados?
- **trios**: Pedimos pros participantes se organizassem em trios. Todos os 3 deveriam estar com o mesmo nível de stress.Quantos trios podem ser formados?

### **Alteração**: 3 funções
- **remove**: Dado a pessoa X, como fica a fila após remover X?
- **insert**: Como fica a fila se eu inserir a pessoa X na posição Y.
- **dance**: O coordenador disse: se você está do lado de alguém da com o mesmo nível de stress que você, saia da fila com ele. Quando os pares saiam, as vezes se formavam novos pares que também saíam. Quem ficou na fila?

