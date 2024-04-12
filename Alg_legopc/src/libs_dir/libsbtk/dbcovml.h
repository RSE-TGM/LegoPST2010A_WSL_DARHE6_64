#ifndef dbcovml_DOUBLE_H
#define dbcovml_DOUBLE_H
void BCO_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CATB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOsymm_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CAB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CATB_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CaATB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOsymm_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CaAB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CaATB_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CATBC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOsymm_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CABC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CATBC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CaATBC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOsymm_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CaABC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CaATBC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,   
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CATBbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCOsymm_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CABbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CATBbC_double(
                 const int mb,  const int kb, 
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCO_VecMult_CaATBbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCOsymm_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CaABbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx, 
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);

void BCOskew_VecMult_CaATBbC_double(
                 const int mb,  const int kb, const double alpha,
                 const double *val, const int *bindx, const int *bjndx,
                 const int bnnz, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 const int ind_base);
#endif
