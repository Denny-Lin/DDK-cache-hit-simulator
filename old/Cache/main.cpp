#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

int main(int argc, char *argv[])
{
    FILE *file; 
    //char * address_oct_s;      
    //address_oct_s = (char*)calloc (10, sizeof (char));
    char trace_file_name_oct_s[10];         
    int trace_file_name_dec_i;     

    cache_t cache;
            
    //cache_init(&cache);       
    cache.cache_size=1024;   
    cache.block_size=16;
    cache.n_way=2;
    
    cache.block_num=cache.cache_size/cache.block_size;
    cache.set_degree=cache.cache_size/cache.block_size/cache.n_way;    
    //cache_block_init(&cache);
    
    cache_block_t * cache_block;
    cache_block = (cache_block_t*)calloc (cache.block_num, sizeof (cache_block_t));
    for(int i;i<cache.block_num;i++){
         cache_block[i].Valid = 'N';
         printf("%c\n",cache_block[i].Valid);
         cache_block[i].TAG=0; 
         printf("%d\n",cache_block[i].TAG);
    }   
         
    printf("%d\n",cache.set_degree);
    //get_cache_block(&cache);
    
    file=fopen("trace.txt","r");
    //for(int i;i<5;i++){
         //fscanf(file,"%c",&address);
    fgets(trace_file_name_oct_s,11,file);
        
    printf("%s\n",trace_file_name_oct_s); 
                       
    trace_file_name_dec_i = strtol(trace_file_name_oct_s,NULL,16);   
         
    printf("%d",trace_file_name_dec_i); 
   
    //set = trace_file_name_dec_i/set_degree;//Memory Block所對應的set為第20(=1109716%32)個set。
    

    fclose(file);
    
    printf("\n"); 
    system("PAUSE");
    return 0;
}
