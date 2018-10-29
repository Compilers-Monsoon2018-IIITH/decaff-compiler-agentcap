
#ifndef POSTFIXVISITOR_H
#define POSTFIXVISITOR_H

#include "ast.h"

class PostFixVisitor: public ASTvisitor
{
  public:
    int level=0;
    virtual void visit(BinaryASTnode& node)
    {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);
        std::cout << node.getBinOperator() << " ";
    }

    virtual void visit(TernaryASTnode& node)
    {
        node.getFirst()->accept(*this);
        node.getSecond()->accept(*this);
        node.getThird()->accept(*this);
        std::cout << "? ";
    }

    virtual void visit(IntLitASTnode& node) 
    {
        std::cout << node.getIntLit() << " ";
    }

    virtual void visit(AssignASTnode& node)
    {
        std::cout << node.getId() << " ";
        node.getExpr()->accept(*this);
        std::cout << node.getOp() << " ";
    }

    virtual void visit(ProgramASTnode& node) {
        indent();
        std::cout << "<PROGRAM>\n";
        level++;
        node.getBody()->accept(*this);
        level--;
        indent();
        std::cout << "</PROGRAM>\n";     
    }

    virtual void visit(BodyASTnode& node) {
        indent();
        std::cout << "<BODY>\n";
        level++;
        node.getFields()->accept(*this);
        level--;
        indent();
        std::cout << "</BODY>\n";
    }
    
    virtual void visit(fieldDeclsASTnode& node) {
        indent();
        vector<ASTnode*> v = node.getFields();
        std::cout << "<fields_decls cnt=\"" << v.size() <<"\">\n";
        level++;
        for(int i=0;i<v.size();i++) {
            v[i]->accept(*this);
        }
        level--;
        indent();
        std::cout << "</fields_decl>\n";
    }
    
    virtual void visit(fieldDeclASTnode& node) {
        indent();
        std::cout << node.getfType() << " ";
        node.getVariables()->accept(*this);
        std::cout << "\n";
    }
    
    virtual void visit(variablesASTnode& node) {
        vector<ASTnode*> t = node.getVariables();

        for(int i=0;i<t.size();i++) {
            t[i]->accept(*this);
        }
    }
    
    virtual void visit(variableASTnode& node) {
        if(node.getVarType() == "Normal") {
            std::cout << "<" << node.getVarType() << ">" << node.getName() << " ";
        }
        else {
            std::cout << "<" << node.getVarType() << ">" << node.getName() << "[" << node.getLength() << "] ";
        }
    }
    
    virtual void visit(methodDeclsASTnode& node){}

    void indent() {
        for(int i=0;i<level;i++) {
            std::cout << "\t";
        }
    }
};

#endif /* POSTFIXVISITOR_H */

