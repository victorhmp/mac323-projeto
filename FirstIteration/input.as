EXTERN main
main    XOR $0,$0,$0
input   SETW   rX, 1
        INT        #80
        JN     rA, end
write   SETW   rX, 2
        STBU   rA, $2, 0
        LDBU   rY, $2, 0
        INT    #80
        JMP    input   
end     INT     0  *termina o programa