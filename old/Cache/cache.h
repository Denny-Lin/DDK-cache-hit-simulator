
typedef struct cache_block{
    int set;
    char Valid; 
    int TAG; 
}cache_block_t;

typedef struct cache{
    unsigned int cache_size;  
    int n_way;//Set Associative 
    int block_size; 
    int block_num;
    //set_degree : 一個set中的cache block個數 ex 1024/16=64  if 2-way, 64/2=32 =>set_degree=cache_size/block_size/n_way
    int set_degree; 
    cache_block_t ** cache_block;
    
    int MissCount;
    int HitCount;
}cache_t;

void cache_block_init (cache_t * cache){//初始化
    cache->cache_block = (cache_block**)calloc (cache->block_num, sizeof (cache_block*)); 
    //cache->cache_block = (cache_block**)malloc(sizeof(*cache_block)*cache->block_num); 
    /*for(int i =0;i<cache->block_num;i++){             
         cache->cache_block[i]->Valid = 'N';
         //int TAG=0; 
    }*/
};

void cache_init (cache_t * cache){//初始化     
    cache->cache_size=1024;
    cache->n_way=1;
    cache->block_size=16;
    
    cache->block_num=cache->cache_size/cache->block_size;
    cache->MissCount=cache->HitCount=0;
};

void get_cache_block(cache_t * cache){     
    printf("%c\n",cache->cache_block[0]->Valid);
}
