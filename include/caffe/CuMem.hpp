#ifndef CAFFE_CUMEM_HPP_
#define CAFFE_CUMEM_HPP_

#include "common.hpp"

#ifdef USE_CNMEM
// CNMEM integration
#include <cnmem.h>
#endif

namespace caffe {

class CuMem {
 public:
#ifndef CPU_ONLY
  static void mallocGPU(void **ptr, size_t size,
                        cudaStream_t stream = cudaStreamDefault);
  static void freeGPU(void *ptr, cudaStream_t = cudaStreamDefault);
  static void registerStream(cudaStream_t stream);
#endif

  static bool usingPool() {
    return using_pool_;
  }

  static void getInfo(size_t *free_mem, size_t *used_mem);

 private:
  static void init(const std::vector<int>& gpus_, bool use_pool=true);
  static void destroy();

  friend class CuMemActivator;
  static bool using_pool_;
  static bool initialized_;


};

class CuMemActivator {
 public:
  explicit CuMemActivator(const std::vector<int>& gpus, bool use_pool) {
    CuMem::init(gpus, use_pool && gpus.size() > 0);
  }
  ~CuMemActivator() {
    CuMem::destroy();
  }
};

}  // namespace caffe

# endif
