a.out: sample.y sample.l main.c
	bison -y -d sample.y
	flex sample.l
	gcc lex.yy.c y.tab.c main.c -lfl

clean:
	rm -f a.exe a.out lex.yy.c y.tab.c y.tab.h
