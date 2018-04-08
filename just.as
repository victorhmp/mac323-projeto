	    EXTERN  main
scflag	IS	$15
flag	IS	$16				*flag para verificação de fim de texto
arg	IS	$17				*argumento: comprimento máximo da linha	
p1	IS	$18				*ponteiros
p2	IS	$19
p3	IS	$20
s       IS      $7
input	SETW	rX, 1
	INT	#80
	STB     rA, $0, 0
	ADDU    $0, $0, 1
	JN	rA, main3
	JMP	input
main    JMP	atoi
main2	XOR 	$0, $0, $0
	STBU	$0, $2, 0
	JMP	input
main3	SETW	flag, 0
	OR	p1, $2, 0		*ponteiros apontam para o começo do texto de entrada
	OR	p2, $2, 0
	OR	p3, $2, 0
	*LDOU	p1, p1, 0	
	*LDOU	p2, p2, 0
	*LDOU	p3, p3, 0
loop    CALL	lmt
	CALL	back
	CALL	write
	SETW	scflag, 0
	JP	flag, 2
	JMP 	loop		
end	INT	0

atoi    SUBU    s, rSP, 16
        LDOU    s, s, 0
        SETW    rA, 0
decim   LDB     rY, s, 0
        CMP     $23, rY, 48 
        JN      $23, fim 
        CMP     $23, rY, 57 
        JP      $23, fim 
        SUBU    rY, rY, 48 
        MULU    rA, rA, 10 
        ADDU    rA, rA, rY
        ADDU    s, s, 1 
        JMP     decim
fim     OR      arg, rA, 0
        JMP	main2