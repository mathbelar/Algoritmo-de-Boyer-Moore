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


