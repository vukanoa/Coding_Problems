/*
    ============
    === EASY ===
    ============

    ===========================
    705) Design HashSet
    ===========================

    ============
    Description:
    ============

    Design a HashSet without using any built-in hash table libraries.

    Implement MyHashSet class:

        void add(key) Inserts the value key into the HashSet.

        bool contains(key) Returns whether the value key exists in the HashSet
        or not.

        void remove(key) Removes the value key in the HashSet. If key does not
        exist in the HashSet, do nothing.

    ===============================
    CLASS:
    class MyHashSet {
    public:
        MyHashSet() {

        }

        void add(int key) {

        }

        void remove(int key) {

        }

        bool contains(int key) {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["MyHashSet", "add", "add", "contains", "contains", "add", "contains",
     "remove", "contains"]
    [[], [1], [2], [1], [3], [2], [2], [2], [2]]
    Output
    [null, null, null, true, false, null, true, null, false]

    Explanation
    MyHashSet myHashSet = new MyHashSet();
    myHashSet.add(1);      // set = [1]
    myHashSet.add(2);      // set = [1, 2]
    myHashSet.contains(1); // return True
    myHashSet.contains(3); // return False, (not found)
    myHashSet.add(2);      // set = [1, 2]
    myHashSet.contains(2); // return True
    myHashSet.remove(2);   // set = [1]
    myHashSet.contains(2); // return False, (already removed)


    *** Constraints ***
    0 <= key <= 10^6
    At most 10%4 calls will be made to add, remove, and contains.

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is using "Separate Chaining" to resolve collisions.

*/

/* Time  Beats: 51.89% */
/* Space Beats: 24.54% */

/* Time  Complexity: O(K)     */ // Amortized O(1), where K is the bucket size
/* Space Complexity: O(P + N) */ // P = Prime, N = Number of stored keys
// class MyHashSet_Separate_Chaining {
class MyHashSet_Separate_Chaining {
private:
    int prime;
    vector<vector<int>> table;

    int hash_key(int key)
    {
        return key % prime;
    }

    int find_index_in_bucket(int bucket_index, int key)
    {
        vector<int>& bucket = table[bucket_index];

        for (int idx = 0; idx < static_cast<int>(bucket.size()); idx++)
        {
            if (bucket[idx] == key)
                return idx;
        }

        return -1;
    }

public:
    MyHashSet_Separate_Chaining()
        : prime(1e4 + 7),
          table(prime)
    {
    }

    void add(int key)
    {
        int bucket_index = hash_key(key);

        if (find_index_in_bucket(bucket_index, key) == -1)
            table[bucket_index].push_back(key);
    }

    void remove(int key)
    {
        int bucket_index = hash_key(key);
        int key_index    = find_index_in_bucket(bucket_index, key);

        if (key_index != -1)
        {
            vector<int>& bucket = table[bucket_index];
            bucket[key_index] = bucket.back();
            bucket.pop_back();
        }
    }

    bool contains(int key)
    {
        int bucket_index = hash_key(key);
        return find_index_in_bucket(bucket_index, key) != -1;
    }
};


// Open Addressing, Linear Probing
class MyHashSet {
private:
    static constexpr int EMPTY   = -1;
    static constexpr int DELETED = -2;

    int m_size;
    int capacity;
    double load_factor;
    vector<int> table;

    int hash_key(int key)
    {
        return key % capacity;
    }

    void rehash(int new_capacity)
    {
        vector<int> old_table = table;

        capacity = new_capacity;
        table.assign(capacity, EMPTY);
        m_size = 0;

        for (int key : old_table)
        {
            if (key >= 0)
                add(key);
        }
    }

public:
    MyHashSet()
        : m_size(0),
          capacity(8),
          load_factor(0.7),
          table(capacity, EMPTY)
    {
    }

    void add(int key)
    {
        if (contains(key))
            return;

        if (m_size + 1 > load_factor * capacity)
            rehash(capacity * 2);

        int idx = hash_key(key);

        while (table[idx] >= 0)
            idx = (idx + 1) % capacity;

        table[idx] = key;
        m_size++;
    }

    void remove(int key)
    {
        int idx = hash_key(key);
        int start_idx = idx;

        while (table[idx] != EMPTY)
        {
            if (table[idx] == key)
            {
                table[idx] = DELETED;
                m_size--;
                return;
            }

            idx = (idx + 1) % capacity;

            if (idx == start_idx)
                return;
        }
    }

    bool contains(int key)
    {
        int idx = hash_key(key);
        int start_idx = idx;

        while (table[idx] != EMPTY)
        {
            if (table[idx] == key)
                return true;

            idx = (idx + 1) % capacity;

            if (idx == start_idx)
                return false;
        }

        return false;
    }
};




/* Time  Beats: 88.05% */
/* Space Beats: 43.44% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */

class MyHashSet_Array_On_The_Stack {
public:
    MyHashSet_Array_On_The_Stack()
    {
    }

    void add(int key)
    {
        array[key] = true;
    }

    void remove(int key)
    {
        array[key] = false;
    }

    bool contains(int key)
    {
        return array[key];
    }

private:
    static constexpr int SIZE = 1e6 + 1;
    bool array[SIZE] = {false};
};




/*
    ------------
    --- IDEA ---
    ------------

    The most natural Solution given the Constraints.

*/

/* Time  Beats: 90.12% */
/* Space Beats: 54.96% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */ // Relative to Input size
class MyHashSet_Bitset {
private:
    /*
        Our "key" is in the range [1, 1000000] because:
        
            31251 * 32bits = 1000032 bits

        I.e., a single bit for each key.
    */
    int set[31251];

public:
    MyHashSet_Bitset()
    {
        // O(1), relative to Input size N, where N is the key range.
        memset(set, 0, sizeof(set));
    }

    // O(1)
    void add(int key)
    {
        set[key / 32] |= mask_of(key);
    }

    // O(1)
    void remove(int key)
    {
        if (contains(key))
            set[key / 32] ^= mask_of(key);

        // Or we could've just:
        // set[key / 32] &= ~mask_of(key);
    }

    // O(1)
    bool contains(int key)
    {
        return set[key / 32] & mask_of(key);
    }

private:
    // O(1)
    int mask_of(int key)
    {
        return 1 << (key % 32); // 2^(key % 32)
    }
};
