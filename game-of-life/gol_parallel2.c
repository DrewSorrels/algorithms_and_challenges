#include "gol_parallel.h"

pthread_barrier_t barrier;
bool *cells;
bool *cells_new;
int width;
int height;
int num_threads;
int iteration_count;
// Computes the given number of iterations for an n x m array of cells using
// the given number of threads.
void gol_parallel2(bool* board, int n, int m, int iterations, int nthreads) {
  pthread_t *threads;
  threads = malloc(sizeof(pthread_t)*nthreads);
  cells = board;
  cells_new = malloc(n * m * sizeof(bool));
  width = m;
  height = n;
  num_threads = nthreads;
  iteration_count = iterations
  int i,j;

  pthread_barrier_init(&barrier, NULL, nthreads);

  for(i = 0; i < nthreads; i++){
    struct arg_struct *args = malloc(sizeof(struct arg_struct));

    int rc = pthread_create(&threads[i], NULL, worker_thread, (void *) i);
    if(rc){
      printf("ERROR with pthread_create.\n");
      exit(EXIT_FAILURE);
    }
  }

  free(cells_new);
  pthread_barrier_destroy(&barrier);
}

void *worker_thread(void *args)
  int row_lo, row_hi;
  int thread_id = *((int *) args);

  row_lo = (height / num_threads) * thread_id;
  if(thread_id + 1 == num_threads){
    row_hi = height;
  } else {
    row_hi = (height / num_threads) * (thread_id + 1);
  }

  int iter, i, j;
  bool *tmp;
  int neighbors;

  // Logic for this iteration of game of life in the rows from row_lo to row_high
  for(iter = 0; iter < iteration_count; iter++){
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
  // pthread_barrier_wait(&barrier);
}