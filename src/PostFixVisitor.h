
#ifndef POSTFIXVISITOR_H
#define POSTFIXVISITOR_H

#include "ast.h"

class PostFixVisitor: public ASTvisitor
{
  public:
    unsigned int level;
    PostFixVisitor(){
        level=0;
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
        node.getMethods()->accept(*this);
        level--;
        indent();
        std::cout << "</BODY>\n";
    }
    
    virtual void visit(fieldDeclsASTnode& node) {
        indent();
        vector<ASTnode*> v = node.getFields();
        std::cout << "<FIELD_DECLS cnt=\"" << v.size() <<"\">\n";
        level++;
        for(unsigned int i=0;i<v.size();i++) {
            v[i]->accept(*this);
        }
        level--;
        indent();
        std::cout << "</FIELD_DECLS>\n";
    }
    
    virtual void visit(fieldDeclASTnode& node) {
        vector<variableASTnode*> v = node.getVariables();
        for(unsigned int i=0;i<v.size();i++) {
            v[i]->accept(*this);
        }
    }
    
    virtual void visit(variablesASTnode& node) {
        vector<variableASTnode*> t = node.getVariables();

        for(unsigned int i=0;i<t.size();i++) {
            t[i]->accept(*this);
        }
    }
    
    virtual void visit(variableASTnode& node) {
        indent();
        if(node.getVarType() == "Normal") {
            std::cout << "<FIELD name=\"" << node.getName() << "\" type=\"" << node.getDataType() << "\">";
        }
        else {
            std::cout << "<FIELD name=\"" << node.getName() << "\" type=\"" << node.getDataType() << "\" size=\"" << node.getLength() <<"\">" ;
        }

        std::cout << "\n";
    }
    
    virtual void visit(methodDeclsASTnode& node){
        indent();
        vector<ASTnode*> methodDecls = node.getMethodsDecls();
        cout << "<METHOD_DECLARATIONS count=\"" << methodDecls.size() << "\">\n";

        level++;
        for(unsigned int i=0;i<methodDecls.size();i++) {
            methodDecls[i]->accept(*this);
        }
        level--;

        indent();
        cout << "</METHOD_DECLARATIONS>\n";
    }

    virtual void visit(methodDeclASTnode& node) {
        indent();
        cout << "<METHOD_DECLARATION return_type=\"" << node.getType() << " name=\""<< node.getName() << "\">\n";

        level++;
        node.getParamList()->accept(*this);
        node.getBlock()->accept(*this);
        level--;

        indent();
        cout << "</METHOD_DECLARATION>\n";
    }
    virtual void visit(blockASTnode& node){
        indent();
        cout << "<BLOCK>\n";
        
        level++;
        node.getVarDecls()->accept(*this);
        node.getStmts()->accept(*this);
        level--;
        
        indent();
        cout << "</BLOCK>\n";
    }
    virtual void visit(varDeclsASTnode& node){
        vector<ASTnode*> varDecls = node.getVarDecls();
        
        indent();
        cout << "<VAR_DECLARATIONS count=\"" << varDecls.size() << "\">\n";
        
        level++;
        for(unsigned int i = 0; i < varDecls.size(); i++){
            varDecls[i]->accept(*this);
        }
        level--;

        indent();
        cout << "</VAR_DECLARATIONS>\n";
    }

    virtual void visit(varDeclASTnode& node) {
        ASTnode* ids = node.getIds();
        
        indent();
        cout << "<VAR_DECLARATION type=\"" << node.getType() << "\">\n";
        
        level++;
        ids->accept(*this);
        level--;

        indent();
        cout << "</VAR_DECLARATION>\n";
    }
    
    virtual void visit(idsASTnode& node) {
        vector<string> ids = node.getIds();
        for(unsigned int i=0;i<ids.size();i++) {
            indent();
            cout << "<VARIABLE name=\"" << ids[i] << "\">\n";
        }
    }
    
    virtual void visit(stmtsASTnode& node) {
        vector<ASTnode*> stmts = node.getStmts();

        indent();
        cout << "<STATMENTS count=\"" << stmts.size() << "\">\n";

        level++;
        for(unsigned int i = 0; i < stmts.size(); i++){
            stmts[i]->accept(*this);
        }
        level--;

        indent();
        cout << "</STATMENTS>\n";
    }

    virtual void visit(stmtASTnode& node) {
        node.getStmt()->accept(*this);
    }

    virtual void visit(assignASTnode& node) {
        indent();
        cout << "<ASSIGNMENT>\n";
        
        level++;
        
        indent();
        cout << "<LHS>\n";
        
        level++;
        node.getLocation()->accept(*this);
        level--;
        
        indent();
        cout << "</LHS>\n";
        
        indent();
        cout << "<OPERATION = \'" << node.getOp() <<"\'>\n";
  
        indent();
        cout << "<RHS>\n";
  
        level++;
        node.getExpr()->accept(*this);
        level--;
        
        indent();
        cout << "</RHS>\n";
        level--;
        
        indent();
        cout << "</ASSIGNMENT>\n";
    }

    virtual void visit(ifElseASTnode& node){
        indent();
        cout << "<IF_ELSE_STMT>\n";
        level++;
        
        indent();
        cout << "<CONDITION>\n";
        level++;
        node.getExpr()->accept(*this);
        level--;
        indent();
        cout << "</CONDITION>\n";

        indent();
        cout << "<IFBLOCK>\n";
        level++;
        node.getIfBlock()->accept(*this);
        level--;
        indent();
        cout << "</IFBLOCK>\n";

        if(node.getElseBlock()!=NULL) {
            indent();
            cout << "<ELSE_BLOCK>\n";
            level++;
            node.getElseBlock()->accept(*this);
            level--;
            indent();
            cout << "</ELSE_BLOCK>\n";
        }
        
        level--;
        indent();
        cout << "</IF_ELSE_STMT>\n";
    }

    virtual void visit(forASTnode& node) {
        indent();
        cout << "<FOR>\n";
        
        level++;
        indent();
        cout << "<ITERATIONS>\n";
        level++;
        indent();
        cout << "<ITR_VARIABLE name=\"" << node.getId() << "\" />\n";

        indent();
        cout << "<INIT_COND>\n";
        level++;
        node.getInitCond()->accept(*this);
        level--;
        indent();
        cout << "</INIT_COND>\n";

        indent();
        cout << "<END_COND>\n";
        level++;
        node.getEndCond()->accept(*this);
        level--;
        indent();
        cout << "</END_COND>\n";

        level--;
        indent();
        cout << "</ITERATIONS>\n";

        indent();
        cout << "<FOR_BODY>\n";
        level++;
        node.getBody()->accept(*this);
        level--;
        indent();
        cout << "</FOR_BODY>\n";

        level--;
        indent();
        cout << "</FOR>\n";
    }
    
    virtual void visit(rtnStmtASTnode& node) {
        indent();
        if(node.getExpr() == NULL){
            cout << "<RTN_STATEMENT />\n";
        }
        else {
            cout << "<RTN_STATEMENT>\n";
            level++;
            node.getExpr()->accept(*this);
            level--;
            indent();
            cout << "</RTN_STATEMENT>\n";

        }
    }

    virtual void visit(breakStmtASTnode& node) {
        indent();
        cout << "<BREAK_STMT />\n";
    }

    virtual void visit(continueStmtASTnode& node) {
        indent();
        cout << "<CONTINUE_STMT />\n";
    }
    virtual void visit(methodCallASTnode& node){
        indent();
        cout << "<METHOD_CALL type=\"" << node.getCallType() << "\">\n";

        level++;
        indent();
        cout << "<FUNCTION_NAME = \"" << node.getName() << "\"/>\n";
        indent();
        cout << "<FUNCTION_ARGS>\n";
        if(node.getArgs() != NULL) {
            level++;
            node.getArgs()->accept(*this);
            level--;
        }
        indent();
        cout << "</FUNCTION_ARGS>\n";
        level--;

        indent();
        cout << "</METHOD_CALL>\n";
    }
    virtual void visit(callOutArgsASTnode& node) {
        vector<ASTnode*> args = node.getArgs();

        for(unsigned int  i=0;i<args.size();i++) {
            args[i]->accept(*this);
        }

    }
    virtual void visit(exprListASTnode& node){
        vector<ASTnode*> exprs = node.getExprs();
        
        for(unsigned int  i=0;i<exprs.size();i++) {
            exprs[i]->accept(*this);
        }
    }

    virtual void visit(locationASTnode& node){
        indent();
        cout << "<IDENTIFIER name=\"" << node.getId() << "\">\n";
        if(node.getType() == "Array") {
            level++;
            
            indent();
            cout << "<LOCATION>\n";

            level++;
            node.getExpr()->accept(*this);
            level--;

            indent();
            cout << "</LOCATION>\n";

            level--;
        }
    }

    virtual void visit(paramListASTnode& node){
        ASTnode* params = node.getParamList();
        if(params != NULL) {
            params->accept(*this);
        }
    }

    virtual void visit(parametersASTnode& node){
        vector<ASTnode*> parameters = node.getParameters();
        indent();
        cout << "<METHOD_ARGS count=\"" << parameters.size() << "\">\n";
        
        level++;
        for(unsigned int i = 0; i < parameters.size(); i++) {
            parameters[i]->accept(*this);
        }
        level--;
        
        indent();
        cout << "</METHOD_ARGS>\n";
    }
    virtual void visit(parameterASTnode& node){
        indent();
        cout << "<METHOD_ARG name=\"" << node.getName() << "\" type=\"" << node.getType() << "\" />\n";
    }
    virtual void visit(exprASTnode& node) {
        node.getExpr()->accept(*this);
    }
    virtual void visit(binaryASTnode& node) {
        indent();
        cout << "<BINARY_EXPR type=\"" << node.getBinOperator() <<"\">\n";
        level++;
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);
        level--;
        
        indent();
        cout << "</BINARY_EXPR>\n";
    }
    virtual void visit(unaryASTnode& node) {
        indent();
        cout << "<UNARY_EXPR type=\"" << node.getOp() <<"\">\n";
        
        level++;
        node.getExpr()->accept(*this);
        level--;
        
        indent();
        cout << "</UNARY_EXPR>\n";
    }
    virtual void visit(callArgASTnode& node) {
        if(node.getExpr() != NULL) {
            indent();
            cout << "<CALLOUT_ARG type=\"expr\">\n";
            
            level++;
            node.getExpr()->accept(*this);
            level--;
            
            indent();
            cout << "</CALLOUT_ARG>\n";
        }
        else {
            indent();
            cout << "<CALLOUT_ARG type=\"string\" value = \"" << node.getStrArg() <<"\">\n";
        }
    }
    virtual void visit(literalASTnode& node) {
        indent();
        if(node.getType() == "INT") {
            cout << "<LITERAL type=\"" << node.getType() << "\" val=\""<<node.getIntVal() <<"\" />\n";
            
        }
        else {
            cout << "<LITERAL type=\"" << node.getType() << "\" val=\""<<node.getStrVal() <<"\" />\n";
        }
    }

    void indent() {
        for(unsigned int i=0;i<level;i++) {
            std::cout << "\t";
        }
    }
};

#endif /* POSTFIXVISITOR_H */

