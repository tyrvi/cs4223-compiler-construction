sample: sample.l sample.y main.c sample.h
	flex sample.l
	bison -y -d sample.y
	gcc -o sample main.c lex.yy.c y.tab.c -lfl

sample4.c:
	true

clean:
	rm -f core *.o lex.yy.c y.tab.c y.tab.h sample sample.exe
