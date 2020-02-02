#include "keisoku.h"
#include <time.h>
#include <stdio.h>

static struct timespec res,t1,t2;
static long sec,nsec;
#define CLOCK_CYCLE_TIME 3.48E-9
//long long CLOCK_CYCLE = 3480000000;
#define CLOCK_CYCLE 3.48E9

int PrintClockRes(void)
{
  if(clock_getres(CLOCK_MONOTONIC,&res) < 0){
    perror("clock_getres");
    return -1;
  }
  printf("Time Precision:\t%ld.%09ld\n",(long)res.tv_sec,res.tv_nsec);
  return 0;
}

int StartClock(void)
{
  if(clock_gettime(CLOCK_MONOTONIC,&t1) < 0){
    perror("clock_gettime begin");
    return -1;
  }
  return 0;
}
int StopClock(void)
{
  if(clock_gettime(CLOCK_MONOTONIC,&t2) < 0){
    perror("clock_gettime end");
    return -1;
  }
  return 0;
}
/*
int PrintClockSpan(void)
{
  sec = t2.tv_sec - t1.tv_sec;
  nsec = t2.tv_nsec - t1.tv_nsec;
  if(nsec<0){
    sec--;
    nsec += 1000000000L;
  }
  FILE *fp;
  fp = fopen("result.txt","a");
  fprintf(fp,"%ld.%09ld\n",sec,nsec);
  fclose(fp);
  return 0;
}
*/
int PrintClockSpan(long num_iter)
{
  sec = t2.tv_sec - t1.tv_sec;
  nsec = t2.tv_nsec - t1.tv_nsec;
  if(nsec<0){
    sec--;
    nsec += 1000000000L;
  }
  FILE *fp;
  fp = fopen("result.txt","a");
  //printf("TIME:%ld.%09ld CLOCK_CYCLE:%lld NUM_ITER:%lld TIME*CLOCK_CYCLE/NUM_ITER:%lld\n",sec,nsec,CLOCK_CYCLE,num_iter,(sec+nsec)*CLOCK_CYCLE/num_iter);
  //fprintf(fp,"%d\n",(sec+nsec)*CLOCK_CYCLE/num_iter);
  fprintf(fp,"%d\n",(sec+nsec)/CLOCK_CYCLE_TIME/num_iter);
  fclose(fp);
  return 0;
}
double CalcClockSpan(void){
  sec = t2.tv_sec - t1.tv_sec;
  nsec = t2.tv_nsec - t1.tv_nsec;
  if(nsec<0){
    sec--;
    nsec += 1000000000L;
  }
  return sec+nsec*1E-9;
}

