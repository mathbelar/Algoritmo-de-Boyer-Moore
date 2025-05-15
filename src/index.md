Algoritmo de Boyer-Moore para Busca em Texto
======

Introdução
---------

Buscar padrões em textos é algo fundamental em várias áreas da computação. Em um cenário onde lidamos com enormes quantidades de dados o tempo todo, ter algoritmos rápidos e eficientes para fazer esse tipo de busca é essencial. Um dos mais conhecidos e eficazes é o algoritmo de Boyer-Moore, criado em 1977 por Robert S. Boyer e J Strother Moore. Ele se destaca por ser um dos mais rápidos para encontrar padrões em textos, principalmente quando o conjunto de caracteres é grande e o padrão a ser buscado é longo.

Neste Handout, vamos explorar como esse algoritmo funciona, por que ele é tão eficiente, e como ele consegue ser, até hoje, uma das melhores opções para buscas rápidas em grandes volumes de dados. Prepare-se para conhecer uma verdadeira obra-prima da computação.


O problema de busca de padrões
---------

Basicamente, o objetivo é encontrar um padrão de caracteres dentro de um texto maior.

Isso pode acontecer, por exemplo, quando:

* você usa **Ctrl + F** para procurar uma palavra em um documento;
* um antivírus tenta identificar trechos suspeitos em um arquivo;
* buscadores na internet procuram páginas com as palavras que você digitou.

O desafio está em fazer isso de forma rápida e eficiente, principalmente quando os textos são longos ou quando há muitos dados para analisar.

``` py 
texto = "Exemplo que o digão usou"
padrao = "digão"
print(padrao in texto)  
```

Antes de explorarmos o algoritmo de Boyer-Moore, vamos tentar fazer nosso proprio codigo de busca!


??? Exercicio 1

Faca um codigo em C que percorre um texto, busca um padrao especifico e devolve o indice desse padrao.
(Faca de maneira simples, pense como voce pode fazer loops que vao checando cada caracter)

::: Gabarito

```C
int buscar_padrao(char *texto, char *padrao) {
    int i = 0;
    int j = 0;
    int len_texto = strlen(texto);
    int len_padrao = strlen(padrao);

    for (i = 0; i <= len_texto - len_padrao; i++) {
        for (j = 0; j < len_padrao; j++) {
            if (texto[i + j] != padrao[j]) {
                break;
            }
        }
        if (j == len_padrao) {
            printf("Padrão '%s' encontrado na posição %d\n", padrao, i);
            return i;
        }
    }

    printf("Padrão '%s' não encontrado no texto.\n", padrao);
    return -1;
}
```

No codigo acima, nos apenas procuramos o primeiro caractero do nosso padrao e assim que ele eh achado, olhamos os caracteres
seguintes ate que algum deles seja diferente do padrao, caso nao seja, achamos nosso padrao.

:::

???

O codigo feito eh funcional, mas como sabemos, ser funcional nao eh a unica coisa que buscamos ao fazer um codigo, precisamos pensar em velocidade, estabilidade, entre outros aspectos. 

??? Exercicio 2
Determine a complexidade do codigo do nosso codigo

::: Gabarito (matheus belarmino esta fazendo)


* n: tamanho do texto (onde buscamos o padrão).
* m: tamanho do padrão (a substring que queremos encontrar).


:::

???


!!! Aviso
Chegamos à seção crucial para compreender o coração do algoritmo de Boyer-Moore!
Aqui, exploraremos as duas heurísticas principais que tornam o algoritmo tão eficiente: a **heurística do mau caractere** e a **heurística do bom sufixo**.
!!!


Heurística do Mau Caractere 
------------------------

Antes de explicar a heuíristica, vamos tentar melhorar nosso codigo anterior para irmos entendendo melhor de onde vem essa ideia do mau caractere.

??? Exercicio 3
Primeiro, pense o seguinte, se voce tivesse que verificar se uma palavra de um texto é igual a palavra que voce esta procurando, seria mais EFICIENTE começar do inicio da palavra ate o final, ou começar do final(esquerda para direita)?

Dica: pense qual seria o proximo passo se o caractere que voce esta checando estiver errado.

::: Gabarito
Começar pelo final é a forma mais eficiente, pois dessa forma voce consegue fazer saltos maiores e ignorar palavras inuteis. Se voce estiver porcurando uma palavra de oito letras e a ultima ja estiver errada, voce pode ignorar as outras sete letras e pular para o proximo intervalo de oito letras, enquanto que se voce estivesse procurando do comeco ao fim, o unico salto possivel seria um(para a proxima letra).

:::

???

??? Exercicio 4
Agora que voce entendeu uma forma mais eficiente de procurar uma palavra num texto, vamos melhorar nosso codigo!

Aprimore o codigo do exercicio 1 para que ele busque pela ultima letra.

::: Gabarito
Voce deve ter chegado em algo assim

```C
int buscar_padrao_otimizado(char *texto, char *padrao) {
    int len_texto = strlen(texto);
    int len_padrao = strlen(padrao);

    // Verificar se o padrão é maior que o texto
    if (len_padrao > len_texto) {
        printf("Padrão '%s' não encontrado no texto.\n", padrao);
        return -1;
    }

    int i = 0;

    while (i <= len_texto - len_padrao) {
        int j = len_padrao - 1;

        // Verificar o intervalo da direita para a esquerda
        while (j >= 0 && texto[i + j] == padrao[j]) {
            j--;
        }

        // Se j < 0, o padrão foi encontrado
        if (j < 0) {
            printf("Padrão '%s' encontrado na posição %d\n", padrao, i);
            return i;
        }

        // Pular para o próximo intervalo
        i += len_padrao;
    }

    printf("Padrão '%s' não encontrado no texto.\n", padrao);
    return -1;
}
```

Iterando dessa forma podemos fazer saltos muito maiores no nosso texto, mas devemos ter cuidado!
Nem sempre pular o intervalo inteiro da palavra é o passo certo, por isso a heurística do mal caractere nem sempre pula esse intervalo, a ideia esta mais relacionado a encaixar o padrão no texto, isso ficará mais claro nos próximos passos.
::: 

???

Essa heurística é usada quando o padrão não bate com o texto durante a comparação.
Em vez de avançar o padrão só uma posição (como na Brute Force), o Boyer-Moore tenta "pular" mais posições com base no caractere que causou o erro.

**Ou seja**

Se um caractere do texto não bate com o do padrão, o algoritmo pergunta:
“Esse caractere aparece em outro lugar do padrão?”

* Se sim, move o padrão até alinhar com essa outra ocorrência.

* Se não, pode pular o padrão todo além desse caractere.

!!! Atenção
O padrão é comparado com o texto da direita para a esquerda. Quando uma letra do texto não corresponde à letra do padrão, o algoritmo usa a **heurística do mau caractere**
!!!


??? Exemplo 1

Texto: "ABCDEF"

Padrão: "CDE"

Vamos comparar da direita pra esquerda:

```plaintext
Texto:  A B C D E F
               ↑
Padrão:     C D E
               ↑
```

1ª comparação:
Letra do texto: F
Letra do padrão: E
→ Não bate!

**Agora é aplicado a heurística:**

* O caractere que causou erro foi o F.

* O F existe dentro do padrão "CDE"?  **Não existe**.

Então, podemos mover o padrão inteiro para a direita do F, porque não faz sentido tentar comparar o padrão onde o F está.

**Resultado:** o padrão é deslocado 3 posições à frente!


???


??? Exemplo 2

Texto: "ABCABCABC"

Padrão: "CAB"


Alinhamento dos caracteres

```plaintext
Texto:    A B C A B C A B C
                      ↑
Padrão:          C A B
                      ↑
```

1ª comparação:
Letra do texto: C
Letra do padrão: B
→ Não bate!

**Caractere do erro:** C

C aparece na primeira letra do padrão.

Então, podemos mover o padrão de forma que o C do texto se alinhe com o C do padrão.

**Resultado**: padrão anda 2 posições para a direita.

???

**Qual a Vantagem?**
Em vez de comparar o padrão com cada posição do texto uma por uma, o algoritmo usa o caractere que causou a falha para decidir quantas posições pode pular com segurança. Isso permite que ele avance mais rápido no texto, economizando tempo e evitando comparações desnecessárias.

Heurística do Bom Sufixo  
------------------------

Essa é a segunda ideia principal do nosso algoritmo. Ela entra em ação quando parte do padrão **bate com o texto**, mas a comparação falha logo **antes do final**.

Em vez de descartar totalmente o que já bateu, o Boyer-Moore tenta **reaproveitar** esse pedaço que deu certo, chamado de **"bom sufixo"**.

**Ou seja**

Se uma parte do final do padrão corresponde ao texto, mas o caractere anterior causa erro, o algoritmo pergunta:
“Esse sufixo que bateu aparece em outro lugar dentro do padrão?”

* Se sim, move o padrão até alinhar esse sufixo com essa outra ocorrência.

* Se não, tenta alinhar com algum sufixo menor que também seja válido, ou então move o padrão inteiro para frente.

!!! Atenção  
A comparação ainda é feita da direita para a esquerda. Se uma parte do final do padrão bateu antes do erro, o algoritmo usa a **heurística do bom sufixo** para evitar trabalho repetido.  
!!!

??? Exemplo 1


Quando ocorre um **mismatch** após alguns caracteres do padrão terem casado com o texto, procuramos alinhar o maior sufixo casado com sua próxima ocorrência dentro do próprio padrão. Isso permite pular múltiplas posições, economizando comparações.

---


### Primeira comparação:

```plaintext
                    t---t
Texto:  C G T G C C T A C T TACTTACTTACTTACGCGAA
                  X ↑ ↑ ↑
Padrão:       C T T A C T T A C
                        X ↑ ↑ ↑
```

C bate com C, A bate com A e T bate com T.  
No entanto, há um **mismatch** na quarta comparação: **T (do padrão)** ≠ **C (do texto)**.

➡ O sufixo que casou foi `TAC`. Esse é o bom sufixo(sera chamado de pequeno t), vamos destacar ele com t tracejado, conforme o algoritmo trabalha esse "pequeno t" aumenta.

🔍 Procuramos o sufixo `TAC` dentro do padrão para encontrar sua próxima ocorrência.

```plaintext
Padrão:       C T T A C T T A C
                  ↑ ↑ ↑
```

Achamos!
Agora vamos "encaixar" esse sufixo no nosso pequeno t.

---

### Segunda comparação:

```plaintext
                     t-----------t 
Texto:   C G T G C C T A C T T A C T T A C T T A C T T A CGCGAA
                   X ↑ ↑ ↑ ↑ ↑ ↑ ↑
Padrão:          C T T A C T T A C
                   X ↑ ↑ ↑ ↑ ↑ ↑ ↑
```

Tentamos novamente. Ainda há um **mismatch** posterior.
Aqui é um pouco mais dificil de visualizar o proximo passo, ja que nosso pequeno t não se encaixaria mais no nosso padrão, mas temos temos uma solução!

A sacada aqui é que há um prefixo do padrão que se encaixa no sufixo do pequeno t.

```plaintext
                     t-----------t 
Texto:   C G T G C C T A C T T A C T T A C T T A C T T A CGCGAA
                         ↑ ↑ ↑ ↑ ↑

Padrão:          C T T A C T T A C
                 ↑ ↑ ↑ ↑ ↑ 
                 (prefixo)
```

Agora, nos resta encaixar esse prefixo com o sufixo do texto e continuar procurando.

---

### Terceira comparação:

```plaintext
Texto:   C G T G C C T A C T T A C T T A C T T A C T T A C G C G A A
                         ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑
Padrão:                  C T T A C T T A C
                         ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑
```

✅ **Todas as letras do padrão casam com o texto!**

➡ O padrão foi encontrado na posição 10 do texto.

---


???


Qual heurística usar?
------------------------
Bom, agora que você entendeu as ideias principais do algortimo, talvez tenha surgido a dúvida de qual eurística usar. 

A resposta é simples, a que pular mais caracteres! Como a ideia do algoritmo é sempre ser otimizado e rápido, a heurística que mais pular caracteres inúteis(mismatches) será a escolhida.

??? Exercicio 2

Portanto, para compreender melhor essa questão, vamos utilizar as duas eurísticas para resolver esse problema. Lembre-se que: é possível utilizá-las ao mesmo tempo,mas deve-se priorizar àquela que mais pulará mismatches!! Pegue um lápis e papel que vamos trabalhar (tente fazer, antes de ver os passos).


Por questão de simplicidade e alinhamento consideraremos texto = T e padrão = P

```plaintext        
                      ↓
T:    G T T A T A G C T G A T C G C G G C G T A G C G G C G A A
        ↓              
P:    G T A G C G G C G 
```
Como ainda não é possível/eficiente utilizar a regra do Bom Sufixo, começaremos pela regra do Mau Caractére, identifique **onde** no padrão aparece caractere T mova-o para alinhá-lo com o texto: 

::: Step 1
```plaintext                
                              ↓ 
T:    G T T A T A G C T G A T C G C G G C G T A G C G G C G A A
                    X       ↓  
P:                  G T A G C G G C G
```         

Foi possível dar um salto de 6 posições! Agora chegamos num dilema. Qual das heurísticas usar? Pense um pouco a respeito, e tente prosseguir (Escolha aquela que der o maior salto). 
::: 

::: Step 2 

```plaintext
                              ↓ t---t        
T:    G T T A T A G C T G A T C G C G G C G T A G C G G C G A A
                    X     X    
P:                        G T A G C G G C G
```     
A melhor escolha a ser feita era a heurística do Bom sufixo, tendo em vista que foi possível pular duas posições. Para melhorar o entendimento, se tivessemos optado pela heurística do Mau Caractére pulariamos apenas um caractere e ficaria assim

```plaintext
T:    G T T A T A G C T G A T C G C G G C G T A G C G G C G A A
                      X   X      
P:                        G T A G C G G C G
```   

Logo, com a escolha da heurística do **Bom Sufixo**, tente prosseguir (Dica: sempre compare o **final do padrão** ao **final do texto**).
:::
::: Step 3 
```plaintext
                                                t---------t 
T:    G T T A T A G C T G A T C G C G G C G T A G C G G C G A A
                    X     X               X
P:                                        G T A G C G G C G
```    
Novamente, a escolha mais eficiente é a do Bom Sufixo, que permitiu um salto de **7 posições**!! Agora , volte ao **Step 2** e tente aplicar a heurística do Mau Caractére:
:::

::: Gabarito 

```plaintext
                                          ↓      
T:    G T T A T A G C T G A T C G C G G C G T A G C G G C G A A
                    X     X   X           ↓
P:                            G T A G C G G C G                                
```   
Nesse caso, a regra do Mau caractere teria alinhado o Caracter "G" do texto com o "G" do padrão e teria dado um salto de apenas 2 posições.
::: 
???
Análise de Complexidade
------------------------
## Análise de Complexidade do Algoritmo de Boyer-Moore

Agora chegamos no pulo do gato! Por que usar o Algoritmo de Boyer-Moore ao invés da força bruta? Para isso, precisamos analisar a **complexidade** de cada algoritmo e entender seu desempenho em termos de **tempo** e **recursos computacionais**!

??? Melhor Caso
**Complexidade Temporal: \( O(n/m) \)**

Aqui, \( n \) é o tamanho do texto e \( m \) é o tamanho do padrão.

Isso acontece quando os caracteres do texto e do padrão são muito diferentes. Como a comparação é feita de **trás para frente**, o algoritmo detecta rapidamente que o padrão não bate, e, graças à **heurística do mau caractere**, consegue pular vários caracteres de uma vez (até \( m \) posições).

::: Exemplo
- **Texto**: `"aaaaaaaaaaaaaaaaaaaa"`
- **Padrão**: `"xyz"`

O algoritmo avança rapidamente, pois nota que o ‘z’ não está no texto, pulando \( m = 3 \) caracteres a cada iteração.
:::
???
??? Pior Caso
**Complexidade Temporal: \( O(n \cdot m) \)**

No pior cenário, o algoritmo pode ser tão lento quanto a força bruta. Isso ocorre em situações específicas, como quando o texto e o padrão têm muitas repetições, dificultando deslocamentos grandes.

::: Exemplo
- **Texto**: `"aaaaaaaaaa"`
- **Padrão**: `"aaaab"`

O algoritmo faz muitas verificações, pois os caracteres `a` aparecem frequentemente, resultando em deslocamentos pequenos (mínimo de 1).
:::
???
??? Caso Médio (Mais Comum no Uso Real)
**Complexidade Temporal Esperada: \( O(n + m) \)**

Na prática, o Boyer-Moore é muito eficiente, especialmente em textos com alfabetos grandes (como inglês ou código-fonte) e padrões longos. O pré-processamento do padrão (\( O(m) \)) e a heurística do mau caractere reduzem significativamente o número de comparações.

::: Exemplo
- **Texto**: `"Em algoritmos de busca, eficiência é tudo. O Boyer-Moore é muito bom em encontrar padrões rapidamente."`
- **Padrão**: `"padrões"`

O algoritmo ignora partes do texto que não contêm o caractere final do padrão (`s`) e faz verificações completas apenas onde há chance de correspondência.
:::

**Por que Boyer-Moore?** Comparado à força bruta (\( O(n \cdot m) \)), o Boyer-Moore é muito mais rápido no caso médio e no melhor caso, tornando-o ideal para busca de padrões em textos grandes!
???