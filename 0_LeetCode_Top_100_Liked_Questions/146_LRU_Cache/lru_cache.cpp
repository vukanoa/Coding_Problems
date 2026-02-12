/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    146) LRU Cache
    ===========================

    ============
    Description:
    ============

    Design a data structure that follows the constraints of a Least Recently
    Used(LRU) cache.

    Implement the LRUCache class:
        - "LRUCache(int capacity)"
              Initialize the LRU cache with positive size "capacity".

        - "int get(int key)"
              Return the value of the "key" if the key exists, otherwise
              return -1.

        - "void put(int key, int value)"
              Update the value of the "key" if the "key" exists. Otherwise, add
              the key-value pair to the cache. If the number of keys exceeds
              the "capacity" from this operation, evict the least recently used
              key.

    =====
    Node: The functions "get" and "put" must each run in O(1) average time
          complexity.
    =====

    ===============================
    CLASS:
    class LRUCache{
    public:
        LRUCache(int capacity);
        int get(int key);
        int put(int key, int value);
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
    [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]

    Output:
    [null, null, null, 1, null, -1, null, -1, 3, 4]

    Explanation:
    LRUCache lRUCache = new LRUCache(2);
    lRUCache.put(1, 1); // cache is {1=1}
    lRUCache.put(2, 2); // cache is {1=1, 2=2}
    lRUCache.get(1);    // return 1
    lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lRUCache.get(2);    // reurns -1 (not found)
    lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lRUCache.get(1);    // return -1(not found)
    lRUCache.get(3);    // return 3
    lRUCache.get(4);    // return 4

    *** Constraints ***
    1 <= capacity <= 3000
    0 <= key <= 10^4
    0 <= value <= 10^5
    At most 2 * 10^5 calls will be made to "get" and "put".

*/

#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since it is said that we need to have an average time Complexity of O(1),
    that strongly indicates that we need to use a Hash Map.

    However, since we're dealing with Least Recently Used items, we need to
    implement it in a way that we know Recency times of using these items and
    we need to update that every time we use "put" or "get" functions.

    So how do we fulfill all these requirements?

        Hash Map + Doubly Linked List(with two DUMMY nodes).

    First, in the Constructor, we'll assign the given capacity to the capacity
    of our cache(Hash Map).

    Then we'll make 2 dummy nodes: dummy_LRU & dummy_MRU.

        dummy_LRU's next pointer will point to actual LRU(Least Recently Used)
        dummy_MRU's prev pointer will point to actual MRU(Most  Recently Used)

    We'll immediately link dummy_LRU's next to dummy_MRU and dummy_MRU's prev
    to dummy_LRU since at the very beginning there are no items(Nodes) in our
    cache.


    Now, go and read the code carefully and you'll get it. Names are verbose
    and there are comments explaining blocks of code.

*/

/* Time  Beats: 88.08% */
/* Space Beats: 55.83% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(N) */
struct Node {
    int key; // This is VERY important
    int val;
    Node* prev;
    Node* next;

    Node ()
    {}

    Node (int key, int val)
        : key(key), val(val), prev(nullptr), next(nullptr)
    {}

    Node (int key, int val, Node* prev, Node* next)
        : key(key), val(val), prev(prev), next(next)
    {}
};

class LRUCache {
public:
    LRUCache(int capacity)
        : dummy_LRU(-1, -1), dummy_MRU(-1, -1), cap(capacity)
    {
        /* Link two dummy nodes */
        dummy_LRU.next = &dummy_MRU;
        dummy_MRU.prev = &dummy_LRU;
    }

    /* Free Memory */
    ~LRUCache()
    {
        Node* curr = dummy_LRU.next;

        while (curr != &dummy_MRU)
        {
            Node* next = curr->next;

            /* Clear & Free Memory */
            curr->prev = nullptr;
            curr->next = nullptr;
            delete curr;

            // Move forward
            curr = next;
        }

        // Remember that "dummy_LRU" and "dummy_MRU" are allocated on the STACK 
    }
    
    int get(int key)
    {
        if (cache.find(key) == cache.end()) // It does NOT exist
            return -1;

        Node* node = cache[key];

        yank_from_linked_list(node);
        insert_as_MRU_node(node);

        return node->val;
    }
    
    void put(int key, int value)
    {
        if (cache.find(key) != cache.end()) // It DOES already exist
        {
            Node* node = cache[key];
            node->val  = value;      // Update value

            yank_from_linked_list(node);
            insert_as_MRU_node(node);

            return;
        }



        if (cache.size() == cap) // Capacity is already full
        {
            /* Remove current LRU node */
            Node* lru_node = dummy_LRU.next;

            yank_from_linked_list(lru_node);
            cache.erase(lru_node->key);

            /* Clear & Free Memory */
            lru_node->prev = nullptr;
            lru_node->next = nullptr;
            delete lru_node;
        }

        /* Put new node */
        Node* new_node = new Node(key, value);

        cache.insert( {key, new_node} );
        insert_as_MRU_node(new_node);
    }

private:
    Node dummy_LRU; // Head (LEAST Recently Used), allocated on the STACK
    Node dummy_MRU; // Tail (MOST  Recently Used), allocated on the STACK

    unsigned cap;   // Maximum capacity for this cache

    unordered_map<int, Node*> cache;

    void yank_from_linked_list(Node* node)
    {
        /* Re-link previous and next node of the current "node" */
        node->prev->next = node->next;
        node->next->prev = node->prev;

        /* Clear Pointers */
        node->prev = nullptr;
        node->next = nullptr;
    }

    /* Put in-between current MRU's node and dummy_MRU */
    void insert_as_MRU_node(Node* node)
    {
        /* Link with current MRU's node */
        dummy_MRU.prev->next = node;
        node->prev           = dummy_MRU.prev;

        /* Link with dummy_MRU */
        dummy_MRU.prev   = node;
        node->next       = &dummy_MRU;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */




/*
    ------------
    --- IDEA ---
    ------------

    The only difference here is that we're using TWO Hash Map instead of one.

    Why am I including this Solution as well?
    Sometimes people forget that they can put additional information within
    the node and then they're obligated to complicate their Solutions like this
    so you should be aware of it.

*/

/* Time  Beats: 71.80% */
/* Space Beats: 47.85% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(N) */
struct MyNode {
    int val;
    MyNode* prev;
    MyNode* next;

    MyNode ()
    {}

    MyNode (int val)
        : val(val), prev(nullptr), next(nullptr)
    {}

    MyNode (int val, MyNode* prev, MyNode* next)
        : val(val), prev(prev), next(next)
    {}
};

class LRUCache_2 {
public:
    LRUCache_2(int capacity)
        : dummy_LRU(-1), dummy_MRU(-1), cap(capacity)
    {
        dummy_LRU.next = &dummy_MRU;
        dummy_MRU.prev = &dummy_LRU;
    }

    /* Free Memory */
    ~LRUCache_2()
    {
        MyNode* curr = dummy_LRU.next;

        while (curr != &dummy_MRU)
        {
            MyNode* next = curr->next;

            /* Clear & Free Memory */
            curr->prev = nullptr;
            curr->next = nullptr;
            delete curr;

            // Move forward
            curr = next;
        }

        // Remember that "dummy_LRU" and "dummy_MRU" are allocated on the STACK 
    }
    
    int get(int key)
    {
        if (cache_key_to_node.find(key) == cache_key_to_node.end()) // It does NOT exist
            return -1;

        MyNode* node = cache_key_to_node[key];

        yank_from_linked_list(node);
        insert_as_MRU_node(node);

        return node->val;
    }
    
    void put(int key, int value)
    {
        if (cache_key_to_node.find(key) != cache_key_to_node.end()) // Exists
        {
            MyNode* node = cache_key_to_node[key];
            node->val = value; // Update value

            yank_from_linked_list(node);
            insert_as_MRU_node(node);

            return;
        }

        if (cache_node_to_key.size() == cap) // Capacity is already full
        {
            /* Remove current LRU node */
            MyNode* lru_node = dummy_LRU.next;
            int     lru_key  = cache_node_to_key[lru_node];

            yank_from_linked_list(lru_node);

            cache_key_to_node.erase(lru_key);
            cache_node_to_key.erase(lru_node);

            /* Clear & Free Memory */
            lru_node->prev = nullptr;
            lru_node->next = nullptr;
            delete lru_node;
        }

        /* Put new node */
        MyNode* node = new MyNode(value);
        cache_key_to_node[key]  = node;
        cache_node_to_key[node] = key;

        insert_as_MRU_node(node);
    }

private:
    MyNode dummy_LRU; // Head (LEAST Recently Used), on the STACK
    MyNode dummy_MRU; // Tail (MOST  Recently Used), on the STACK

    unsigned cap;     // Maximum capacity for this cache

    unordered_map<int, MyNode*> cache_key_to_node;
    unordered_map<MyNode*, int> cache_node_to_key;

    void yank_from_linked_list(MyNode* node)
    {
        /* Re-link previous and next node of the current "node" */
        node->prev->next = node->next;
        node->next->prev = node->prev;

        /* Clear Pointers */
        node->prev = nullptr;
        node->next = nullptr;
    }

    /* Put in-between current MRU's node and dummy_MRU */
    void insert_as_MRU_node(MyNode* node)
    {
        /* Link with current MRU's node */
        dummy_MRU.prev->next = node;
        node->prev           = dummy_MRU.prev;

        /* Link with dummy_MRU */
        dummy_MRU.prev   = node;
        node->next       = &dummy_MRU;
    }
};
