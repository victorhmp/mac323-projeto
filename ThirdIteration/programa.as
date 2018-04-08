        EXTERN  main
flag    IS        $16                *flag para verificação de fim de texto
arg     IS        $17                *argumento: comprimento máximo da linha    
p1      IS        $18                *ponteiros
p2      IS        $19
p3      IS        $20
input   SETW    rX, 1
        INT     #80
        STBU    rA, $0, 0
        JN      rA, 6
        ADDU    $0, $0, 1
        JMP     input
main    XOR     $0, $0, $0
        STBU    $2, $0, 0
        JMP     input
        SETW    arg, 30
        SETW    flag, 0
        STBU    $2, $3, 0
        LDBU    p1, $3, 0        *ponteiros apontam para o começo do texto de entrada
        LDBU    p2, $3, 0
        LDBU    p3, $3, 0
        LDOU    p1, p1, 0    
        LDOU    p2, p2, 0
        LDOU    p3, p3, 0
loop    CALL    lmt
        CALL    back
        CALL    write
        JP      flag, 2
        JMP     loop        
end     INT     0