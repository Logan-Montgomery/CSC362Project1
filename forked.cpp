#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

long int test;

bool ct(int start, int end, int test){
    bool prime = true;
    while(start < end){
        if(test%start == 0){
            prime = false;
            //printf("Divisor is: %d", start);
            break;
        }
        start++;
        
    }
    if(prime){
        
        //printf("Prime number is: %d \n", test);
        
    }
    return prime;
}



int main(){
    
    test = 1000000;
    pid_t pid;
    
    
    pid = getpid();
    fork();
    if(pid == getpid())
    
    {
        clock_t tstartf1 = clock();
        for(long int i = 2; i<test/2; i++){
        ct(2,(long int)i/2,i);
        }
        printf("Time taken fork 1: %.2fs\n",(double)(clock() - tstartf1) / CLOCKS_PER_SEC);
        
        
        
        
    } else{
        clock_t tstartf1 = clock();
        for(long int i = test/2; i<=test; i++){
        ct(2,(long int)i/2,i);
        }
        printf("Time taken fork 2: %.2fs\n",(double)(clock() - tstartf1) / CLOCKS_PER_SEC);
    }
    
    
    
    
    
return 0;    
}
