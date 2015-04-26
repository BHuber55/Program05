#if !defined (POLY)
#define POLY

namespace CSC2110
{
class Poly
{
   private:
      int max_power;
      int degree;
      double* coeffs;

   public:
      Poly(int max_power);
      ~Poly();

      int getDegree();

      double getCoeff(int power);
      void setCoeff(int power, double coeff);

      double evaluate(double x);
      Poly* multiply(Poly* other);
      static Poly* multiply(Poly* one, Poly* two);

      void displayPoly();
      static Poly* readPoly(const char* file_name);
      void writePoly(const char* file_name);
};
}

#endif
