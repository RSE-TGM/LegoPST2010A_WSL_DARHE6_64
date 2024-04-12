#ifndef dvbrvml_DOUBLE_H
#define dvbrvml_DOUBLE_H
void VBR_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CATB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRsymm_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CATB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CaATB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRsymm_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CaATB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CATBC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRsymm_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CATBC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CaATBC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRsymm_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CaATBC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,   
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CATBbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBRsymm_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CATBbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBR_VecMult_CaATBbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBRsymm_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void VBRskew_VecMult_CaATBbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);
#endif
