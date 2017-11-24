checkpoint4: checkpoint4-tminet.l checkpoint4-tminet.yy main.c
	flex checkpoint4-tminet.l
	bison -y -d checkpoint4-tminet.yy
	gcc -o checkpoint4-tminet main.c lex.yy.c y.tab.c -lfl


clean:
	rm -f core *.o lex.yy.c y.tab.c y.tab.h checkpoint4-tminet checkpoint4-tminet.exe
