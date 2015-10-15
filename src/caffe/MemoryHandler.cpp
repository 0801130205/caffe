#include <vector>

#include "caffe/common.hpp"
#include "caffe/MemoryHandler.hpp"
#ifdef USE_CNMEM
// CNMEM integration
#include <cnmem.h>
#endif

namespace caffe {

  MemoryHandler::PoolMode MemoryHandler::mode_ = MemoryHandler::NoPool;

#ifndef CNMEM_CHECK
#  define CNMEM_CHECK(x)
#endif

#ifndef CPU_ONLY  // CPU-only Caffe.

  void MemoryHandler::mallocGPU(void **ptr, size_t size, cudaStream_t stream) {
    CHECK((ptr) != NULL);
    switch (mode_) {
    case CnMemPool:
      CNMEM_CHECK(cnmemMalloc(ptr, size, stream));
      break;
    case CubPool:
    default:
      CUDA_CHECK(cudaMalloc(ptr, size));
      break;
    }
  }


  void MemoryHandler::freeGPU(void *ptr, cudaStream_t stream) {
    // allow for null pointer deallocation
    if (!ptr)
      return;
    switch (mode_) {
    case CnMemPool:
      CNMEM_CHECK(cnmemFree(ptr, stream));
      break;
    case CubPool:
    default:
      CUDA_CHECK(cudaFree(ptr));
      break;
    }
  }

  void MemoryHandler::registerStream(cudaStream_t stream) {
    switch (mode_) {
    case CnMemPool:
      CNMEM_CHECK(cnmemRegisterStream(stream));
      break;
    case CubPool:
    default:
      break;
    }
  }

  void MemoryHandler::destroy() {
    switch (mode_) {
    case CnMemPool:
      CNMEM_CHECK(cnmemFinalize());
      break;
    case CubPool:
    default:
      break;
    }
    mode_ = NoPool;
  }

  void MemoryHandler::initCNMEM(const std::vector<int>& gpus) {
#ifdef USE_CNMEM
    cnmemDevice_t* devs = new cnmemDevice_t[gpus.size()];
    int initial_device;
    CUDA_CHECK(cudaGetDevice(&initial_device));

    for (int i = 0; i < gpus.size(); i++) {
      CUDA_CHECK(cudaSetDevice(gpus[i]));
      devs[i].device = gpus[i];
      size_t free_mem, used_mem;
      CUDA_CHECK(cudaMemGetInfo(&free_mem, &used_mem));
      devs[i].size = size_t(0.95*free_mem);
      devs[i].numStreams = 0;
      devs[i].streams = NULL;
    }
    CNMEM_CHECK(cnmemInit(gpus.size(), devs, CNMEM_FLAGS_DEFAULT));
    CUDA_CHECK(cudaSetDevice(initial_device));
    delete [] devs;
    mode_  = CnMemPool;
#endif
  }

  void MemoryHandler::init(const std::vector<int>& gpus,
                           PoolMode m)  {
    if (gpus.size() <= 0) {
      // should we report an error here ?
      m = MemoryHandler::NoPool;
    }

    switch (m) {
    case CnMemPool:
      initCNMEM(gpus);
      break;
    case CubPool:
    default:
      break;
    }

    std::cout << "MemoryHandler initialized with "
              << getName() << std::endl;
  }

  const char* MemoryHandler::getName()  {
    switch (mode_) {
    case CnMemPool:
      return "CNMEM Pool";
    case CubPool:
      return "CUB Pool";
    default:
      return "No Pool : Plain CUDA Allocator";
    }
  }

  void MemoryHandler::getInfo(size_t *free_mem, size_t *total_mem) {
    switch (mode_) {
    case CnMemPool:
      CNMEM_CHECK(cnmemMemGetInfo(free_mem, total_mem, cudaStreamDefault));
      break;
    case CubPool:
    default:
      CUDA_CHECK(cudaMemGetInfo(free_mem, total_mem));
    }
  }

#endif  // CPU_ONLY

}  // namespace caffe
