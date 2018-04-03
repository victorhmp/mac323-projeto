 EXTERN  main
flag2    IS        $15                *flag para evitar whitespaces no começo da linha
flag    IS        $16                 *flag para verificação de fim de texto
arg        IS        $17              *argumento: comprimento máximo da linha    
p1        IS        $18               *ponteiros
p2        IS        $19
p3        IS        $20
c1        IS        $21                *contadores
c2        IS        $22
main    XOR     $0, $0, $0
        STBU    $2, $0, 0
        SETW    rX, 1
        INT        #80
        JN        rA, 4
        STBU    rA, $0, 0
        ADDU    $0, $0, 1
        JMP        -5
        SETW    arg, 8            *argumento arbitrário (ajustar)
        SETW    c1, 0            *contadores e flags zerados
        SETW    c2, 0
        SETW    flag, 0
        SETW    flag2, 0
        LDBU    p1, $2, 0    *ponteiros apontam para o começo do texto de entrada
        LDBU    p2, $2, 0
        LDBU    p3, $2, 0
        LDOU    p1, p1, 0    
        LDOU    p2, p2, 0
        LDOU    p3, p3, 0
loop    CALL    fst                *primeira palavra da linha
        CALL    line
        RET        1
        SETW    flag2, 1        *evita whitespace no começo da linha
        JP        flag, 4            *se já chegou ao fim, pula verificações
        SUBU    c2, p3, p1
        CALL    next            *vê comprimento da palavra subsequente
        CALL    chk                *checa se cabe
        JNZ        rA, -2            *se couber, vê a próxima
        CALL    line            *se não couber, escreve até a anterior e termina linha (FALTA FAZER O ESPAÇAMENTO)
        OR        p1, p3, 0
        OR        p2, p3, 0
        JP        flag, end
        SETW    c1, 0            *zera contadores para próximo loop
        SETW    c2, 0
        JMP     loop        
end     INT        0        