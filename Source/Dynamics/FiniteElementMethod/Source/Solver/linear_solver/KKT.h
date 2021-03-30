#ifndef PhysIKA_KKT
#define PhysIKA_KKT

#include "linear_solver.h"

namespace PhysIKA{
  template<typename T>
  class range_based_KKT: public KKT<T>{
    using SPM = Eigen::SparseMatrix<double, Eigen::RowMajor>;
  public:
    range_based_KKT(const bool hes_is_constant);
    int solve(const SPM& A, const T* b, const SPM& J, const T* c, double* solution) const;
  private:
    const bool hes_is_constant_;
  };

  template<typename T>
  class null_space_KKT: public KKT<T>{
    using SPM = Eigen::SparseMatrix<T, Eigen::RowMajor>;
  public:
    null_space_KKT(const bool hes_is_constant);
    int solve(const SPM& A, const T* b, const SPM& J, const T* c, double* solution) const;
  private:
    const bool hes_is_constant_;
  };
}
#endif
