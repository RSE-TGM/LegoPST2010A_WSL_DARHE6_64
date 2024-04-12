#ifndef dvbrmml_DOUBLE_H
#define dvbrmml_DOUBLE_H
void VBR_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CATB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRsymm_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CAB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CATB_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CaATB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRsymm_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CaAB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CaATB_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CATBC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRsymm_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CABC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CATBC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CaATBC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRsymm_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CaABC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CaATBC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CATBbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBRsymm_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CABbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CATBbC_double(
                 const int mb, const int n, const int kb, 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBR_MatMult_CaATBbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBRsymm_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CaABbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);

void VBRskew_MatMult_CaATBbC_double(
                 const int mb, const int n, const int kb, const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 const int ind_base);
#endif
