center: buffer.c center.c
		gcc -Wall -ansi -pedantic -O2 -Wextra center.c buffer.c -o center

test: center foo.txt test.txt
		echo "running made-up test"
		./center test.txt test.out.txt 30
		echo "running test from Paca"			
		./center foo.txt bar.txt 25

clean:
		rm -f buffer center bar.txt *.out.txt