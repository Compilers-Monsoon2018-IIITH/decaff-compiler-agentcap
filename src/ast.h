
#ifndef AST_H
#define AST_H

#include <string>
using namespace std;

class BinaryASTnode;
class TernaryASTnode;
class IntLitASTnode;
class AssignASTnode;


class ASTvisitor
{
  public:
    virtual void visit(BinaryASTnode& node) = 0;
    virtual void visit(TernaryASTnode& node) = 0;
    virtual void visit(IntLitASTnode& node) = 0;
    virtual void visit(AssignASTnode& node) = 0;
};


class ASTnode
{
  public :
    virtual ~ASTnode()
    {
    }

    //  virtual void printPostFix() const = 0;
    virtual void accept(ASTvisitor& V) = 0;
};


class BinaryASTnode : public ASTnode
{
    public:
    // Constructor to initialize binary operator, 
    // left node and right node of the binary expression.
    BinaryASTnode (string binOperatorParm,
                   ASTnode* pLeftParm,
                   ASTnode* pRightParm)
    :pLeft(pLeftParm)
    ,pRight(pRightParm)
    ,mBinaryOperator(binOperatorParm)
    {
    }  

    /*  virtual void printPostFix() const 
    {
    	lhs->printPostFix();
    	rhs->printPostFix();
    	std::cout << bin_operator << " "; 
    } */

    ASTnode* getLeft()
    {
        return pLeft;
    }

    ASTnode* getRight()
    {
        return pRight;
    }

    string getBinOperator()
    {
        return mBinaryOperator;
    }
    
    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

  private:
    // left node and right node can be of any type. 
    // So we need to use Base ASTnode type
    ASTnode* pLeft;
    ASTnode* pRight;
    string   mBinaryOperator;
};


class TernaryASTnode : public ASTnode
{
    public:

    TernaryASTnode (ASTnode* pFirstParm,
                    ASTnode* pSecondParm,
                    ASTnode* pThirdParm)
    :pFirst(pFirstParm)
    ,pSecond(pSecondParm)
    ,pThird(pThirdParm)
    {
    }

    /*
    virtual void printPostFix() const
    {
     	first->printPostFix();
     	second->printPostFix();
     	third->printPostFix();
     	std::cout << "? " << std::endl; 
    }
    */

    ASTnode* getFirst()
    {
        return pFirst;
    }

    ASTnode* getSecond()
    {
        return pSecond;
    }

    ASTnode* getThird()
    {
        return pThird;
    }

     virtual void accept(ASTvisitor& v) 
    {
      v.visit(*this);
    }

  private:
    ASTnode* pFirst;
    ASTnode* pSecond;
    ASTnode* pThird;
};


class IntLitASTnode: public ASTnode
{
	public:
	IntLitASTnode(int intlit)
    : intlit(intlit)
    {
    }

    int getIntLit()
    {
        return intlit;
    }

    virtual void accept(ASTvisitor& v) 
    {
        v.visit(*this);
    }
    
	/*
    virtual void printPostFix() const
	{
		std::cout << intlit << " " ;
	}
    */

  private:
	int intlit;
};

class AssignASTnode: public ASTnode {
public:
    AssignASTnode(string assignOpParam, string idParam, ASTnode* expParam)
    : assignOpParam(assignOpParam)
    , idParam(idParam)
    , expParam(expParam)
    {
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
    virtual void accept(ASTvisitor& v) 
    {
        v.visit(*this);
    }

private:
    string assignOpParam;
    string idParam;
    ASTnode* expParam;
};

class ASTContext
{
  public:
    ASTnode* pRoot;
    ~ASTContext()
    {
	    clearAST();
    }

    // free all saved expression trees
    void clearAST()
    {
        delete pRoot;
    }
};

#endif /* End of AST_H */
