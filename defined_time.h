#include <iostream>
using namespace std;
/*
ref: https://www.programiz.com/cpp-programming/examples/time-structure
*/
class TIME {
public:
  int seconds;
  int minutes;
  int hours;
  TIME(){};
  TIME(int h, int m, int s){
      hours=h; minutes=m; seconds=s;
  }
  void set(int h, int m, int s){
      hours=h; minutes=m; seconds=s;
  }
};

TIME computeTimeDifference(TIME t1, TIME t2){
    
    TIME difference;

    if(t2.seconds > t1.seconds)
    {
        --t1.minutes;
        t1.seconds += 60;
    }

    difference.seconds = t1.seconds - t2.seconds;
    if(t2.minutes > t1.minutes)
    {
        --t1.hours;
        t1.minutes += 60;
    }
    difference.minutes = t1.minutes-t2.minutes;
    difference.hours = t1.hours-t2.hours;

    return difference;
}


// Manual testing
// TIME t1 = TIME(15, 35, 20);
// TIME t2 = TIME(12, 20, 20);
// TIME diff = computeTimeDifference(t1, t2);
// cout << diff.minutes << endl;