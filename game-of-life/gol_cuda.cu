#include "gol_parallel.h"
#include <cuda_runtime.h>

__global__ void gol_kernal(bool *cells_d, bool *cells_new_d, int n, int m, int block_width, int block_height, int thread_width, int thread_height){
  int i, j;
  int startRow = blockIdx.y * block_height + threadIdx.y * thread_height;
  int startCol = blockIdx.x * block_width + threadIdx.x * thread_width;
  int endRow = min(startRow + thread_height, n); // End should probably be min of start + height and n
  int endCol = min(startCol + thread_width, m);
  int neighbors;

  for(i = startRow; i < endRow; i++){
    for(j = startCol; j < endCol; j++){
      neighbors = 0;

      if(i>0 && j>0) neighbors += cells_d[(i-1) * m + j-1] ? 1 : 0;
      if(i>0) neighbors += cells_d[(i-1) * m + j] ? 1 : 0;
      if(i>0 && j<m-1) neighbors += cells_d[(i-1) * m + j+1] ? 1 : 0;
      if(j>0) neighbors += cells_d[i * m + j-1] ? 1 : 0;
      if(j<m-1) neighbors += cells_d[i * m + j+1] ? 1 : 0;
      if(i<n-1 && j>0) neighbors += cells_d[(i+1) * m + j-1] ? 1 : 0;
      if(i<n-1) neighbors += cells_d[(i+1) * m + j] ? 1 : 0;
      if(i<n-1 && j<m-1) neighbors += cells_d[(i+1) * m + j+1] ? 1 : 0;

      cells_new_d[i * m + j] = neighbors == 3 || (cells_d[i * m + j] && neighbors == 2);
    }
  }
}

void gol_cuda(char* cells, int n, int m, int iterations, int xBlockDim, int yBlockDim, int xThreadDim, int yThreadDim){
  int i;
  int size = n * m * sizeof(bool);
  bool *cells_d, *cells_new_d, *tmp;

  cudaMalloc(&cells_d, size);
  cudaMemcpy(cells_d, cells, size, cudaMemcpyHostToDevice);

  cudaMalloc(&cells_new_d, size);
  cudaMemcpy(cells_new_d, cells, size, cudaMemcpyHostToDevice);

  // Kernal implementation
  dim3 dimGrid(xThreadDim, yThreadDim);
  dim3 dimBlock(xBlockDim, yBlockDim);

  int block_width = m % xBlockDim ? m / xBlockDim + 1 : m / xBlockDim;
  int block_height = n % yBlockDim ? n / yBlockDim + 1 : n / yBlockDim;
  int thread_width = block_width % xThreadDim ? block_width / xThreadDim + 1 : block_width / xThreadDim;
  int thread_height = block_height % yThreadDim ? block_height / yThreadDim + 1 : block_height / yThreadDim;

  for(i = 0; i < iterations; i++){
    gol_kernal<<<dimBlock, dimGrid>>>(cells_d, cells_new_d, n, m, block_width, block_height, thread_width, thread_height);

    tmp = cells_d;
    cells_d = cells_new_d;
    cells_new_d = tmp;
  }


  cudaMemcpy(cells, cells_d, size, cudaMemcpyDeviceToHost);
  cudaFree(cells_d); cudaFree(cells_new_d);

}