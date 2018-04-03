	    EXTERN  next
flag2	IS		$15				*flag para evitar whitespaces no começo da linha
flag	IS		$16				*flag para verificação de fim de texto
arg		IS		$17				*argumento: comprimento máximo da linha	
p1		IS		$18				*ponteiros
p2		IS		$19
p3		IS		$20
c1		IS		$21				*contadores
c2		IS		$22
next	ADDU	p2, p2, 1		*p2 percorre a palavra a ser analisada
		LDB		rZ, p2, 0
		CMP		$23, rZ, 9 		*para em whitespaces
		JZ		$23, end      
		CMP		$23, rZ, 10 	
		JZ		$23, end
		CMP		$23, rZ, 13 		
		JZ		$23, end
		CMP		$23, rZ, 32 		
		JZ		$23, end
		CMP		$23, rZ, 0      *fim de texto: flag ativada
		JZ		$23, flg
		JMP		next
flg 	SETW	flag2, 1
end		SUBU	c1, p2, p3		*contador1 = p2 - p3 (para ver se cabe na linha)
		RET		1

