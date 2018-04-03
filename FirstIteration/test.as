EXTERN main
linebr  STR     "\n"    
main    SUBU    $0, rSP, 16     *pega o segundo argumento da linha de comando(primeiro é o nome do programa) e guarda em $0
        LDOU    $0, $0, 0       *transforma em octa o que tem no registrador %0
        PUSH    $0              
        CALL    puts            *printa o argumento
        GETA    $0, linebr      *coloca o valor definido em linebr em $0
        PUSH    $0
        CALL    puts            *printa uma quebra de linha
        XOR $0,$0,$0
input   SETW   rX, 1            *define modo leitura    
        INT    #80              *le o caracter
        JN     rA, end          *verifica se chegou no final do arquivo => se o valor no registrador rA é negativo
write   SETW   rX, 2            *define modo escrita
        STBU   rA, $2, 0        *guarda no registrador $2 o conteúdo de rA
        LDBU   rY, $2, 0        *coloca em rY o conteúdo de $2
        INT    #80              *escreve o caracter
        JMP    input   
end     INT     0               *termina o programa