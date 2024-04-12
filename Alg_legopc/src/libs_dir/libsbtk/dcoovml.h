#ifndef dcoovml_DOUBLE_H
#define dcoovml_DOUBLE_H
void COO_VecMult_CAB_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COOsymm_VecMult_CAB_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COOskew_VecMult_CAB_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COO_VecMult_CaAB_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COOsymm_VecMult_CaAB_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COOskew_VecMult_CaAB_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COO_VecMult_CABC_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COOsymm_VecMult_CABC_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COOskew_VecMult_CABC_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COO_VecMult_CaABC_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COOsymm_VecMult_CaABC_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COOskew_VecMult_CaABC_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  
                 double *c,  
                 const int ind_base);

void COO_VecMult_CABbC_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  const double beta,
                 double *c,  
                 const int ind_base);

void COOsymm_VecMult_CABbC_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  const double beta,
                 double *c,  
                 const int ind_base);

void COOskew_VecMult_CABbC_double(
                 const int m,  const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  const double beta,
                 double *c,  
                 const int ind_base);

void COO_VecMult_CaABbC_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  const double beta,
                 double *c,  
                 const int ind_base);

void COOsymm_VecMult_CaABbC_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  const double beta,
                 double *c,  
                 const int ind_base);

void COOskew_VecMult_CaABbC_double(
                 const int m,  const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b,  const double beta,
                 double *c,  
                 const int ind_base);
#endif
