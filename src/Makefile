

CXX = g++
#CXXFLAGS =
CXXFLAGS = -W -Wall -Wextra -ansi -g
INCLUDE = -I/usr/local/opt/flex/include/ -I./

all: decaf

# generate parser and scanner
parser.cc: decaf.yy
	bison -o parser.cc --defines=parser.h decaf.yy

scanner.cc: decaf.ll
	flex -o scanner.cc decaf.ll


# Implicit rule to compile c++ files
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<


# Link executable
decaf: parser.o scanner.o driver.o ast.o
	$(CXX) $(LDFLAGS) -o $@ parser.o scanner.o driver.o ast.o
	rm *.o

clean: 
	rm -rf parser.cc parser.h scanner.cc location.hh  position.hh stack.hh *.o decaf
