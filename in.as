flag IS $2
        EXTERN main
parag   STR     "Fim\n"
main    XOR     $0, $0, $0       
read    SETW    rX, 1            *define modo leitura
        INT     #80              *le o caracter
        JN      rA, end 
        CMP     $1, rA, 10       *verifica se eh um \n
        JZ      $1, verify       *pula para o verify
        SETW    flag, 0          *como o caracter nao eh \n entao flag=0       
        JMP     write            *vai para o modo escrito                    
verify  CMP     $3, flag, 1      *verifica se a flag tem valor 1
        JZ      $3, print1       *printa o \n
        SETW    flag, 1          *caso seja o primeiro \n setar a flag=1
        JMP     write            *printar normalmente
print   GETA    $3, parag         
        PUSH    $3
        CALL    puts  
        JMP     read      
print1  SETW    rX, 2            *apenas printa o \n (caso especial)
        STBU    rA,rA, 0         
        LDBU    rY,rA, 0        
        INT     #80 
        JMP     print           
write   SETW    rX, 2            *define o modo escrito
        STBU    rA,rA, 0         *coloca o conteudo de rA na memoria
        LDBU    rY,rA, 0         *coloca em rY o conteudo de rA
        INT     #80              *printa o caracter em rY
        JMP     read             *volta para o modo leitura
end     INT     0 