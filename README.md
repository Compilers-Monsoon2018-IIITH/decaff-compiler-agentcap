# Compiler for Decaf language

## Structure
> ast.h : Declarations and Definitions of all the ASTnode
> CodeGenerator.h : Definitions of Codegen of each ASTnode used in the Vistor Pattern.
> decaf.l : Contains the code of scanner
> PostFixVisitor.h : Definitions of Vistors which generates XML representation of the input code.
> Makefile : Makefile to compile and link the required files.

## Run
> Navigate to the src directory and run `make`, which generates a executable `decaf`
> Now run `./decaf [filename]` to get the Vistor output and also the code that is generated
> Example: 
`make
./decaf ../test-programs/even.dcf`

## Description
> The compiler is built using Vistor pattern. All the Shift-reduce errors have been fixed using the table generated.
> The things that are still remaining to be implemented are implement codegen for `callout` function and fix a few bugs with global arrays and the things that couldn't be completed are `break` and `continue` statements and some rules in the semantic analysis.
