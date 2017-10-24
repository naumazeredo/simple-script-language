// auto-generated. DON'T MODIFY

/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#ifndef SSL_PARSER_GEN
#define SSL_PARSER_GEN

#include "lexer.h"

#define get_rule_len(r) rule[(r)][0]
#define get_rule_left(r) rule[(r)][1]

#define is_shift(p)     ((p)>0)
#define is_reduction(p) ((p)<0)
#define get_rule(p)     (-(p))

extern int rule[85][2];
extern int action[168][85];

typedef enum {
  EOF = TOKEN_NUM, DF, DE, DC, DV, DT, TRUE, IDD, LE, LDE, NB, NF, LI, LV, NUM, LS, LP, LDV, B, E, F, IDU, L, P, S, R, T, STR, Y, ID, ME, MF, FALSE, MC, CHR, MT, MW
} t_nonterminal;

enum {
  RULE_P_0,
  RULE_LDE_0,
  RULE_LDE_1,
  RULE_DE_0,
  RULE_DE_1,
  RULE_T_0,
  RULE_T_1,
  RULE_T_2,
  RULE_T_3,
  RULE_T_4,
  RULE_DT_0,
  RULE_DT_1,
  RULE_DT_2,
  RULE_DC_0,
  RULE_DC_1,
  RULE_DF_0,
  RULE_LP_0,
  RULE_LP_1,
  RULE_B_0,
  RULE_LDV_0,
  RULE_LDV_1,
  RULE_LS_0,
  RULE_LS_1,
  RULE_DV_0,
  RULE_LI_0,
  RULE_LI_1,
  RULE_S_0,
  RULE_S_1,
  RULE_S_2,
  RULE_S_3,
  RULE_S_4,
  RULE_S_5,
  RULE_S_6,
  RULE_S_7,
  RULE_E_0,
  RULE_E_1,
  RULE_E_2,
  RULE_L_0,
  RULE_L_1,
  RULE_L_2,
  RULE_L_3,
  RULE_L_4,
  RULE_L_5,
  RULE_L_6,
  RULE_R_0,
  RULE_R_1,
  RULE_R_2,
  RULE_Y_0,
  RULE_Y_1,
  RULE_Y_2,
  RULE_F_0,
  RULE_F_1,
  RULE_F_2,
  RULE_F_3,
  RULE_F_4,
  RULE_F_5,
  RULE_F_6,
  RULE_F_7,
  RULE_F_8,
  RULE_F_9,
  RULE_F_10,
  RULE_F_11,
  RULE_F_12,
  RULE_F_13,
  RULE_LE_0,
  RULE_LE_1,
  RULE_LV_0,
  RULE_LV_1,
  RULE_LV_2,
  RULE_NB_0,
  RULE_NF_0,
  RULE_MF_0,
  RULE_MT_0,
  RULE_ME_0,
  RULE_MW_0,
  RULE_MC_0,
  RULE_IDD_0,
  RULE_IDU_0,
  RULE_ID_0,
  RULE_TRUE_0,
  RULE_FALSE_0,
  RULE_CHR_0,
  RULE_STR_0,
  RULE_NUM_0
};

#endif //SSL_PARSER