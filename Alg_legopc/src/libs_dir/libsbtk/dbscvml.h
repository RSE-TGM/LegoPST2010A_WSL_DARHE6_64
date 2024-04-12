#ifndef dbscvml_DOUBLE_H
#define dbscvml_DOUBLE_H
void BSC_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CATB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCsymm_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CATB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CaATB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCsymm_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CaATB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CATBC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCsymm_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CATBC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CaATBC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCsymm_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CaATBC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CATBbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSCsymm_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CATBbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSC_VecMult_CaATBbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSCsymm_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BSCskew_VecMult_CaATBbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);
#endif
