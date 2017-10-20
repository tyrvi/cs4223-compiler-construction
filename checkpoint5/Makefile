checkpoint5: scanner.l parser.yy hashtable.c hashtable.h main.c 
	flex scanner.l
	bison -y -d parser.yy
	gcc -o checkpoint5-tminet main.c lex.yy.c y.tab.c hashtable.c -lfl


clean:
	rm -f core *.o lex.yy.c y.tab.c y.tab.h checkpoint5-tminet checkpoint5-tminet.exe
