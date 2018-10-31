// $Id$

#include <iostream>
#include <fstream>
#include "driver.h"
#include "ast.h"
#include "PostFixVisitor.h"


int main() {
    ASTContext ast;
    decaf::Driver driver(ast);
    PostFixVisitor pfv;
    
    string fname;
    while( cout << "input Filename: " && getline(cin, fname) && !fname.empty() ) {
	    bool result = driver.parse_file(fname);

	    if (result) {
            if (ast.pRoot != NULL ) {
                cout << "AST:\n";
                ProgramASTnode * pnode;

                pnode = dynamic_cast<ProgramASTnode *>(ast.pRoot);
                if (pnode != NULL)
                    pfv.visit(*pnode);

            }
            ast.clearAST();
	    }
	}
}

