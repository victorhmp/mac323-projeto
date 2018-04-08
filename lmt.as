EXTERN  lmt

scflag  IS        $15
flag    IS        $16                *flag para verificação de fim de texto
arg     IS        $17                *argumento: comprimento máximo da linha    
p1      IS        $18                *ponteiros
p2      IS        $19
p3      IS        $20
lmt     SETW      $3, 0
        LDB       $40, p2, 0        *nao comeca com espaco
        CMP       $23, $40, 32
        JNZ       $23, loop
        ADDU      p1, p1, 1
        ADDU      p2, p2, 1
        JMP       -5
loop    SUBU      $4, $3, arg        *acresce p2 até chegar ao que o limite
        JZ        $4, end
        LDB       $40, p2, 0
        JN        $40, flg
        CMP       $23, $40, 32    ***
        JNZ       $23, 2            ***
        SETW      scflag, 1        ***
        ADDU      p2, p2, 1
        ADDU      $3, $3, 1
        CMP       $23, $40, 10    
        JZ        $23, 2            
        JMP       loop
        SETW      $98, 6            
        JMP       end                
flg     SETW      flag, 1
end     RET       0