#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
#include<time.h>

int main(int argc,char**argv)
{
   int fileid=open("a.txt",O_RDWR|O_CREAT,0764);
   int flag=0;
   char arr[100]="*****";
   struct flock lk;
   lk.l_type=F_WRLCK;
   lk.l_whence=SEEK_SET;
   lk.l_start=0;
   lk.l_len=0;
   lk.l_pid=-1;//一般为-1
 
   if(fcntl(fileid,F_SETLK,&lk)<0)
   {
     printf("SETLK FAILURE\n");
   }   

  while(1)
  {
    if(write(fileid,arr,5)<0)
    {
          printf("ERROR\n");
    }
    sleep(1);
  } 


}