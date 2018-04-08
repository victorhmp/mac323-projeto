	    EXTERN  back
scflag	IS		$15
flag	IS		$16				*flag para verificação de fim de texto
arg		IS		$17				*argumento: comprimento máximo da linha	
p1		IS		$18				*ponteiros
p2		IS		$19
p3		IS		$20
back	CMP		$23, $98, 6		
		JZ		$23, end		
		*CMP	$23, arg, 1		*se argumento for 1, este programa é ignorado
		*JZ		$23, end
		JZ 		scflag, end			
		LDB		rY, p2, 0
		JN		rY, flg
loop	LDB		rY, p2, 0
		CMP		$23, rY, 32		*busca o whitespace
		JZ		$23, end
		CMP		$23, rY, 10		*busca o whitespace
		JZ		$23, end
		SUBU	p2, p2, 1
		JMP		loop
flg		SETW	flag, 1
end		RET		0