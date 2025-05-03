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
padrao = "Digão"
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




