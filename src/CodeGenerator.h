#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "ast.h"

class CodeGen: public CodeGenerator {
public:
	virtual Value* codegen(ProgramASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(BodyASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(fieldDeclsASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(fieldDeclASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(variableASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(variablesASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(methodDeclsASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(methodDeclASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(blockASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(varDeclsASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(varDeclASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(idsASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(stmtsASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(stmtASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(assignASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(ifElseASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(forASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(rtnStmtASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(breakStmtASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(continueStmtASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(methodCallASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(callOutArgsASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(exprListASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(locationASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(paramListASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(parametersASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(parameterASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(exprASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(binaryASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(unaryASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(callArgASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(literalASTnode& node) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}


};


#endif /* CODEGENERATOR_H */