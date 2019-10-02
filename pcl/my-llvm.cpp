#include "my-llvm.hpp"
#include "my-ast.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <stack>

/* Inside Functions Installation */
void codegenLibs();
bool isLibFunction(string str);

/* Forward declarations */
llvm::Value* codegenOtherLocals(std::list<Local*> *locs);
llvm::Value* codegenHeader(Header* head);
llvm::Value* codegenBody(Body* bod,std::string name);
llvm::Value* codegenBlock(Block *bl);
llvm::Value* codegenStmt(Stmt* stmt);
llvm::Value* codegenRval(Rval *r);
llvm::Value* codegenLval(Lval *lval);
llvm::Value* codegenExpr(Expr* exp);
std::vector<llvm::Type* > fill_frame_fields(std::list<Local* >* locals);
std::list<llvm::Type* > getHeaderParam(Header*);
std::vector<llvm::Type* > myListmerge(std::vector<llvm::Type *> ,std::list<llvm::Type *> );
llvm::Value* givaPointertoArray(llvm::Value* lhs);
llvm::Value* args_Convert(llvm::Value* a , llvm::Value* b );
std::vector<llvm::Value *>  ready_params_for_call(std::list<Expr*> *exp_list,llvm::Function::arg_iterator arg_it);
llvm::Value* codegenExpr2(Expr* exp) ;
int Pointer_diff(llvm::Value* a , llvm::Value* b );
bool isPointertoVoid(llvm::Type* a);

/* Useful global variables */
static llvm::LLVMContext TheContext;//llvm engine
static llvm::IRBuilder<> Builder(TheContext);//o gtiaxtjs
static std::unique_ptr<llvm::Module> TheModule;// to xarti tou ftiaxth
static std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;

 
/* Useful LLVM types. */
static llvm::Type *i16 =  llvm::Type::getInt16Ty(TheContext);
static llvm::Type *i8 = llvm::IntegerType::get(TheContext, 8);
static llvm::Type *i32 = llvm::IntegerType::get(TheContext, 32);
static llvm::Type *i64 = llvm::IntegerType::get(TheContext, 64);
static llvm::Type *bo = llvm::IntegerType::getInt1Ty(TheContext);
static llvm::Type *re = llvm::Type::getX86_FP80Ty(TheContext);


/* Other usefull variables */
 llvm::StructType* old2 ;
llvm::StructType* currentFrame ;
llvm::AllocaInst*  currentAlloca;
std::string father = "";
std::list<llvm::Type* > param_holder ={};
std::stack <llvm::AllocaInst* > ret_holder ;
std::stack <llvm::BasicBlock* > bb_holder ;
std::stack <int> checker;
std::stack <llvm::BasicBlock*> RetConts;
bool array_flag = false ;
int size_of_arr =0 ;

// Useful LLVM helper functions.
 llvm::ConstantInt* c8(char c) {
  return llvm::ConstantInt::get(TheContext, llvm::APInt(8, c, true));
}
 llvm::ConstantInt* c32(int n) {
  return llvm::ConstantInt::get(TheContext, llvm::APInt(32, n, true));
}





/* Translates symb.table types
   to llvm types          */
llvm::Type *translate(Type a) {
    if (myequalType(a,typeReal,0))
        return llvm::Type::getX86_FP80Ty(TheContext);
    if (myequalType(a,typeBoolean,0))
        return llvm::Type::getInt1Ty(TheContext);
    if (myequalType(a, typeInteger,0))
        return llvm::Type::getInt16Ty(TheContext);
    if (myequalType(a, typeChar,0))
        return llvm::Type::getInt8Ty(TheContext);
    if (myequalType(a, typeVoid,0))
        return llvm::Type::getVoidTy(TheContext);
    if (isIArray(a)) {
        Type b = a->refType;
        llvm::Type *translatedRef = translate(b);
        return llvm::PointerType::get(translatedRef, 0);
    }
    if (isArray(a)) {
        Type b = a->refType;
        // llvm::Type *translatedRef = translate(b);
        vector<int> sizes;
        sizes.push_back(a->size);
        while (isArray(b)) {
            sizes.push_back(b->size);
            b = b->refType;
        }
        llvm::Type *result = translate(b);
        for (auto i : sizes) {
            // //cout << i << endl;
            result = llvm::ArrayType::get(result, i);
        }
        // return nullptr;
        return result;
    }

    if(a->TYPE_POINTER){
        Type b = a->refType;
        llvm::Type *translatedRef = translate(b);
        return llvm::PointerType::get(translatedRef, 0);
    }
    // If everything is good , it will never go in here 
    //cout << "Type that i dont know yet.Probably array or byref" << endl;
    printType(a);
    return llvm::Type::getVoidTy(TheContext);
    // exit(-1);
}


void compile(Program* prog){
    
    //kanw arxikoipoish tou module
    TheModule = llvm::make_unique<llvm::Module>("tomodulo", TheContext);
    TheModule->setTargetTriple("x86_64-pc-linux-gnu");
    
    // Create a new pass manager attached to it.
    TheFPM = llvm::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());
    //osa eixa me * einai auta pou prepei na exw
    TheFPM->add(llvm::createConstantPropagationPass());
    TheFPM->add(llvm::createConstantHoistingPass());
    TheFPM->add(llvm::createPromoteMemoryToRegisterPass());
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    TheFPM->add(llvm::createInstructionCombiningPass());
    // Reassociate expressions.
    TheFPM->add(llvm::createReassociatePass());
    // Eliminate Common SubExpressions.
    TheFPM->add(llvm::createGVNPass(true));
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    TheFPM->add(llvm::createCFGSimplificationPass());
    

    for (int i = 0; i < 10; ++i){
        TheFPM->add(llvm::createDeadCodeEliminationPass());
        TheFPM->add(llvm::createDeadInstEliminationPass());
        TheFPM->add(llvm::createAggressiveDCEPass());
    }


    TheFPM->doInitialization();


    codegenLibs();


    // Define and start the main function.
    llvm::Constant *c = TheModule->getOrInsertFunction("main", i32, NULL);
    llvm::Function* main = llvm::cast<llvm::Function>(c);
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);
    Builder.SetInsertPoint(BB);


    // Make of a basic AR--dummy struct
    currentFrame = llvm::StructType::create(TheContext,"dummy");

    // Emit the program code
    codegenBody( prog->body,"main");
   
    // For testing *
    Builder.CreateRet(c32(0));
   // Builder.CreateRet(c32(0));
    bool bad = verifyModule(*TheModule, &llvm::errs());
    if (bad) {
        fprintf(stderr, "The faulty IR is:\n");
        fprintf(stderr, "------------------------------------------------\n\n");
        TheModule->print(llvm::outs(), nullptr);
      return;
    }

   // cout<< "---------before the function pass manager ir-----------------" << endl ;
    
    
    // IR before opts
    TheModule->print(llvm::outs(), nullptr);
    
    
    //cout<<"----------------------------------------------------------------"<<endl;
    //cout<<"----------------------------------------------------------------"<<endl;
    //cout<<"----------------------------------------------------------------"<<endl;
    //cout<<"----------------------------------------------------------------"<<endl;
    // Optimizations 
    TheFPM->run(*main);
    // Print out the IR after FPM opts
   //* TheModule->print(llvm::outs(), nullptr);
    return;
}


// Gets *body , and string-name of function
llvm::Value* codegenBody(Body* bod,std::string name){


   
    // Keep the old-frame , because imma about to make a new one 
    llvm::AllocaInst* oldAlloca = currentAlloca;

    llvm::StructType* old = currentFrame;
    old2 = old ;
    // Frame to hold vars of function
    llvm::StructType* frame = TheModule->getTypeByName("struct." + std::string(name)+ "_" + father );
    
    if(!frame){
        // New struct in case its not defined
        frame = llvm::StructType::create(TheContext,"struct." + std::string(name)+"_" + father);
    }

    currentFrame = frame ;
    
    // In case struct has no fields/vars yet 
    if(currentFrame->isOpaque()){
        
        // Fill frame with its vars and old frame
        auto frame_fields = fill_frame_fields(bod->locals); 
       
        //cout<< "HEy here the name of func "<< name << endl ;
        // Need to push params if exist
        frame_fields = myListmerge(frame_fields,param_holder);
       
        auto iterator = frame_fields.begin();
        // This is needed  for nested things ;)
        
        //auto tmp = Builder.CreateAlloca(old);
       // Builder.CreateStore(old,tmp);
        if(name.compare("main") == 0) {
            frame_fields.insert(iterator,llvm::PointerType::get(frame,0));}
        else
        frame_fields.insert(iterator,llvm::PointerType::get(old,0));
        
        currentFrame->setBody(frame_fields); 
    }
    //cout << currentFrame->getNumElements() << endl ;
    //cout<< "to panw  current frame nums" << endl ;
   


    currentAlloca = Builder.CreateAlloca(currentFrame,0,"");
    
    
  //  if((name.compare("main"))!=0 ) {
        
    //    llvm::Value* first45[]={c32(0) , c32(0)};
      //  auto yoga = Builder.CreateGEP(currentAlloca,first45,"");
    
    //yoga = Builder.CreateLoad(yoga) ;
   // auto yoga2 = Builder.CreateLoad(oldAlloca);
   // Builder.CreateStore(oldAlloca,yoga);
   // }



    int strct_size = currentFrame->getNumContainedTypes();
    int p_hol = param_holder.size() ;
    int gep_offset = strct_size - p_hol  ;


    if (std::string(name).compare("main") == 0 ){
        std::vector<llvm::Value *> values432;
        llvm::APInt zero24(32, 0);
        //llvm::APInt offset2(32, j);
        values432.push_back(llvm::Constant::getIntegerValue(
            llvm::Type::getInt32Ty(TheContext), zero24));
        values432.push_back(llvm::Constant::getIntegerValue(
            llvm::Type::getInt32Ty(TheContext), zero24));

        auto gep42 = Builder.CreateGEP(currentAlloca, values432, "");
        
        Builder.CreateStore(currentAlloca,gep42 );
    }


    if( !(std::string(name).compare("main") == 0 )  ) {

        llvm::Function *fun = TheModule->getFunction(std::string(name)+ "_" + father );
        if(fun == nullptr){ error("Something weird here") ;  }
        llvm::Function::arg_iterator arg_it = fun->arg_begin();
        llvm::Value *current;


        std::vector<llvm::Value *> values23;
        llvm::APInt zero2(32, 0);
        //llvm::APInt offset2(32, j);
        values23.push_back(llvm::Constant::getIntegerValue(
            llvm::Type::getInt32Ty(TheContext), zero2));
        values23.push_back(llvm::Constant::getIntegerValue(
            llvm::Type::getInt32Ty(TheContext), zero2));
        auto gep = Builder.CreateGEP(currentAlloca, values23, "");
        current = &(*arg_it);
        Builder.CreateStore(current, gep);
        arg_it++ ;

        


        for (int j = 1; j < p_hol + 1; ++j, ++arg_it) {
        std::vector<llvm::Value *> values;
        llvm::APInt zero(32, 0);
        llvm::APInt offset(32, j);
        values.push_back(llvm::Constant::getIntegerValue(
            llvm::Type::getInt32Ty(TheContext), zero));
        values.push_back(llvm::Constant::getIntegerValue(
            llvm::Type::getInt32Ty(TheContext), offset));
        auto gep = Builder.CreateGEP(currentAlloca, values, "");
        current = &(*arg_it);
        Builder.CreateStore(current, gep);
        }
    }
     // Handle other cases:headers,labels
    //cout <<"----LOCALS SIZE-----"<< endl;
    //cout << bod->locals->size()<< endl;
    //cout <<"-------------------"<< endl;
    codegenOtherLocals(bod->locals);
    codegenBlock(bod->block);

    currentFrame = old ;
    currentAlloca = oldAlloca;


    return nullptr;
}

// TO-DO --Handles locals into frame,only vars and labels
std::vector<llvm::Type* > fill_frame_fields(std::list<Local* >* locals){ 
    
    // Frame = AR
    std::vector<llvm::Type* > frame_fields;

    // Fill frame fields with the var types
    for( auto i : *locals){
        if(i == NULL) return {} ;
      //  if(i == NULL) return frame_fields ;
        switch(i->loc_type){
            case var :
                for(auto z : *i->ids){
                   frame_fields.push_back(translate(i->type));
                }
                break ;
            // I belive i dont need it    
            case label :
                for(auto z : *i->ids){ 
                    frame_fields.push_back(llvm::Type::getInt1Ty(TheContext));
                }
                break;
            default :
                break ;

        }
    }
    return frame_fields;
}



// Handles ,headers,forward
llvm::Value* codegenOtherLocals(std::list<Local*>* locals){
   
    if(locals == NULL) return nullptr ;
    for( auto i : *locals){
       
        switch(i->loc_type){
            case header : {
            
                // Must have have here - so each local know its own
                llvm::AllocaInst*  retAlloca;
   
                //   auto fun = Builder.GetInsertBlock()->getParent();    
               // RetConts.push( llvm::BasicBlock::Create(TheContext,"",fun));
    

                // Codegen of Header
                codegenHeader(i->header);
                // Keep it for name mangling
                father = i->header->parent;
                // Must keep params for frame 
                param_holder = getHeaderParam(i->header);
                
                // Get Now block and Function
                auto currentBlock = Builder.GetInsertBlock() ;
                llvm::Function *function = TheModule->getFunction(i->header->id->id +"_"+i->header->parent );
                if(!function ){
                    error("something wrong HERE!!");
                }
                
              

                // Create new block -to write for the about to come function
                llvm::BasicBlock* bb = llvm::BasicBlock::Create(TheContext,"",function);      
                Builder.SetInsertPoint(bb);
                

                // New-block for the Ret part--Neeeded to be taken after the bb
                // to become the second.
                RetConts.push( llvm::BasicBlock::Create(TheContext,"",function));


                // this is for the return type
                if(myequalType(i->header->type,typeVoid,0)){
                    retAlloca=nullptr;
                }
                else{
                    retAlloca=Builder.CreateAlloca(translate(i->header->type),0,"");
                }
                
                // Keep needded things in stack
            //    bb_holder.push(currentBlock);
                ret_holder.push(retAlloca);
            //    checker.push(1);
                
              
                
                codegenBody(i->body,i->header->id->id);
                

                // Return block
                // RetCont = llvm::BasicBlock::Create(TheContext,"",function); 
                
                // POP it
                //bb_holder.pop();
                //ret_holder.pop();
                
                Builder.CreateBr(RetConts.top());
                Builder.SetInsertPoint(RetConts.top());


                // Now in case of previous return not 
                llvm::Value* retval ;

                if(ret_holder.top() != nullptr ){
        
                    retval = Builder.CreateLoad(ret_holder.top(),"");
                }
                else{
                    retval = nullptr ;
                }
                
               // ret_holder.pop();
            
            
            //    Builder.CreateBr(RetConts.top());
            //    Builder.SetInsertPoint(RetConts.top());
                // Create ret
                 Builder.CreateRet(retval);
               // Builder.CreateRet(ret_holder.top());

                RetConts.pop();
                ret_holder.pop();

                Builder.SetInsertPoint(currentBlock);
            


                break ;
            }
            case forwad:
                codegenHeader(i->header);
                father = i->header->parent;
                param_holder = getHeaderParam(i->header);
                
                
                break;
            // shoudent be here
           // case label:
                // Must create Label to put in frame
             //   for(auto z : *i->ids){
               //     llvm::Type::getLabelTy(TheContext);
               // }
               // break ;
            default:
                break;
        }
    }
    // Whatev
        return nullptr;

}

// Function and Procedures with thei params
llvm::Value* codegenHeader(Header* header ){
    if(header == NULL) return nullptr ;
  
    if(isLibFunction(header->id->id)){
        error("cant declare libfunction");
    }

    /*  Local Variables */
    llvm::Type* resultType ;
    std::vector<llvm::Type* > params = {} ;

    // Takes care of result type of header
    switch(header->kind){
        case procedure:
            resultType = llvm::Type::getVoidTy(TheContext);
            break;
        case 0: // case function
            resultType = translate(header->type);
            break ;
        default : 
            //cout<< "sHITTTTTTTT MAN" << endl;
            error("something wrong heeere");
    }

   // params.push_back(llvm::PointerType::get(old2,0));
     params.push_back(llvm::PointerType::get(currentFrame,0));
    // Takes care of ids in formals
   // //cout<< "------List size of formals------------"<<endl;
   // //cout<< header->formals->size() << endl ;
    if(header->formals){
        for(auto i : *header->formals){
                switch(i->kind){
                    case value:
                        for (int z =0 ; z < i->ids->size(); z++){
                            params.push_back(translate(i->type));
                        }
                        break;
                    case refernce: 
                        for (int z =0 ; z < i->ids->size(); z++){
                             if(isArray(i->type) || isIArray(i->type) ){
                                params.push_back( translate(i->type)); 
                            }
                            else
                            params.push_back(llvm::PointerType::get( translate(i->type),0));
                        }
                        break;
                    default :
                        //cout<<"my fault" << endl ;
                        error("again internal here");

                }
        }
    }
    // Declare chapter-type imma abou to make
    auto *ftype = llvm::FunctionType::get(resultType,params,false);

    // Grab the function/chapter
    llvm::Function *function = TheModule->getFunction(header->id->id +"_"+header->parent );

    if(function == NULL){
        function = llvm::Function::Create(
            /*Type=*/ftype,
            /*Linkage=*/llvm::GlobalValue::ExternalLinkage,
            /*Name=*/header->id->id +"_" + header->parent, TheModule.get());
    }
    // TODO : I DONT KNOW FROM HERE ON HOW IT GOES..edw eixa meini

    //will grab function
 //   llvm::BasicBlock* funcBB = llvm::BasicBlock::Create(TheContext,header->id->id + "_" + header->parent,function);
 //  auto RetCont = llvm::BasicBlock::Create(TheContext, "", function);
  //  Builder.SetInsertPoint(funcBB);

    return nullptr;
}



// todos
llvm::Value* codegenBlock(Block *bl){
    codegenStmt(bl->stmt);
    for(auto i : *bl->stmts){
        codegenStmt(i);
    }
    return nullptr;
}

// TO-DO
llvm::Value* codegenStmt(Stmt* stmt){
    if(stmt == NULL) return nullptr;
    switch(stmt->kind){
       
        case tlva:{
            auto lhs = codegenLval(stmt->lval);
            auto rhs = codegenExpr(stmt->expr);
            if(rhs->getType()->isPointerTy() && rhs->getType()->getPointerElementType()->isVoidTy()){
                Builder.CreateStore(llvm::Constant::getNullValue(lhs->getType()->getPointerElementType()),lhs);
               // cout << "yoyohkghkghkgyoyoyo" <<endl ;
                break;
            }

 /* thats prbably bullshit
            // giati mporei na einai a[1] kai na einai array alla oxi ta alla
           if(array_flag == true  && lhs->getType()->isPointerTy()  &&  lhs->getType()->getPointerElementType()->isPointerTy()){
                array_flag = false ;
                llvm::Value* a   ;
                llvm::Value* b ;
                
                //gg is a helper to get pointer to pointer
//                auto gg = Builder.CreateAlloca(rhs->getType(),0,"");
//                Builder.CreateStore(rhs,gg);
//                if(lhs->getType()->isPointerTy()  &&  lhs->getType()->getPointerElementType()->isPointerTy()) cout << "gfsagsgagsad";
 //               auto gg2= Builder.CreateLoad(lhs,"");
                //gg2= Builder.CreateLoad(lhs,"");
                lhs = Builder.CreateLoad(lhs,"");
                for(int i=0 ; i < size_of_arr ;i++){
                  //  a = Builder.CreateGEP(gg2,c32(i),"");
                    //b = Builder.CreateGEP(gg,c32(i),"");
                    a = Builder.CreateGEP(lhs,c32(i),"");
                    b = Builder.CreateGEP(rhs,c32(i),"");
                    b = Builder.CreateLoad(b);
                   // a = Builder.CreateLoad(a);
                   // b = Builder.CreateLoad(b);
                    Builder.CreateStore(b,a);
                }
                break;
            }
*/
            array_flag = false ;

            if(rhs->getType()->isIntegerTy() && lhs->getType()->getPointerElementType()
            ->isX86_FP80Ty() )
                rhs = Builder.CreateSIToFP(rhs,re);

            Builder.CreateStore(rhs,lhs);
            break ;
        }
      
        case tid:{
            llvm::Function* TheFunction = Builder.GetInsertBlock()->getParent();
         

            bool flag = false ;

            auto currentB = Builder.GetInsertBlock();
            
            auto begin = TheFunction->begin();
            auto end = TheFunction->end();
            
            llvm::Function::iterator iter = begin ;

            // Somehow iterator of function converts to basic block
            for( iter  ; iter != end ; iter ++){
            
                llvm::BasicBlock* BB= &*iter;
            
                if((BB->getName().str().compare(stmt->b->id)) == 0) {

                    flag = true ;
                     Builder.CreateBr(BB);
                    Builder.SetInsertPoint(BB);
                    codegenStmt(stmt->stmt1);

                }


            }

            
            if(!flag){
                llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, stmt->b->id,TheFunction);
                Builder.CreateBr(BB);
                Builder.SetInsertPoint(BB);
                codegenStmt(stmt->stmt1);


            }

        //    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, stmt->b->id,TheFunction);
        //    Builder.CreateBr(BB);


//            Builder.SetInsertPoint(BB);
//            codegenStmt(stmt->stmt1);
            //cout<< "------------------------------------------------" << endl ;
            //cout<< "-----------------------------------------------" << endl ;
            //cout <<"The BlockList size : " << TheFunction->getBasicBlockList().size();
            break;
        }
      
        case tgoto:{
            llvm::Function* TheFunction = Builder.GetInsertBlock()->getParent();
            bool flag = false ;

            auto begin = TheFunction->begin();
            auto end = TheFunction->end();
            
            llvm::Function::iterator iter = begin ;

            // Somehow iterator of function converts to basic block
            for( iter  ; iter != end ; iter ++){
                // Everything else didnt compile for a
                // reason ???
                llvm::BasicBlock* BB= &*iter;
               // auto j = &BB;
               if((BB->getName().str().compare(stmt->b->id)) == 0) {
                    flag = true ;
                    Builder.CreateBr(BB);
                    //llvm::BasicBlock* BB2 = llvm::BasicBlock::Create(TheContext,"",TheFunction);
                   // Builder.SetInsertPoint(BB2);
                    break ;    
                }
                

       
            }


if(!flag)    {
            
            auto CrBlock = llvm::BasicBlock::Create(TheContext,stmt->b->id,TheFunction);
            Builder.CreateBr(CrBlock);
            //llvm::BasicBlock* BB3 = llvm::BasicBlock::Create(TheContext,"",TheFunction);
            //Builder.SetInsertPoint(BB3);

        } 

        
            

            break;
        }

        // Call 
        case tcall :{

            // Needed for builder-call func
            std::vector<llvm::Value *> params;


            if (isLibFunction(stmt->call->id->id)) {
                // std:://cout << "I have found a lib function" << std::endl;
                llvm::Function *CalleeF = TheModule->getFunction(stmt->call->id->id);
                llvm::Function::arg_iterator arg_it = CalleeF->arg_begin();
                if (CalleeF == NULL) {
                    cerr << stmt->call->id->id << "No such function";
                    exit(1);
                }

                 // Now do the params
                auto exp_list = stmt->call->e;

                if(stmt->call->id->id.compare( "readString") == 0){
                    //reverse(params.begin(),params.end());
                    exp_list->reverse();
                }

                params = ready_params_for_call(exp_list,arg_it);


                /*
                llvm::Value *curr_arg = &(*arg_it);


                // Codegen-Give values to call-params
                for(auto i : *exp_list){
                    params.push_back(codegenExpr(i));
                }
                */
                // Make the call
              /*  if(stmt->call->id->id.compare( "readString") == 0){
                    reverse(params.begin(),params.end());
                } */
                Builder.CreateCall(CalleeF, params, "");

                break;

            }


            
            // Get function         
        llvm::Function* func = TheModule->getFunction(stmt->call->id->id +"_"+stmt
                ->call->parent );
            
        llvm::Function::arg_iterator arg_it = func->arg_begin();


            //cout<<"----Function search is ---"<<stmt->call->id->id + "_" +stmt
            //->call->parent <<endl;
           
        if (!func){
            error("couldnt find function");
        }

         
            // Now do the params
        arg_it++ ;
        auto exp_list = stmt->call->e;

        params = ready_params_for_call(exp_list,arg_it);


        llvm::Value* link;         
        llvm::Value* fatherStruct = currentAlloca;
        int z = stmt->call->nd;

        // First element
        llvm::Value* first[]={c32(0) , c32(0)};
        while(z>0){
            // Get pointer to old-Frame
            link = Builder.CreateGEP(fatherStruct,first,"");
            fatherStruct = Builder.CreateLoad(link,"");
            z--;
        }
        
              //  auto val = Builder.CreateGEP(currentAlloca,values23);

            //    val =Builder.CreateLoad(val);

             params.insert(params.begin(),fatherStruct); 
               // params.insert(params.begin(),val);
            
        
            // Make the call
        Builder.CreateCall(func, params, "");

        break;
    }


        case treturn:{
            // Again take care of return
            llvm::Value* retval ;
          
            //ret alloca here was pointless
          //  auto retAlloca = ret_holder.top();
                
           // if( retAlloca != nullptr ){
            //    retval = Builder.CreateLoad(retAlloca,"");
           // }

          //  else{
          //      retval = nullptr ;
          //  }
            
            auto fun = Builder.GetInsertBlock()->getParent();    
            auto newBB = llvm::BasicBlock::Create(TheContext,"paok",fun);
            //RetCont = llvm::BasicBlock::Create(TheContext,"",fun);

            //
            Builder.CreateBr(RetConts.top());
            Builder.SetInsertPoint(newBB);


            break;
        }

        case tif: {
            // Must have to cases here --one for if then
            // one for if-then-else
                if(stmt->stmt2 != nullptr){

                    auto expr = codegenExpr(stmt->expr) ;
                    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
                    //auto yo = Builder.CreateLoad(expr);
                    llvm::Value *CondV = Builder.CreateICmpEQ( expr, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 1, true));
                    
                    llvm::BasicBlock *ThenBB =  llvm::BasicBlock::Create(TheContext, "then", TheFunction);
                    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else");    
                    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(TheContext, "ifcont");

                    Builder.CreateCondBr(CondV, ThenBB, ElseBB);

                    Builder.SetInsertPoint(ThenBB);

                    auto ThenV  = codegenStmt(stmt->stmt1);

                    Builder.CreateBr(MergeBB);
                    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
                    ThenBB = Builder.GetInsertBlock();


                    // Emit else block.
                    TheFunction->getBasicBlockList().push_back(ElseBB);
                    Builder.SetInsertPoint(ElseBB);

                    auto ElseV = codegenStmt(stmt->stmt2);
                    
                    Builder.CreateBr(MergeBB);
                    // codegen of 'Else' can change the current block, update ElseBB for the PHI.
                    ElseBB = Builder.GetInsertBlock();

                    // Emit merge block.
                    TheFunction->getBasicBlockList().push_back(MergeBB);
                    Builder.SetInsertPoint(MergeBB);
                    //llvm::PHINode *PN = Builder.CreatePHI((llvm::Type::getInt1Ty(TheContext)), 2, "iftmp");

                    //PN->addIncoming(ThenV, ThenBB);
                    //PN->addIncoming(ElseV, ElseBB);
                    //return PN;
                    return nullptr;
                }
                else{
                    auto expr = codegenExpr(stmt->expr) ;
                    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
                    //auto yo = Builder.CreateLoad(expr);
                    llvm::Value *CondV = Builder.CreateICmpEQ( expr, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 1, true));
                    
                    llvm::BasicBlock *ThenBB =  llvm::BasicBlock::Create(TheContext, "then", TheFunction);
                    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "pseudoelse");    
                    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(TheContext, "ifcont");

                    Builder.CreateCondBr(CondV, ThenBB, ElseBB);

                    Builder.SetInsertPoint(ThenBB);

                    auto ThenV  = codegenStmt(stmt->stmt1);

                    Builder.CreateBr(MergeBB);
                    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
                    ThenBB = Builder.GetInsertBlock();


                    // Emit else block.
                    TheFunction->getBasicBlockList().push_back(ElseBB);
                    Builder.SetInsertPoint(ElseBB);

                    //auto ElseV = codegenStmt(stmt->stmt2);
                    
                    Builder.CreateBr(MergeBB);
                    // codegen of 'Else' can change the current block, update ElseBB for the PHI.
                    ElseBB = Builder.GetInsertBlock();

                    // Emit merge block.
                    TheFunction->getBasicBlockList().push_back(MergeBB);
                    Builder.SetInsertPoint(MergeBB);
                    //llvm::PHINode *PN = Builder.CreatePHI((llvm::Type::getInt1Ty(TheContext)), 2, "iftmp");

                    //PN->addIncoming(ThenV, ThenBB);
                    //PN->addIncoming(ElseV, ElseBB);
                    //return PN;
                    return nullptr;
                }

                break;
        } 

        case twhile :{
                   
                    auto expr = codegenExpr(stmt->expr) ;
                    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
                    //auto yo = Builder.CreateLoad(expr);
                    llvm::Value *CondV = Builder.CreateICmpEQ( expr, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 1, true));
                    
                    llvm::BasicBlock *LoopBB =  llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
                    llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "after");    
                    

                    Builder.CreateCondBr(CondV, LoopBB, AfterBB);
                    Builder.SetInsertPoint(LoopBB);

                    auto ThenV  = codegenStmt(stmt->stmt1);
                    auto nextCond = codegenExpr(stmt->expr);


                   // nextCond = Builder.CreateICmpEQ(nextCond, c32(1));
                   // nextCond = Builder.CreateICmpEQ( expr, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 1, true));
                    nextCond = Builder.CreateICmpEQ( nextCond, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 1, true));
                    Builder.CreateCondBr(nextCond, LoopBB, AfterBB);


                    //Builder.CreateBr(MergeBB);
                    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
                    //ThenBB = Builder.GetInsertBlock();


                    // Emit else block.
                    TheFunction->getBasicBlockList().push_back(AfterBB);
                    Builder.SetInsertPoint(AfterBB);

                    //auto ElseV = codegenStmt(stmt->stmt2);
                    
                   // Builder.CreateBr(MergeBB);
                    // codegen of 'Else' can change the current block, update ElseBB for the PHI.
                    //ElseBB = Builder.GetInsertBlock();

                    // Emit merge block.
                    //TheFunction->getBasicBlockList().push_back(MergeBB);
                    //Builder.SetInsertPoint(MergeBB);
                    //llvm::PHINode *PN = Builder.CreatePHI((llvm::Type::getInt1Ty(TheContext)), 2, "iftmp");

                    //PN->addIncoming(ThenV, ThenBB);
                    //PN->addIncoming(ElseV, ElseBB);
                    //return PN;
                    return nullptr;

        
        
        
            break;
        }

        case tnew :{
            llvm::Value* new_stuff ;
            llvm::Value* lv =  codegenLval(stmt->lval);
            auto lv2 = Builder.CreateLoad(lv,"");
            if(auto check =llvm::dyn_cast<llvm::PointerType>(lv2->getType())){
               
                new_stuff=Builder.CreateAlloca( check->getPointerElementType(),0,"");
             
                Builder.CreateStore(new_stuff,lv);
           
            }
            else
                error("i messed up here");
            break;
        }

        case tnew_ex:{
            auto exp = codegenExpr(stmt->expr);
            llvm::Value* new_stuff ;

            llvm::Value* lv =  codegenLval(stmt->lval);
            // edw einai pointer se 
            auto lv2 = Builder.CreateLoad(lv,"");
            
           // auto lv3 = Builder.CreateLoad(lv2,"");
           // auto lv4 = Builder.CreateLoad(lv3,"");
            if(auto check =llvm::dyn_cast<llvm::PointerType>(lv2->getType())){
                new_stuff=Builder.CreateAlloca( lv2->getType()->getPointerElementType(),0,"");
                //auto new_stuff2 = Builder.CreateAlloca(lv2->getType()->getPointerElementType()->getPointerElementType(),exp,"");


                llvm::Value* yo =  Builder.CreateAlloca(lv2->getType()->getPointerElementType()->getPointerElementType(),exp,"");
                Builder.CreateStore(yo,new_stuff);
                //llvm::Value* first[]={c32(0) , c32(0)};


               // Builder.CreateGEP(yo,first,"");
                //auto new_stuff3 = Builder.CreateGEP(new_stuff2,0,"") ;

                //Builder.CreateStore(new_stuff2,lv2);
                Builder.CreateStore(new_stuff,lv);
               
                //Builder.CreateStore(new_stuff,lv);
            }
            else
                ////cout <<"I MESSSED UP HERE " << endl ;
                error("i messed up heeere");
            break;
        }    

        case tdispose:{
            auto lv = codegenLval(stmt->lval);
            auto lv2 = Builder.CreateLoad(lv,"");

            Builder.CreateStore(llvm::Constant::getNullValue(lv2->getType()),lv);
            break;
        }
        
        case tdispose_ar:{
            auto lv = codegenLval(stmt->lval);
            auto lv2 = Builder.CreateLoad(lv,"");

            Builder.CreateStore(llvm::Constant::getNullValue(lv2->getType()),lv);
            break;

        }
        //to do
        case tblock:{
            codegenStmt(stmt->block->stmt);
            for(auto i : *stmt->block->stmts){
                codegenStmt(i);
            }
            break ;
        }

        default:
            //cout<< "something went wrong " << endl ;
            error("something wrong here");
    }

    return nullptr;
}

//TODO
llvm::Value* codegenRval(Rval *r){
    if(r == NULL) return nullptr;
    switch(r->kind){
        case tint_r:
            return llvm::ConstantInt::get(TheContext, llvm::APInt(16,r->integer , true));
            break;

        case tbool_r:
            if(r->boolean == 't')
                return llvm::ConstantInt::get(TheContext,llvm::APInt(1,1,true));
                
            if(r->boolean =='f')
                return llvm::ConstantInt::get(TheContext,llvm::APInt(1,0,true));
            break;
            /* an error would be nice */
        //to-do
        case treal_r:
                return llvm::ConstantFP::get(llvm::Type::getX86_FP80Ty(TheContext),r->flot); //llvm::ConstantFP::get(TheContext,llvm::APFloat(r->flot));
                break;
        //kai oi chars einai integer ousiastika
        case tchar_r:
                return llvm::ConstantInt::get(TheContext,llvm::APInt(8,char(r->cho)));
                break;
        case trval_r:
                return codegenRval(r->rval1);
                break;
        //TO-DO
        
        case tcall_r:{
            // Needed for builder-call func
//            std::vector<llvm::Value *> params;


             std::vector<llvm::Value *> params;


            if (isLibFunction(r->call->id->id)) {
                // std:://cout << "I have found a lib function" << std::endl;
                llvm::Function *CalleeF = TheModule->getFunction(r->call->id->id);
                llvm::Function::arg_iterator arg_it = CalleeF->arg_begin();
                if (CalleeF == NULL) {
                    cerr << r->call->id->id << "No such function";
                    exit(1);
                }
                

                


                 // Now do the params
                auto exp_list = r->call->e;
            

                   if(r->call->id->id.compare( "readString") == 0){
                    //reverse(params.begin(),params.end());
                    exp_list->reverse();
                }


                params = ready_params_for_call(exp_list,arg_it);
                /*
                llvm::Value *curr_arg = &(*arg_it);

                // Codegen-Give values to call-params
                for(auto i : *exp_list){
                    params.push_back(codegenExpr(i));
                    arg_it++;
                }
                */
                // Make the call
              /*   if(r->call->id->id.compare("readString") == 0){
                    reverse(params.begin(),params.end());
                }
                */
                return Builder.CreateCall(CalleeF, params, "");

                break;

            }







            // Get function         
            llvm::Function* func = TheModule->getFunction(r->call->id->id +"_"+ r
            ->call->parent );
            
            llvm::Function::arg_iterator arg_it = func->arg_begin();



            //cout<<"----Function search is ---"<<r->call->id->id + "_" +r
            //->call->parent <<endl;
           
            if (!func){
               error("couldnt find function");
            }

            
            arg_it++;
            // Now do the params
            auto exp_list = r->call->e;
            
            params = ready_params_for_call(exp_list,arg_it);

           // cout << r->call->parent<< endl;
          //  cout<<"i did it " << endl ;
        


            llvm::Value* link;         
            llvm::Value* fatherStruct = currentAlloca;
            int z = r->call->nd;

            // First element
            llvm::Value* first[]={c32(0) , c32(0)};
            while(z>0){
                // Get pointer to old-Frame
                link = Builder.CreateGEP(fatherStruct,first,"");
                fatherStruct = Builder.CreateLoad(link,"");
                z--;
            }
            
                
            
              //  auto val = Builder.CreateGEP(currentAlloca,values23);
              //  val = Builder.CreateLoad(val);

             params.insert(params.begin(),fatherStruct); 
              //  params.insert(params.begin(),val);
        
            /*
            llvm::Value *curr_arg = &(*arg_it);


            // Codegen-Give values to call-params
            for(auto i : *exp_list){
                params.push_back(codegenExpr(i));
            }
            */
            // Make the call
            return Builder.CreateCall(func, params, "");

             break;
        }

        case tnill_r:{
            return llvm::ConstantPointerNull::get(llvm::PointerType::get(llvm::Type::getVoidTy(TheContext),0));
        }
        
        case tderfe_r:{
           auto lva = codegenLval(r->lval1);
           return lva ;
        }

        case tnot_r:{
            auto exp = codegenExpr(r->expr1);
            return Builder.CreateNot(exp,"");
        }

        case tuminus_r:{
            auto exp = codegenExpr(r->expr1);
            if(r->expr1->type == typeInteger )
                return Builder.CreateNeg(exp,"");
            else return Builder.CreateFNeg(exp,"");
        }
     
        case tuplus_r:{
            auto exp = codegenExpr(r->expr1);
            return exp;
        }

        case tplus_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);

            if( exp->getType()->isIntegerTy() && exp2->getType()->isIntegerTy() ){
                return Builder.CreateAdd(exp,exp2);
            }
            if (exp->getType()->isIntegerTy() ) {
                exp = Builder.CreateSIToFP(exp,re) ;
            }
            if (exp2->getType()->isIntegerTy() ) {
                exp2 = Builder.CreateSIToFP(exp2,re) ;
            }


            return Builder.CreateFAdd(exp,exp2);

        }

        case tminus_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);


            if( exp->getType()->isIntegerTy() && exp2->getType()->isIntegerTy() ){
                return Builder.CreateSub(exp,exp2);
            }
            if (exp->getType()->isIntegerTy() ) {
                exp = Builder.CreateSIToFP(exp,re) ;
            }
            if (exp2->getType()->isIntegerTy() ) {
                exp2 = Builder.CreateSIToFP(exp2,re) ;
            }



            return Builder.CreateFSub(exp,exp2);
        }



         case tmul_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);


            if( exp->getType()->isIntegerTy() && exp2->getType()->isIntegerTy() ){
                return Builder.CreateMul(exp,exp2);
            }
            if (exp->getType()->isIntegerTy() ) {
                exp = Builder.CreateSIToFP(exp,re) ;
            }
            if (exp2->getType()->isIntegerTy() ) {
                exp2 = Builder.CreateSIToFP(exp2,re) ;
            }



            return Builder.CreateFMul(exp,exp2);
        }

         case tslash_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);
            

            if( exp->getType()->isIntegerTy() && exp2->getType()->isIntegerTy() ){
                //mporei na einai kai sdiv
                return Builder.CreateFDiv(exp,exp2);
            }
            if (exp->getType()->isIntegerTy() ) {
                exp = Builder.CreateSIToFP(exp,re) ;
            }
            if (exp2->getType()->isIntegerTy() ) {
                exp2 = Builder.CreateSIToFP(exp2,re) ;
            }




            return Builder.CreateFDiv(exp,exp2);


        }

         case tdiv_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);

            return Builder.CreateSDiv(exp,exp2);


        }


         case tmod_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);

            return Builder.CreateSRem(exp,exp2);


        }
        

        case tequal_r:{

            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);
            bool flag = false ;


            /*
                exp and exp1 reach her 
                with their final form
                meaning their type are
                like x86_80
                or i16 ..
                not pointerr to ...
            */

            auto ty_a1 = exp->getType() ;
            auto ty_b1 = exp2->getType() ; 


  

            if(ty_a1 ==i16 && ty_b1 == re ) {
                flag = true ;
                exp = Builder.CreateSIToFP(exp,re);
            }


            if(ty_a1 ==re && ty_b1 == i16 ) {
                flag = true ;
                exp2 = Builder.CreateSIToFP(exp2,re);
            }

            if(ty_a1 == re && ty_b1== re){
                flag = true ;
            }

            if(isPointertoVoid(ty_a1) && isPointertoVoid(ty_b1) ){
                return Builder.CreateICmpEQ(exp,exp2);
            }

            // if its only one of em
            if(isPointertoVoid(ty_a1)  ){
                exp = llvm::Constant::getNullValue(exp2->getType());
                return Builder.CreateICmpEQ(exp,exp2);
            }

             if(isPointertoVoid(ty_b1)  ){
                exp2 = llvm::Constant::getNullValue(exp->getType());
                return Builder.CreateICmpEQ(exp,exp2);
            }

            if (flag)
                return Builder.CreateFCmpOEQ(exp,exp2);
            else
                return Builder.CreateICmpEQ(exp,exp2);

        }

         case twhot_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);
            bool flag = false ;


            auto ty_a1 = exp->getType() ;
            auto ty_b1 = exp2->getType() ; 


  

            if(ty_a1 ==i16 && ty_b1 == re ) {
                flag = true ;
                exp = Builder.CreateSIToFP(exp,re);
            }


            if(ty_a1 ==re && ty_b1 == i16 ) {
                flag = true ;
                exp2 = Builder.CreateSIToFP(exp2,re);
            }

            if(ty_a1 == re && ty_b1== re){
                flag = true ;
            }


            if(isPointertoVoid(ty_a1) && isPointertoVoid(ty_b1) ){
                return Builder.CreateICmpNE(exp,exp2);
            }

            // if its only one of em
            if(isPointertoVoid(ty_a1)  ){
                exp = llvm::Constant::getNullValue(exp2->getType());
                return Builder.CreateICmpNE(exp,exp2);
            }

             if(isPointertoVoid(ty_b1)  ){
                exp2 = llvm::Constant::getNullValue(exp->getType());
                return Builder.CreateICmpNE(exp,exp2);
            }



            if (flag)
                return Builder.CreateFCmpONE(exp,exp2);
            else
                return Builder.CreateICmpNE(exp,exp2);


        }

         case tless_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);
            bool flag = false ;

            auto ty_a1 = exp->getType() ;
            auto ty_b1 = exp2->getType() ; 


  

            if(ty_a1 ==i16 && ty_b1 == re ) {
                flag = true ;
                exp = Builder.CreateSIToFP(exp,re);
            }


            if(ty_a1 ==re && ty_b1 == i16 ) {
                flag = true ;
                exp2 = Builder.CreateSIToFP(exp2,re);
            }

            if(ty_a1 == re && ty_b1== re){
                flag = true ;
            }

            if (flag)
                return Builder.CreateFCmpOLT(exp,exp2);
            else
                return Builder.CreateICmpSLT(exp,exp2);

        }


         case tleseq_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);
            bool flag = false ;

            auto ty_a1 = exp->getType() ;
            auto ty_b1 = exp2->getType() ; 


  

            if(ty_a1 ==i16 && ty_b1 == re ) {
                flag = true ;
                exp = Builder.CreateSIToFP(exp,re);
            }


            if(ty_a1 ==re && ty_b1 == i16 ) {
                flag = true ;
                exp2 = Builder.CreateSIToFP(exp2,re);
            }

            if(ty_a1 == re && ty_b1== re){
                flag = true ;
            }

            if (flag)
                return Builder.CreateFCmpOLE(exp,exp2);
            else
                return Builder.CreateICmpSLE(exp,exp2);

        }

        case tge_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);
            bool flag = false ;

            auto ty_a1 = exp->getType() ;
            auto ty_b1 = exp2->getType() ; 


  

            if(ty_a1 ==i16 && ty_b1 == re ) {
                flag = true ;
                exp = Builder.CreateSIToFP(exp,re);
            }


            if(ty_a1 ==re && ty_b1 == i16 ) {
                flag = true ;
                exp2 = Builder.CreateSIToFP(exp2,re);
            }

            if(ty_a1 == re && ty_b1== re){
                flag = true ;
            }

            if (flag)
                return Builder.CreateFCmpOGT(exp,exp2);
            else
                return Builder.CreateICmpSGT(exp,exp2);



   //         return Builder.CreateICmpSGT(exp,exp2);
        }

        case tgeq_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);
            bool flag = false ;


            auto ty_a1 = exp->getType() ;
            auto ty_b1 = exp2->getType() ; 


            if(ty_a1 ==i16 && ty_b1 == re ) {
                flag = true ;
                exp = Builder.CreateSIToFP(exp,re);
            }


            if(ty_a1 ==re && ty_b1 == i16 ) {
                flag = true ;
                exp2 = Builder.CreateSIToFP(exp2,re);
            }

            if(ty_a1 == re && ty_b1== re){
                flag = true ;
            }

            if (flag)
                return Builder.CreateFCmpOGE(exp,exp2);
            else
                return Builder.CreateICmpSGE(exp,exp2);





          //  return Builder.CreateICmpSGE(exp,exp2);
        }


        case tand_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);

            return Builder.CreateAnd(exp,exp2);
        }

        case tor_r:{
            auto exp = codegenExpr(r->expr1);
            auto exp2 = codegenExpr(r->expr2);

           return Builder.CreateOr(exp,exp2);
        }

        default : return nullptr ;
    }
    return nullptr ;
}

//TODO--aurio auto na prospa8hsw na exw auto to kainourio feature
llvm::Value* codegenLval(Lval *lval){
    if(lval == NULL) return nullptr;
    switch(lval->kind){
        case tid_l:{
            /* Handle nesting diff */ 

            llvm::Value* link;         
            llvm::Value* fatherStruct = currentAlloca;
            int z = lval->nesting_diff;

            // First element
            llvm::Value* first[]={c32(0) , c32(0)};
            while(z>0){
                // Get pointer to old-Frame
                link = Builder.CreateGEP(fatherStruct,first,"");
                fatherStruct = Builder.CreateLoad(link,"");
                z--;
            }

            // Getting indexes for gep -+1 for offset becouse of old-frame
            llvm::Value* indList[]={c32(0) , c32(lval->id->offset + 1 )};
            auto lhs = Builder.CreateGEP(fatherStruct,indList,"");



            
            // aRRAY STUFF
            if(lhs->getType()->isPointerTy() && lhs->getType()->getPointerElementType()->isArrayTy() ) {
                //cout << "yoooyoyoyoyo" << endl ;
                array_flag = true ;
                size_of_arr = lhs->getType()->getPointerElementType()->getArrayNumElements();

                std::vector<llvm::Value *> indlist40;
                indlist40.push_back(c32(0));
                indlist40.push_back(c32(0));

        
                lhs = Builder.CreateInBoundsGEP(lhs, indlist40, "");
                
                // llvm::Value* temporal = Builder.CreateAlloca(llvm::PointerType::get(lhs->getType(),0),0,"");
                // nmz auta ta 3 de ta xreiazomai
               //* llvm::Value* temporal = Builder.CreateAlloca(lhs->getType(),0,"");   
               //* Builder.CreateStore(lhs , temporal);
               //* return temporal;
                return lhs ; 
            }
            array_flag = false ;
            size_of_arr = 0 ;
            if ((lval->isByRef) && !isArray(lval->type)  && !isIArray(lval->type)) { lhs = Builder.CreateLoad(lhs); }
           //auto lhs_value  = Builder.CreateLoad(lhs);
            return lhs;        /* o makakas gyrnousa nullpnt 
                                *kai  de to eida gt olh merea
                                *  den eimai sygkentomenos
                                */            
            break;
        }
        case tresult_l:
            /* No worries for procedures
            * they will be handled be sem
            * (the problem was what if retalloca was Null)
            * but earlier semantic analysis will nitlet 
            * that happen */
            return ret_holder.top();
        break;

        
        
       
        case tarr_l:{
       
            
            //Codegen index of arrey
            llvm::Value *indx = codegenLval(lval->l2);
            indx = Builder.CreateLoad(indx);
            //indx = Builder.CreateLoad(indx);
            

            auto lhs = codegenLval(lval->l1);
            //lhs =  Builder.CreateLoad(lhs);
            if(array_flag == false){
                lhs = Builder.CreateLoad(lhs);
            }


            std::vector<llvm::Value *> indlist2;

            llvm::Value *ext = Builder.CreateSExt(indx, i16, "");
         

            llvm::APInt zero64(64, 0);

           // indlist2.push_back(llvm::Constant::getIntegerValue(i64, zero64));
            indlist2.push_back(ext);

            
           

            //auto gep = Builder.CreateInBoundsGEP(lhs, indlist2, "");
            auto gep2 = llvm::GetElementPtrInst::CreateInBounds(lhs,indlist2,"",Builder.GetInsertBlock());
         
            return gep2 ;

           // break ;
        }

        case tarr_r:{
            //llvm::Value *indx = codegenLval(lval->l2);
            //indx = Builder.CreateLoad(indx);
            auto rhs = codegenRval(lval->r1);

            auto lhs = codegenLval(lval->l1);
            //nmz de xreiazetai
            //* lhs = Builder.CreateLoad(lhs);
            //gt to nmuza
             if(array_flag == false){
                lhs = Builder.CreateLoad(lhs);
            }
            
            std::vector<llvm::Value *> indlist2;

            llvm::Value *ext = Builder.CreateSExt(rhs, i64, "");

            llvm::APInt zero64(64, 0);

          //  indlist2.push_back(llvm::Constant::getIntegerValue(i64, zero64));
            indlist2.push_back(ext);

        
            auto gep = Builder.CreateInBoundsGEP(lhs, indlist2, "");
            
            return gep ;


        }

        case tref_lv:{
            /* I belive if it gets here
            * we know its a pointer */
            auto ref = codegenLval(lval->l1);
            auto ref_value = Builder.CreateLoad(ref);
            // i am not sure
        //    ref_value = Builder.CreateLoad(ref_value);

            return ref_value ;
        }

        case tref_rv:{
            /* I belive if it gets here
            * we know its a pointer */
            auto ref = codegenRval(lval->r1);
            auto ref_value = Builder.CreateLoad(ref);
            // iam not sure
           // ref_value = Builder.CreateLoad(ref_value);
            return ref_value ;
        }


        case t_group_l:{
            return codegenLval(lval->l1);
        }

        case tstring_l:{
            string temp =  lval->str ;
            char * tab2 = new char [temp.length()+1];
            strcpy (tab2, temp.c_str());
            //cout << tab2 << endl ;




            llvm::Value* gep_elem;
            llvm::Value* str_alloc  = Builder.CreateAlloca(llvm::ArrayType::get(i8,temp.length()+1),0,"");

           // llvm::Value* indList[]={c32(0) , c32(lval->id->offset + 1 )};

        
            for(int i=0 ; i < temp.length() +1 ;i++ ){

                llvm::Value* indList[]={c32(0) , c32(i) };

                //auto list = {c8(0),c8(int(tab2[i]))}
                gep_elem = Builder.CreateGEP(str_alloc,indList);
               
                Builder.CreateStore(c8((tab2[i])),gep_elem);
                
            }

            std::vector<llvm::Value *> indlist60;


            // aRRAY STUFF
            if(str_alloc->getType()->isPointerTy() && str_alloc->getType()->getPointerElementType()->isArrayTy() ) {
                

                //std::vector<llvm::Value *> indlist40;
                indlist60.push_back(c32(0));
                indlist60.push_back(c32(0));

        
                str_alloc = Builder.CreateInBoundsGEP(str_alloc, indlist60, "");


               // auto temporal = Builder.CreateAlloca(llvm::PointerType::get(llvm::ArrayType::get(i8,temp.length()+1),0),0,"");
                
                // auta nomizw ta 3 de xreiazontai  
               //* auto temporal = Builder.CreateAlloca(str_alloc->getType(),0,"");
               //* Builder.CreateStore(str_alloc , temporal);
               /* return temporal; */
               // gnk nmz de xreiazontai

               
             
                return str_alloc;
                break ;
            }    
        }

    }
    return nullptr;
}


llvm::Value* codegenExpr(Expr* exp) {
    if(exp == NULL ) return nullptr ;
    switch(exp->kind){
        case lva :
            //return codegenLval(exp->lval);
            // I belive this is the right thing to do 
            return  Builder.CreateLoad(codegenLval(exp->lval));
            break;

        case rva:
            return codegenRval(exp->rval);
            break; 

        default: 
            return nullptr;
    }
}

std::list<llvm::Type* > getHeaderParam(Header* header){
    std::list<llvm::Type*> params = {} ;
    if(header->formals != nullptr){
    if (header->formals->size() > 0){
        for(auto i : *header->formals){
           // if(i != NULL ){
                switch(i->kind){
                    case value:
                        for (int z =0 ; z < i->ids->size(); z++){
                            params.push_back(translate(i->type));
                        }
                        break;
                    case refernce: 
                        for (int z =0 ; z < i->ids->size(); z++){
                            if(isArray(i->type) || isIArray(i->type) ){
                                params.push_back( translate(i->type)); 
                            }
                            else
                            params.push_back(llvm::PointerType::get( translate(i->type),0));
                        }
                        break;
                    default :
                        //cout<<"my fault" << endl ;
                        error("internal here");
                    }
           // }    
        }
        }
    }
    return params;
}

/*

std::vector<llvm::Type* > myListmerge(std::vector<llvm::Type *> one ,std::list<llvm::Type *>two){


    if(one.size() == 0) {
        std::vector<llvm::Type* > v { std::begin(two), std::end(two) } ;
        return v ;
    }
    ////cout<< "TO SIZE TOU EINAI "<< one.size()<<endl;
    //std::string type_str;
    //llvm::raw_string_ostream rso(type_str);
 
    
    auto iterator = one.begin();
  //  //cout << "nauoini to pepouni" <<endl ; 
   // std::string type_str;
   // llvm::raw_string_ostream rso(type_str);
    for(auto i : two){
       // //cout << "nauoini to pepouni" <<endl ; 
      //   i->print(rso);
        // std:://cout<<rso.str() <<endl;
         one.insert(iterator,i);
      //  std:://cout<<rso.str() <<endl;
        if(iterator != one.end() ){ 
           // //cout << "YO MPIKA " << endl ;
            iterator++;
        }
    }
    return one ;
}
*/


std::vector<llvm::Type* > myListmerge(std::vector<llvm::Type *> one ,std::list<llvm::Type *>two){
    
    std::list<llvm::Type*> one_in_list;

    std::copy( one.begin(), one.end(), std::back_inserter( one_in_list ) );

    two.insert(two.end(), one_in_list.begin(), one_in_list.end());

    std::vector<llvm::Type* > ret {std::begin(two),std::end(two)};

    return ret ;
}

/*
    if(one.size() == 0) {
        std::vector<llvm::Type* > v { std::begin(two), std::end(two) } ;
        return v ;
    }
    ////cout<< "TO SIZE TOU EINAI "<< one.size()<<endl;
    //std::string type_str;
    //llvm::raw_string_ostream rso(type_str);
 
    
    auto iterator = one.begin();
  //  //cout << "nauoini to pepouni" <<endl ; 
   // std::string type_str;
   // llvm::raw_string_ostream rso(type_str);
    for(auto i : two){
       // //cout << "nauoini to pepouni" <<endl ; 
      //   i->print(rso);
        // std:://cout<<rso.str() <<endl;
         one.insert(iterator,i);
      //  std:://cout<<rso.str() <<endl;
        if(iterator != one.end() ){ 
           // //cout << "YO MPIKA " << endl ;
            iterator++;
        }
    }
    return one ;
}

*/




void codegenLibs() {

    /*-------------writeInteger--------------------------------*/

    llvm::FunctionType *writeInteger_type = llvm::FunctionType::get(
        llvm::Type::getVoidTy(TheContext), std::vector<llvm::Type *>{i16}, false);
    llvm::Value* writeInteger = llvm::Function::Create(writeInteger_type, llvm::Function::ExternalLinkage,
    "writeInteger", TheModule.get());
    /*---------------------------------------------------------*/



    /*-------------writeChar-----------------------------------*/
    llvm::FunctionType *writeChar_type = llvm::FunctionType::get(
        llvm::Type::getVoidTy(TheContext), std::vector<llvm::Type *>{i8}, false);
        
    llvm::Function::Create(writeChar_type, llvm::Function::ExternalLinkage, "writeChar",
    TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------writeBoolean-----------------------------------*/
    llvm::FunctionType *writeBoolean_type = llvm::FunctionType::get(
            llvm::Type::getVoidTy(TheContext), std::vector<llvm::Type *>{bo}, false);
    llvm::Function *writeBoolean = llvm::Function::Create(
    writeBoolean_type, llvm::Function::ExternalLinkage, "writeBoolean", TheModule.get());
    /*---------------------------------------------------------*/

    /*-------------writeString-----------------------------------*/
    llvm::FunctionType *writeString_type = llvm::FunctionType::get(
        llvm::Type::getVoidTy(TheContext),
            std::vector<llvm::Type *>{llvm::PointerType::get(i8, 0)}, false);
    //std::vector<llvm::Type *>{llvm::PointerType::get(llvm::PointerType::get(i8,0), 0)}, false);
    llvm::Function::Create(writeString_type, llvm::Function::ExternalLinkage, "writeString",
                        TheModule.get());
    /*---------------------------------------------------------*/




    /*-------------writeReal-----------------------------------*/
    llvm::FunctionType *writeReal_type = llvm::FunctionType::get(
            llvm::Type::getVoidTy(TheContext), std::vector<llvm::Type *>{llvm::Type::getX86_FP80Ty(TheContext)}, false);
    llvm::Function *writeReal = llvm::Function::Create(
    writeReal_type, llvm::Function::ExternalLinkage, "writeReal", TheModule.get());
    /*---------------------------------------------------------*/


    /*---------------------------------------------------------*/

    /*****************reading***********************************/


    /*-------------readInteger-----------------------------------*/
    llvm::FunctionType *readInteger_type =
            llvm::FunctionType::get(i16, std::vector<llvm::Type *>{}, false);
    llvm::Function::Create(readInteger_type, llvm::Function::ExternalLinkage, "readInteger",
        TheModule.get());
    /*---------------------------------------------------------*/



    /*-------------readBoolean-----------------------------------*/
    llvm::FunctionType *readBoolean_type =
            llvm::FunctionType::get(bo, std::vector<llvm::Type *>{}, false);
    llvm::Function::Create(readBoolean_type, llvm::Function::ExternalLinkage, "readBoolean",
        TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------readChar-----------------------------------*/
    llvm::FunctionType *readChar_type =
            llvm::FunctionType::get(i8, std::vector<llvm::Type *>{}, false);
    llvm::Function::Create(readChar_type, llvm::Function::ExternalLinkage, "readChar", TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------readString-----------------------------------*/
    llvm::FunctionType *readString_type = llvm::FunctionType::get(
            llvm::Type::getVoidTy(TheContext),
            std::vector<llvm::Type *>{  i16 ,llvm::PointerType::get(i8, 0),}, false);
    llvm::Function::Create(readString_type, llvm::Function::ExternalLinkage, "readString",
    TheModule.get());
    /*---------------------------------------------------------*/

    /*-------------readReal-----------------------------------*/
    llvm::FunctionType *readReal_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{}, false);
    llvm::Function::Create(readReal_type, llvm::Function::ExternalLinkage, "readReal", TheModule.get());
    /*---------------------------------------------------------*/

    /**************Math-Func*************************************/


    /*-------------abs-----------------------------------*/
    llvm::FunctionType *abs_type =
            llvm::FunctionType::get(i16, std::vector<llvm::Type *>{i16}, false);
    llvm::Function::Create(abs_type, llvm::Function::ExternalLinkage, "abs", TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------fabs-----------------------------------*/
    llvm::FunctionType *fabs_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(fabs_type, llvm::Function::ExternalLinkage, "fabs", TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------sqrt-----------------------------------*/
    llvm::FunctionType *sqrt_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(sqrt_type, llvm::Function::ExternalLinkage, "sqrt", TheModule.get());
    /*---------------------------------------------------------*/

    /*-------------sin-----------------------------------*/
    llvm::FunctionType *sin_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(sin_type, llvm::Function::ExternalLinkage, "sin", TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------cos-----------------------------------*/
    llvm::FunctionType *cos_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(cos_type, llvm::Function::ExternalLinkage, "cos", TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------tan-----------------------------------*/
    llvm::FunctionType *tan_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(tan_type, llvm::Function::ExternalLinkage, "tan", TheModule.get());
    /*---------------------------------------------------------*/



    /*-------------arctan-----------------------------------*/
    llvm::FunctionType *arctan_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(arctan_type, llvm::Function::ExternalLinkage, "arctan", TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------exp-----------------------------------*/
    llvm::FunctionType *exp_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(exp_type, llvm::Function::ExternalLinkage, "exp", TheModule.get());
    /*---------------------------------------------------------*/


    /*---------------ln-----------------------------------*/
    llvm::FunctionType *ln_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(ln_type, llvm::Function::ExternalLinkage, "ln", TheModule.get());
    /*---------------------------------------------------------*/


    /*-------------phi-----------------------------------*/
    llvm::FunctionType *phi_type =
            llvm::FunctionType::get(re, std::vector<llvm::Type *>{}, false);
    llvm::Function::Create(phi_type, llvm::Function::ExternalLinkage, "pi", TheModule.get());
    /*---------------------------------------------------------*/



    /***********Convert-functions******************************/

    /*-------------trunc-----------------------------------*/
    llvm::FunctionType *trunc_type =
            llvm::FunctionType::get(i16, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(trunc_type, llvm::Function::ExternalLinkage, "trunc", TheModule.get());
    /*---------------------------------------------------------*/

    /*-------------round-----------------------------------*/
    llvm::FunctionType *round_type =
            llvm::FunctionType::get(i16, std::vector<llvm::Type *>{re}, false);
    llvm::Function::Create(round_type, llvm::Function::ExternalLinkage, "round", TheModule.get());
    /*---------------------------------------------------------*/

    /*-------------ord-----------------------------------*/
    llvm::FunctionType *ord_type =
            llvm::FunctionType::get(i16, std::vector<llvm::Type *>{i8}, false);
    llvm::Function::Create(ord_type, llvm::Function::ExternalLinkage, "ord", TheModule.get());
    /*---------------------------------------------------------*/

    /*-------------chr-----------------------------------*/
    llvm::FunctionType *chr_type =
            llvm::FunctionType::get(i8, std::vector<llvm::Type *>{i16}, false);
    llvm::Function::Create(chr_type, llvm::Function::ExternalLinkage, "chr", TheModule.get());
    /*---------------------------------------------------------*/




}

bool isLibFunction(string id) {
    return id == "writeInteger" or id == "writeReal" or id == "writeChar" or
           id == "writeString" or id == "writeBoolean" or 
           
           id == "readInteger" or id == "readReal" or
           id == "readChar" or id == "readString" or 
           id == "readBoolean" or

           id == "abs" or
           id == "fabs" or id == "sqrt" or id == "sin" or
           id == "cos" or id == "tan" or
           id == "arctan" or id == "exp" or
           id == "ln" or id == "pi" or 
           
           id == "ord" or id == "chr" or
           id == "trunc" or id == "round"
           ;
}


llvm::Value* isPointertoArray(Lval* lval) {




    llvm::Value* link;         
    llvm::Value* fatherStruct = currentAlloca;
    int z = lval->nesting_diff;

    // First element
    llvm::Value* first[]={c32(0) , c32(0)};
    while(z>0){
        // Get pointer to old-Frame
        link = Builder.CreateGEP(fatherStruct,first,"");
        fatherStruct = Builder.CreateLoad(link,"");
        z--;
    }

    // Getting indexes for gep -+1 for offset becouse of old-frame
    llvm::Value* indList[]={c32(0) , c32(lval->id->offset + 1 )};
    auto lhs = Builder.CreateGEP(fatherStruct,indList,"");







    // aRRAY STUFF
    if(lhs->getType()->isPointerTy() && lhs->getType()->getPointerElementType()->isArrayTy() ) {
        //cout << "yoooyoyoyoyo" << endl ;
        std::vector<llvm::Value *> indlist40;
        indlist40.push_back(c32(0));
        indlist40.push_back(c32(0));


        lhs = Builder.CreateInBoundsGEP(lhs, indlist40, "");
        
        // llvm::Value* temporal = Builder.CreateAlloca(llvm::PointerType::get(lhs->getType(),0),0,"");
        llvm::Value* temporal = Builder.CreateAlloca(lhs->getType(),0,"");   
        Builder.CreateStore(lhs , temporal);
        return temporal; 
    }

    return nullptr;
}


llvm::Value* args_Convert(llvm::Value* func_arg , llvm::Value* call_param ){

    int i = Pointer_diff(func_arg,call_param) ;
    auto a_ty = func_arg->getType();
    auto b_ty = call_param->getType();
    llvm::Value* ret ;

    
    if( b_ty->isPointerTy() &&  ( i < 0 ) )  {
    
       // cout << "i am in  nooot" << endl ;
       // i = Pointer_diff(func_arg,call_param);
        call_param =Builder.CreateLoad(call_param,"");
        ret = call_param ;
        b_ty = call_param->getType();

    }
    

    if( i > 0 ){
        //cout << "i am in " << endl ;
        auto temp30 = Builder.CreateAlloca(call_param->getType(),0,"") ;
        Builder.CreateStore(call_param,temp30,"");
        return temp30 ;
    }


    if(a_ty == b_ty  ){
        //cout << "Yahoo" << endl ;
        ret = call_param ;
        return ret ;
    }

    // re == X80 llvm type
    if( a_ty == re 
        && b_ty == i16 ){
            
            ret = Builder.CreateSIToFP(call_param,re,"");
            return ret;
    }


  


    //* thats probaly a mistake */
   // cout<< "i messed up something" <<endl ;
    //else is reference so get it Pointeee
 //   llvm::Value* tempo = Builder.CreateAlloca(call_param->getType(),0,"");
 //   Builder.CreateStore(call_param,tempo);

   // return tempo ;
    return call_param;
}


std::vector<llvm::Value *>  ready_params_for_call(std::list<Expr*> *exp_list,llvm::Function::arg_iterator arg_it) {

    // Now do the params
    std::vector<llvm::Value *> params;
    //params.push_back(currentAlloca) ;
   // arg_it++ ;
                    
    // Codegen-Give values to call-params
    for(auto i : *exp_list){
        llvm::Value *curr_arg = &(*arg_it);
        
        auto kk = codegenExpr2(i) ;
         
        // getType get the actual type dispite llvm uses pointers to everything
        //if( curr_arg->getType()->isPointerTy() && kk->getType()->isIntegerTy() )cout << "Malakesss" << endl;
        kk = args_Convert(curr_arg,kk);
        params.push_back(kk);
        arg_it++;
           
    }

    return params;


 }


// One load less for references
llvm::Value* codegenExpr2(Expr* exp) {
    if(exp == NULL ) return nullptr ;
    switch(exp->kind){
        case lva :
            //return codegenLval(exp->lval);
            // I belive this is the right thing to do 
            //if ((exp->lval->isByRef)) { return Builder.CreateLoad(codegenLval(exp->lval)); }

            return (codegenLval(exp->lval));

            break;

        case rva:
            return codegenRval(exp->rval);
            break; 

        default: 
            return nullptr;
    }
}


int Pointer_diff(llvm::Value* a , llvm::Value* b ) {

    auto a_ty = a->getType();
    auto b_ty = b->getType();
    int a_minus_b = 0 ;

    while( a_minus_b == 0) {

        if(a_ty->getNumContainedTypes() == b_ty->getNumContainedTypes() && (a_ty->getNumContainedTypes() >0)  ){
            a_ty = a_ty->getContainedType(0);
            b_ty = b_ty->getContainedType(0);
        }

        else break ;
    }
    
    if ( a_ty->getNumContainedTypes() > b_ty->getNumContainedTypes() )
        a_minus_b = 1 ;
    if ( a_ty->getNumContainedTypes() < b_ty->getNumContainedTypes() )
        a_minus_b = -1 ;
    
    
    
    return a_minus_b;

}

bool isPointertoVoid(llvm::Type* a){
    if(a->isPointerTy() && a->getPointerElementType()->isVoidTy()){
        return true ;
    }
    else 
        return false ;
}