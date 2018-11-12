#ifndef AST_H
#define AST_H

#include <bits/stdc++.h>

using namespace std;

union Node
{
	int integerVal;
    std::string* stringVal;
    class ASTnode* astnode;
    class ProgramASTnode* programnode;
    class BodyASTnode* bodynode;
    class fieldDeclsASTnode* fielddeclsnode;
    class fieldDeclASTnode* fielddeclnode;
    class variableASTnode* variablenode;
    class variablesASTnode* variablesnode;
    class methodDeclsASTnode* methoddeclsnode;
    class methodDeclASTnode* methoddeclnode;
    class blockASTnode* blocknode;
    class varDeclsASTnode* vardeclsnode;
    class varDeclASTnode* vardeclnode;
    class idsASTnode* idsnode;
    class stmtsASTnode* stmtsnode;
    class stmtASTnode* stmtnode;
    class assignASTnode* assignnode;
    class ifElseASTnode* ifelsenode;
    class forASTnode* fornode;
    class rtnStmtASTnode* rntstmtnode;
    class breakStmtASTnode* breakstmtnode;
    class continueStmtASTnode* continuenode;
    class methodCallASTnode* methodcallnode;
    class callOutArgsASTnode* calloutargsnode;
    class exprListASTnode* exprlistnode;
    class locationASTnode* locationnode;
    class paramListASTnode* paramlistnode;
    class parametersASTnode* parametersnode;
    class exprASTnode* exprnode;
    class binaryASTnode* binarynode;
    class unaryASTnode* unarynode;
    class callArgASTnode* callargnode;
    class literalASTnode* literalnode;
};

typedef union Node YYSTYPE;

#define YYSTYPE_IS_DECLARED 1

class ProgramASTnode;
class BodyASTnode;
class fieldDeclsASTnode;
class fieldDeclASTnode;
class variableASTnode;
class variablesASTnode;
class methodDeclsASTnode;
class methodDeclASTnode;
class blockASTnode;
class varDeclsASTnode;
class varDeclASTnode;
class idsASTnode;
class stmtsASTnode;
class stmtASTnode;
class assignASTnode;
class ifElseASTnode;
class forASTnode;
class rtnStmtASTnode;
class breakStmtASTnode;
class continueStmtASTnode;
class methodCallASTnode;
class callOutArgsASTnode;
class exprListASTnode;
class locationASTnode;
class paramListASTnode;
class parametersASTnode;
class parameterASTnode;
class exprASTnode;
class binaryASTnode;
class unaryASTnode;
class callArgASTnode;
class literalASTnode;


class ASTvisitor {
  public:
    virtual void visit(ProgramASTnode& node) = 0;
    virtual void visit(BodyASTnode& node) = 0;
    virtual void visit(fieldDeclsASTnode& node) = 0;
    virtual void visit(fieldDeclASTnode& node) = 0;
    virtual void visit(variableASTnode& node) = 0;
    virtual void visit(variablesASTnode& node) = 0;
    virtual void visit(methodDeclsASTnode& node) = 0;
    virtual void visit(methodDeclASTnode& node) = 0;
    virtual void visit(blockASTnode& node) = 0;
    virtual void visit(varDeclsASTnode& node) = 0;
    virtual void visit(varDeclASTnode& node) = 0;
    virtual void visit(idsASTnode& node) = 0;
    virtual void visit(stmtsASTnode& node) = 0;
    virtual void visit(stmtASTnode& node) = 0;
    virtual void visit(assignASTnode& node) = 0;
    virtual void visit(ifElseASTnode& node) = 0;
    virtual void visit(forASTnode& node) = 0;
    virtual void visit(rtnStmtASTnode& node) = 0;
    virtual void visit(breakStmtASTnode& node) = 0;
    virtual void visit(continueStmtASTnode& node) = 0;
    virtual void visit(methodCallASTnode& node) = 0;
    virtual void visit(callOutArgsASTnode& node) = 0;
    virtual void visit(exprListASTnode& node) = 0;
    virtual void visit(locationASTnode& node) = 0;
    virtual void visit(paramListASTnode& node) = 0;
    virtual void visit(parametersASTnode& node) = 0;
    virtual void visit(parameterASTnode& node) = 0;
    virtual void visit(exprASTnode& node) = 0;
    virtual void visit(binaryASTnode& node) = 0;
    virtual void visit(unaryASTnode& node) = 0;
    virtual void visit(callArgASTnode& node) = 0;
    virtual void visit(literalASTnode& node) = 0;
};


class ASTnode {
public :
    virtual ~ASTnode() {
    }

    virtual void accept(ASTvisitor& V) = 0;
};

class ProgramASTnode : public ASTnode {
public:
    ProgramASTnode(ASTnode* bodyParam)
    : body(bodyParam) {
    }

    ASTnode* getBody() {
        return body;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* body;
};

class BodyASTnode : public ASTnode {
public:
    BodyASTnode(ASTnode* fDeclsParam, ASTnode* mDeclsParam)
    : fDecls(fDeclsParam)
    ,mDecls(mDeclsParam) {
    }

    ASTnode* getFields() {
        return fDecls;
    }

    ASTnode* getMethods() {
        return mDecls;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* fDecls;
    ASTnode* mDecls;
};

class fieldDeclsASTnode : public ASTnode {
public:
    fieldDeclsASTnode() {
    }

    void push_back(ASTnode* fDeclParam) {
        fDecls.push_back(fDeclParam);
    }

    vector<ASTnode*> getFields() {
        return fDecls;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> fDecls;
};

class variableASTnode : public ASTnode {
public:
    variableASTnode(string varTypeParam, string nameParam) {
        varType = varTypeParam;
        name = nameParam;
    }
    
    variableASTnode(string varTypeParam, string nameParam, unsigned int arrLengthParam) {
        varType = varTypeParam;
        name = nameParam;
        arrLength = arrLengthParam;
    }

    string getVarType() {
        return varType;
    }

    string getDataType() {
        return dataType;
    }

    string getName() {
        return name;
    }

    unsigned int getLength() {
        return arrLength;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

    void setDataType(string dataTypeParam) {
        dataType = dataTypeParam;
    }

private:
    string varType;
    string dataType;
    string name;
    unsigned int arrLength;
};


class variablesASTnode : public ASTnode {
public:
    variablesASTnode() {
    }
    
    void push_back(variableASTnode* variable) {
        variables.push_back(variable);
    }

    vector<variableASTnode*> getVariables() {
        return variables;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<variableASTnode*> variables;
};

class fieldDeclASTnode : public ASTnode {
public:
    fieldDeclASTnode(string fTypeParam, variablesASTnode* variablesParam) {
        variables = variablesParam->getVariables();

        for(unsigned int i=0;i<variables.size();i++) {
            variables[i]->setDataType(fTypeParam);
        }
    }

    vector<variableASTnode*> getVariables() {
        return variables;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<variableASTnode*> variables;
};

class methodDeclsASTnode : public ASTnode {
public:
    methodDeclsASTnode() {
    }

    void push_back(ASTnode* methodDeclParam) {
        methodDecls.push_back(methodDeclParam);
    }

    vector<ASTnode*> getMethodsDecls() {
        return methodDecls;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> methodDecls;
};

class methodDeclASTnode : public ASTnode {
public:
    methodDeclASTnode(string type, string name, ASTnode* paramList, ASTnode* block)
    : type(type)
    , name(name)
    ,paramList(paramList)
    , block(block) {
    }


    string getType() {
        return type;
    }

    string getName() {
        return name;
    }

    ASTnode* getParamList() {
        return paramList;
    }

    ASTnode* getBlock() {
        return block;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    string type;
    string name;
    ASTnode* paramList;
    ASTnode* block;
};

class blockASTnode : public ASTnode {
public:
    blockASTnode(ASTnode* varDecls, ASTnode* stmts)
    : varDecls(varDecls)
    , stmts(stmts) {
    }

    ASTnode* getVarDecls() {
        return varDecls;
    }

    ASTnode* getStmts() {
        return stmts;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* varDecls;
    ASTnode* stmts;
};

class varDeclsASTnode : public ASTnode {
public:
    varDeclsASTnode() {
    }

    void push_back(ASTnode* varDecl) {
        varDecls.push_back(varDecl);
    }

    vector<ASTnode*> getVarDecls() {
        return varDecls;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> varDecls;
};

class varDeclASTnode : public ASTnode {
public:
    varDeclASTnode(string type, ASTnode* ids)
    : type(type)
    , ids(ids) {
    }

    string getType() {
        return type;
    }

    ASTnode* getIds() {
        return ids;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    string type;
    ASTnode* ids;
};

class idsASTnode : public ASTnode {
public:
    idsASTnode() {
    }

    void push_back(string id) {
        ids.push_back(id);
    }

    vector<string> getIds() {
        return ids;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<string> ids;
};

class stmtsASTnode : public ASTnode {
public:
    stmtsASTnode() {
    }

    void push_back(ASTnode* stmt) {
        stmts.push_back(stmt);
    }

    vector<ASTnode *> getStmts() {
        return stmts;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> stmts;
};

class stmtASTnode : public ASTnode {
public:
    stmtASTnode(ASTnode* stmt)
    :stmt(stmt) {
    }

    ASTnode* getStmt() {
        return stmt;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* stmt;
};

class assignASTnode : public ASTnode {
public:
    assignASTnode(ASTnode* location, string op, ASTnode* expr)
    : location(location)
    , op(op)
    , expr(expr) {
    }

    ASTnode* getLocation() {
        return location;
    }

    string getOp() {
        return op;
    }

    ASTnode* getExpr() {
        return expr;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* location;
    string op;
    ASTnode* expr;
};

class ifElseASTnode : public ASTnode {
public:
    ifElseASTnode(ASTnode* expr, ASTnode* ifblock, ASTnode* elseblock)
    : expr(expr)
    , ifblock(ifblock)
    , elseblock(elseblock) {
    }

    ASTnode* getExpr() {
        return expr;
    }

    ASTnode* getIfBlock() {
        return ifblock;
    }

    ASTnode* getElseBlock() {
        return elseblock;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* expr;
    ASTnode* ifblock;
    ASTnode* elseblock;
};

class forASTnode : public ASTnode {
public:
    forASTnode(string id, ASTnode* initCond, ASTnode* endCond, ASTnode* body)
    : id(id)
    , initCond(initCond)
    , endCond(endCond)
    , body(body) {
    }

    string getId() {
        return id;
    }

    ASTnode* getInitCond() {
        return initCond;
    }

    ASTnode* getEndCond() {
        return endCond;
    }

    ASTnode* getBody() {
        return body;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    string id;
    ASTnode* initCond;
    ASTnode* endCond;
    ASTnode* body;
};

class rtnStmtASTnode : public ASTnode {
public:
    rtnStmtASTnode(ASTnode* expr)
    :expr(expr) {
    }

    ASTnode* getExpr() {
        return expr;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* expr;
};

class breakStmtASTnode : public ASTnode {
public:
    breakStmtASTnode() {
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }
private:
};

class continueStmtASTnode : public ASTnode {
public:
    continueStmtASTnode() {
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }
private:
};

class methodCallASTnode : public ASTnode {
public:
    methodCallASTnode(string callType, string name, ASTnode* args)
    : callType(callType)
    , name(name)
    , args(args) {
    }

    string getCallType() {
        return callType;
    }

    string getName() {
        return name;
    }

    ASTnode* getArgs() {
        return args;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }
private:
    string callType;
    string name;
    ASTnode* args;
};

class callOutArgsASTnode : public ASTnode {
public:
    callOutArgsASTnode() {
    }

    void push_back(ASTnode* argsParam) {
        args.push_back(argsParam);
    }
    vector<ASTnode*> getArgs() {
        return args;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> args;
};

class exprListASTnode : public ASTnode {
public:
    exprListASTnode() {
    }

    void push_back(ASTnode* expr) {
        exprs.push_back(expr);
    }
    vector<ASTnode*> getExprs() {
        return exprs;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> exprs;
};

class locationASTnode : public ASTnode {
public:
    locationASTnode(string type, string id)
    : type(type)
    , id(id) {
    }

    locationASTnode(string type, string id, ASTnode* expr)
    : type(type)
    , id(id)
    , expr(expr) {
    }

    string getType() {
        return type;
    }

    string getId() {
        return id;
    }

    ASTnode* getExpr() {
        return expr;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    string type;
    string id;
    ASTnode* expr;
};

class paramListASTnode : public ASTnode {
public:
    paramListASTnode(ASTnode* paramList)
    :paramList(paramList) {
    }

    ASTnode* getParamList() {
        return paramList;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* paramList;
};

class parametersASTnode : public ASTnode {
public:
    parametersASTnode() {
    }

    void push_back(ASTnode* parameter) {
        parameters.push_back(parameter);
    }
    vector<ASTnode*> getParameters() {
        return parameters;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> parameters;
};

class parameterASTnode : public ASTnode {
public:
    parameterASTnode(string type,string name)
    :type(type)
    , name(name) {
    }

    string getType() {
        return type;
    }

    string getName() {
        return name;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    string type;
    string name;
};

class exprASTnode : public ASTnode {
public:
    exprASTnode(ASTnode* expr)
    :expr(expr) {
    }

    ASTnode* getExpr() {
        return expr;
    }    

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* expr;
};

class binaryASTnode : public ASTnode {
public:
    binaryASTnode (ASTnode* pLeftParm,
                    string binOperatorParm,
                    ASTnode* pRightParm)
    :pLeft(pLeftParm)
    ,mBinaryOperator(binOperatorParm)
    ,pRight(pRightParm) {
    }

    ASTnode* getLeft() {
        return pLeft;
    }

    ASTnode* getRight() {
        return pRight;
    }

    string getBinOperator() {
        return mBinaryOperator;
    }
    
    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    ASTnode* pLeft;
    string   mBinaryOperator;
    ASTnode* pRight;
};

class unaryASTnode : public ASTnode {
public:
    unaryASTnode (string op,ASTnode* expr)
    :op(op)
    ,expr(expr) {
    }

    string getOp() {
        return op;
    }

    ASTnode* getExpr() {
        return expr;
    }

    virtual void accept(ASTvisitor& v) {
      v.visit(*this);
    }

private:
    string op;
    ASTnode* expr;
};

class callArgASTnode : public ASTnode {
public:
    callArgASTnode (ASTnode* expr,string strArg)
    :expr(expr)
    , strArg(strArg) {
    }
    
    string getStrArg() {
        return strArg;
    }

    ASTnode* getExpr() {
        return expr;
    }

    virtual void accept(ASTvisitor& v) {
      v.visit(*this);
    }

private:
    ASTnode* expr;
    string strArg;
};

class literalASTnode: public ASTnode {
public:
    literalASTnode(string type,int intVal)
    : type(type)
    , intVal(intVal) {
    }

    literalASTnode(string type,string strVal)
    : type(type)
    , strVal(strVal) {
    }
    
    string getType() {
        return type;
    }

    string getStrVal() {
        return strVal;
    }

    int getIntVal() {
        return intVal;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }
    
private:
    string type;
    string strVal;
    int intVal;
};

class ASTContext {
public:
    ASTnode* pRoot;
    ~ASTContext() {
        clearAST();
    }

    // free all saved expression trees
    void clearAST() {
        delete pRoot;
    }
};

#endif /* End of AST_H */
