#ifndef dbsrvml_DOUBLE_H
#define dbsrvml_DOUBLE_H
void BSR_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CATB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRsymm_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CATB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CaATB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRsymm_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CaATB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CATBC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRsymm_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CATBC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CaATBC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRsymm_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CaATBC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CATBbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSRsymm_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CATBbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSR_VecMult_CaATBbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSRsymm_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSRskew_VecMult_CaATBbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);
#endif
