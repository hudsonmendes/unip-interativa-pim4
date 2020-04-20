#include <time.h>
#include "definitions.h"

int parkingHours(time_t,time_t);
float parkingPayment(configInfo, int);
bool checkLockOut(configInfo,int);
void clear();
void pause();
void breakLine();
void getDate(char*,time_t*);
void getDateExt(char*,time_t*,bool);
void formatDate(time_t*,char*);
#ifdef _WIN32
#else
char getch(void);
#endif
