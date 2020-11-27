## ClockCache
+ [rocksdb/clock_cache.cc](https://github.com/facebook/rocksdb/blob/master/cache/clock_cache.cc)

## 注释
+ clock cache是一种缓存算法，和LRU相比，查找不需要修改缓存（LRU查找时需要修改链表，将当前查找的节点放到链表头），因此clock cache查找不需要加锁。
+ 查找。通过并行map实现查找，只需要从map中查找是否存在该key，再额外增加引用计数即可，引用计数是为了保证用户在使用handle时不会因为该handle被驱逐而被delete造成crach。另外，只有cache命中才能增加引用计数，因此增加引用计数的时候可能由于另外一个线程正在清空缓存bit而导致失败
+ 插入。首先去要驱逐部分缓存保证剩余空间能够满足带插入缓存的负载大小，由于插入会更改head和list，因此需要持有mutex。驱逐的实验是通过每个handle的usage bit来驱逐的，每次在release handle都会设置usage bit位表示刚才使用过该handle，clock cache算法会优先驱逐没有设置usage bit的handle，同时驱逐也会考虑到引用计数，引用计数不为0表示正在使用，还没有结束，因此还没有release，综上，驱逐优先会将在缓存中并且uasge bit为0和引用计数为0的handle，clock cache算法会环形遍历两边list，如果仍旧没有驱逐足够的空间，插入失败。如果插入之前缓存已经包含同名的key，clock cache不会简单地覆盖，而是新增一个handle来插入，并把旧值缓存Bit为清空，后续release就会直接释放内存
+ 删除。由于删除会影响list，因此需要持有Mutex，删除比较简单，如果引用计数为0并且不在缓存了就会释放内存