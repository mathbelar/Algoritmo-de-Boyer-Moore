# Algoritmo de Boyer-Moore: Desvendando a Busca Rápida em Textos


## 1. Introdução: A Arte de Encontrar Agulhas em Palheiros Digitais
---------

Você já parou para pensar como o seu computador ou celular encontra uma palavra específica em um documento gigantesco em questão de segundos? Ou como um site de busca consegue vasculhar a imensidão da internet para trazer exatamente a informação que você procura? Por trás dessa "mágica", existe muita ciência da computação e algoritmos inteligentes trabalhando a todo vapor.

Buscar por padrões – sejam eles palavras, frases ou sequências específicas de caracteres – dentro de grandes volumes de texto é uma tarefa fundamental no mundo digital. Fazemos isso o tempo todo, desde o simples "Ctrl+F" (ou "Cmd+F") até operações complexas em bancos de dados, análise de DNA ou sistemas de detecção de vírus.

Imagine que você tem um livro com milhares de páginas e precisa encontrar todas as vezes que um nome específico aparece. Você poderia ler o livro do início ao fim, palavra por palavra, mas isso levaria uma eternidade, certo? Precisamos de métodos mais espertos e rápidos!

É aqui que entram os algoritmos de busca em texto. Existem várias maneiras de resolver esse problema, algumas mais simples, outras incrivelmente eficientes. Neste handout, vamos embarcar em uma jornada para conhecer um dos algoritmos mais célebres e eficientes para essa tarefa: o **Algoritmo de Boyer-Moore**.

Criado por Robert S. Boyer e J Strother Moore em 1977, esse algoritmo revolucionou a forma como realizamos buscas em texto, introduzindo ideias muito inteligentes que permitem "saltar" grandes trechos do texto, economizando um tempo precioso. Mesmo décadas depois, ele continua sendo uma referência de velocidade e eficiência.

Prepare-se para descobrir os segredos por trás dessa ferramenta poderosa. Vamos explorar, passo a passo e de forma didática, como o Boyer-Moore funciona, por que ele é tão rápido e como suas ideias podem nos inspirar a pensar de forma mais inteligente sobre como resolver problemas computacionais. Vamos começar?

## 2. O Problema da Busca em Texto: Onde Está Wally?
---------

Antes de mergulharmos nas soluções inteligentes, vamos entender bem qual é o desafio. O problema da **busca de padrões em texto** (ou *string matching*, em inglês) é bem direto:

**Dado um texto (T) e um padrão (P), queremos encontrar todas as ocorrências (ou a primeira ocorrência) do padrão P dentro do texto T.**

Parece simples, não é? Mas pense nas dimensões que isso pode tomar:

*   **Texto (T):** Pode ser qualquer sequência de caracteres. Desde uma frase curta, um parágrafo, um livro inteiro (como "Guerra e Paz"), o código genético de um organismo, o código-fonte de um programa gigante, ou até mesmo todo o conteúdo de um site.
*   **Padrão (P):** É a sequência específica que estamos procurando. Pode ser uma única letra, uma palavra ("casa"), uma frase ("ser ou não ser"), uma sequência numérica ("12345"), ou um trecho de código (`if (x > 0)`).

**Exemplos do Dia a Dia:**

*   **Ctrl+F / Cmd+F:** Quando você aperta essas teclas no seu navegador ou editor de texto para encontrar uma palavra, está resolvendo exatamente esse problema.
*   **Busca em Sites:** Motores de busca como Google ou DuckDuckGo precisam encontrar bilhões de páginas que contenham as palavras que você digitou (o padrão) dentro de um "texto" gigantesco (a internet).
*   **Editores de Código:** Programadores frequentemente buscam por nomes de variáveis, funções ou trechos específicos de código.
*   **Biologia Computacional:** Cientistas buscam por sequências específicas de genes (padrões) dentro de longas cadeias de DNA (texto).
*   **Antivírus:** Programas de segurança procuram por "assinaturas" de vírus (padrões) dentro dos arquivos do seu computador (texto).

??? Para Refletir (Atividade 1)

Pense em outras situações do seu dia a dia ou de áreas que você conhece onde a busca por padrões em texto é importante. Onde mais você acha que essa "habilidade" computacional é utilizada?

::: Gabarito

Algumas ideias:

*   **Processamento de Linguagem Natural:** Identificar nomes de pessoas, lugares ou organizações em notícias.
*   **Verificação de Plágio:** Comparar um documento com uma base de dados para encontrar trechos copiados.
*   **Análise de Logs:** Encontrar mensagens de erro específicas em arquivos de log de sistemas.
*   **Redes Sociais:** Filtrar conteúdo ou encontrar posts que mencionem um determinado termo.
*   **Música:** Identificar plágio em melodias (representadas como sequências).
*   **Edição de Vídeo:** Buscar por cenas específicas baseadas em legendas ou metadados.

Percebe como é uma tarefa onipresente?

:::

???

O grande desafio, como mencionamos, é fazer essa busca de forma **eficiente**. Se o texto for muito grande (pense em terabytes de dados) ou se precisarmos fazer muitas buscas repetidamente, um método lento pode se tornar um gargalo enorme. Precisamos de algoritmos que sejam rápidos e inteligentes!

No próximo capítulo, vamos conhecer a abordagem mais intuitiva, porém nem sempre a mais rápida, para resolver esse problema: o algoritmo de força bruta.

## 3. A Primeira Tentativa: O Algoritmo de Força Bruta (Ingênuo)
---------

Ok, já entendemos o problema. Qual seria a forma mais direta e óbvia de encontrar o padrão P dentro do texto T?

A ideia mais simples, que provavelmente ocorreria a qualquer um de nós, é a seguinte:

1.  **Alinhar:** Coloque o padrão P no início do texto T.
2.  **Comparar:** Verifique, caractere por caractere (da esquerda para a direita), se o padrão P corresponde ao trecho do texto T onde ele está alinhado.
3.  **Encontrou?** Se todos os caracteres baterem, ótimo! Encontramos uma ocorrência do padrão. Registre a posição.
4.  **Não Encontrou?** Se algum caractere não bater, pare a comparação para essa posição.
5.  **Deslizar:** Mova o padrão P **uma posição** para a direita no texto T.
6.  **Repetir:** Volte ao passo 2 e continue comparando até que o padrão P tenha deslizado por todo o texto T.

Essa abordagem é chamada de **algoritmo de força bruta** ou **algoritmo ingênuo**. Ele testa *todas* as posições possíveis do texto onde o padrão poderia começar.

??? Mão na Massa (Atividade 2)

Vamos aplicar o algoritmo de força bruta manualmente. Encontre o padrão P = "GATO" no texto T = "UMGATOSENTADONOGATO".
Mostre cada alinhamento e comparação, indicando onde falha ou se encontra o padrão.

**Texto:** U M G A T O S E N T A D O N O G A T O

**Alinhamento 1:**
```pseudocode
Texto:  U M G A T O S E N T A D O N O G A T O
        ↑
Padrão: G A T O
        ↑
```
Comparação: U != G. Falha.

**Alinhamento 2:**
```pseudocode
Texto:  U M G A T O S E N T A D O N O G A T O
          ↑
Padrão:   G A T O
          ↑
```
Comparação: M != G. Falha.

**Continue você!** Quais são os próximos passos? Onde o padrão é encontrado?

::: Gabarito

:AT2

:::

???

**Pseudocódigo Simples:**

```pseudocode
funcao busca_forca_bruta(texto T, padrao P):
  n = tamanho de T
  m = tamanho de P

  // Percorre todas as posições possíveis de início no texto
  para i de 0 até n - m:
    // Compara o padrão com o trecho do texto a partir de i
    j = 0
    enquanto j < m e T[i + j] == P[j]:
      j = j + 1
    
    // Se j chegou ao fim do padrão, encontramos!
    se j == m:
      imprimir "Padrão encontrado na posição " + i
      // Se quiser só a primeira ocorrência, pode parar aqui (retornar i)

  // Se o loop terminar sem encontrar, o padrão não está no texto
  // (Opcional: imprimir "Padrão não encontrado")
```

**Qual o Problema Dessa Abordagem?**

O algoritmo de força bruta é fácil de entender e implementar, e funciona! Mas... ele pode ser **lento**, especialmente em alguns casos.

??? Pense Rápido: O Pior Cenário (Atividade 3)

Imagine um texto formado por muitos 'A's seguidos e um padrão também com muitos 'A's, mas terminando com um 'B'. Por exemplo:

Texto T = "AAAAAAAAAAAAAAAAAB" (n=18)
Padrão P = "AAAAAB" (m=6)

Quantas comparações o algoritmo de força bruta faria *no total* para determinar que o padrão não está presente até a última posição possível?

::: Gabarito

O padrão pode ser alinhado em `n - m + 1 = 18 - 6 + 1 = 13` posições.

*   Nas primeiras 12 posições (índices 0 a 11), o padrão "AAAAAB" será comparado com "AAAAAA". Ele fará 6 comparações em cada uma, falhando na última.
*   Na 13ª posição (índice 12), o padrão "AAAAAB" será comparado com "AAAAAB". Ele fará 6 comparações e encontrará o padrão.

Se estivéssemos procurando *todas* as ocorrências, ou se o texto fosse "AAAAAAAAAAAAAAAAAA" (sem o B final), ele faria 6 comparações em cada uma das 13 posições.
Total de comparações no pior caso (sem encontrar): `(n - m + 1) * m = 13 * 6 = 78` comparações.

Isso ilustra a complexidade O(n*m). Se n e m forem grandes, o número de comparações explode!

:::

???

Essa potencial lentidão do algoritmo de força bruta nos motiva a buscar estratégias mais inteligentes. Como podemos evitar tantas comparações desnecessárias? Como podemos "saltar" pelo texto de forma mais eficiente quando encontramos uma incompatibilidade?

É exatamente isso que o algoritmo de Boyer-Moore faz, usando algumas ideias brilhantes que conheceremos a seguir!

## 4. Indo Além do Óbvio: A Busca por Saltos Inteligentes
---------

Vimos que o algoritmo de força bruta, apesar de funcional, pode gastar muito tempo verificando cada posiçãozinha do texto, mesmo quando parece óbvio que o padrão não vai encaixar ali. A grande sacada do algoritmo de Boyer-Moore é justamente pensar: **"Será que podemos usar a informação das incompatibilidades (mismatches) para dar saltos maiores e mais inteligentes pelo texto?"**

Em vez de apenas deslizar o padrão teimosamente uma posição para a direita após uma falha, o Boyer-Moore analisa *por que* a comparação falhou e usa essa informação para decidir o quão longe ele pode pular com segurança, sem correr o risco de perder uma possível ocorrência do padrão.

**A Mudança de Perspectiva: Comparando de Trás para Frente**

Uma das primeiras ideias que Boyer e Moore tiveram foi mudar a direção da comparação dentro de cada alinhamento. Enquanto a força bruta compara o padrão com o texto da esquerda para a direita, o Boyer-Moore faz o oposto: ele compara **da direita para a esquerda**, começando pelo último caractere do padrão.

```plaintext
Texto: ... C A B ...
               ↑
Padrão:    X Y Z
               ↑  <-- Começa a comparar aqui!
```

??? Por que da Direita para a Esquerda? (Atividade 4)

Pode parecer estranho no início, mas pense um pouco: imagine que você está procurando a palavra `P = "TESTE"` no texto `T = "... ABCDE ..."`. Se você comparar da direita para a esquerda, a primeira comparação é E (texto) vs E (padrão). Bateu! A segunda é D vs T. Falhou!

Agora, imagine que você comparou da esquerda para a direita. A vs T. Falhou!

Qual falha (a da direita para a esquerda ou a da esquerda para a direita) te deu mais informação útil sobre o *texto* naquele ponto?

::: Gabarito

A falha da direita para a esquerda (D vs T) te diz que o caractere D está presente no texto naquela posição. A falha da esquerda para a direita (A vs T) te diz que o caractere A está presente.

A informação sobre o caractere D (obtida comparando da direita para a esquerda) é potencialmente mais útil para o Boyer-Moore. Se D não existir no padrão "TESTE" (e não existe!), a heurística do mau caractere já pode sugerir um salto maior. Comparar da direita para a esquerda em sí não é mais rápido, mas é mais útil para o nosso algoritmo.

:::

???

**As Ferramentas Mágicas: Heurísticas**

Para decidir o tamanho desses saltos inteligentes, o Boyer-Moore utiliza duas regras principais, chamadas **heurísticas**. Uma heurística, em ciência da computação, é como uma "regra de bolso" ou um atalho inteligente que ajuda a encontrar uma boa solução rapidamente, mesmo que não seja garantido que seja a *melhor* solução *sempre* (embora, no caso do Boyer-Moore, as heurísticas sejam muito eficazes!).

As duas heurísticas do Boyer-Moore são:

1.  **Heurística do Mau Caractere (Bad Character Heuristic):** Foca no caractere do *texto* que causou a falha na comparação.
2.  **Heurística do Bom Sufixo (Good Suffix Heuristic):** Foca na parte do *padrão* que *coincidiu* com o texto antes da falha ocorrer.

!!! Atenção
Estamos entrando no coração do algoritmo! As próximas seções vão detalhar cada uma dessas heurísticas com exemplos visuais. Entendê-las bem é a chave para dominar o Boyer-Moore.
!!!

Vamos começar explorando a primeira e talvez mais intuitiva delas: a Heurística do Mau Caractere.

## 5. Heurística 1: O Dedo-Duro do Mau Caractere
---------

Vamos começar com a primeira regra inteligente do Boyer-Moore: a **Heurística do Mau Caractere**. O nome pode parecer engraçado, mas a ideia é genial!

Lembre-se que comparamos o padrão com o texto da direita para a esquerda. Quando encontramos um caractere no **texto** que *não bate* com o caractere correspondente no **padrão**, esse caractere do texto é o nosso "mau caractere". Ele é o "dedo-duro" que nos diz que o padrão não pode estar naquela posição atual.

A heurística do mau caractere usa essa informação para responder à seguinte pergunta:

**"Ok, a comparação falhou por causa desse 'mau caractere' no texto. Onde é a próxima posição *segura* para a qual podemos deslizar o padrão, levando em conta esse caractere?"**

A ideia é alinhar o padrão de forma que o "mau caractere" do texto coincida com a *última ocorrência* (mais à direita) desse mesmo caractere *dentro do padrão*. Se o mau caractere nem existir no padrão, podemos pular o padrão inteiro para depois dele!

Vamos ver isso com calma e exemplos.

**Cenário 1: O Mau Caractere NÃO Existe no Padrão**

Este é o caso mais simples e que geralmente permite os maiores saltos.

*   **Texto T:** `... U M G A T O` (Onde A é o mau caractere)
*   **Padrão P:** `...  T O` (Mismatch entre A(Texto) e T(Padrão))

Se o caractere "A' (o mau caractere do texto) **não aparece em lugar nenhum** dentro do padrão "p", então não há nenhuma chance do padrão se alinhar corretamente com o texto naquela região que inclui o "A". Podemos, com segurança, deslizar o padrão inteiro para a direita, posicionando seu início logo *após* o mau caractere "A".

??? Pratique o Salto (Atividade 5)

Considere o seguinte texto e padrão, quantos saltos serao necessarios para encontrar nosso padrão? Além disso, qual seria a diferenca de iteracoes se compararmos com o brute force visto(comece comparando D e M):

![](AT5.1.png)

::: Gabarito

:AT5

Como não existe M no padrão, podemos saltar direito para o próximo intervalo do texto.

O Brute Force anterior levaria 10 iterações para achar o primeiro match, ja utilizando nossa heurística podemos encontrar esse match em 4 pulos.


:::

???

**Cenário 2: O Mau Caractere EXISTE no Padrão**

Agora, e se o mau caractere do texto *existir* dentro do padrão?

*   **Texto T:**  `...  G C T T C T G C ...` (Onde C é o mau caractere)
*   **Padrão P:** `... C C T T T T G C` (Mismatch entre o C(texto) e T(padrão))

Neste caso, sabemos que o "C" do texto causou a falha. A heurística diz: encontre a **última ocorrência** (a mais à direita) do caractere "C" *dentro do padrão P*. Então, deslize o padrão para a direita de forma que essa última ocorrência no padrão se alinhe com o "C" do texto.

Depois, de encontrar essa última ocorrência, podemos alinha P com T e continuar comparando os caractéres. 

Por que a última ocorrência? Para garantir que não pulemos demais e percamos uma possível correspondência. Nesse caso, a última ocorrência de "C" é na segunda posição do padrão.

??? Pratique o Salto (Atividade 6)

Pensando na atividade 5 e no que você acabou de ler, como ficariam os saltos para o seguinte caso?
(Lembre-se da ideia de "alinhar" texto e padrão)

![](AT6.0.png)


::: Gabarito

:AT6

Na primeira e segunda iteração podemos pular totalmente o intervalo pois o mau caractére não aparece no padrão, porém na terceira iteração o maú caractére é o A, e ele aparece no padrão, logo podemos usar a ideia de alinhar e conseguimos encontrar a ocorrência.

:::

???

**Calculando o Salto (Pré-processamento)**

Para aplicar essa heurística rapidamente, o algoritmo Boyer-Moore primeiro faz um **pré-processamento** do padrão. Ele cria uma tabela (geralmente chamada de tabela do mau caractere ou *bad character table*) que armazena, para cada caractere possível no alfabeto, a posição da sua última ocorrência no padrão. Se um caractere não estiver no padrão, podemos armazenar -1 ou um valor que indique isso.

!!! Reforçando a Tabela
Criar essa tabela *antes* de começar a busca é crucial para a velocidade do Boyer-Moore. Ela permite descobrir o salto do mau caractere em tempo constante (O(1)) durante a fase de busca.
!!!

| Caractere | Última Posição em EXAMPLE |
| :-------- | :------------------------ |
| E         | 6                         |
| L         | 5                         |
| P         | 4                         |
| M         | 3                         |
| A         | 2                         |
| X         | 1                         |
| ... (outros) | -1                       |

Quando ocorre um mismatch com um mau caractere X do texto na posição k do texto, e o caractere do padrão na posição **j** (lembre-se, **j** diminui da direita para a esquerda), o salto é calculado como: **salto = max(1, j - ultima_posicao(X))** . Usamos **max(1, ...)** para garantir que o padrão sempre avance pelo menos uma posição.

Essa heurística sozinha já torna o Boyer-Moore muito mais rápido que a força bruta em muitos casos. Mas ainda há outra heurística poderosa que podemos usar, especialmente quando uma parte do padrão *já coincidiu* com o texto antes da falha. Vamos conhecê-la!

**Pseudocódigo**

Agora que entendemos a lógica por trás da heurística, veja como isso é traduzido em um pequeno pseudocódigo:

```pseudocode

FUNÇÃO CalcularSaltoMauCaractere(texto, padrao, pos_erro_texto, pos_erro_padrao, tabela_mau):

    caractere_ruim = texto[pos_erro_texto]
    ultima_posicao = tabela_mau.obter(caractere_ruim, -1)

    salto = pos_erro_padrao - ultima_posicao
    RETORNAR max(1, salto)

FIM_FUNÇÃO


```

## 6. Heurística 2: Aproveitando o "Bom Sufixo"
---------

A Heurística do Mau Caractere é ótima, mas e se a comparação falhar *depois* que já tivemos alguns acertos? Ou seja, começamos a comparar da direita para a esquerda, alguns caracteres bateram, mas aí... um deles falhou.

**Exemplo Rápido:**

```plaintext
Texto:  ... D E A C F E A A B C D E ...
                            ↑ ↑ ↑
Padrão:         A B C D X Y B C D
                            ↑ ↑ ↑
       (Falha!) (Match) (Match) (Match)
```

Neste caso, os caracteres **B**, **C** e **D** do padrão coincidiram com o texto. Esse trecho que deu match, **BCD**, é o que chamamos de **"Bom Sufixo"**. Seria um desperdício simplesmente ignorar essa informação e usar apenas o mau caractere (**A** do texto vs **Y** do padrão), não acha?

A **Heurística do Bom Sufixo** entra em cena justamente para aproveitar essa correspondência parcial. A ideia é:

**"Já que encontramos esse 'bom sufixo' (BCD) no texto, será que existe *outra ocorrência* desse mesmo sufixo ou de parte dele *dentro do próprio padrão*? Se sim, podemos deslizar o padrão para alinhar essa outra ocorrência com o trecho que já sabemos que bateu no texto."**

Vamos analisar os cenários possíveis:

**Cenário 1: O Bom Sufixo Aparece Novamente no Padrão**

Este é o caso ideal. Se o sufixo que deu match (t) aparece novamente *exatamente igual* em outra posição dentro do padrão (e não sobrepondo a ocorrência original), podemos deslizar o padrão para alinhar essa segunda ocorrência (a mais à direita possível que não seja a original) com o t que encontramos no texto.

??? Identifique o Bom Sufixo e o Salto (Atividade 7)

Usando a heurística do bom sufixo, quantos saltos seriam necessários para achar a occorrência do padrão no texto?

![](AT7.0.png)

::: Gabarito

:AT7

Nosso bom sufixo nesse caso é o "bcd".

:::

???


**Cenário 2: Um Prefixo do Padrão Coincide com um Sufixo do Bom Sufixo**

E se o bom sufixo inteiro não se repetir dentro do padrão? A heurística ainda tenta salvar alguma coisa!

Ela verifica se existe um **prefixo** (começo) do padrão P que seja igual a um **sufixo** (final) do bom sufixo t. Se houver vários, escolhemos o mais longo.

Talvez você precise ler essa última frase mais uma vez, ela pode parecer confusa, mas com o exemplo tudo ficará mais facil!

??? Identifique Prefixo e Sufixo (Atividade 8)

Quais serão as iterações do algoritmo(usando a heurística do bom sufixo) para achar a ocorrência do padrão no texto?

Dica: Comece resolvendo da mesma forma que fez na atividade anterior, quando chegar num ponto sem saída ou confuso, releia a frase sobre os prefixos!

![](AT8.0.png)

::: Gabarito

:AT8

Até a terceira iteração você deve ter conseguido chegar sem problemas, porém depois disso, nosso bom sufixo (t) em azul fica grande demais e claramente nao se repete dentro do padrão, é nessa hora que você deve olhar o prefixo do padrão!

Fazendo isso podemos ver que o início "CTTAC" do padrão aparece no bom sufixo(t), permitindo mais um salto.

:::

???

**Cenário 3: Nenhuma Ocorrência ou Prefixo Correspondente**

Se nem o bom sufixo inteiro se repete, nem um prefixo do padrão casa com um sufixo do bom sufixo, então não temos informação útil para reutilizar. Nesse caso, a heurística do bom sufixo sugere deslizar o padrão inteiro para a direita, passando completamente pelo local do mismatch (salto de m, tamanho do padrão).

**Calculando o Salto (Pré-processamento)**

Assim como a heurística do mau caractere, a do bom sufixo também exige um pré-processamento do padrão para calcular os possíveis saltos de antemão. Isso envolve criar tabelas (mais complexas que a do mau caractere) que armazenam, para cada possível posição de falha i no padrão, qual seria o deslocamento correto baseado nos Cenários 1, 2 e 3.

!!! Foco no Reuso
A beleza da Heurística do Bom Sufixo é tentar **reaproveitar** o trabalho já feito (a parte que deu match) para encontrar o próximo possível alinhamento.
!!!

Agora temos duas ferramentas poderosas: a Heurística do Mau Caractere e a Heurística do Bom Sufixo. Mas qual delas usar quando ambas puderem ser aplicadas? É o que veremos a seguir!

**Pseudocódigo**

Vamos ver agora como a heurística do bom sufixo é aplicada em forma de pseudocódigo simples:

```pseudocode

FUNÇÃO CalcularSaltoBomSufixo(pos_erro_padrao, tam_padrao, tabela_bom):

    indice = pos_erro_padrao + 1
    RETORNAR tabela_bom[indice]

FIM_FUNÇÃO


```

## 7. O Grande Duelo: Mau Caractere vs. Bom Sufixo
---------

Agora que conhecemos as duas heurísticas do Boyer-Moore, surge uma pergunta natural: **qual delas devemos usar quando ocorre uma falha na comparação?**

Imagine a situação:

```plaintext
Texto:  ... A D W A C D ...
                    ↑ ↑
Padrão:     C D A B C D
                    ↑ ↑
          (Falha) (Match)
```

Aqui, temos:
*   Um **mau caractere**: A (do texto, que não bateu com B do padrão).
*   Um **bom sufixo**: CD (a parte do padrão que coincidiu).

A Heurística do Mau Caractere nos daria um salto baseado na posição do W dentro do padrão ABCD.
A Heurística do Bom Sufixo nos daria um salto baseado na próxima ocorrência de CD (ou de um prefixo que case com seu sufixo) dentro de ABCD.

Qual salto escolher?

A resposta é simples e focada na eficiência: **escolha o maior salto!** Nesse caso, o bom sufixo nos permite um salto maior.

O algoritmo Boyer-Moore calcula o deslocamento sugerido por *ambas* as heurísticas e aplica aquele que mover o padrão mais para a direita. O objetivo é sempre avançar o máximo possível pelo texto com segurança, pulando o maior número de comparações desnecessárias.

**Regra de Ouro:**
salto_final = max(salto_mau_caractere, salto_bom_sufixo)

(Lembrando que o salto mínimo é sempre 1, para garantir o progresso).

??? Decida o Salto (Atividade 9)

Um desafio simples para ver se você entendeu, qual heurística garante mais saltos no exemplo abaixo?
(Pense apenas na primeira iteração!)

![](AT9.0.png)

::: Gabarito

Bom Sufixo = "AB", esse sufixo se repete no padrão, e nos permite fazer 2 saltos, mas essa é a melhor opção? 

Mau Caractere = "F", esse caractere aparece denovo no padrão, e ele nos permite fazer 3 saltos, sendo a melhor opção!

:::

???

Dominar a aplicação combinada dessas duas heurísticas é o segredo para entender a eficiência do Boyer-Moore.

**Pseudocódigo final**

Agora que entendemos como combinar as duas heurísticas, veja como isso aparece no pseudocódigo completo do algoritmo Boyer-Moore:

```pseudocode

FUNÇÃO BoyerMooreBuscaCombinada(texto, padrao):

    n = comprimento(texto)
    m = comprimento(padrao)
    ocorrencias = []

    tabela_mau = PreProcessarMauCaractere(padrao)
    tabela_bom = PreProcessarBomSufixo(padrao)

    i = 0

    ENQUANTO i <= n - m:

        j = m - 1

        // Comparação do padrão com o texto (direita para esquerda)
        ENQUANTO j >= 0 E padrao[j] == texto[i + j]:
            j = j - 1
        FIM_ENQUANTO

        SE j < 0:
            ocorrencias.adicionar(i)
            i = i + tabela_bom[0] // salto após match completo

        SENÃO:
            salto_mau = CalcularSaltoMauCaractere(texto, padrao, i + j, j, tabela_mau)
            salto_bom = CalcularSaltoBomSufixo(j, m, tabela_bom)
            i = i + max(salto_mau, salto_bom)

    FIM_ENQUANTO

    RETORNAR ocorrencias

FIM_FUNÇÃO


```

???  Como seria esse pseudocódigo em C? 🤔 

Bom, para os corajosos de plantão, aqui está uma versão do algoritmo Boyer-Moore com as heurísticas combinadas.

:::

``` c

void BoyerMooreBuscaCombinada(char *texto, char *padrao) {

    int n = strlen(texto);
    int m = strlen(padrao);
    int tabela_mau[MAX_CHAR];
    int *tabela_bom = malloc((m + 1) * sizeof(int));

    PreProcessarMauCaractere(padrao, m, tabela_mau);
    PreProcessarBomSufixo(padrao, m, tabela_bom);

    int i = 0;

    while (i <= n - m) {
        int j = m - 1;

        // Comparação do padrão com o texto (da direita para a esquerda)
        while (j >= 0 && padrao[j] == texto[i + j]) {
            j = j - 1;
        }

        if (j < 0) {
            // ocorrência encontrada
            printf("Ocorrência encontrada na posição %d\n", i);
            i = i + tabela_bom[0];  
        } else {
            int salto_mau = CalcularSaltoMauCaractere(texto, padrao, i + j, j, tabela_mau);
            int salto_bom = CalcularSaltoBomSufixo(j, m, tabela_bom);
            int salto = (salto_mau > salto_bom) ? salto_mau : salto_bom;
            i = i + salto;
        }
    }

}
```
:::

???

## 8. Performance: Por Que o Boyer-Moore é Tão Rápido?
---------

Vimos o Boyer-Moore em ação e como suas heurísticas permitem saltos inteligentes. Mas quão rápido ele é na prática? Vamos analisar sua **complexidade de tempo**, que é uma forma de medir como o tempo de execução do algoritmo cresce conforme o tamanho da entrada (texto e padrão) aumenta.

Lembre-se:
*   n = tamanho do texto
*   m = tamanho do padrão

**Pré-processamento:**

Antes mesmo de começar a busca no texto, o Boyer-Moore precisa pré-processar o padrão para construir as tabelas do Mau Caractere e do Bom Sufixo. Essa etapa geralmente leva um tempo proporcional ao tamanho do padrão mais o tamanho do alfabeto (conjunto de caracteres possíveis). Podemos dizer que é algo em torno de **O(m + k)**, onde *k* é o tamanho do alfabeto. Na prática, para alfabetos de tamanho fixo (como ASCII ou Unicode), consideramos isso como **O(m)**.

**Fase de Busca:**

É aqui que a mágica acontece!

*   **Melhor Caso: O(n / m)**
    Este é o cenário dos sonhos! Acontece quando o padrão e o texto são muito diferentes, ou quando o mau caractere encontrado no texto frequentemente não existe no padrão. Nesses casos, a heurística do mau caractere permite saltos enormes, do tamanho do próprio padrão (m). O algoritmo acaba examinando apenas uma fração do texto, aproximadamente n / m caracteres. Isso é chamado de performance **sublinear**, pois ele nem precisa olhar para todos os caracteres do texto! É incrivelmente rápido, especialmente para padrões longos.

*   **Pior Caso: O(n * m) ou O(n)**
    Sim, infelizmente, existe um cenário (embora raro na prática com textos reais) onde o Boyer-Moore pode se degradar e ter um desempenho semelhante ao da força bruta, **O(n * m)**. Isso pode acontecer com padrões e textos muito repetitivos, onde as heurísticas acabam gerando saltos mínimos (de apenas 1 posição) consistentemente.
    !!! Otimização Crucial
    Com implementações cuidadosas da heurística do bom sufixo (como a versão de Galil), o pior caso da fase de busca do Boyer-Moore pode ser garantido como **O(n)**, ou seja, linear em relação ao tamanho do texto, mesmo mantendo a eficiência do melhor caso! A maioria das implementações modernas inclui essa otimização.
    !!!

*   **Caso Médio (Textos Reais): Próximo de O(n)**
    Na grande maioria das aplicações práticas, especialmente com textos em linguagem natural ou códigos-fonte (que têm alfabetos relativamente grandes e não são *extremamente* repetitivos), o desempenho do Boyer-Moore é excelente. Ele tende a se aproximar do seu melhor caso ou a ter um desempenho linear, **O(n)**. Isso significa que o tempo de busca cresce de forma diretamente proporcional ao tamanho do texto, o que é muito bom!

**Comparando com a Força Bruta:**

| Algoritmo      | Pré-processamento | Busca (Melhor Caso) | Busca (Pior Caso) | Busca (Caso Médio) |
| :------------- | :---------------- | :------------------ | :---------------- | :----------------- |
| Força Bruta    | Nenhum (O(1))     | O(n)                | O(n * m)          | O(n * m)           |
| Boyer-Moore    | O(m + k) ou O(m)  | **O(n / m)**        | O(n * m) ou **O(n)**¹ | **O(n)**           |

¹ *Com implementações otimizadas do Bom Sufixo.*

A tabela mostra claramente a vantagem do Boyer-Moore, especialmente no melhor caso (sublinear!) e no caso médio (linear). Mesmo que seu pior caso teórico possa ser ruim sem otimizações, na prática ele supera a força bruta na maioria das vezes.

??? Reflexão Final (Atividade 10)

Considerando a performance do Boyer-Moore:
1. Em que tipo de situação você acha que o Boyer-Moore seria *muito* mais vantajoso que a força bruta?
2. Existe alguma situação onde a força bruta *poderia* ser preferível (mesmo que rara)?

::: Gabarito

1.  O Boyer-Moore é especialmente vantajoso quando:
    *   O **padrão é longo**: Isso aumenta a chance de saltos maiores (melhor caso O(n/m)).
    *   O **alfabeto é grande** (ex: texto em português, código-fonte): Isso aumenta a chance do mau caractere não estar no padrão, levando a saltos maiores.
    *   O **texto é muito grande**: A diferença entre O(n) ou O(n/m) e O(n*m) se torna gigantesca.

2.  A força bruta *poderia* ser considerada (embora raramente seja a melhor escolha geral) se:
    *   O **padrão for extremamente curto** (ex: 1 ou 2 caracteres). Nesse caso, a sobrecarga do pré-processamento do Boyer-Moore pode não compensar, e a simplicidade da força bruta pode ser aceitável.
    *   A **memória for extremamente limitada**, impedindo o armazenamento das tabelas de pré-processamento do Boyer-Moore (cenário muito específico).
    *   A **implementação for trivial** e a performance não for crítica (mas geralmente, usar uma biblioteca otimizada é melhor).

Em geral, para a maioria das aplicações práticas de busca em texto, algoritmos como Boyer-Moore (ou KMP, Rabin-Karp) são preferíveis à força bruta devido à sua eficiência superior.

:::

???

## 9. Conclusão: O Legado do Salto Inteligente
---------

Chegamos ao fim da nossa jornada pelo algoritmo de Boyer-Moore! Vimos como a simples ideia de buscar padrões em texto pode levar a soluções surpreendentemente inteligentes.

Partimos da abordagem direta da força bruta e descobrimos como ela pode ser ineficiente. Então, mergulhamos nas ideias centrais do Boyer-Moore:

*   **Comparar da direita para a esquerda:** Uma mudança de perspectiva que permite obter informações valiosas mais cedo.
*   **Heurística do Mau Caractere:** Usar o caractere do texto que causou a falha para guiar o salto, alinhando-o com sua última ocorrência no padrão.
*   **Heurística do Bom Sufixo:** Reaproveitar a parte do padrão que já coincidiu, buscando realinhá-la com outra ocorrência ou um prefixo correspondente.
*   **Escolher o Maior Salto:** Combinar as duas heurísticas para maximizar o avanço pelo texto.

Essas ideias, juntas, resultam em um algoritmo que é frequentemente muito mais rápido que a força bruta, especialmente em textos reais, e que possui um desempenho médio excelente.


??? Desafio Final (Atividade 11)

Agora é sua vez de aplicar tudo o que aprendeu! Use o algoritmo de Boyer-Moore (combinando as duas heurísticas) para encontrar a primeira ocorrência do padrão 

```plaintext
Texto  = G T T A T A G C T G A T C G C G G C G T A G C G G C G A A

Padrão = G T A G C G G C G

```



::: Gabarito (Resumido)

:DESAFIO

O segredo do problema é entender que há casos em que será possível utilizar as duas heurísticas, nesses casos, deve-se escolher àquela que proporcionará o maior número de saltos
:::

???
