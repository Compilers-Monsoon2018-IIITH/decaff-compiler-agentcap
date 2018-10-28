parser: parser.y scanner.l
		bison --verbose -d parser.y
		flex scanner.l
		gcc -o parser.out parser.tab.c lex.yy.c -ll
