	    EXTERN  line
flag2	IS		$15				*flag para evitar whitespaces no começo da linha
flag	IS		$16				*flag para verificação de fim de texto
arg		IS		$17				*argumento: comprimento máximo da linha	
p1		IS		$18				*ponteiros
p2		IS		$19
p3		IS		$20
c1		IS		$21				*contadores
c2		IS		$22
line	CMP		$23, p1, p3		
		JZ		$23, end		*se p1 == p3, fim da escrita
		LDB		rY, p1, 0		*carrega caractere em rY
		ADDU	p1, p1, 1		*após carregamento, p1++
		JZ		flag2, 10		*se não é primeiro caractere, pula as verificações de whitespace
		CMP		$23, rY, 9 		
		JZ		$23, line
		CMP		$23, rY, 10 	*ATENCAO: quebra de linha pode ser paragrafo - ajustar
		JZ		$23, line
		CMP		$23, rY, 13 		
		JZ		$23, line
		CMP		$23, rY, 32 		
		JZ		$23, line
		SETW	flag2, 0		*zera flag2
		SETW	rX, 2
		INT 	#80
		JMP 	line
end		JP 		flag2, 4
		SETW	rX, 2			*fim e quebra de linha
		SETW	rY, 10		
		INT		#80		
		RET		1


