#include "3.LRU.h"

int main()
{
    LRUCache cache(2);
    cache.put(1, 1); cache.put(2, 2);

    cout<<"--->"<< cache.get(1);       // returns 1

    cache.put(3, 3);    // evicts key 2
    cout<<"--->"<< cache.get(2);       // returns -1 (not found)
    cache.put(4, 4);    // evicts key 1
    cout<<"--->"<< cache.get(1);       // returns -1 (not found)
    cout<<"--->"<< cache.get(3);       // returns 3
    cout<<"--->"<< cache.get(4);       // returns 4
    cout<<endl;
    return 0;
}

