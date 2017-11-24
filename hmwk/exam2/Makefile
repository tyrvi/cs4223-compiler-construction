build: main.c parser.c parser.h scanner.l
	flex scanner.l
	gcc -o exam2-tminet main.c parser.c lex.yy.c -lfl

clean:
	rm -f core *.o lex.yy.c exam2-tminet exam2-tminet.exe
