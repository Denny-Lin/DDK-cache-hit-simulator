
typedef struct cache_block{
    char Valid; 
    int TAG; 
    int line;
}cache_block_t;

typedef struct cache{
    unsigned int cache_size;  
    int block_size; 
    int block_num;
    int set_num;
    
    int set_degree;//一個set中的cache block個數 n_way Set Associative
    cache_block_t ** cache_block;
    
    int MissCount;
    int HitCount;
}cache_t;
 
void cache_block_init (cache_t * cache){//初始化
   //cache->cache_block = (strcut cache_block**)malloc(sizeof(struct cache_block*)*cache->block_num); 
   //cache->cache_block[i]=(strcut cache_block*)malloc(sizeof(struct cache_block));
    cache->cache_block = (cache_block_t**)malloc(sizeof(cache_block_t*) * cache->block_num);   

    for(int i =0;i<cache->block_num;i++){      
	     cache->cache_block[i]=(cache_block_t*)malloc(sizeof(cache_block_t));       
         cache->cache_block[i]->Valid = 'N';
         cache->cache_block[i]->TAG = 0;
         cache->cache_block[i]->line = 0;
    }
};

void cache_init (cache_t * cache){//初始化     
    cache->cache_size=1024*1024;
    cache->set_degree=1;
    cache->block_size=8;
    
    cache->block_num=cache->cache_size/cache->block_size;
    cache->set_num=cache->block_num/cache->set_degree;
    cache->MissCount=cache->HitCount=0;
    
    cache_block_init(cache);
};

void get_cache_block_inf(cache_t * cache,int num){     
    printf("%c\n",cache->cache_block[num-1]->Valid);
    printf("%d\n",cache->cache_block[num-1]->TAG);
    printf("%d\n",cache->cache_block[num-1]->line);
} 

char get_cache_block_Valid(cache_t * cache,int num){	   
    return cache->cache_block[num]->Valid;
} 

int get_cache_block_TAG(cache_t * cache,int num){     
  return cache->cache_block[num]->TAG;
} 

int get_cache_block_line(cache_t * cache,int num){     
  return cache->cache_block[num]->line;
} 

void change_cache_block_Valid(cache_t * cache,int num,char tmp){     
    cache->cache_block[num]->Valid = tmp;
} 

void change_cache_block_TAG(cache_t * cache,int num,int tmp){     
    cache->cache_block[num]->TAG = tmp;
} 

void change_cache_block_line(cache_t * cache,int num,int tmp){     
    cache->cache_block[num]->line = tmp;
} 
