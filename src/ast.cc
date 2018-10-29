// $Id$

#include <iostream>
#include <fstream>
#include "driver.h"
#include "ast.h"
#include "PostFixVisitor.h"


int main()
{
    ASTContext ast;
    decaf::Driver driver(ast);
    PostFixVisitor pfv;
    
    string line;
    while( cout << "input: " &&
	   getline(cin, line) &&
	   !line.empty() )
    {
	    
	    bool result = driver.parse_string(line, "input");

	    if (result)
    	{
            if (ast.pRoot != NULL ) {
                BinaryASTnode *bnode;
                TernaryASTnode *tnode;
                IntLitASTnode *inode;
                AssignASTnode * anode;

                cout << "Postfix Form: " << endl; 

                bnode = dynamic_cast<BinaryASTnode *>(ast.pRoot);
                if (bnode != NULL)
                    pfv.visit(*bnode);

                tnode = dynamic_cast<TernaryASTnode *>(ast.pRoot);
                if (tnode != NULL)
                    pfv.visit(*tnode);

                inode = dynamic_cast<IntLitASTnode *>(ast.pRoot);
                if (inode != NULL)
                    pfv.visit(*inode);

                anode = dynamic_cast<AssignASTnode *>(ast.pRoot);
                if (anode != NULL)
                    pfv.visit(*anode);
                
                
                 cout <<  endl; 
            }
            ast.clearAST();
	    }
	}
}

