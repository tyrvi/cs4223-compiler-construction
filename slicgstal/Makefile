build: main.c scanner.l parser.yy symboltable.c symboltable.h ast.c ast.h generator.c generator.h code.c code.h error.c error.h
	flex scanner.l
	bison -y -d parser.yy
	gcc -o sgc main.c lex.yy.c y.tab.c symboltable.c ast.c generator.c error.c code.c -lfl


clean:
	rm -f core *.o lex.yy.c y.tab.c y.tab.h sgc sgc.exe
