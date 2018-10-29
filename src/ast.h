
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
    methodDeclsASTnode(string t) {
        val = t;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    vector<ASTnode*> variables;
    string val;
};















class BinaryASTnode : public ASTnode {
public:
    BinaryASTnode (string binOperatorParm,
                   ASTnode* pLeftParm,
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


class TernaryASTnode : public ASTnode {
public:
    TernaryASTnode (ASTnode* pFirstParm,
                    ASTnode* pSecondParm,
                    ASTnode* pThirdParm)
    :pFirst(pFirstParm)
    ,pSecond(pSecondParm)
    ,pThird(pThirdParm) {
    }

    ASTnode* getFirst() {
        return pFirst;
    }

    ASTnode* getSecond() {
        return pSecond;
    }

    ASTnode* getThird() {
        return pThird;
    }

     virtual void accept(ASTvisitor& v) {
      v.visit(*this);
    }

private:
    ASTnode* pFirst;
    ASTnode* pSecond;
    ASTnode* pThird;
};


class IntLitASTnode: public ASTnode {
public:
	IntLitASTnode(int intlit)
    : intlit(intlit) {
    }

    int getIntLit() {
        return intlit;
    }

    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }
    
private:
	int intlit;
};

class AssignASTnode: public ASTnode {
public:
    AssignASTnode(string assignOpParam, string idParam, ASTnode* expParam)
    : assignOpParam(assignOpParam)
    , idParam(idParam)
    , expParam(expParam) {
    }

    string getOp() {
        return assignOpParam;
    }

    string getId() {
        return idParam;
    }

    ASTnode* getExpr() {
        return expParam;
    }
    virtual void accept(ASTvisitor& v) {
        v.visit(*this);
    }

private:
    string assignOpParam;
    string idParam;
    ASTnode* expParam;
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
