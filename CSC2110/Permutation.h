#if !defined (PERMUTATION_H)
#define PERMUTATION_H

#include "ListArray.h"
using CSC2110::ListArray;
#include "Integer.h"
using CSC2110::Integer;
#include "Random.h"
using CSC2110::Random;

namespace CSC2110
{
class Permutation
{
   private:
      int r;
      ListArray<Integer>* numbers;
      Random* random;

   public:
      Permutation(int r, int n);
      virtual ~Permutation();
      int next();
};
}

#endif
