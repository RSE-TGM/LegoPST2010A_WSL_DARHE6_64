#ifndef dcoomml_DOUBLE_H
#define dcoomml_DOUBLE_H
void COO_MatMult_CAB_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COOsymm_MatMult_CAB_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COOskew_MatMult_CAB_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COO_MatMult_CaAB_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COOsymm_MatMult_CaAB_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COOskew_MatMult_CaAB_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COO_MatMult_CABC_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COOsymm_MatMult_CABC_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COOskew_MatMult_CABC_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COO_MatMult_CaABC_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COOsymm_MatMult_CaABC_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COOskew_MatMult_CaABC_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, 
                 double *c, const int ldc, 
                 const int ind_base);

void COO_MatMult_CABbC_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, const double beta,
                 double *c, const int ldc, 
                 const int ind_base);

void COOsymm_MatMult_CABbC_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, const double beta,
                 double *c, const int ldc, 
                 const int ind_base);

void COOskew_MatMult_CABbC_double(
                 const int m, const int n, const int k, 
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, const double beta,
                 double *c, const int ldc, 
                 const int ind_base);

void COO_MatMult_CaABbC_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, const double beta,
                 double *c, const int ldc, 
                 const int ind_base);

void COOsymm_MatMult_CaABbC_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, const double beta,
                 double *c, const int ldc, 
                 const int ind_base);

void COOskew_MatMult_CaABbC_double(
                 const int m, const int n, const int k, const double alpha,
                 const double *val, const int *indx, const int *jndx,
                 const int nnz, 
                 const double *b, const int ldb, const double beta,
                 double *c, const int ldc, 
                 const int ind_base);
#endif
