#if !defined (HIGHPERFORMANCECOUNTER_H)
#define HIGHPERFORMANCECOUNTER_H

namespace CSC2110
{
class HighPerformanceCounter
{
   private:
      double micro_spt;  //micro_seconds per tick

      HighPerformanceCounter();
      static HighPerformanceCounter* hpc;
      static int getTicksPerSecond();

   public:
      virtual ~HighPerformanceCounter();

      static HighPerformanceCounter* getHighPerformanceCounter();
      int getCurrentTimeInTicks();
      double getTimeDifferenceInMicroSeconds(int start_time, int end_time);
};
}

#endif
