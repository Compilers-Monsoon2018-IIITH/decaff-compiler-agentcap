#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "ast.h"

class CodeGen: public CodeGenerator {
public:
	static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, const std::string &VarName, string type) {
		IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
		AllocaInst* Alloca;
		if(type == "int") Alloca = TmpB.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, VarName.c_str());
		else Alloca = TmpB.CreateAlloca(Type::getInt1Ty(getGlobalContext()), 0, VarName.c_str());
		return Alloca;
	}

	virtual Value* codegen(ProgramASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
		Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
		v = node.getBody()->codegen(*this,map_Oldvals);
		return v;
	}

    virtual Value* codegen(BodyASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
    	v = node.getFields()->codegen(*this,map_Oldvals);
    	v = node.getMethods()->codegen(*this,map_Oldvals);
    	return v;
    }

    virtual Value* codegen(fieldDeclsASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
        vector<ASTnode*> V = node.getFields();	
    	for(unsigned int i=0; i < V.size(); i++) {
    		v = V[i]->codegen(*this,map_Oldvals);
    	}
    	return v;
    }
    
    virtual Value* codegen(fieldDeclASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
        vector<variableASTnode*> V = node.getVariables();

        for(int i=0;i<V.size();i++) {
        	llvm::Type *type;
        	if(V[i]->getDataType() == "int") type = Type::getInt32Ty(Context);
        	else type = Type::getInt1Ty(Context);

        	if(V[i]->getVarType() == "Normal") {
				PointerType* ptr = PointerType::get(type,0);
      			GlobalVariable* gv = new GlobalVariable(*TheModule,ptr,false,GlobalValue::ExternalLinkage, 0, V[i]->getName());
        	}
        	else {
        		ArrayType* arrType = ArrayType::get(type,V[i]->getLength());
      			GlobalVariable* gv = new GlobalVariable(*TheModule,arrType,false,GlobalValue::ExternalLinkage,0,V[i]->getName());
      			gv->setInitializer(ConstantAggregateZero::get(arrType));
        	}

        }

    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); 
    	return v;
    }

    virtual Value* codegen(variableASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(variablesASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    
    virtual Value* codegen(methodDeclsASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
        vector<ASTnode*> methodDecls = node.getMethodsDecls();

    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); 
        for(int i=0;i<methodDecls.size();i++) {
        	v = methodDecls[i]->codegen(*this,map_Oldvals);
        }

    	return v;
    }

    virtual Function* codegen(methodDeclASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) {
    	paramListASTnode* param_list = dynamic_cast<paramListASTnode*>(node.getParamList());
    	parametersASTnode* params_list = dynamic_cast<parametersASTnode*>(param_list->getParamList());

    	vector<Type*> arguments;
    	vector<string> arg_names,arg_types;
    	if(params_list) {
    		vector<ASTnode*> params = params_list->getParameters();

    		for(int i=0;i<params.size();i++) {
    			parameterASTnode* param = dynamic_cast<parameterASTnode*>(params[i]);
    			if(param->getType()=="int") arguments.push_back(Type::getInt32Ty(getGlobalContext()));
    			else arguments.push_back(Type::getInt1Ty(getGlobalContext()));

    			arg_names.push_back(param->getName());
    			arg_types.push_back(param->getType());
    		}
    	}

    	Type* rtnType;
    	if(node.getType() == "int") rtnType = Type::getInt32Ty(getGlobalContext());
    	else if(node.getType() == "boolean") rtnType = Type::getInt1Ty(getGlobalContext());
    	else rtnType = Type::getVoidTy(getGlobalContext());

    	FunctionType *FT = llvm::FunctionType::get(rtnType, arguments, false);
		Function *F = llvm::Function::Create(FT, Function::ExternalLinkage, node.getName(), TheModule);

		unsigned idx = 0;
		for (Function::arg_iterator arg = F->arg_begin(); idx < arg_names.size(); ++arg, ++idx) {
			arg->setName(arg_names[idx]);
		}

		BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
		Builder.SetInsertPoint(BB);

		idx = 0;
		for (auto &Arg : F->args()) {
			if(idx == arg_names.size()) break;
			AllocaInst *Alloca = CreateEntryBlockAlloca(F, arg_names[idx],arg_types[idx]);
			Builder.CreateStore(&Arg, Alloca);
			NamedValues[arg_names[idx]] = Alloca;
			idx++;
		}


		Value *rtnVal = node.getBlock()->codegen(*this,map_Oldvals);
		///////////////////////////////////////Change this/////////////////////////////////
		if(true || rtnVal){
			if(node.getType() != "void") Builder.CreateRet(rtnVal);
			else Builder.CreateRetVoid();
			
			verifyFunction(*F);
			return F;
		}
		else {
			F->eraseFromParent();
			return 0;
		}
    }

    virtual Value* codegen(blockASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); 
		std::map<std::string,llvm::AllocaInst *> cur_vals;
		v = node.getVarDecls()->codegen(*this,cur_vals);
		v = node.getStmts()->codegen(*this,map_Oldvals);
		for(std::map<std::string,llvm::AllocaInst *>::iterator it = cur_vals.begin(); it != cur_vals.end();it++){
			NamedValues[it->first] = map_Oldvals[it->first];
		}
    	return v;
    }

    virtual Value* codegen(varDeclsASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) {
		Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
        vector<ASTnode*> varDecls = node.getVarDecls();

		for(int i=0;i<varDecls.size();i++) {
			varDecls[i]->codegen(*this,map_Oldvals);
		}
		return v;
	}

    virtual Value* codegen(varDeclASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); 
    	Function *TheFunction = Builder.GetInsertBlock()->getParent();

        idsASTnode* idsnode = dynamic_cast<idsASTnode*>(node.getIds());
        vector<string> ids = idsnode->getIds();
        string ids_type = node.getType();
    	for(int i=0;i<ids.size();i++) {
    		llvm::AllocaInst *Alloca;
    		Alloca = CreateEntryBlockAlloca(TheFunction,ids[i],ids_type);
    		Builder.CreateStore(ConstantInt::get(getGlobalContext(),APInt(32,0)),Alloca);

    		map_Oldvals[ids[i]] = NamedValues[ids[i]];
    		NamedValues[ids[i]] = Alloca;
    	}

    	return v;
    }
    virtual Value* codegen(idsASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(stmtsASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
        vector<ASTnode*> stmts = node.getStmts();

        for(int i=0;i<stmts.size();i++) {
        	v = stmts[i]->codegen(*this,map_Oldvals);
        }

    	return v;
    }

    virtual Value* codegen(stmtASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
    	v = node.getStmt()->codegen(*this,map_Oldvals);
    	return v;
    }

    virtual Value* codegen(assignASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { 
    	Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
    	locationASTnode* location = dynamic_cast<locationASTnode*>(node.getLocation());
    	
    	Value* var = NamedValues[location->getId()];
		if(var == 0){
			errors++;
			string msg = "Undefined Variable ";
			msg += location->getId();
			return reportError::ErrorV(msg);
		}

		Value* val = node.getExpr()->codegen(*this,map_Oldvals);
		if(val == 0){
			errors++;
			return reportError::ErrorV("Invalid Expression");
		}

		if(node.getOp() == "+=") val = Builder.CreateAdd(Builder.CreateLoad(var,location->getId()), val,"addEqualToTmp");
		else if(node.getOp() == "-=") val = Builder.CreateSub(Builder.CreateLoad(var,location->getId()), val,"subEqualToTmp");

		if(location->getType() == "Array") {
			Value* index = location->getExpr()->codegen(*this,map_Oldvals);
			    std::vector<llvm::Value *> args;
				args.push_back(Builder.getInt32(0));
				args.push_back(index);
				Value *cur = Builder.CreateGEP(cur, args, location->getId()+"_IDX"); 
		}

		return Builder.CreateStore(val, var);
	}

    virtual Value* codegen(ifElseASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(forASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(rtnStmtASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(breakStmtASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(continueStmtASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(methodCallASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(callOutArgsASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(exprListASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(locationASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(paramListASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(parametersASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(parameterASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(exprASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(binaryASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(unaryASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(callArgASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}
    virtual Value* codegen(literalASTnode& node,map<string,llvm::AllocaInst *>& map_Oldvals) { Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1)); return v;}


};


#endif /* CODEGENERATOR_H */