
#ifndef AST_H
#define AST_H

#include <string>
using namespace std;

class BinaryASTnode;
class TernaryASTnode;
class IntLitASTnode;
class AssignASTnode;
class ProgramASTnode;
class BodyASTnode;
class fieldDeclsASTnode;
class fieldDeclASTnode;
class variableASTnode;
class variablesASTnode;
class methodDeclsASTnode;


class ASTvisitor {
  public:
    virtual void visit(BinaryASTnode& node) = 0;
    virtual void visit(TernaryASTnode& node) = 0;
    virtual void visit(IntLitASTnode& node) = 0;
    virtual void visit(AssignASTnode& node) = 0;
    virtual void visit(ProgramASTnode& node) = 0;
    virtual void visit(BodyASTnode& node) = 0;
    virtual void visit(fieldDeclsASTnode& node) = 0;
    virtual void visit(fieldDeclASTnode& node) = 0;
    virtual void visit(variableASTnode& node) = 0;
    virtual void visit(variablesASTnode& node) = 0;
    virtual void visit(methodDeclsASTnode& node) = 0;
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

class fieldDeclASTnode : public ASTnode {
public:
    fieldDeclASTnode(string ftypeParam, ASTnode* variablesParam) {
        fType = ftypeParam;
        variables = variablesParam;
    }

    string getfType() {
        return fType;
    }

    ASTnode* getVariables() {
        return variables;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    string fType;
    ASTnode* variables;
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
    
    void push_back(ASTnode* variable) {
        variables.push_back(variable);
    }

    vector<ASTnode*> getVariables() {
        return variables;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> variables;
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
        return paramList
    }

    ASTnode* getblock() {
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

    vector<ASTnode*> getMethodsDecls() {
        return methodDecls;
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
    assignASTnode(ASTnode* expr, ASTnode* ifblock, ASTnode* elseblock)
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
    , initCond(initC)
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
        exprs.push_back(exp);
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
    ,pRight(pRightParm)
    ,mBinaryOperator(binOperatorParm) {
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
    ASTnode* pRight;
    string   mBinaryOperator;
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
    string strArg;
    ASTnode* expr;
};

class literalASTnode: public ASTnode {
public:
	literalASTnode(string type,int intVal)
    : intVal(intVal) {
    }

    literalASTnode(string type,string strVal)
    : strVal(strVal) {
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
