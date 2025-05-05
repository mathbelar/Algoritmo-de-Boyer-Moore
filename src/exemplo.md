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

Antes de explorarmos o algoritmo de Boyer-Moore, é interessante entender como a busca de padrões era feita antes. O método mais simples é a Busca Brute Force

??? Busca Brute Force

O algoritmo tenta comparar o padrão com todas as possíveis posições do texto, começando da primeira posição. Para cada posição, ele verifica se o padrão se encaixa, caracter por caracter.

1. O algoritmo começa pela primeira posição do texto e tenta comparar o padrão com o pedaço da frase do texto que começa naquela posição.

2. Ele compara a primeira letra do padrão com a primeira letra do pedaço da frase.

3. Se a letra for diferente, ele move uma posição à frente e tenta novamente.

4. Quando ele encontra uma correspondência exata para todas as letras do padrão, ele encontrou o padrão no texto!

::: Exemplos
**Passo a Passo da Busca:**

1. Tenta "Eu ad" – o algoritmo começa pela primeira parte do texto. Ele olha as primeiras 11 letras: "Eu adoro" (porque o padrão "programação" tem 11 letras).

    * Ele começa comparando a primeira letra do padrão "p" com a primeira letra do trecho do texto "E". Como são diferentes, ele sabe que não encontrou o padrão aqui.

    * Resultado da comparação: não bate. O algoritmo move para a próxima posição no texto.

2. Tenta "u ado" – o algoritmo agora olha a parte do texto que começa na segunda letra: "u adoro".

    * De novo, ele compara a primeira letra do padrão "p" com a primeira letra do novo trecho "u". Como são diferentes, ele sabe que também não encontrou o padrão aqui.

    * Resultado da comparação: não bate. Ele move uma posição para frente.

3. Tenta " adoro" – agora ele começa a comparar a parte do texto que começa na terceira letra: " adoro".

    * Ele compara a primeira letra do padrão "p" com a primeira letra da nova parte do texto "a". São diferentes, então ele sabe que ainda não encontrou o padrão.

    * Resultado da comparação: não bate. Ele continua movendo uma posição à frente.

O algoritmo continua repetindo esse processo: ele vai comparando o padrão com pedaços do texto, movendo-se uma posição para frente a cada vez, até chegar à parte em que o padrão de fato se encaixa.

4. Encontra o Padrão:
Depois de tentar várias vezes, ele chega a um ponto onde o trecho do texto é "programação".

Agora, ele compara o padrão "programação" com esse trecho do texto, e tudo bate perfeitamente!

Resultado Final:
O padrão "programação" foi encontrado na posição 18 do texto. Isso significa que, se você começar a contar a partir do começo do texto, a palavra "programação" começa na 18ª posição.



:::

???

!!! Aviso
Chegamos à seção crucial para compreender o coração do algoritmo de Boyer-Moore!
Aqui, exploraremos as duas heurísticas principais que tornam o algoritmo tão eficiente: a **heurística do mau caractere** e a **heurística do bom sufixo**.
!!!


Heurística do Mau Caractere 
------------------------

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
Bom, agora que você entendeu as ideias principais do algortimo, talvez tenha surgido a questão de qual usar, ja que em alguns casos, ambas podem ser aplicadas.

A resposta é simples, o que pular mais caracteres! Como a ideia do aloritmo é sempre ser otimizado e rápido, a heurística que mais pular caracteres inúteis(mismatches) será a escolhida.

Análise de Complexidade
------------------------
O algoritmo de Boyer-Moore é conhecido por ser um dos algoritmos mais rápidos para busca de padrões em textos. Isso acontece porque, diferente da abordagem de força bruta, ele é capaz de “pular” grandes trechos do texto sem precisar comparar todos os caracteres um por um. Logo, vamos analisar isso em três cenários:


??? Melhor Caso 


**Complexidade: O(n/m)**

Aqui, n é o tamanho do texto e m é o tamanho do padrão.

Isso acontece quando os caracteres do texto e do padrão são muito diferentes.

Como a comparação é feita de **trás para frente**, ele detecta rapidamente que o padrão não bate, e graças à heurística do mau caractere, consegue pular vários caracteres de uma vez.

::: Exemplo

* **Texto** = "aaaaaaaaaaaaaaaaaaaa"
* **Padrão** = "xyz" 

 O algoritmo avança rapidamente, pois nota que o ‘z’ não está em lugar nenhum.
:::
???

??? Pior Caso


**Complexidade: O(n·m)**

No pior cenário, o algoritmo pode acabar sendo tão lento quanto os métodos tradicionais, isso ocorre em situações bem específicas, onde as heurísticas não conseguem oferecer pulos vantajosos.

Pode acontecer quando o padrão tem repetições internas que atrapalham os saltos, ou quando os dados são manipulad os justamente para enganar as heurísticas.

::: Exemplo 

* **Texto** = "aaaaaaaaaa"
* **Padrão** = "aaaab" 

O algoritmo vai tentar alinhar muitas vezes até perceber que o padrão não está ali.

:::
???

??? Caso Médio (mais comum no uso real)

Complexidade esperada: Entre O(n) e O(n + m)

Graças ao pré-processamento do padrão e à eficiência das heurísticas (especialmente em padrões grandes), o algoritmo geralmente faz muito menos comparações que a força bruta.

Na prática, o Boyer-Moore costuma ser várias vezes mais rápido do que outros algoritmos, especialmente quando o alfabeto é grande (como em textos em inglês ou código-fonte) e o padrão é longo.

::: Exemplo 

* **Texto** = "Em algoritmos de busca, eficiência é tudo. O Boyer-Moore é muito bom em encontrar padrões rapidamente."

* **Padrão** = "padrões"

O algoritmo ignora partes do texto que não têm letras do final do padrão e foca onde realmente há chance de encontrar. Quando encontra algo parecido, faz a verificação completa.

::: 
???