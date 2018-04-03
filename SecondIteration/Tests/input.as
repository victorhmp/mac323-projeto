EXTERN main
main    XOR $0,$0,$0
        STBU    $2, $0, 0
input   SETW    rX, 1
        INT     #80
        JN      rA, write
        STBU    rA, $0, 0
        ADDU    $0, $0, 1
write   SETW    rX, 2
load    LDBU    rY, $2, 0
        CMP     $100, $2, $0
        JZ      $100, end
        ADDU    $2, $2, 1
        INT     #80
        JMP     input  
end     INT     0  *termina o programa
