
#ifndef POSTFIXVISITOR_H
#define POSTFIXVISITOR_H

#include "ast.h"

class PostFixVisitor: public ASTvisitor
{
  public:
    int level=0;
    
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
    virtual void visit(methodDeclASTnode& node){}
    virtual void visit(blockASTnode& node){}
    virtual void visit(varDeclsASTnode& node){}
    virtual void visit(varDeclASTnode& node){}
    virtual void visit(idsASTnode& node){}
    virtual void visit(stmtsASTnode& node){}
    virtual void visit(stmtASTnode& node){}
    virtual void visit(assignASTnode& node){}
    virtual void visit(ifElseASTnode& node){}
    virtual void visit(forASTnode& node){}
    virtual void visit(rtnStmtASTnode& node){}
    virtual void visit(breakStmtASTnode& node){}
    virtual void visit(continueStmtASTnode& node){}
    virtual void visit(methodCallASTnode& node){}
    virtual void visit(callOutArgsASTnode& node){}
    virtual void visit(exprListASTnode& node){}
    virtual void visit(locationASTnode& node){}
    virtual void visit(paramListASTnode& node){}
    virtual void visit(parametersASTnode& node){}
    virtual void visit(parameterASTnode& node){}
    virtual void visit(exprASTnode& node){}
    virtual void visit(binaryASTnode& node){}
    virtual void visit(unaryASTnode& node){}
    virtual void visit(callArgASTnode& node){}
    virtual void visit(literalASTnode& node){}

    void indent() {
        for(int i=0;i<level;i++) {
            std::cout << "\t";
        }
    }
};

#endif /* POSTFIXVISITOR_H */

