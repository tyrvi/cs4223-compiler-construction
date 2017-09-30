a.out: sample3.y sample3.l main.c
	bison -y -d sample3.y
	flex sample3.l
	gcc lex.yy.c y.tab.c main.c -lfl

clean:
	rm -f a.exe a.out lex.yy.c y.tab.c y.tab.h
