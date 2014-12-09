#include "gol_parallel.h"

pthread_barrier_t barrier;
// Computes the given number of iterations for an n x m array of cells using
// the given number of threads.
void gol_parallel(bool* cells, int n, int m, int iterations, int nthreads) {
  pthread_t *threads;
  threads = malloc(sizeof(pthread_t)*nthreads);
  bool *cells_new = malloc(n * m * sizeof(bool));
  int i,j;

  pthread_barrier_init(&barrier, NULL, nthreads);

  for(i = 0; i < nthreads; i++){
    struct arg_struct *args = malloc(sizeof(struct arg_struct));

    // Set the data for the struct
    args->cells = cells;
    args->cells_new = cells_new;
    args->id = i;
    args->m = m;
    args->n = n;
    args->nthreads = nthreads;
    args->iterations = iterations;
    int rc = pthread_create(&threads[i], NULL, worker_thread, (void *) args);
    if(rc){
      printf("ERROR with pthread_create.\n");
      exit(EXIT_FAILURE);
    }
  }

  free(cells_new);
  pthread_barrier_destroy(&barrier);
}

void *worker_thread(void *args){
  struct arg_struct *aData = (struct arg_struct *) args;
  int thread_id = aData->id;
  int row_lo, row_hi;

  row_lo = (aData->n / aData->nthreads) * thread_id;

  if(thread_id + 1 == aData->nthreads){
    row_hi = aData->n;
  } else {
    row_hi = (aData->n / aData->nthreads) * (thread_id + 1);
  }
  update(aData->iterations, row_lo, row_hi, aData->m, aData->n, aData->cells, aData->cells_new);

  free(args);
  pthread_exit();
}

void update(int iters, int row_lo, int row_hi, int m, int n, bool *cells, bool *cells_new){
  int iter, i, j;
  bool *tmp;
  int neighbors;

  pthread_barrier_wait(&barrier);
  // Logic for this iteration of game of life in the rows from row_lo to row_high
  for(iter = 0; iter < iters; iter++){
    for(i = row_lo; i < row_hi; i++){
      for(j = 0; j < m; j++){
        neighbors = 0;

        if(i>0 && j>0) neighbors += cells[(i-1) * m + j-1] ? 1 : 0;
        if(i>0) neighbors += cells[(i-1) * m + j] ? 1 : 0;
        if(i>0 && j<m-1) neighbors += cells[(i-1) * m + j+1] ? 1 : 0;
        if(j>0) neighbors += cells[i * m + j-1] ? 1 : 0;
        if(j<m-1) neighbors += cells[i * m + j+1] ? 1 : 0;
        if(i<n-1 && j>0) neighbors += cells[(i+1) * m + j-1] ? 1 : 0;
        if(i<n-1) neighbors += cells[(i+1) * m + j] ? 1 : 0;
        if(i<n-1 && j<m-1) neighbors += cells[(i+1) * m + j+1] ? 1 : 0;

        cells_new[i * m + j] = neighbors == 3 || (cells[i*m+j] && neighbors == 2);
      }
    }

    tmp = cells;
    cells = cells_new;
    cells_new = tmp;
    pthread_barrier_wait(&barrier);

  }

  if(iters % 2) {
    for(i = 0; i < n; ++i) {
      for(j = 0; j < m; ++j) {
          cells_new[i * m + j] = cells[i * m + j];
      }
    }
  }
  pthread_barrier_wait(&barrier);
}