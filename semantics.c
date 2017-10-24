/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "semantics.h"

#define MAX_STACK_SIZE 256
#define false 0
#define true 1

t_attrib semantic_stack[MAX_STACK_SIZE];
int semantic_stack_size = 0;
pobject curFunction;

void semantic_stack_push(t_attrib attrib) {
  if (semantic_stack_size == MAX_STACK_SIZE)
    return;
  semantic_stack[semantic_stack_size++] = attrib;
}

void semantic_stack_pop () {
  if (semantic_stack_size == 0)
    return;
  semantic_stack_size--;
}

t_attrib semantic_stack_top () {
  if (semantic_stack_size == 0)
    return (t_attrib){}; // Error
  return semantic_stack[semantic_stack_size-1];
}

void semantics(int rule) {
  // TODO
  static int name,n,l,l1,l2;
  static pobject p,t,f;
  static t_attrib IDD_static,IDU_static,ID_static,T_static,LI_static,LI0_static,LI1_static,TRU_static,FALS_static,STR_static,CHR_static,NUM_static,DC_static,DC0_static,DC1_static,LP_static,LP0_static,LP1_static,E_static,E0_static,E1_static,L_static,L0_static,L1_static,R_static,R0_static,R1_static,Y_static,Y0_static,Y1_static,F_static,F0_static,F1_static,LV_static,LV0_static,LV1_static,MC_static,LE_static,LE0_static,LE1_static,MT_static,ME_static,MW_static;

  switch(rule){
    case RULE_P_0:
      break;
    case RULE_LDE_0:
      break;
    case RULE_LDE_1:
      break;
    case RULE_DE_0:
      break;
    case RULE_DE_1:
      break;
    case RULE_T_0:
      T_static.type = T;
      T_static.nSize = 1;
      semantic_stack_push(T_static);
      break;
    case RULE_T_1:
      T_static.type = T;
      T_static.nSize = 1;
      semantic_stack_push(T_static);
      break;
    case RULE_T_2:
      T_static.type = T;
      T_static.nSize = 1;
      semantic_stack_push(T_static);
      break;
    case RULE_T_3:
      T_static.type = T;
      T_static.nSize = 1;
      semantic_stack_push(T_static);
      break;
    case RULE_T_4:
      IDU_static = semantic_stack_top();
      p = IDU_static.ID.obj;
      semantic_stack_pop();
      
      if(IS_TYPE_KIND(p->kind) || p->kind == KIND_UNIVERSAL){
          T_static.T.type = p;
          if(p->kind == KIND_ALIAS_TYPE){
              T_static.nSize = p->Alias.nSize;
          }
          else if(p->kind == KIND_ARRAY_TYPE){
              T_static.nSize = p->Array.nSize;
          }
          else if(p->kind == KIND_STRUCT_TYPE){
              T_static.nSize = p->Struct.nSize;
          }
      }
      else{
          //T_static.T.type = pUniversal;
          T_static.nSize = 0;
          //Error
      }
      T_static.type = T;
      semantic_stack_push(T_static);
      break;
    case RULE_DT_0:
      T_static = semantic_stack_top();
      semantic_stack_pop();
      NUM_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      
      p = IDD_static.ID.obj;
      n = NUM_static.NUM.val;
      t = T_static.T.type;
      
      p->kind = KIND_ARRAY_TYPE;
      p->Array.nNumElems = n;
      p->Array.pElemType = t;
      p->Array.nSize = n * T_static.nSize;
      break;
    case RULE_DT_1:
      DC_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      
      p = IDD_static.ID.obj;
      p->kind = KIND_STRUCT_TYPE;
      p->Struct.pFields = DC_static.DC.list;
      p->Struct.nSize = DC_static.nSize;
      end_block();
      break;
    case RULE_DT_2:
      T_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      
      p = IDD_static.ID.obj;
      t = T_static.T.type;
      
      p->kind = KIND_ALIAS_TYPE;
      p->Alias.pBaseType = t;
      p->Alias.nSize = T_static.nSize;
      break;
    case RULE_DC_0:
      T_static = semantic_stack_top();
      semantic_stack_pop();
      LI_static = semantic_stack_top();
      semantic_stack_pop();
      DC1_static = semantic_stack_top();
      semantic_stack_pop();
      
      p = LI_static.LI.list;
      t = T_static.T.type;
      n = DC1_static.nSize;
      
      while( p != NULL && p->kind == KIND_UNDEFINED){
          p->kind = KIND_FIELD;
          p->Field.pType = t;
          p->Field.nIndex = n;
          p->Field.nSize = T_static.nSize;
          n = n + T_static.nSize;
          p = p->next;
      }
      
      DC0_static.DC.list = DC1_static.DC.list;
      DC0_static.nSize = n;
      DC0_static.type = DC;
      semantic_stack_push(DC0_static);
      break;
    case RULE_DC_1:
      T_static = semantic_stack_top();
      semantic_stack_pop();
      LI_static = semantic_stack_top();
      semantic_stack_pop();
      
      p = LI_static.LI.list;
      t = T_static.T.type;
      n = 0;
      while( p != NULL && p->kind == KIND_UNDEFINED){
          p->kind = KIND_FIELD;
          p->Field.pType = t;
          p->Field.nSize = T_static.nSize;
          p->Field.nIndex = n;
          n = n + T_static.nSize;
          p = p->next;
      }
      DC_static.DC.list = LI_static.LI.list;
      DC_static.nSize = n;
      DC_static.type = DC;
      semantic_stack_push(DC_static);
      break;
    case RULE_DF_0:
      end_block();
      /*fpos_t currentPos;
      fgetpos(out,&currentPos);
      fsetpos(out,&functionVarPos);
      fprintf(out,"%d",f->_.Function.nVars-f->_.Function.nParams);
      fsetpos(out,&currentPos);
      fprintf(out,"END_FUNC\n");*/
      break;
    case RULE_LP_0:
      T_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      LP1_static = semantic_stack_top();
      semantic_stack_pop();
      
      p = IDD_static.ID.obj;
      t = T_static.T.type;
      n = LP1_static.nSize;
      
      p->kind = KIND_PARAM;
      p->Param.pType = t;
      p->Param.nIndex = n;
      p->Param.nSize = T_static.nSize;
      
      LP0_static.LP.list = LP1_static.LP.list;
      LP0_static.nSize = n + T_static.nSize;
      LP0_static.type = LP;
      semantic_stack_push(LP0_static);
      break;
    case RULE_LP_1:
      T_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      
      p = IDD_static.ID.obj;
      t = T_static.T.type;
      p->kind = KIND_PARAM;
      p->Param.pType = t;
      p->Param.nIndex = 0;
      p->Param.nSize = T_static.nSize;
      LP_static.LP.list = p;
      LP_static.nSize = T_static.nSize;
      LP_static.type = LP;
      
      semantic_stack_push(LP_static);
      break;
    case RULE_B_0:
      break;
    case RULE_LDV_0:
      break;
    case RULE_LDV_1:
      break;
    case RULE_LS_0:
      break;
    case RULE_LS_1:
      break;
    case RULE_DV_0:
      T_static = semantic_stack_top();
      t = T_static.T.type;
      semantic_stack_pop();
      LI_static = semantic_stack_top();
      semantic_stack_pop();
      p = LI_static.LI.list;
      n = curFunction->Function.nVars;
      
      while(p != NULL && p->kind == KIND_UNDEFINED){
          p->kind = KIND_VAR;
          p->Var.pType = t;
          p->Var.nSize = T_static.nSize;
          p->Var.nIndex = n;
          
          n += T_static.nSize;
          p = p->next;
      }
      
      curFunction->Function.nVars = n;
      break;
    case RULE_LI_0:
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      LI1_static = semantic_stack_top();
      semantic_stack_pop();
      LI0_static.LI.list = LI1_static.LI.list;
      LI0_static.type = LI;
      semantic_stack_push(LI0_static);
      break;
    case RULE_LI_1:
      IDD_static = semantic_stack_top();
      LI_static.LI.list = IDD_static.ID.obj;
      LI_static.type = LI;
      semantic_stack_pop();
      semantic_stack_push(LI_static);
      break;
    case RULE_S_0:
      MT_static = semantic_stack_top();
      semantic_stack_pop();
      E_static = semantic_stack_top();
      semantic_stack_pop();
      
      t = E_static.E.type;
      //if( !check_types(t,pBool)){//Error}
      
      //fprintf(out,"L%d\n",MT_._.MT.label);
      break;
    case RULE_S_1:
      ME_static = semantic_stack_top();
      semantic_stack_pop();
      MT_static = semantic_stack_top();
      semantic_stack_pop();
      E_static = semantic_stack_top();
      semantic_stack_pop();
      
      l = ME_static.ME.label;
      
      t = E_static.E.type;
      //if( !check_types(t,pBool)){//Error}
      //fprintf(out,"L%d\n",l);
      break;
    case RULE_S_2:
      MT_static = semantic_stack_top();
      semantic_stack_pop();
      E_static = semantic_stack_top();
      semantic_stack_pop();
      MW_static = semantic_stack_top();
      semantic_stack_pop();
      
      l1 = MW_static.MW.label;
      l2 = MT_static.MT.label;
      
      t = E_static.E.type;
      //if( !check_types(t,pBool)){//Error}
      
      //fprintf(out,"\tJMP_BW L%d\nL%d\n",l1,l2);
      break;
    case RULE_S_3:
      E_static = semantic_stack_top();
      semantic_stack_pop();
      MW_static = semantic_stack_top();
      semantic_stack_pop();

      l = MW_static.MW.label;
      
      t = E_static.E.type;
      //if( !check_types(t,pBool)){//Error}
      
      //fprintf(out,"\tNOT\n\tTJMP_BW L%d\n",l);
      break;
    case RULE_S_4:
      end_block();
      break;
    case RULE_S_5:
      E_static = semantic_stack_top();
      semantic_stack_pop();
      //fprintf(out,"\tPOP\n");
      break;
    case RULE_S_6:
      break;
    case RULE_S_7:
      break;
    case RULE_E_0:
      L_static = semantic_stack_top();
      semantic_stack_pop();
      E1_static = semantic_stack_top();
      semantic_stack_pop();
      //if( !check_types(E1_static.E.type,pBool)){//Error}
      
      //if( !check_types(L_static.L.type,pBool)){//Error}
      
      E0_static.E.type = pBool;
      E0_static.type = E;
      semantic_stack_push(E0_static);
      //fprintf(out,"\tAND\n");
      break;
    case RULE_E_1:
      L_static = semantic_stack_top();
      semantic_stack_pop();
      E1_static = semantic_stack_top();
      semantic_stack_pop();
      //if( !check_types(E1_._.E.type,pBool)){Error(ERR_BOOL_TYPE_EXPECTED);}
      
      //if( !check_types(L_._.L.type,pBool)){Error(ERR_BOOL_TYPE_EXPECTED);}
      
      E0_static.E.type = pBool;
      E0_static.type = E;
      semantic_stack_push(E0_static);
      //fprintf(out,"\tOR\n");
      break;
    case RULE_E_2:
      L_static = semantic_stack_top();
      semantic_stack_pop();
      E_static.E.type = L_static.L.type;
      E_static.type = E;
      semantic_stack_push(E_static);
      break;
    case RULE_L_0:
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
      
      //fprintf(out,"\tLT\n");
      break;
    case RULE_L_1:
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
      //fprintf(out,"\tGT\n");
      break;
    case RULE_L_2:
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
      //fprintf(out,"\tLE\n");
      break;
    case RULE_L_3:
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
      //fprintf(out,"\tGE\n");
      break;
    case RULE_L_4:
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
      //fprintf(out,"\tEQ\n");
      break;
    case RULE_L_5:
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
      L0_static.L.type = pBool;
      L0_static.type = L;
      semantic_stack_push(L0_static);
      //fprintf(out,"\tNE\n");
      break;
    case RULE_L_6:
      R_static = semantic_stack_top();
      semantic_stack_pop();
      L_static.L.type = R_static.R.type;
      L_static.type = L;
      semantic_stack_push(L_static);
      break;
    case RULE_R_0:
      Y_static = semantic_stack_top();
      semantic_stack_pop();
      R1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( ! check_types(R1_._.R.type,K_._.K.type)){Error(ERR_TYPE_MISMATCH);}
      
      //if( !check_types(R1_._.R.type,pInt) && !check_types(R1_._.R.type,pString)){Error(ERR_INVALID_TYPE);}
      
      R0_static.R.type = R1_static.R.type;
      R0_static.type = R;
      semantic_stack_push(R0_static);
      //fprintf(out,"\tADD\n");
      break;
    case RULE_R_1:
      Y_static = semantic_stack_top();
      semantic_stack_pop();
      R1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( ! check_types(R1_._.R.type,K_._.K.type)){Error(ERR_TYPE_MISMATCH);}
      
      //if( !check_types(R1_._.R.type,pInt)){Error(ERR_INVALID_TYPE);}
      
      R0_static.R.type = R1_static.R.type;
      R0_static.type = R;
      semantic_stack_push(R0_static);
      //fprintf(out,"\tSUB\n");
      break;
    case RULE_R_2:
      Y_static = semantic_stack_top();
      semantic_stack_pop();
      R_static.R.type = Y_static.Y.type;
      R_static.type = R;
      semantic_stack_push(R_static);
      break;
    case RULE_Y_0:
      F_static = semantic_stack_top();
      semantic_stack_pop();
      Y1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( !check_types(K1_._.K.type,F_._.F.type)){Error(ERR_TYPE_MISMATCH);}
      
      //if( !check_types(K1_._.K.type,pInt)){Error(ERR_INVALID_TYPE);}
      
      Y0_static.Y.type = Y1_static.Y.type;
      Y0_static.type = Y;
      semantic_stack_push(Y0_static);
      //fprintf(out,"\tMUL\n");
      break;
    case RULE_Y_1:
      F_static = semantic_stack_top();
      semantic_stack_pop();
      Y1_static = semantic_stack_top();
      semantic_stack_pop();
      
      //if( !check_types(K1_._.K.type,F_._.F.type)){Error(ERR_TYPE_MISMATCH);}
      
      //if( !check_types(K1_._.K.type,pInt)){Error(ERR_INVALID_TYPE);}
      
      Y0_static.Y.type = Y1_static.Y.type;
      Y0_static.type = Y;
      semantic_stack_push(Y0_static);
      //fprintf(out,"\tDIV\n");
      break;
    case RULE_Y_2:
      F_static = semantic_stack_top();
      semantic_stack_pop();
      Y_static.Y.type = F_static.F.type;
      Y_static.type = Y;
      semantic_stack_push(Y_static);
      break;
    case RULE_F_0:
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      
      n = LV_static.LV.type->Type.nSize;
      
      F_static.F.type = LV_static.LV.type;
      F_static.type = F;
      semantic_stack_push(F_static);
      //fprintf(out,"\tDE_REF %d\n",n);
      break;
    case RULE_F_1:
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}
      
      F_static.F.type = pInt;
      F_static.type = F;
      //fprintf(out,"\tDUP\n\tDUP\n\tDE_REF 1\n");
      //fprintf(out,"\tINC\n\tSTORE_REF 1\n\tDE_REF 1\n");
      semantic_stack_push(F_static);
      break;
    case RULE_F_2:
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}
      
      F_static.F.type = LV_static.LV.type;
      F_static.type = F;
      semantic_stack_push(F_static);
      //fprintf(out,"\tDUP\n\tDUP\n\tDE_REF 1\n");
      //fprintf(out,"\tDEC\n\tSTORE_REF 1\n\tDE_REF 1\n");
      break;
    case RULE_F_3:
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}
      
      F_static.F.type = LV_static.LV.type;
      F_static.type = F;
      semantic_stack_push(F_static);
      //fprintf(out,"\tDUP\n\tDUP\n\tDE_REF 1\n");
      //fprintf(out,"\tINC\n\tSTORE_REF 1\n\tDE_REF 1\n");
      //fprintf(out,"\tDEC\n");
      break;
    case RULE_F_4:
      LV_static = semantic_stack_top();
      semantic_stack_pop();
      t = LV_static.LV.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}
      
      F_static.F.type = t;
      F_static.type = F;
      semantic_stack_push(F_static);
      //fprintf(out,"\tDUP\n\tDUP\n\tDE_REF 1\n");
      //fprintf(out,"\tDEC\n\tSTORE_REF 1\n\tDE_REF 1\n");
      //fprintf(out,"\tINC\n");
      break;
    case RULE_F_5:
      E_static = semantic_stack_top();
      semantic_stack_pop();
      
      F_static.F.type = E_static.E.type;
      F_static.type = F;
      semantic_stack_push(F_static);
      break;
    case RULE_F_6:
      LE_static = semantic_stack_top();
      semantic_stack_pop();
      MC_static = semantic_stack_top();
      semantic_stack_pop();
      IDU_static = semantic_stack_top();
      semantic_stack_pop();
      f = IDU_static.ID.obj;
      F_static.F.type = MC_static.MC.type;
      //if(!LE_static.LE.err){
          //if(LE_._.LE.n-1 < f->_.Function.nParams && LE_._.LE.n != 0){
              //Error(ERR_TOO_FEW_ARGS);
          //}
         //else if(LE_._.LE.n-1 > f->_.Function.nParams){
              //Error(ERR_TOO_MANY_ARGS);
          //}
      //}
      F_static.type = F;
      semantic_stack_push(F_static);
      //fprintf(out,"\tCALL %d\n",f->_.Function.nIndex);
      break;
    case RULE_F_7:
      F1_static = semantic_stack_top();
      semantic_stack_pop();
      
      t = F1_static.F.type;
      //if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}
      
      F0_static.F.type = t;
      F0_static.type = F;
      semantic_stack_push(F0_static);
      //fprintf(out,"\tNEG\n");
      break;
    case RULE_F_8:
      F1_static = semantic_stack_top();
      semantic_stack_pop();
      
      t = F1_static.F.type;
      //if( !check_types(t,pBool)){Error(ERR_INVALID_TYPE);}
      
      F0_static.F.type = t;
      F0_static.type = F;
      semantic_stack_push(F0_static);
      //fprintf(out,"\tNOT\n");
      break;
    case RULE_F_9:
      TRU_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pBool;
      F_static.type = F;
      semantic_stack_push(F_static);
      //fprintf(out,"\tLOAD_TRUE\n");
      break;
    case RULE_F_10:
      FALS_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pBool;
      F_static.type = F;
      semantic_stack_push(F_static);
      //fprintf(out,"\tLOAD_FALSE\n");
      break;
    case RULE_F_11:
      CHR_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pChar;
      F_static.type = F;
      semantic_stack_push(F_static);
      n = secondary_token;
      //fprintf(out,"\tLOAD_CONST %d\n",n);
      break;
    case RULE_F_12:
      STR_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pString;
      F_static.type = F;
      semantic_stack_push(F_static);
      n = secondary_token;
      //fprintf(out,"\tLOAD_CONST %d\n",n);
      break;
    case RULE_F_13:
      STR_static = semantic_stack_top();
      semantic_stack_pop();
      F_static.F.type = pInt;
      F_static.type = F;
      semantic_stack_push(F_static);
      n = secondary_token;
      //fprintf(out,"\tLOAD_CONST %d\n",n);
      break;
    case RULE_LE_0:
      E_static = semantic_stack_top();
      semantic_stack_pop();
      MC_static = semantic_stack_top();
      
      LE_static.LE.param = NULL;
      LE_static.LE.err = MC_static.MC.err;
      n = 1;
      if( !MC_static.MC.err){
          p = MC_static.MC.param;
          if(p == NULL){
              //Error(ERR_TOO_MANY_ARGS);
              LE_static.LE.err = true;
          }
          else{
              //if(!check_types(p->_.Param.pType,E_._.E.type)){Error(ERR_PARAM_TYPE);}
              LE_static.LE.param = p->next;
              LE_static.LE.n = n+1;
          }
      }
      LE_static.type = LE;
      semantic_stack_push(LE_static);
      break;
    case RULE_LE_1:
      E_static = semantic_stack_top();
      semantic_stack_pop();
      LE1_static = semantic_stack_top();
      semantic_stack_pop();
      LE0_static.LE.param = NULL;
      LE0_static.LE.err = L1_static.LE.err;

      n = LE1_static.LE.n;
      if(!LE1_static.LE.err){
          p = LE1_static.LE.param;
          if(p == NULL){
              //Error(ERR_TOO_MANY_ARGS);
              LE0_static.LE.err = true;
          }
          else{
              //if(!check_types(p->_.Param.pType,E_._.E.type)){Error(ERR_PARAM_TYPE);}
              LE0_static.LE.param = p->next;
              LE0_static.LE.n = n + 1;
          }
      }
      LE0_static.type = LE;
      semantic_stack_push(LE0_static);
      break;
    case RULE_LV_0:
      ID_static = semantic_stack_top();
      semantic_stack_pop();
      LV1_static = semantic_stack_top();
      semantic_stack_pop();
      
      t = LV1_static.LV.type;
      if( t-> kind != KIND_STRUCT_TYPE){
          if(t->kind != KIND_UNIVERSAL){
              //Error( ERR_KIND_NOT_STRUCT);
          }
          LV0_static.LV.type = pUniversal;
      }
      else{
          p = t->Struct.pFields;
          while(p!=NULL){
              if(p->name == ID_static.ID.name){
                  break;
              }
              p = p->next;
          }
          if(p == NULL){
              //Error(ERR_FIELD_NOT_DECL);
              LV0_static.LV.type = pUniversal;
          }
          else{
              LV0_static.LV.type = p->Field.pType;
              LV0_static.LV.type->Type.nSize = p->Field.nSize;
          }
      }
      
      LV0_static.type = LV;
      semantic_stack_push(LV0_static);
      //fprintf(out,"\tADD %d\n",p->_.Field.nIndex);
      break;
    case RULE_LV_1:
      E_static = semantic_stack_top();
      semantic_stack_pop();
      LV1_static = semantic_stack_top();
      semantic_stack_pop();
      
      t = LV1_static.LV.type;
      if(check_types(t,pString)){
          LV0_static.LV.type = pChar;
      }
      else if(t->kind != KIND_ARRAY_TYPE){
          if(t->kind != KIND_UNIVERSAL){
              //Error(ERR_KIND_NOT_ARRAY);
          }
          LV0_static.LV.type = pUniversal;
      }
      else{
          LV0_static.LV.type = t->Array.pElemType;
          n = t->Array.pElemType->Struct.nSize;
          //fprintf(out,"\tMUL %d\n\tADD\n",n);
      }
      
      if( !check_types(E_static.E.type,pInt)){
          //Error(ERR_INVALID_INDEX_TYPE);
      }
      
      LV0_static.type = LV;
      semantic_stack_push(LV0_static);
      break;
    case RULE_LV_2:
      IDU_static = semantic_stack_top();
      semantic_stack_pop();
      
      p = IDU_static.ID.obj;
      if(p->kind != KIND_VAR && p->kind != KIND_PARAM){
          if(p->kind != KIND_UNIVERSAL){
              //Error(ERR_KIND_NOT_VAR);
          }
          LV_static.LV.type = pUniversal;
      }
      else{
          LV_static.LV.type = p->Var.pType;
          LV_static.LV.type->Type.nSize = p->Var.nSize;
      }
      LV_static.type = LV;
      semantic_stack_push(LV_static);
      //fprintf(out,"\tLOAD_REF %d\n",p->_.Var.nIndex);
      break;
    case RULE_NB_0:
      new_block();
      break;
    case RULE_MF_0:
      T_static = semantic_stack_top();
      semantic_stack_pop();
      LP_static = semantic_stack_top();
      semantic_stack_pop();
      IDD_static = semantic_stack_top();
      semantic_stack_pop();
      
      f = IDD_static.ID.obj;
      f->kind = KIND_FUNCTION;
      f->Function.pRetType = T_static.T.type;
      f->Function.pParams = LP_static.LP.list;
      f->Function.nParams = LP_static.nSize;
      f->Function.nVars = LP_static.nSize;
      curFunction = f;
      
      /*fprintf(out,"BEGIN_FUNC %d %d ",f->_.Function.nIndex,
              f->_.Function.nParams
              );
      fgetpos(out,&functionVarPos);
      fprintf(out,"                        \n");*/
      break;
    case RULE_MC_0:
      IDU_static = semantic_stack_top();
      f = IDU_static.ID.obj;
      
      if(f->kind != KIND_FUNCTION){
          //Error(ERR_KIND_NOT_FUNCTION);
          MC_static.MC.type = pUniversal;
          MC_static.MC.param = NULL;
          MC_static.MC.err = true;
      }
      else{
          MC_static.MC.type = f->Function.pRetType;
          MC_static.MC.param = f->Function.pParams;
          MC_static.MC.err = false;
      }
      MC_static.type = MC;
      semantic_stack_push(MC_static);
      break;
    case RULE_IDD_0:
      name = secondary_token;
      IDD_static.ID.name = name;
      if((p = search_symbol_in_scope(name)) != NULL){
        //Error
      }
      else
        p = define_symbol(name);
      p->kind = KIND_UNDEFINED;
      IDD_static.ID.obj = p;
      semantic_stack_push(IDD_static);
      break;
    case RULE_IDU_0:
      name = secondary_token;
      IDU_static.ID.name = name;
      
      if((p = search_symbol_globally(name)) == NULL){
          //Error
          p = define_symbol(name);
      }
      IDU_static.ID.obj = p;
      semantic_stack_push(IDU_static);
      break;
    case RULE_ID_0:
      name = secondary_token;
      ID_static.ID.name = name;
      ID_static.ID.obj = NULL;
      semantic_stack_push(ID_static);
      break;
    case RULE_TRUE_0:
      TRU_static.type = TRUE;
      TRU_static.TRU.val = true;
      TRU_static.TRU.type = pBool;
      semantic_stack_push(TRU_static);
      break;
    case RULE_FALSE_0:
      FALS_static.type = FALSE;
      FALS_static.FALS.val = false;
      FALS_static.FALS.type = pBool;
      semantic_stack_push(FALS_static);
      break;
    case RULE_CHR_0:
      CHR_static.type = CHR;
      CHR_static.CHR.type = pChar;
      CHR_static.CHR.pos = secondary_token;
      CHR_static.CHR.val = get_char_const(secondary_token);
      semantic_stack_push(CHR_static);
      break;
    case RULE_STR_0:
      STR_static.type = STR;
      STR_static.STR.type = pString;
      STR_static.STR.pos = secondary_token;
      STR_static.STR.val = get_string_const(secondary_token);
      semantic_stack_push(STR_static);
      break;
    case RULE_NUM_0:
      NUM_static.type = NUM;
      NUM_static.NUM.type = pInt;
      NUM_static.NUM.pos = secondary_token;
      NUM_static.NUM.val = get_numeral_const(secondary_token);
      semantic_stack_push(NUM_static);
      break;

  }
}