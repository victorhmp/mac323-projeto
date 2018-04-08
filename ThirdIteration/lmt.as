EXTERN  lmt
flag    IS        $16                *flag para verificação de fim de texto
arg     IS        $17                *argumento: comprimento máximo da linha    
p1      IS        $18                *ponteiros
p2      IS        $19
p3      IS        $20
lmt     SETW      $3, 0
        LDB       rY, p2, 0        *nao comeca com espaco
        CMP       $23, rY, 32
        JNZ       $23, loop
        ADDU      p1, p1, 1
        ADDU      p2, p2, 1
        JMP       -5
loop    SUBU      $4, arg, $3        *acresce p2 até chegar ao que o limite
        JZ        $4, end
        LDBU      rY, p2, 0
        JN        rY, flg
        ADDU      p2, p2, 1
        ADDU      $3, $3, 1
        JMP       loop
flg     SETW      flag, 1
end     RET       1