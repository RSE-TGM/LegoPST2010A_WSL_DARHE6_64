#ifndef dbsrvtsl_DOUBLE_H
#define dbsrvtsl_DOUBLE_H
void BSR_VecTriangSlvLU_CAB_double(
                 const int mb,  
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvUU_CAB_double(
                 const int mb, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvLU_CATB_double(
                 const int mb, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvUU_CATB_double(
                 const int mb,  
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvLU_CaAB_double(
                 const int mb,  
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvUU_CaAB_double(
                 const int mb, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvLU_CaATB_double(
                 const int mb, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvUU_CaATB_double(
                 const int mb,  
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvLU_CABC_double(
                 const int mb,  
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CABC_double(
                 const int mb, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CATBC_double(
                 const int mb, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CATBC_double(
                 const int mb,  
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaABC_double(
                 const int mb,  
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaABC_double(
                 const int mb, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaATBC_double(
                 const int mb, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaATBC_double(
                 const int mb,  
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CABbC_double(
                 const int mb,  
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CABbC_double(
                 const int mb, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CATBbC_double(
                 const int mb, 
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CATBbC_double(
                 const int mb,  
                  
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaABbC_double(
                 const int mb,  
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaABbC_double(
                 const int mb, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaATBbC_double(
                 const int mb, 
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaATBbC_double(
                 const int mb,  
                  
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDAB_double(
                 const int mb,  
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDAB_double(
                 const int mb, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDATB_double(
                 const int mb, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDATB_double(
                 const int mb,  
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDAB_double(
                 const int mb,  
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDAB_double(
                 const int mb, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDATB_double(
                 const int mb, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDATB_double(
                 const int mb,  
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDABC_double(
                 const int mb,  
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDABC_double(
                 const int mb, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDATBC_double(
                 const int mb, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDATBC_double(
                 const int mb,  
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDABC_double(
                 const int mb,  
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDABC_double(
                 const int mb, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDATBC_double(
                 const int mb, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDATBC_double(
                 const int mb,  
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDABbC_double(
                 const int mb,  
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDABbC_double(
                 const int mb, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDATBbC_double(
                 const int mb, 
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDATBbC_double(
                 const int mb,  
                 const double *dvl, 
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDABbC_double(
                 const int mb,  
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDABbC_double(
                 const int mb, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDATBbC_double(
                 const int mb, 
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDATBbC_double(
                 const int mb,  
                 const double *dvl, 
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CADB_double(
                 const int mb,  
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvUU_CADB_double(
                 const int mb, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvLU_CATDB_double(
                 const int mb, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvUU_CATDB_double(
                 const int mb,  
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvLU_CaADB_double(
                 const int mb,  
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvUU_CaADB_double(
                 const int mb, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvLU_CaATDB_double(
                 const int mb, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvUU_CaATDB_double(
                 const int mb,  
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                  const int ind_base);

void BSR_VecTriangSlvLU_CADBC_double(
                 const int mb,  
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CADBC_double(
                 const int mb, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CATDBC_double(
                 const int mb, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CATDBC_double(
                 const int mb,  
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaADBC_double(
                 const int mb,  
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaADBC_double(
                 const int mb, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaATDBC_double(
                 const int mb, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaATDBC_double(
                 const int mb,  
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CADBbC_double(
                 const int mb,  
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CADBbC_double(
                 const int mb, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CATDBbC_double(
                 const int mb, 
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CATDBbC_double(
                 const int mb,  
                  const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaADBbC_double(
                 const int mb,  
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaADBbC_double(
                 const int mb, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaATDBbC_double(
                 const int mb, 
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaATDBbC_double(
                 const int mb,  
                  const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDADB_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDADB_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDATDB_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDATDB_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDADB_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDADB_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDATDB_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDATDB_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDADBC_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDADBC_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDATDBC_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDATDBC_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDADBC_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDADBC_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDATDBC_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDATDBC_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,   
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDADBbC_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDADBbC_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CDATDBbC_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CDATDBbC_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDADBbC_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDADBbC_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvLU_CaDATDBbC_double(
                 const int mb, 
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);

void BSR_VecTriangSlvUU_CaDATDBbC_double(
                 const int mb,  
                 const double *dvl, const double *dvr,
                 const double alpha,
                 const double *val, const int *bindx, 
                 const int *bpntrb, const int *bpntre, const int lb,
                 const double *b,  const double beta, 
                 double *c, 
                 double *work, const int ind_base);
#endif
