#ifndef dbscmml_DOUBLE_H
#define dbscmml_DOUBLE_H
void BSC_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CATB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCsymm_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CATB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CaATB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCsymm_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CaATB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CATBC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCsymm_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CATBC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CaATBC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCsymm_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CaATBC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CATBbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSCsymm_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CATBbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSC_MatMult_CaATBbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSCsymm_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSCskew_MatMult_CaATBbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);
#endif
