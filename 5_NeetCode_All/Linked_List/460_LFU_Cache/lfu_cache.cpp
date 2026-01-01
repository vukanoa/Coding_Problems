#include <iostream>
#include <unordered_map>

/*
    ============
    === HARD ===
    ============

    ===========================
    460) LFU Cache
    ===========================

    ============
    Description:
    ============

    Design and implement a data structure for a Least Frequently Used (LFU)
    cache.

    Implement the LFUCache class:

        + LFUCache(int capacity) Initializes the object with the capacity of
          the data structure.

        + int get(int key) Gets the value of the key if the key exists in the
          cache. Otherwise, returns -1.

        + void put(int key, int value) Update the value of the key if present,
          or inserts the key if not already present. When the cache reaches its
          capacity, it should invalidate and remove the least frequently used
          key before inserting a new item. For this problem, when there is a
          tie (i.e., two or more keys with the same frequency), the least
          recently used key would be invalidated.

    To determine the least frequently used key, a use counter is maintained for
    each key in the cache. The key with the smallest use counter is the least
    frequently used key.

    When a key is first inserted into the cache, its use counter is set to 1
    (due to the put operation). The use counter for a key in the cache is
    incremented either a get or put operation is called on it.

    The functions get and put must each run in O(1) average time complexity.

    ===============================
    CLASS:

    class LFUCache {
    public:
        LFUCache(int capacity) {

        }

        int get(int key) {

        }

        void put(int key, int value) {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
    [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
    Output
    [null, null, null, 1, null, -1, 3, null, -1, 3, 4]

    Explanation
    // cnt(x) = the use counter for key x
    // cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
    LFUCache lfu = new LFUCache(2);
    lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
    lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    lfu.get(1);      // return 1
                     // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                     // cache=[3,1], cnt(3)=1, cnt(1)=2
    lfu.get(2);      // return -1 (not found)
    lfu.get(3);      // return 3
                     // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                     // cache=[4,3], cnt(4)=1, cnt(3)=2
    lfu.get(1);      // return -1 (not found)
    lfu.get(3);      // return 3
                     // cache=[3,4], cnt(4)=1, cnt(3)=3
    lfu.get(4);      // return 4
                     // cache=[4,3], cnt(4)=2, cnt(3)=3


    *** Constraints ***
    1 <= capacity <= 10^4
    0 <= key <= 10^5
    0 <= value <= 10^9
    At most 2 * 105 calls will be made to get and put.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    It's not too complicated, but there are a lot of things you have to keep
    track of.

    Not very difficult, but a lot of code to write.

*/

/* Time  Beats: 32.77% */
/* Space Beats: 22.51% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class MyListNode {
public:
    int val;
    MyListNode* prev;
    MyListNode* next;

    MyListNode(int val = 0, MyListNode* prev = nullptr, MyListNode* next = nullptr)
        : val(val), prev(prev), next(next)
    {}
};

class LinkedList {
public:
    MyListNode* left;
    MyListNode* right;
    std::unordered_map<int, MyListNode*> umap;

    LinkedList()
    {
        left  = new MyListNode(0);
        right = new MyListNode(0, left);
        left->next = right;
    }

    ~LinkedList()
    {
        delete left;
        delete right;
    }

    int length() const
    {
        return umap.size();
    }

    void pushRight(int val)
    {
        MyListNode* node = new MyListNode(val, right->prev, right);
        umap[val] = node;
        right->prev->next = node;
        right->prev = node;
    }

    void pop(int val)
    {
        if (umap.find(val) != umap.end())
        {
            MyListNode* node = umap[val];
            node->prev->next = node->next;
            node->next->prev = node->prev;

            umap.erase(val);
            delete node;
        }
    }

    int popLeft()
    {
        int result = left->next->val;
        pop(result);

        return result;
    }

    void update(int val)
    {
        pop(val);
        pushRight(val);
    }
};

class LFUCache {
private:
    int cap;
    int LFU_count;
    std::unordered_map<int, int> umap_val;         // Maps {key : value}
    std::unordered_map<int, int> umap_count;       // Maps {key : count}
    std::unordered_map<int, LinkedList> umap_list; // Maps {count : LinkedList of keys}

public:
    LFUCache(int capacity)
        : cap(capacity), LFU_count(0)
    {}

    void counter(int key)
    {
        int count = umap_count[key];
        umap_count[key]++;

        umap_list[count].pop(key);
        umap_list[count + 1].pushRight(key);

        if (count == LFU_count && umap_list[count].length() == 0)
            LFU_count++;
    }

    int get(int key)
    {
        if (umap_val.find(key) == umap_val.end())
            return -1;

        counter(key);
        return umap_val[key];
    }

    void put(int key, int value)
    {
        if (cap == 0)
            return;

        if (umap_val.find(key) == umap_val.end() && umap_val.size() == cap)
        {
            int result = umap_list[LFU_count].popLeft();

            umap_val.erase(result);
            umap_count.erase(result);
        }

        umap_val[key] = value;
        counter(key);
        LFU_count = std::min(LFU_count, umap_count[key]);
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
