
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