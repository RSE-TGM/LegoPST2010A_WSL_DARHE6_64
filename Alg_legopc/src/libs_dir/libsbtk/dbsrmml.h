#ifndef dbsrmml_DOUBLE_H
#define dbsrmml_DOUBLE_H
void BSR_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CATB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRsymm_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CATB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CaATB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRsymm_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CaATB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CATBC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRsymm_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CATBC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CaATBC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRsymm_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CaATBC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CATBbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSRsymm_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CATBbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSR_MatMult_CaATBbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSRsymm_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BSRskew_MatMult_CaATBbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);
#endif
