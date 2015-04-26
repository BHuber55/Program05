#if !defined (INTEGER_H)
#define INTEGER_H

namespace CSC2110
{
class Integer
{

   private:
      int value;

   public:
      Integer(int val);
      virtual ~Integer();
      int getValue();

};
}

#endif
