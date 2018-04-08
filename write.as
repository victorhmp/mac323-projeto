	EXTERN  write
scflag	IS	$15
flag	IS      $16				*flag para verificação de fim de texto
arg     IS	$17				*argumento: comprimento máximo da linha	
p1      IS	$18				*ponteiros
p2      IS	$19
p3      IS	$20
spct    IS      $21
spn     IS      $22
c1      IS      $24
write   OR      p3, p1, 0           
        SETW    spct, 0
        SETW    rZ, 0
        JMP     count
count   ADDU    p3, p3, 1       *conta numero de espacos presentes OK
        CMP     $23, p3, p2
        JNN     $23, calc
        LDB     rY, p3, 0
        CMP     $23, rY, 32
        JNZ     $23, count
        ADDU    spct, spct, 1
        JMP     count
calc    SUBU    $23, p2, p1     *calcula número de espacos adicionais OK
        SUBU    $23, arg, $23
        JZ      spct, output
        DIVU    spn, $23, spct
        MULU    c1, spn, spct
        SUBU    rZ, $23, c1
        SUBU    rZ, spct, rZ
        JMP     output
output  SUBU	$23, p2, p1
	    JNP	    $23, end
        SETW	rX, 2
	    LDB	    rY, p1, 0
        LDB     $100, p1, 0     *
	    INT	    #80
        CMP     $23, $98, 6     **
        JZ      $23, 17         **
        JP      flag, 16
        CMP     $23, rY, 32
        OR      c1, spn, 0
        JNZ     $23, 13         
        JZ      c1, 6
        SETW	rX, 2
        SETW    rY, 32
        INT 	#80
        SUBU    c1, c1, 1
        JMP     -5
        JNZ     rZ, 5                     
        SETW    rX, 2                            
        SETW    rY, 32                            
        INT     #80                             
        JMP     2                                        
        SUBU    rZ, rZ, 1
        ADDU    p1, p1, 1
        JMP     output
end     CMP     $23, $100, 10   
        JZ      $23, 5          
        JZ      scflag, loop    ****
end2    SETW	rX, 2           
        SETW    rY, 10
        INT	    #80
        SETW    $98, 0          
        RET     0
loop    LDB     rY, p1, 0
        ADDU    p1, p1, 1
        ADDU    p2, p2, 1
        SETW    rX, 2
        JN      rY, end2
        INT     #80
        CMP     $23, rY, 32
        JZ      $32, end2
        CMP     $23, rY, 10
        JZ      $32, end2
        JMP     loop