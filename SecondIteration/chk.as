	    EXTERN  chk
flag2	IS		$15				*flag para evitar whitespaces no começo da linha
flag	IS		$16				*flag para verificação de fim de texto
arg		IS		$17				*argumento: comprimento máximo da linha	
p1		IS		$18				*ponteiros
p2		IS		$19
p3		IS		$20
c1		IS		$21				*contadores
c2		IS		$22
chk		ADDU 	$23, c1, c2		
		SUBU	$24, $23, arg	*compara (c1+c2) e o argumento
		JN		$24, 5			*se for negativo, não cabe. ponteiros ajustados pra próxima linha
		OR		p3, p2, 0		*caso contrário, cabe e a contagem continua
		SETW	rA, 1
		ADDU	c2, c2, c1
		JMP		end

end		RET		1
