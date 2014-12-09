#include "gameoflife.h"
#include <pthread.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
void gol_parallel(bool*, int, int, int, int);
void *worker_thread(void *args);
void update(int iters, int row_lo, int row_hi, int m, int n, bool *cells, bool *cells_new);

void gol_cuda(char* cells, int n, int m, int iterations, int xBlockDim, int yBlockDim, int xThreadDim, int yThreadDim);

struct arg_struct {
  bool *cells;
  bool *cells_new;
  int   id;
  int   m;
  int   n;
  int   nthreads;
  int   iterations;

};

#ifdef __cplusplus
}
#endif
