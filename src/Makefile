TARGET=mycomp
all=$(TARGET)
CC = g++
CFLAGS = -lfl `llvm-config-3.8 --cxxflags --cppflags mcjit native --ldflags --libs core` -ltinfo -lpthread -ldl
FLAGS=-w -Wno-deprecated -g -std=c++11
all: $(TARGET)
$(TARGET): lex.yy.c decaf.tab.c ast.h
	$(CC) $(FLAGS) lex.yy.c decaf.tab.c $(CFLAGS) -o decaf
lex.yy.c: decaf.l
	flex decaf.l
decaf.tab.c: decaf.y
	bison -vd decaf.y
clean:
	rm *.c decaf.tab.h decaf.output decaf