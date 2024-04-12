#ifndef dbcomml_DOUBLE_H
#define dbcomml_DOUBLE_H
void BCO_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CATB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOsymm_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CATB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CaATB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOsymm_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CaATB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CATBC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOsymm_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CATBC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CaATBC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOsymm_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CaATBC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CATBbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCOsymm_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CATBbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCO_MatMult_CaATBbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCOsymm_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void BCOskew_MatMult_CaATBbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);
#endif
