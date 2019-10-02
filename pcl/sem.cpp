#include "sem.hpp"
#include "my-llvm.hpp"
//function declaration de xreuazetai semicolon
stack<SymbolEntry* > func_stack;
SymbolEntry* dummy;
// String parent for function mangling
std::string parent;
int forward_counter = 0 ;

// Semantic of prog
void sem_prog(Program* p){
  if (p == NULL) return ;
  // open scope for variables about to come
  openScope();
  // Parent program for first body
  parent = "program";
  add_lib_func();
  sem_body(p->body);
  if (forward_counter > 0){
    error("Forgot function definition");
  }
 
  closeScope();
  return ;
}

void sem_body(Body* p){
  if ( p == NULL ) return ;
  //nmz oti einai swsto na krathsw auto pou ew sto header
  // openScope();

  for(auto i : *(p->locals)){
    sem_local(i);
  }
  sem_block(p->block);

//  closeScope();
  return ;
}


void sem_local(Local* p){
  if(p==NULL) return ;
  
  if(p->loc_type == var){ 
    for(auto i : *p->ids){
     
     // cout << i->id << endl ;
    
      // push every var in symp.table
      SymbolEntry* k = newVariable(i->id.c_str(),p->type);
    }
  }
  
  // DEN KSERW TI NA KANW GIA LABEL
  
  if(p->loc_type == forwad){
    //Problem me currnet scioe edw
    //eprepe na asxolh8w san na htan header prwta
    //SymbolEntry * k = lookupEntry((p->header)->id->id.c_str(),LOOKUP_ALL_SCOPES,false);
    //if ( k == NULL ) return ;
    //forwardFunction(k);
    sem_header(p->header,NULL);
    //m,z 8a koitakswsto current scope SWSTO TO SCOPE KAI EDW
    SymbolEntry * k = lookupEntry((p->header)->id->id.c_str(),LOOKUP_CURRENT_SCOPE,true);
    forwardFunction(k);
    forward_counter++;


  }

  if(p->loc_type == header){
    sem_header(p->header,p->body);
   // sem_body(p->body);
  }

  //goa tis etiletes lamw to paradoxh pto dem 

  if(p->loc_type == label){
    for(auto i : *p->ids){
      // to-do
    SymbolEntry* k = newVariable(i->id.c_str(),typeVoid);
    }
  }


  return ;
}


//header 8a nalavanei kai to body
void sem_header(Header* p,Body *body){
  if(p == NULL) return ;

  /* First need to take care of the parent */

  // Store my ancient-parent IWAS HERE
  p->parent = parent;
 // cout<< "-----Parent received----"<<endl;
 // cout<<parent<<endl;
  // Keep the ancient-parent of the current body
  if(!isLibFunction(p->id->id)){
    if(currentScope->nestingLevel == 1){
     // cout<<"----------------------"<< endl;
     // cout<< "HERE IS DA PARENT"<< endl ;
     // cout << p->id->id  <<endl ;
     // cout<<"-----------------------"<<endl;
      p->parent = "main";
      parent = p->id->id ;
    }
  }
  SymbolEntry* f = newFunction((p->id)->id.c_str()) ;
  if(f->u.eFunction.isForward == true ){
    forward_counter --;
    f->u.eFunction.isForward = false ;
  }
  // new scope for variables of function
  openScope();
  sem_formals(p->formals ,f);

  // elenxos gua to an einai fuction kai prepei na epistrepsei type 
  if (p->kind == function) {
  //ean einai function vazw typo
  // 5 ==type array   6 tupe iarray
  if(p->type->kind == 5 || p->type->kind == 6) error("cant have array as function output %s " ,p->id->id.c_str());
  }
  if (p->kind == procedure){
      p->type = typeVoid ;
  }
  //tp end function header eprepe na paizei gia ola
  endFunctionHeader(f,p->type);
  //8esh mnhmhhs pou kratei prwsorina to aporelesma
  if( p->kind == function){
   
   // auto pou ginotan tosh wra 
  // na psaxnw gt dhmiourgei provlhma h malakia auth
  // enw den thn xreaizomouna kan einai asteio 
  // trelh malakia na exw  xasei toses wres
  // kai na exw faei frikh 
  // enw apla mporousa na kanw comment out 


   //** auto vlakeia = newTemporary(p->type);
   
   
   
   // cout << "-----------Temporary offset------------" << endl ;
   // cout<<"-----------------------------------------"<< endl;
   // cout<<"-----------------------------------------"<< endl;
   // cout << vlakeia->u.eTemporary.offset << endl;
   // cout<<"-----------------------------------------"<< endl;
   // cout<<"-----------------------------------------"<< endl;
   // cout<<"-----------------------------------------"<< endl;
   // cout<<"-----------------------------------------"<< endl;

  //pousarw tis sunarthseis
    func_stack.push(f); 
  }
  //upo8etw oti prpei na krathsw zwtanes tis parametrous
  


  // Keep the ancient-parent of the current body
 // cout<< currentScope->nestingLevel << endl;
  if(currentScope->nestingLevel == 1){
   // cout<<"----------------------"<< endl;
   // cout<< "HERE IS DA PARENT"<< endl ;
   // cout << parent <<endl ;
   // cout<<"--------------"<<endl;
    parent = p->id->id ;
  }
  
  sem_body(body);

  // I think here is a better place than before
  if( p->kind == function)
    func_stack.pop();
  closeScope();
  return ;

}


//kai kala einai lista apo formals --ta arguments kai h sunarthsh
void sem_formals(list<Formal *> *list_form , SymbolEntry* function){
   if(list_form == NULL ) return ;
  //if(list_form == NULL ) error("Must have at least a forma;");
  for(auto i : *list_form){
      sem_formal(i,function); 
    }
  return ;
}

//edw 8a valw parametrous sunarthshs--ka8e formal exei parametrous
void sem_formal(Formal *form,SymbolEntry *function){
  if(form == NULL) return ;
  
  PassMode mode ;
  if (form->kind == refernce)
    mode = PASS_BY_REFERENCE ;
  else mode = PASS_BY_VALUE ;

  //elenxos mh to dialostilo    //type array kai type  iarray //e
  if(mode == PASS_BY_VALUE && ( form->type->kind == 5 || form->type->kind == 6 ) ) error("cant pass as a parameter  array , function %s ",function->id);

  for(auto i : *(form->ids)){

    auto ultradummy = newParameter(i->id.c_str(),form->type,mode,function);
   // cout << "---------------------------------------------------"<< endl ;
   // cout << "Parameter Offset :" <<ultradummy->u.eParameter.offset << endl ;
  }
  return ;
}


void sem_block(Block* p){
  sem_stmt(p->stmt);
  for(auto i : *(p->stmts))
  sem_stmt(i);
  return;
}

void sem_stmt(Stmt *statement){
  if(statement ==   NULL ) return ;
  
  switch(statement->kind){

    case tlva :
      sem_lvalue(statement->lval);
      sem_expr(statement->expr);
//      if(statement->expr->type == NULL)// cout << " to lval type eina null" << endl ;
     
      if(! (myequalType(statement->lval->type,statement->expr->type,0)) )
        error("type mismatch in lval  := expr , lval %s   ",statement->lval->id->id.c_str());
    break ;

    case tblock :
      //to do ftiaksw my bliock
      sem_block(statement->block);
    break ;

    case tcall :
      sem_call(statement->call);
    break ;

    //asuto 8a ftiaxtei
    case tif :
  //    sem_if(statement);
      sem_expr(statement->expr);
      sem_stmt(statement->stmt1);
      sem_stmt(statement->stmt2);
      if( !(statement->expr->type == typeBoolean) )
        error("if must have boolean");
      //de lserew edw ti allo
    break;

    
    case twhile :
      sem_expr(statement->expr);
      sem_stmt(statement->stmt1);
      if( !(statement->expr->type == typeBoolean) )
         error("if must have boolean");
    break;

    //idea
    case tid :{
     
      SymbolEntry* t = lookupEntry(statement->b->id.c_str(),LOOKUP_CURRENT_SCOPE,true);
      if(t->u.eVariable.type != typeVoid) error ("something wrong woth label");
      sem_stmt(statement->stmt1);
      /* I am very very proud for this
      * when i see a label for a first time
      * in body 
      * i change its type
      * so if i see it again (double declaration)
      * an error hit happens */
      t->u.eVariable.type = typePointer(typeVoid);
    }
    break ;

    case tgoto :{                                            //nmz CURRENT scopes
       SymbolEntry* t = lookupEntry(statement->b->id.c_str(),LOOKUP_CURRENT_SCOPE,true);
      // If label declared it should be pointer to Void .
       if( !((t->u.eVariable.type->kind == 7) && ( t->u.eVariable.type->refType->kind == 0 ) )){
          //error("not defined label ");}
       }
    }
    break ;

    case treturn:
      //to-do
    break ;

    case tnew :
      sem_lvalue(statement->lval);
      if( !(check_whole_type(statement->lval->type) )) error("must be plhrhs typos");
      statement->lval->newed = true ;
    break ;

    case tnew_ex:
      sem_lvalue(statement->lval);
      sem_expr(statement->expr);
      if ( !(check_new_ex(statement->lval->type,statement->expr->type))) error("something wrong with new");
      if(statement->expr->rval->integer < 0 )  error("something wrong with new");
      statement->lval->newed = true ;
    break;


    case tdispose :
      sem_lvalue(statement->lval);
      if( !(check_whole_type(statement->lval->type) )) error("something wrong with dispose");
     // if(!(statement->lval->newed)) error("should be newed first") ;
     // statement->lval->newed = false ;
    break ;
    
    case tdispose_ar :
      sem_lvalue(statement->lval);
      if(!(check_disp_arr(statement->lval->type))) error("something wrong with dispose on lval");
     // if(!(statement->lval->newed)) error("should be newed first") ;
     // statement->lval->newed = false ;

    break ;


  }
}

//ta kanw ena ena --simplest next step

void sem_lvalue(Lval* lva){
  if(lva == NULL) return ;
  switch(lva->kind){
    
    case tid_l : 
      //kai kala 8a elenksie an uparxei h metavlhdh NMZ PREPEI NA EINAI ALL
      dummy = lookupEntry(lva->id->id.c_str(),LOOKUP_ALL_SCOPES,true);
      
      switch(dummy->entryType){
        case ENTRY_VARIABLE :
          lva->type = dummy->u.eVariable.type ;
          /* keep the offset of var from symb
             table to ast for llvm GEP */
          lva->id->offset = dummy->u.eVariable.offset ;



       //   cout <<"Offset of " << lva->id->id <<
       //   " is " << lva->id->offset << endl ;


          lva->nesting_diff =  currentScope->nestingLevel -  dummy->nestingLevel ;
         // cout<< "------ NESTING LEVEL IS ----" << endl;
         // cout <<  lva->nesting_diff <<endl;
        break ;

        case ENTRY_CONSTANT :
          lva->type = dummy->u.eConstant.type ;
          // 8elw na piseuw mhedn
          lva->nesting_diff =  0;//dummy->nestingLevel - currentScope->nestingLevel;

        break ;

        case ENTRY_PARAMETER :
          lva->type = dummy->u.eParameter.type ;
          // again keep offset
          lva->id->offset = dummy->u.eParameter.offset;
         // cout << " ---Parameter---: "  << lva->id->id << "offset is "<<
         // lva->id->offset << endl;  
          lva->nesting_diff =   currentScope->nestingLevel -  dummy->nestingLevel;
         // cout << " ---Parameter---: "  << lva->id->id << "nesting diff is "<<
         // lva->nesting_diff  << endl;
          
          //HERE I HANDLE PASS BY REFERENCE
          if( dummy->u.eParameter.mode == PASS_BY_REFERENCE)
            lva->isByRef = true ;
        break ;

        case ENTRY_TEMPORARY :
          lva->type = dummy->u.eTemporary.type ;
          lva->id->offset =dummy->u.eTemporary.offset;
          lva->nesting_diff =  currentScope->nestingLevel - dummy->nestingLevel ;
        break ;
        
        case ENTRY_FUNCTION :
          lva->nesting_diff = currentScope->nestingLevel -  dummy->nestingLevel ;
          //gia na einai edw mallon kati phge strava
          error("you propably forgot something  in your function definition");
          lva->type = dummy->u.eFunction.resultType;
        break ;

      }
      
      //lva->type = dummy->u.eVariable.type ;
      //isw prepei na elenzw ta upoloipa
      //isws kai allao
    break ;

    case tresult_l :
      if(func_stack.empty()) error("something wrong with your result stmts") ;
      dummy = func_stack.top() ;
      //func_stack.pop(); //I dont pop here becouse of multiple result stms 
      if(dummy == NULL) error("SOmething wrong with da function");
      lva->type = dummy->u.eFunction.resultType ;
    break ;

    case tstring_l :
      //ta lvalue-string prepei na exeo katalhlo type
      //*lva->type = typeArray(lva->str.length() + 1 , typeChar );
      lva->type =  typeArray(lva->str.length() + 1 , typeChar );
    break ;

    case tarr_l :
      sem_lvalue(lva->l1 );
      sem_lvalue(lva->l2);

    

      if(( isArray(lva->l1->type) || isIArray(lva->l1->type) ) && equalType(lva->l2->type,typeInteger) ) {
          lva->type = lva->l1->type->refType ;
      }
      

      else error("BUGY ARRAY ") ;
      
      //provlhma --pws edw ti ginetai an parw lval [lval ] den exi nohma gt prepei 
      //na exw integer
       
    break ;


    case tarr_r:
      sem_lvalue(lva->l1 );
      sem_rvalue(lva->r1);

      if( (isArray(lva->l1->type) || isIArray(lva->l1->type)) && equalType(lva->r1->type,typeInteger) ) {
          lva->type = lva->l1->type->refType ;
      }
    
      else error("BUGY ARRAY ") ;
    
   //   if(lva->r1->integer < 0 ) error("very BUGY ARRAY");
  //    if(lva->r1->integer > lva->l1->type->size - 1) error("OUTTA BOUNDS ARR !!-CMON");
    break;

    case tref_lv :
      sem_lvalue(lva->l1);
      //7 == type pointer
      if(lva->l1->type->kind == 7  && (!(lva->l1->type->refType->kind == 0))){
        lva->type = lva->l1->type->refType ;
      }
      else error("something WRONG with your pointer-idea");

    break ;


    case tref_rv :
      sem_rvalue(lva->r1);
      //type pointer                            //type void
      if(lva->r1->type->kind == 7 && !(lva->r1->type->refType->kind == 0) ){
        lva->type = lva->r1->type->refType ;
      }
      else error("something WRONG with your pointer-idea");
    break ;

    case t_group_l :
      sem_lvalue(lva->l1);
      lva->type = lva->l1->type ;
    break ;

    default:
      internal("my mistake");
      //no break needed

  }

}


void sem_rvalue(Rval* rval){
  if(rval == NULL) return ;

  switch(rval->kind){

    case tint_r:
      rval->type = typeInteger ;
    break ;

    case tbool_r:
      rval->type = typeBoolean ;
    break;

    case treal_r:
      rval->type = typeReal ;
    break;

    case tchar_r:
      rval->type = typeChar ;
    break ;

    case trval_r :
      sem_rvalue(rval->rval1);
      rval->type =  rval->rval1->type ;
    break ;
    

    case tnill_r:
      //idea den exew gia to an einai swsto
      rval->type = typePointer(typeVoid);
      
    break ;


    case tcall_r:
      sem_call(rval->call);
      rval->type = rval->call->type ;
    break ;

   // case : //exw kai all

    case tderfe_r:
    sem_lvalue(rval->lval1);
    rval->type=typePointer(rval->lval1->type);
    break ;

    case tuminus_r:
      //sem_lvalue(rval->lval1);
      sem_expr(rval->expr1);
      if( !(rval->expr1->type == typeInteger  || rval->expr1->type == typeReal) ) error(" must be numerical  stuff");
      rval->type=rval->expr1->type;
    break;


    case tuplus_r:
      sem_expr(rval->expr1);
      if( !(rval->expr1->type == typeInteger  || rval->expr1->type == typeReal) ) error(" must be numerical  stuff");
      rval->type=rval->expr1->type;
    break;

    case tnot_r:
    sem_expr(rval->expr1);
    if(!(rval->expr1->type == typeBoolean)) error("must be type boolean");
    rval->type=rval->expr1->type;
    break;

    case tplus_r:{
  //  sem_lvalue(rval->lval1);
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;

      if ( ! (check_if_numer(rval->expr1->type , rval->expr2->type) )) error("must be numerical");
    //  if(!(t1 == t2 && (t2 == typeInteger  || t2 == typeReal ))) error("tyoe mismatch on plus");
      //if(!(t1 == t2 && t2 == typeReal)) error("tyoe mismatch on plus");
      if(t1 ==  typeInteger  && t2 == typeInteger ) rval->type = typeInteger ; 
      else rval->type = typeReal ;
    }
    break ;

    case tminus_r:
    {
  //  sem_lvalue(rval->lval1);
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;

      if ( ! (check_if_numer(rval->expr1->type , rval->expr2->type) )) error("must be numerical");
     // if(!(t1 == t2 && (t2 == typeInteger  || t2 == typeReal ))) error("tyoe mismatch on plus");
      //if(!(t1 == t2 && t2 == typeReal)) error("tyoe mismatch on plus");
       if(t1 ==  typeInteger  && t2 == typeInteger ) rval->type = typeInteger ; 
       else rval->type = typeReal ;
    }
    break ;
  

    case tmul_r:
    {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;

      if ( ! (check_if_numer(rval->expr1->type , rval->expr2->type) )) error("must be numerical");
     // if(!(t1 == t2 && (t2 == typeInteger  || t2 == typeReal ))) error("tyoe mismatch on plus");
       if(t1 ==  typeInteger  && t2 == typeInteger ) rval->type = typeInteger ; 
      else rval->type = typeReal ;
    }
    break ;



    case tslash_r:
    {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;

      if ( ! (check_if_numer(rval->expr1->type , rval->expr2->type) )) error("must be numerical");
       //if(!(t1 == t2 && (t2 == typeInteger  || t2 == typeReal ))) error("tyoe mismatch on plus");
      //if(!(t1 == t2 && t2 == typeReal)) error("tyoe mismatch on plus");
      rval->type = typeReal ;
    }
    break ;

    //to do apo edw 
    case tdiv_r:
    { 
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      if(!(t1->kind==t2->kind && t1 == typeInteger)) error("must be  integer for div");
      rval->type = typeInteger ;
    }
    break ;


     case tmod_r: 
     {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      if(!(t1->kind==t2->kind && t1 == typeInteger)) error("must be  integer for mod");
      rval->type = typeInteger ;
     }
    break ;

    case tequal_r :
    {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      // an einai ari8mitika
      if ( check_if_numer(t1,t2) ) {
        //code henee
      }
      //alliws
      else {
        // an einai idiou typou
        if ( (t1->kind == t2->kind) && !((t1->kind == 5) || t1->kind == 6 ) ){
        }
        else error("check again \"equal\" params");
      }
  
      rval->type = typeBoolean ;
    }
    break ;



    case twhot_r :
    {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      // an einai ari8mitika
      if ( check_if_numer(t1,t2) ) {
        //code henee
      }
      //alliws
      else {
        // an einai idiou typou
        if ( (t1->kind == t2->kind) && !((t1->kind == 5) || t1->kind == 6 ) ){
        }
        else error("check again not-equal params");
      }
  
      rval->type = typeBoolean ;
    }
    break ;

    case tge_r :
    {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      if ( !(check_if_numer(t1,t2)) )  error("must be numeric");
      rval->type = typeBoolean ;
    }
    break ;

   case tgeq_r :
   {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      if ( !(check_if_numer(t1,t2)) )  error("must be numeric");
      rval->type = typeBoolean ;
   }
    break ;
  
  
   case tless_r :
   {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      if ( !(check_if_numer(t1,t2)) )  error("must be numeric");
      rval->type = typeBoolean ;
   }
    break ;


    case tleseq_r :{
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      if ( !(check_if_numer(t1,t2)) )  error("must be numeric");
      rval->type = typeBoolean ;
    }
    break ;


    case tand_r :{
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      if ( !( t1 ==typeBoolean && t1 == t2 ) )  error("must be boolean");
      rval->type = typeBoolean ;
    }
    break ;


    case tor_r :
    {
      sem_expr(rval->expr1);
      sem_expr(rval->expr2);
      Type t1,t2;
      t1 = rval->expr1->type;
      t2 = rval->expr2->type;
      if ( !( t1 ==typeBoolean && t1 == t2 ) )  error("must be boolean");
      rval->type = typeBoolean ;
    }
    break ;


  }

}

void sem_expr(Expr *exp){
  if(exp == NULL ) return ;
  switch (exp->kind)
  {
    case rva:
      sem_rvalue(exp->rval);
      exp->type = exp->rval->type ;
    break ;

    case lva:
      sem_lvalue(exp->lval);
      exp->type = exp->lval->type ;
    break ;

    default : internal("in here my fault");

  }
  

}


//TO-DO:finish it
void sem_call(Call *call){
  int exp_num = 0 ;
  int param_num = 0 ;
  int yo = 0 ;
  if(call == NULL) return ;

  //EDW TO SCOPE EINAI SWSTO
  SymbolEntry* t = lookupEntry(call->id->id.c_str(),LOOKUP_ALL_SCOPES,true);
  if(!(t->entryType == ENTRY_FUNCTION)) error("Not a function");
 //sto telos o typos tou call
 // call->type = t->u.eFunction.resultType;
  SymbolEntry* func_param= t->u.eFunction.firstArgument ;
  while(func_param != NULL){
    param_num++;
    func_param = func_param->u.eParameter.next ;
  }

  //elenxos gia ari8mo parametrewn
  yo = (*(call->e)).size();
  if (  ! ( yo == param_num) ) { error("wron number of pars",call->id->id); }
   func_param = t->u.eFunction.firstArgument ;//edw einai idia h sunarthsh
  
  // Helper variable
  Type typ ;

  for(auto i : *call->e ){
    sem_expr(i);
  //  if(func_param->u.eParameter.mode == PASS_BY_REFERENCE)
   //    typ = typePointer(i->type) ;
    
    //else typ = i->type;

    if(!(isComp(func_param , i->type))) error( "type mismatch parameter on call %s ",call->id->id.c_str());
    if(func_param->u.eParameter.mode == PASS_BY_REFERENCE)
      typ = typePointer(i->type) ;
    
    func_param = func_param->u.eParameter.next ;
  }

  //to eixa ksexasei
  call->type = t->u.eFunction.resultType ;

  if(t->nestingLevel == 1){
    call->parent = "main";
  }
  else
    call->parent = parent;


  call->nd = currentScope->nestingLevel - t->nestingLevel;
  //cout << call->id->id << endl ;
  //cout << "nesting diference is :"<< call->nd << endl ;
}


void add_lib_func(){

/*-------------------WriteInteger------------------------*/
  // Parameters
  T_id* n = new T_id("n");
  std::list<T_id*> *listab = new std::list<T_id*> ;
  listab->push_back(n);
  
  //Form of header
  Formal* forma = new Formal(value,listab,typeInteger);
  std::list<Formal* > *list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* wrintID = new T_id("writeInteger");
  Header* writeInteger_Header = new Header(procedure,wrintID,list);
  Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(writeInteger_Header,nullptr);
/*-------------------------------------------------------*/




/*-------------------WriteBoolean------------------------*/
  // Parameters
  n = new T_id("b");
  listab = new std::list<T_id*> ;
  listab->push_back(n);
  
  //Form of header
  forma = new Formal(value,listab,typeBoolean);
  list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* wrBo = new T_id("writeBoolean");
  Header* writeBoolean_Header = new Header(procedure,wrBo,list);
  Local*  writeBoolean = new Local(header,writeBoolean_Header,nullptr);

  sem_header(writeBoolean_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------WriteChar------------------------*/
  // Parameters
   n = new T_id("c");
  listab = new std::list<T_id*> ;
  listab->push_back(n);
  
  //Form of header
  forma = new Formal(value,listab,typeChar);
  list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* wrchar = new T_id("writeChar");
  Header* writeChar_Header = new Header(procedure,wrchar,list);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(writeChar_Header,nullptr);
/*-------------------------------------------------------*/

/*-------------------WriteReal------------------------*/
  // Parameters
  n = new T_id("r");
  listab = new std::list<T_id*> ;
  listab->push_back(n);
  
  //Form of header
 forma = new Formal(value,listab,typeReal);
  list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* wrReal = new T_id("writeReal");
  Header* writeReal_Header = new Header(procedure,wrReal,list);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(writeReal_Header,nullptr);
/*-------------------------------------------------------*/

/*-------------------WriteString------------------------*/
  // Parameters
  n = new T_id("s");
  listab = new std::list<T_id*> ;
  listab->push_back(n);
  
  //Form of header
  forma = new Formal(refernce,listab,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* wrStr = new T_id("writeString");
  Header* writeStr_Header = new Header(procedure,wrStr,list);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(writeStr_Header,nullptr);
/*-------------------------------------------------------*/

/**********************READ-Func******************************/



/*-------------------ReadInt------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;
  //listab->push_back(n);
  
  //Form of header
  forma = new Formal(value,listab,typeVoid);
  list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* readInt = new T_id("readInteger");
  Header* readInteger_Header = new Header(function,readInt,list,typeInteger);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(readInteger_Header,nullptr);
/*-------------------------------------------------------*/

/*-------------------ReadBoolean------------------------*/
  // Parameters
  n = new T_id("b");
  listab = new std::list<T_id*> ;
  //listab->push_back(n);
  
  //Form of header
  forma = new Formal(value,listab,typeVoid);
  list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* readBool = new T_id("readBoolean");
  Header* readBoolean_Header = new Header(function,readBool,list,typeBoolean);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(readBoolean_Header,nullptr);
/*-------------------------------------------------------*/

/*-------------------ReadChar------------------------*/
  // Parameters
   n = new T_id("i");
  listab = new std::list<T_id*> ;
  //listab->push_back(n);
  
  //Form of header
  forma = new Formal(value,listab,typeVoid);
  list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* readChar = new T_id("readChar");
  Header* readChar_Header = new Header(function,readChar,list,typeChar);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(readChar_Header,nullptr);
/*-------------------------------------------------------*/

/*-------------------ReadReal------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;
  //listab->push_back(n);
  
  //Form of header
  forma = new Formal(value,listab,typeVoid);
  list = new std::list<Formal*> ;
  list->push_back(forma);

  //Creation of Header
  T_id* readReal = new T_id("readReal");
  Header* readReal_Header = new Header(function,readReal,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(readReal_Header,nullptr);
/*-------------------------------------------------------*/

/*-------------------ReadString------------------------*/
  // Parameters
  T_id* siize = new T_id("i");
  T_id* sii = new T_id("zo");
  listab = new std::list<T_id*> ;
  std::list<T_id*> *listab2 = new std::list<T_id*> ;
  listab->push_back(siize);
  listab2->push_back(sii);
  

  //Form of header
  forma = new Formal(value,listab,typeInteger);
  Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
   list->push_back(forma2);
  list->push_back(forma);
 


  //Creation of Header
  T_id* readStr = new T_id("readString");
  Header* readSt_Header = new Header(procedure,readStr,list);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(readSt_Header,nullptr);
/*-------------------------------------------------------*/

/*******************MATH-FUNC****************************/

/*-------------------abs------------------------*/
  // Parameters
   n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeInteger);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* abs = new T_id("abs");
  Header* abs_Header = new Header(function,abs,list,typeInteger);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(abs_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------fabs------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
   forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* fabs = new T_id("fabs");
  Header* fabs_Header = new Header(function,fabs,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(fabs_Header,nullptr);
/*-------------------------------------------------------*/

/*-------------------sqrt------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* sqrt = new T_id("sqrt");
  Header* sqrt_Header = new Header(function,sqrt,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(sqrt_Header,nullptr);
/*-------------------------------------------------------*/

/*-------------------sin------------------------*/
  // Parameters
   n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
   forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* sin = new T_id("sin");
  Header* sin_Header = new Header(function,sin,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(sin_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------cos------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* cos = new T_id("cos");
  Header* cos_Header = new Header(function,cos,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(cos_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------tan------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* tan = new T_id("tan");
  Header* tan_Header = new Header(function,tan,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(tan_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------arctan------------------------*/
  // Parameters
   n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* arctan = new T_id("arctan");
  Header* arctan_Header = new Header(function,arctan,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(arctan_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------exp------------------------*/
  // Parameters
   n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* exp = new T_id("exp");
  Header* exp_Header = new Header(function,exp,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(exp_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------ln------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* ln = new T_id("ln");
  Header* ln_Header = new Header(function,ln,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(ln_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------pi------------------------*/
  // Parameters
   n = new T_id("i");
  listab = new std::list<T_id*> ;  
  //listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeVoid);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* pi = new T_id("pi");
  Header* pi_Header = new Header(function,pi,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(pi_Header,nullptr);
/*-------------------------------------------------------*/

/************************Convert-func************************/

/*-------------------trunc------------------------*/
  // Parameters
   n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* trunc = new T_id("trunc");
  Header* trunc_Header = new Header(function,trunc,list,typeInteger);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(trunc_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------round------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeReal);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* round = new T_id("round");
  Header* round_Header = new Header(function,round,list,typeReal);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(round_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------ord------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeChar);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* ord = new T_id("ord");
  Header* ord_Header = new Header(function,ord,list,typeInteger);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(ord_Header,nullptr);
/*-------------------------------------------------------*/


/*-------------------chr------------------------*/
  // Parameters
  n = new T_id("i");
  listab = new std::list<T_id*> ;  
  listab->push_back(n);



  //Form of header
  forma = new Formal(value,listab,typeInteger);
  //Formal* forma2 = new Formal(refernce,listab2,typeIArray(typeChar));
  list = new std::list<Formal*> ;
  list->push_back(forma);
  //list->push_back(forma2);


  //Creation of Header
  T_id* chr = new T_id("chr");
  Header* chr_Header = new Header(function,chr,list,typeChar);
  //Local*  writeInteger = new Local(header,writeInteger_Header,nullptr);

  sem_header(chr_Header,nullptr);
/*-------------------------------------------------------*/

}