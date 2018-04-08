EXTERN  write
flag    IS        $16                *flag para verificação de fim de texto
arg     IS        $17                *argumento: comprimento máximo da linha    
p1      IS        $18                *ponteiros
p2      IS        $19
p3      IS        $20
write   SUBU      $23, p2, p1
        JNP       $23, end
        SETW      rX, 2
        LDB       rY, p1, 0
        INT       #80
        ADDU      p1, p1, 1
        JMP       write
end     SETW      rX, 2
        SETW      rY, 10
        INT       #80
        RET       1