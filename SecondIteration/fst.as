        EXTERN  fst
flag2	IS	$15		*flag para evitar whitespaces no começo da linha
flag	IS	$16		*flag para verificação de fim de texto
arg	IS	$17		*argumento: comprimento máximo da linha	
p1	IS	$18		*ponteiros
p2	IS	$19
p3	IS	$20
c1	IS	$21		*contadores
c2	IS	$22
fst	LDB	rZ, p3, 0	*caractere em rZ
	CMP	$23, rZ, 9 	*para em whitespaces
	JZ	$23, end      
	CMP	$23, rZ, 10 	
	JZ	$23, end
	CMP	$23, rZ, 13 		
	JZ	$23, end
	CMP	$23, rZ, 32 		
	JZ	$23, end
	CMP	$23, rZ, 0      *fim de texto: flag ativada
	JZ	$23, flg
	ADDU	p3, p3, 1
	ADDU	p2, p2, 1
	JMP	fst
flg     SETW    flag, 1
end     RET     1