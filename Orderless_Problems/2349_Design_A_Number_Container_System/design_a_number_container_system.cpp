/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2349) Design a Number Container System
    ======================================

    ============
    Description:
    ============


    Design a number container system that can do the following:

        + Insert or Replace a number at the given index in the system.

        + Return the smallest index for the given number in the system.


    Implement the NumberContainers class:

        + NumberContainers() Initializes the number container system.

        + void change(int index, int number) Fills the container at index with
          the number. If there is already a number at that index, replace it.

        + int find(int number) Returns the smallest index for the given number,
          or -1 if there is no index that is filled by number in the system.

    ===============================
    CLASS:
    class NumberContainers {
    public:
        NumberContainers()
        {

        }

        void change(int index, int number)
        {

        }

        int find(int number)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
    [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
    Output
    [null, -1, null, null, null, null, 1, null, 2]

    Explanation
    NumberContainers nc = new NumberContainers();
    nc.find(10); // There is no index that is filled with number 10. Therefore, we return -1.
    nc.change(2, 10); // Your container at index 2 will be filled with number 10.
    nc.change(1, 10); // Your container at index 1 will be filled with number 10.
    nc.change(3, 10); // Your container at index 3 will be filled with number 10.
    nc.change(5, 10); // Your container at index 5 will be filled with number 10.
    nc.find(10); // Number 10 is at the indices 1, 2, 3, and 5. Since the smallest index that is filled with 10 is 1, we return 1.
    nc.change(1, 20); // Your container at index 1 will be filled with number 20. Note that index 1 was filled with 10 and then replaced with 20.
    nc.find(10); // Number 10 is at the indices 2, 3, and 5. The smallest index that is filled with 10 is 2. Therefore, we return 2.


    *** Constraints ***
    1 <= index, number <= 10^9
    At most 105 calls will be made in total to change and find.

*/

#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The code is more or less self-explanatory. The only thing that is important
    to note here is how "number_to_heap" HashMap works.

    We'll have a total of 3 HashMaps:
        1. idx_to_number
        2. number_to_heap
        3. number_to_removed_indices

    the first one, i.e. "idx_to_number", is just a basic helper HashMap,
    nothing fancy about it.

    The second and third HashMaps are working together.
    Since for every number we need the SMALLEST index, we can't just assign
    currently smallest index to that number because what happens if that index
    gets overwritten with some other number?

    Then we'd need to know what's the 2nd smallest index. However, what happens
    if even that one gets overwritten(changed) with some other number?
    And so on.

    That's why we need to, somehow, keep all of the indices that are using this
    number, but we only care about the smallest index the most.

    Minimum Heap is literally made for these kinds of problems.

    But there's one problem with it.

    Imagine that we had this situation in "number_to_heap":

             Hash Map
        | Number :  MinHeap  |
        |  (Key) :  (Value)  |
        +--------------------+
        |   20   :   [4]     |
        +---------------------
        |   10   : [2,7,3,5] |
        +--------------------+
        |   40   :   [1]     |
        +--------------------+

    For number 10, the minimum index from MinHeap is 2, right?
    But what happens if we say that:

        change(3, 50) ? // It's THREE(3), not TWO(2), it's not a mistake

    We would certainly push index 3 to number_to_heap[50], however there' one
    problem -- What would happen with "index 3" that is in number_to_heap[10]?

    If after this we've had this change:

        change(2, 40) // Now this is TWO(2)

    Then we'd have this situation:

             Hash Map
        | Number :  MinHeap  |
        |  (Key) :  (Value)  |
        +--------------------+
        |   20   :   [4]     |
        +---------------------
        |   10   : [3,7,5]   |  // Look at this! It looks like 3 is smallest
        +--------------------+
        |   40   : [1,2]     |
        +--------------------+
        |   50   :   [3]     |
        +--------------------+

    And if we wanted to find the minimum index for 10, we'd return 3, which is
    INCORRECT!

    Why?
    Because we've already put 3 to number 50, which means it should've been
    removed from number 10's min_heap.

    So, how do we remove elements from the heap that are NOT top ones?
    This seems impossible or very challenging.

    The solution is -- another HashMap.
    This Hashmap will be called "number_to_removed_indices" and will track all
    the indices that are REMOVED from that number.

    In this case we'll have index 3 at number 10.
    But there's yet another problem.

    What if we had removed 3 and thus have put it in HashMap
    "number_to_removed_indices", but then afterwards we add 3 to number 10?

    In that case we'll only have ONE removal of "index 3" from number 10 which
    would be correct for this case, but what if we, then, removed "index 3"
    from 10 again?

    Then our "number_to_removed_indices" would have ONLY ONE "index 3" in it,
    but we'd have two 3's in min_heap of number 10.

    That's why, for every number in "number_to_removed_indices" we'll not only
    have an index, but a whole other unordered_map of itself where we'll keep
    the track of the amount of removals of some specific index from some
    "number".

    It's a little confusing at first, but once you read the code CAREFULLY and
    reason every line, it's not too bad.

*/

/* Time  Beats: 95.63% */
/* Space Beats: 83.44% */
class NumberContainers {
public:
    NumberContainers()
    {

    }

    /* Time  Complexity: O(1) */
    void change(int index, int number)
    {
        if (idx_to_number.count(index))
        {
            int old_number = idx_to_number[index];

            if ( ! number_to_removed_indices.count(old_number))
                number_to_removed_indices.insert( {old_number, {}} );

            number_to_removed_indices[old_number][index]++;
        }

        // if (number_heap[number].empty())
        number_to_heap[number].push(index);
        idx_to_number[index] = number;
    }

    /* Time  Complexity: O(logN) */
    int find(int number)
    {
        while ( ! number_to_heap[number].empty())
        {
            int smallest_idx = number_to_heap[number].top();

            if (number_to_removed_indices[number].count(smallest_idx))
            {
                number_to_removed_indices[number][smallest_idx]--;

                if (number_to_removed_indices[number][smallest_idx] == 0)
                    number_to_removed_indices[number].erase(smallest_idx);

                number_to_heap[number].pop();
            }
            else
                return smallest_idx;
        }

        return -1;
    }

private:
    unordered_map<int,int> idx_to_number;
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> number_to_heap;
    unordered_map<int,unordered_map<int,int>> number_to_removed_indices;
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent idea as above, though this one doesn't use
    "number_removed_idx" HashMap, instead it uses "Lazy Update" technique in
    MinHeap.

    We can do a "Lazy Update" and not have an additional HashMap because we can
    now in O(1) in which "number" does some index belong to.

    If it DOESN'T belong to the current number, then we should've removed it
    already, but since this is "Lazy Update" we're doing it here.

    That's the whole difference.

    It's good to see both Solutions. Sometimes "Lazy Update" is difficult to
    spot.

*/

/* Time  Beats: 95.63% */
/* Space Beats: 93.13% */

/* Space Complexity: O(N) */
class NumberContainers_Lazy_Update {
public:
    NumberContainers_Lazy_Update () {}

    /* Time  Complexity: O(1) */
    void change(int index, int number)
    {
        idx_to_number[index] = number;
        number_to_heap[number].push(index);
    }

    /* Time  Complexity: O(logN) */
    int find(int number)
    {
        if (number_to_heap.find(number) == number_to_heap.end())
            return -1;

        while ( ! number_to_heap[number].empty())
        {
            int index = number_to_heap[number].top();

            // If index still maps to our target number, return it
            if (idx_to_number[index] == number)
                return index;

            // Otherwise remove this stale index
            number_to_heap[number].pop();
        }

        return -1;
    }

private:
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> number_to_heap;
    unordered_map<int, int> idx_to_number;
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses a HashSet, but ORDERED HashSet(sometimes referred to as
    "Tree Set" because it's usually impemented using Red-Black Trees)

    Idea is very similar to two above. If you've understood MinHeap ones, then
    reading the code of this one we'll invoke an "AHA" moment.

*/

/* Time  Beats: 36.56% */
/* Space Beats: 45.63% */

/* Space Complexity: O(N) */
class NumberContainers_Tree_Set {
public:
    NumberContainers_Tree_Set() {}

    /* Time  Complexity: O(logN) */
    void change(int index, int number)
    {
        if (idx_to_number.find(index) != idx_to_number.end()) // If exists
        {
            int old_number = idx_to_number[index];

            number_to_indices[old_number].erase(index);

            if (number_to_indices[old_number].empty())
                number_to_indices.erase(old_number);
        }

        idx_to_number[index] = number;
        number_to_indices[number].insert(index);
    }

    /* Time  Complexity: O(1) */
    int find(int number)
    {
        if (number_to_indices.find(number) != number_to_indices.end())
            return *number_to_indices[number].begin();

        return -1;
    }

private:
    unordered_map<int, set<int>> number_to_indices;
    unordered_map<int, int> idx_to_number;
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
