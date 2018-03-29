flag IS $11
    EXTERN main
parag   STR     " # "
main    XOR     $0, $0, $0
read    SETW    rX, 1        *define modo leitura
        INT     #80          *le o caracter
        JN      rA, end
        CMP     flag, rA, 32  *ve se eh um espaco em branco
        JMP     write        *vai para o modo escrito 
write   SETW    rX, 2        *define o modo escrito
        STBU    rA,rA, 0     *coloca o conteudo de rA na memoria
        LDBU    rY,rA, 0     *coloca em rY o conteudo de rA
        INT     #80          *printa o caracter em rY
        JZ      flag, print     
        JMP     read         *volta para o modo leitura
print   GETA    $3, parag         
        PUSH    $3
        CALL    puts       
        JMP     read
end     INT     0 