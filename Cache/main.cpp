#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

int main(int argc, char *argv[])
{
    FILE *file; 
    char trace_file_name_oct_s[20];//存讀近來的記憶體位置         
    int trace_file_name_dec_i;//存讀近來的記憶體位置 //16轉10   
	  
    int which_block;//位置是落在第????個Memory Block 
    int which_set;////位置在第幾個cahce set    
    int count=0;//用來算做到第幾筆資料   
    
    cache_t cache;
               
    cache_init(&cache);        
	              
    file=fopen("trace.txt","r");   
    do{
        count++;//計算行數                
        //printf("第%d筆資料 :",count);
                                        
        fgets(trace_file_name_oct_s,20,file);        
        //printf("%s",trace_file_name_oct_s);                        
        trace_file_name_dec_i = strtol(trace_file_name_oct_s,NULL,16);          
        //printf("   十進位 :%d\n",trace_file_name_dec_i); 
        
        int which_block = trace_file_name_dec_i/cache.block_size;
		int which_set = which_block % cache.set_num;	  
        //printf("Memory block: %d\n",which_block);  
        //printf("cache set: %d\n",which_set);  
						  
        for(int i=0;i<cache.set_degree;i++){//set裡面每個block做檢查               
            //printf("cache block:%d  Valid:%c  TAG:%d\n",which_set*cache.set_degree+i,get_cache_block_Valid(&cache ,which_set*cache.set_degree+i),get_cache_block_TAG(&cache ,which_set*cache.set_degree+i));     
            //system("pause");                               
            if(get_cache_block_Valid(&cache ,which_set*cache.set_degree+i) =='Y' && get_cache_block_TAG(&cache ,which_set*cache.set_degree+i) == which_block/cache.set_num){//先比較Valid 還要在比較TAG是否相同  
                //printf("hit\n");               
                cache.HitCount++;
                break;//找到了就break不再繼續找 
            }
            else if(i==cache.set_degree-1){//最後都沒找到就是miss 
                cache.MissCount++;
                //printf("miss"); 
                //找出最少被使用的block換成新讀近來的記憶體位置                          
                int small_line = get_cache_block_line(&cache, which_set*cache.set_degree);//設目前set的第一個block為最小 
                int tmp = which_set*cache.set_degree;//紀錄是第幾個block的line最小 新的地址會取代它 
				 
                for(int j=0;j<cache.set_degree;j++){//選擇其中一個Line最小的block替換成新近來資料的                    
                    if(get_cache_block_line(&cache, which_set*cache.set_degree + j)<small_line){
                        small_line = get_cache_block_line(&cache, which_set*cache.set_degree + j); 
                        tmp = which_set*cache.set_degree + j; 
                    } 
                }               
                
                change_cache_block_Valid(&cache, tmp,'Y');//block的 Valid改為'Y' 
                change_cache_block_TAG(&cache, tmp, which_block/cache.set_num);//TAG 
                change_cache_block_line(&cache, tmp, count);//計算上一次用的時間 少的下次會被換掉   
				
			    //printf("放進第%d個cache block TAG:%d\n\n",tmp,get_cache_block_TAG(&cache, tmp));              
            } 
        } 
		//system("PAUSE");
    }while(feof(file)== 0);
    
    printf("%lf\n",(double)cache.MissCount/(double)(cache.HitCount+cache.MissCount));
    fclose(file);    
    printf("\n"); 
    system("PAUSE");
    return 0;
}
