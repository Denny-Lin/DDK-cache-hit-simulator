#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

int main(int argc, char *argv[])
{
    FILE *file; 
    char trace_file_name_oct_s[20];//�sŪ��Ӫ��O�����m         
    int trace_file_name_dec_i;//�sŪ��Ӫ��O�����m //16��10   
	  
    int which_block;//��m�O���b��????��Memory Block 
    int which_set;////��m�b�ĴX��cahce set    
    int count=0;//�ΨӺⰵ��ĴX�����   
    
    cache_t cache;
               
    cache_init(&cache);        
	              
    file=fopen("trace.txt","r");   
    do{
        count++;//�p����                
        //printf("��%d����� :",count);
                                        
        fgets(trace_file_name_oct_s,20,file);        
        //printf("%s",trace_file_name_oct_s);                        
        trace_file_name_dec_i = strtol(trace_file_name_oct_s,NULL,16);          
        //printf("   �Q�i�� :%d\n",trace_file_name_dec_i); 
        
        int which_block = trace_file_name_dec_i/cache.block_size;
		int which_set = which_block % cache.set_num;	  
        //printf("Memory block: %d\n",which_block);  
        //printf("cache set: %d\n",which_set);  
						  
        for(int i=0;i<cache.set_degree;i++){//set�̭��C��block���ˬd               
            //printf("cache block:%d  Valid:%c  TAG:%d\n",which_set*cache.set_degree+i,get_cache_block_Valid(&cache ,which_set*cache.set_degree+i),get_cache_block_TAG(&cache ,which_set*cache.set_degree+i));     
            //system("pause");                               
            if(get_cache_block_Valid(&cache ,which_set*cache.set_degree+i) =='Y' && get_cache_block_TAG(&cache ,which_set*cache.set_degree+i) == which_block/cache.set_num){//�����Valid �٭n�b���TAG�O�_�ۦP  
                //printf("hit\n");               
                cache.HitCount++;
                break;//���F�Nbreak���A�~��� 
            }
            else if(i==cache.set_degree-1){//�᳣̫�S���N�Omiss 
                cache.MissCount++;
                //printf("miss"); 
                //��X�ֳ̤Q�ϥΪ�block�����sŪ��Ӫ��O�����m                          
                int small_line = get_cache_block_line(&cache, which_set*cache.set_degree);//�]�ثeset���Ĥ@��block���̤p 
                int tmp = which_set*cache.set_degree;//�����O�ĴX��block��line�̤p �s���a�}�|���N�� 
				 
                for(int j=0;j<cache.set_degree;j++){//��ܨ䤤�@��Line�̤p��block�������s��Ӹ�ƪ�                    
                    if(get_cache_block_line(&cache, which_set*cache.set_degree + j)<small_line){
                        small_line = get_cache_block_line(&cache, which_set*cache.set_degree + j); 
                        tmp = which_set*cache.set_degree + j; 
                    } 
                }               
                
                change_cache_block_Valid(&cache, tmp,'Y');//block�� Valid�אּ'Y' 
                change_cache_block_TAG(&cache, tmp, which_block/cache.set_num);//TAG 
                change_cache_block_line(&cache, tmp, count);//�p��W�@���Ϊ��ɶ� �֪��U���|�Q����   
				
			    //printf("��i��%d��cache block TAG:%d\n\n",tmp,get_cache_block_TAG(&cache, tmp));              
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
