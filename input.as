EXTERN input

input    SETW   rX, 1
        INT        #80
        CMP    $0, rA, 10     
        JNZ    $0, read
        INT        0
write   SETW   rX, 2
        STBU   rA, $2, 0
        LDBU   rY, $2, 0
        INT    #80
        JMP    input          
