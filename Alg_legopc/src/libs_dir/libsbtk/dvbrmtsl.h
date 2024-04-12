#ifndef dvbrmtsl_DOUBLE_H
#define dvbrmtsl_DOUBLE_H
void VBR_MatTriangSlvLU_CAB_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvUU_CAB_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvLU_CATB_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvUU_CATB_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvLU_CaAB_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvUU_CaAB_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvLU_CaATB_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvUU_CaATB_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvLU_CABC_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CABC_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CATBC_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CATBC_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaABC_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaABC_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaATBC_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaATBC_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CABbC_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CABbC_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CATBbC_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CATBbC_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaABbC_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaABbC_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaATBbC_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaATBbC_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDAB_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDAB_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDATB_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDATB_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDAB_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDAB_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDATB_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDATB_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDABC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDABC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDATBC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDATBC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDABC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDABC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDATBC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDATBC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDABbC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDABbC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDATBbC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDATBbC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDABbC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDABbC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDATBbC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDATBbC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CADB_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvUU_CADB_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvLU_CATDB_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvUU_CATDB_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvLU_CaADB_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvUU_CaADB_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvLU_CaATDB_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvUU_CaATDB_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void VBR_MatTriangSlvLU_CADBC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CADBC_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CATDBC_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CATDBC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaADBC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaADBC_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaATDBC_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaATDBC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CADBbC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CADBbC_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CATDBbC_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CATDBbC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaADBbC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaADBbC_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaATDBbC_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaATDBbC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDADB_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDADB_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDATDB_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDATDB_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDADB_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDADB_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDATDB_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDATDB_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDADBC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDADBC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDATDBC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDATDBC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDADBC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDADBC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDATDBC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDATDBC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDADBbC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDADBbC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CDATDBbC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CDATDBbC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDADBbC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDADBbC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvLU_CaDATDBbC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void VBR_MatTriangSlvUU_CaDATDBbC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *indx,
                 const int *bindx, const int *rpntr,
                 const int *cpntr, const int *bpntrb, const int *bpntre, 
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);
#endif
