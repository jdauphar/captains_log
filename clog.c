#include "stdio.h"
#include "string.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "dirent.h"
#include "errno.h"
#include "stdlib.h"
#include "time.h"


#define NOT_ENOUGH_ARGS 1


int main(int argc, char* argv[]){
  if(argc == 1){
    printf("you must enter a message:\n");
    printf("eg: 'clog hosts are in /etc/hosts'\n");
    return NOT_ENOUGH_ARGS;
  }

  char* logloc = getenv("HOME");
  char* logname = ".captains_log.txt";
  strcat(logloc, "/");
  strcat(logloc, logname);
  FILE *fp = fopen(logloc, "ab+");

  // put time of creation into log
  time_t t = time(NULL);
  struct tm logtime = *localtime(&t);

  fprintf(fp,"%d-%d-%d at %d:%d >>\n",
	  logtime.tm_year + 1900, logtime.tm_mon + 1,
	  logtime.tm_mday, logtime.tm_hour, logtime.tm_min);

  // put message in log
  for(int i = 1; i < argc; i++ ){
    fprintf(fp, argv[i]);
    fprintf(fp, " ");
  }
  fprintf(fp,"\n\n");

  fclose(fp);
  return 0;
}
