#ifndef dbscmtsl_DOUBLE_H
#define dbscmtsl_DOUBLE_H
void BSC_MatTriangSlvLU_CAB_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvUU_CAB_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvLU_CATB_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvUU_CATB_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvLU_CaAB_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvUU_CaAB_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvLU_CaATB_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvUU_CaATB_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvLU_CABC_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CABC_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CATBC_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CATBC_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaABC_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaABC_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaATBC_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaATBC_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CABbC_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CABbC_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CATBbC_double(
                 const int mb, const int n,
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CATBbC_double(
                 const int mb, const int n, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaABbC_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaABbC_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaATBbC_double(
                 const int mb, const int n,
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaATBbC_double(
                 const int mb, const int n, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDAB_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDAB_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDATB_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDATB_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDAB_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDAB_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDATB_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDATB_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDABC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDABC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDATBC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDATBC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDABC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDABC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDATBC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDATBC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDABbC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDABbC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDATBbC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDATBbC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDABbC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDABbC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDATBbC_double(
                 const int mb, const int n,
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDATBbC_double(
                 const int mb, const int n, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CADB_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvUU_CADB_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvLU_CATDB_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvUU_CATDB_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvLU_CaADB_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvUU_CaADB_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvLU_CaATDB_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvUU_CaATDB_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                  const int ind_base);

void BSC_MatTriangSlvLU_CADBC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CADBC_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CATDBC_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CATDBC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaADBC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaADBC_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaATDBC_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaATDBC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CADBbC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CADBbC_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CATDBbC_double(
                 const int mb, const int n,
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CATDBbC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaADBbC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaADBbC_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaATDBbC_double(
                 const int mb, const int n,
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaATDBbC_double(
                 const int mb, const int n, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDADB_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDADB_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDATDB_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDATDB_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDADB_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDADB_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDATDB_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDATDB_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDADBC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDADBC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDATDBC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDATDBC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDADBC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDADBC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDATDBC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDATDBC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb,  
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDADBbC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDADBbC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CDATDBbC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CDATDBbC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDADBbC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDADBbC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvLU_CaDATDBbC_double(
                 const int mb, const int n,
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);

void BSC_MatTriangSlvUU_CaDATDBbC_double(
                 const int mb, const int n, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b, const int ldb, const double beta, 
                 double *c, const int ldc,
                 double *work, const int ind_base);
#endif
