#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    347) Top K Frequent Elements
    ============================

    ============
    Description:
    ============

    Given an integer array "nums" and an integer 'k', return the k most
    frequent elements. You may return the answer in any order.

    Follow up: Your algorithm's time complexity must be better than O(n * logn)
    (where n is the array's size)

    =============================================================
    FUNCTION: vector<int> topKFrequent(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 1, 1, 2, 2, 3], k = 2
    Output: [1, 2]

    --- Example 2 ---
    Input:  nums = [1], k = 1
    Output: [1]

    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4
    k is in the range [1, the number of unique elements in the array]
    It is guaranteed that the answer is unique.

*/


/*
    ------------
    --- IDEA ---
    ------------

    First we need to store the number of occurrences of each number and we do
    that by storing frequencies in a hash map for each number.

    If we were to sort that hash map by value, that would've take O(N * logN)
    which is prohibited by the Problem description.
    (Your algorithm's time complexity must be better than O(N * logN))

    So how can we "sort" our Hash Map without sorting so that we can extract
    top k elements from it?
    Heap!

    Making a Heap from a vector will take O(N)
    Popping an element from the Heap is O(logN)

    Since we have to take only top K elements, we will pop from the Heap
    exactly K times.

    O(N + N + K * logN)

    That makes this Algorithm O(K * logN) which is better than O(N * logN)
    since K is almost always less than N by a large margin.

    It's important to note that the absolutely worst Time Complexity of this
    Algorithm can indeed be O(N * logN) but that happens very rarely that we
    can conclude the complexity is: O(K * logN)

*/

/* Time  Beats: 94.66% */
/* Space Beats: 34.30% */

/* Time  Complexity: O(M * logM) or O(N) */
/*
    Space Complexity: O(M)
    Where M is the number of different values in vector "nums".
*/
class Solution_Heap_1{
private:
    struct Node{
        int num;
        int freq;

        Node (int a, int b)
            : num(a), freq(b) {}
    };

    struct Compare {
        bool operator() (Node const& a, Node const& b)
        {
            return a.freq < b.freq;
        }
    };

public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map; // Key->Number ... Value->Freq

        // Step 1: Store frequence of all elements in map
        // O(N)
        for (int n : nums)
            map[n]++;

        // Step 2: Now build a Heap
        // Compare defines a max-heap based on frequency
        // O(M * logM), where M is number of different values in vector "nums"
        // O(M) for traversing through "map", O(logM) to push in a Heap
        std::priority_queue<struct Node, std::vector<struct Node>, struct Compare> heap;
        for (auto it: map)
            heap.push(Node(it.first, it.second));

        std::vector<int> ret;

        // Step 3: Pop top K elements and store the numbers in "results" vector
        // O(K)
        while (k--)
        {
            struct Node tmp = heap.top();
            heap.pop();
            ret.push_back(tmp.num);
        }

        return ret;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, just implemented in a different way.

*/

/* Time  Beats: 90.33% */
/* Space Beats: 58.62% */

/* Time  Beats: 83.57% */
/* Space Beats: 97.10% */

/* Time  Complexity: O(M * logM) or O(N) */
/*
    Space Complexity: O(M)
    Where M is the number of different values in vector "nums".
*/
class Solution_Heap_2 {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k)
    {
        // Key=Number    Value=Frequency
        std::unordered_map<int, int> umap_freq;

        // Step 1: Store frequence of all elements in a Hash Map
        // O(N)
        for (int& num : nums)
            umap_freq[num]++;

        // Step 2: Build a Heap
        // O(M * logM), where M is number of different values in vector "nums"
        // O(M) for traversing through "map", O(logM) to push in a Heap
        std::priority_queue<std::pair<int, int>> max_heap;
        for (auto& entry : umap_freq)
            max_heap.push({entry.second, entry.first});

        // Step 3: Pop top K elements and store the numbers in "results" vector
        // O(K)
        std::vector<int> results;
        while (k--)
        {
            std::pair<int, int> pair = max_heap.top();
            max_heap.pop();

            results.push_back(pair.second);
        }

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Step 1 is the same as in the previous(above) idea.

    Now we should simulate what Bucket Sort does, but not all the way. We do
    not have to sort it completely.

    Example:
        [8, 8, 8, 8, 8]

    It is absolutely impossible to have more than N occurences. Also we can
    observe that we can have two elements occur the same amount of time.
    (Though there will always be K distinct unique elements. Meaning we will
    always have a result, we don't have to check these cases)

    The solution is to have an array of size N(maximum possible number of
    occurences) and that for each slot, we maintain a vector of elements that
    have that number of occurences in the array "nums".

    Example:
    [5, 6, 2, 3, 4, 9, 9, 9, 6, 6, 6, 7, 7]

    Map:
        5: 1
        6: 4
        2: 1
        3: 1
        4: 1
        9: 3
        7: 2

    vector of vectors "freq" is of size N

        freq:
        [
   0:   /
   1:   [5, 2, 3, 4]
   2:   [7]
   3:   [9]
   4:   [6]
   5:   /
   6:   /
   7:   /
   8:   /
   9:   /
  10:   /
  11:   /
        ]

    After forming this "freq", we just iterate from the back and push in vector
    "ret" until ret.size() becomes k, that is until we have "pushed" k elements
    in our vector that is our return value.

*/

/* Time  Beats: 89.18% */
/* Space Beats: 6.12% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bucket{
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map;

        // Step 1: Store frequence of all elements in map
        // O(N)
        for (int& num : nums)
            map[num]++;

        // Step 2: Bucket Sort's first step
        // O(N)
        std::vector<std::vector<int>> freq(nums.size() + 1);
        for (const auto& it: map)
            freq[it.second].push_back(it.first);

        // Step 3: Take every item from the back until k elements are taken
        // O(K)
        std::vector<int> ret;
        for (int i = freq.size() - 1; i >= 0; i--)
        {
            for (int& elem : freq[i])
            {
                ret.push_back(elem);

                if (ret.size() == k)
                    return ret;
            }
        }

        return ret;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The main reason why this Solution is as Efficient is the Time Complexity
    explanation which is explained down below, but I will repeat it again to
    emphasize its importance for this problem:

    Time  Complexity: O(M * log M) or (N)

    In Constraints, it is said:
        1 <= nums.length <= 10^5
        -10^4 <= nums[i] <= 10^4

                  nums.length, let's call it => N
    2 * 10^4 DIFFERENT VALUES, let's call it => M

    We can see that:
        N >= M

    Since even if in theory M can be greater than N, practically that is not
    possible.

    If we have a vector "nums" of size 4, we cannot use more than 4 DIFFERENT
    VALUES insides that vector "nums".

    So in case we have vector size of N and in it all the elements are unique,
    that means that M == N.

    However in the VAST majority of cases we can consider:
        N > M

    In the Follow-Up Question we're asked to solve it better than O(N * logN).

    Since N > M, we can conclude that:
        O(M * log M) is BETTER than O(N * logN)

    Also:
        O(N) can be either BETTER or WORSE than O(M * logM) depending on the
        vector nums.

    So the Time Complexity is either O(N) or O(M * logM) whichever happens to
    take more time is the "bottleneck" and thus that will be the overall Time
    Complexity.

    In case where O(N) > O(M * logM), Time Complexity is going to be:
        O(N + M * logM) => O(N)

        Example: [3, 3, 3, 3, 3, 2, 2, 3, 1, 1, 3, 2, 3, ...]
        (There are only 1's, 2's and 3's in this vector)

        N = 50 000
        M = 3
        O(N) > O(M * logM) => The overall Time Complexity is: O(N)



    In case where O(N) < O(M * logM), Time Complexity is going to be:
        O(N + M * logM) => O(M * logM)

        Example: [7, 2, 8, 9, 1] => N == M => O(N) < O(M * logM) => The overall
        Time Complexity is: O(M * logM), i.e. O(N * logN) since N == M.


    Why do we have O(N + M * logM)? Where did we get those "numbers"?

    First we have to find a Min element and the Max element value in "nums".
    That takes O(2 * N) => O(N)

    Then we initialize a vector of size: Max element - Min element
    We create a Hash Map:(However I'm implementing it as a vector of pairs)

         key      value(occurrences)
        +-------+-------+
        | min+0 |   0   |
        +-------+-------+
        | min+1 |   3   |
        +-------+-------+
        | min+2 |   2   |
        +-------+-------+
        | min+3 |   9   |
        +-------+-------+
        | ...   |       |
        +-------+-------+
        | min+8 |   7   |
        +-------+-------+
        | ...   |       |
        +-------+-------+
        | max   |   5   |
        +-------+-------+

    Now sort this Hash Map(vector of pairs). Since there are M elements in this
    Hash Map(vector of pairs), sorting takes O(M * logM) Time Complexity.

    After Sorting:


         key      value(occurrences)
        +-------+-------+
        | min+6 |   0   |
        +-------+-------+
        |  ...  |       |
        +-------+-------+
        |  ...  |       |
        +-------+-------+
        | min+2 |   2   |
        +-------+-------+
        | min+1 |   3   |
        +-------+-------+
        | max   |   5   |
        +-------+-------+
        | min+8 |   7   |
        +-------+-------+
        | min+3 |   9   |
        +-------+-------+

    After that return last k elements. That's the whole IDEA.

*/

/* Time  Beats: 99.13% */
/* Space Beats: 99.04% */

/*
    Time  Complexity: O(M * log M) or (N)

    In Constraints, it is said:
        1 <= nums.length <= 10^5
        -10^4 <= nums[i] <= 10^4

                  nums.length, let's call it => N
    2 * 10^4 DIFFERENT VALUES, let's call it => M

    We can see that:
        N >= M

    Since even if in theory M can be greater than N, practically that is not
    possible.

    If we have a vector "nums" of size 4, we cannot use more than 4 DIFFERENT
    VALUES insides that vector "nums".

    So in case we have vector size of N and in it all the elements are unique,
    that means that M == N.

    However in the VAST majority of cases we can consider:
        N > M

    In the Follow-Up Question we're asked to solve it better than O(N * logN).

    Since N > M, we can conclude that:
        O(M * log M) is BETTER than O(N * logN)

    Also:
        O(N) can be either BETTER or WORSE than O(M * logM) depending on the
        vector nums.

    So the Time Complexity is either O(N) or O(M * logM) whichever happens to
    take more time is the "bottleneck" and thus that will be the overall Time
    Complexity.

    In case where O(N) < O(M * logM), Time Complexity is going to be:
        O(N + M * logM) => O(M * logM)

        Example: [3, 3, 3, 3, 3, 2, 2, 3, 1, 1, 3, 2, 3, ...]
        (There are only 1's, 2's and 3's in this vector)

        N = 50 000
        M = 3
        O(N) > O(M * logM) => The overall Time Complexity is: O(N)

*/
/* Space Complexity: O(M) */
class Solution_Efficient {
private:
    struct sort_pred {
        bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right)
        {
            return left.second < right.second;
        }
    };

public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k)
    {
        int max = *std::max_element(nums.begin(), nums.end());
        int min = *std::min_element(nums.begin(), nums.end());

        std::vector<std::pair<int, int>> map;

        for (int i = min; i <= max; i++)
            map.emplace_back(i, 0);

        for (int i = 0; i < nums.size(); i++)
        {
            auto& pair = map[nums[i] - min];
            pair.second++;
        }

        // Sort the vector by "second" value
        std::sort(map.begin(), map.end(), sort_pred());

        std::vector<int> results;

        for (int i = k; i > 0; i--)
        {
            auto& pair = map[map.size() - i];
            results.push_back(pair.first);
        }

        return results;
    }
};



int
main()
{
    Solution_Heap_1    sol_heap_1;
    Solution_Heap_2    sol_heap_2;
    Solution_Bucket    sol_bucket;
    Solution_Efficient sol_eff;

    /* Example 1 */
    // std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    // int k = 2;

    /* Example 2 */
    // std::vector<int> nums = {1};
    // int k = 1;

    /* Example 3 */
    std::vector<int> nums = {5, 6, 2, 3, 4, 9, 9, 9, 6, 6, 6, 7, 7};
    int k = 3;


    std::cout << "\n\t===============================";
    std::cout << "\n\t=== TOP K FREQUENT ELEMENTS ===";
    std::cout << "\n\t===============================\n";


    /* Write Input */
    std::cout << "\n\tK = " << k;

    bool first = true;
    std::cout << "\n\tArray: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // std::vector ret = sol_heap_1.topKFrequent(nums, k);
    // std::vector ret = sol_heap_2.topKFrequent(nums, k);
    // std::vector ret = sol_bucket.topKFrequent(nums, k);
    std::vector ret = sol_eff.topKFrequent(nums, k);


    /* Write Output */
    first = true;
    if (k > 1)
        std::cout << "\n\tTop " << k << " Frequent elements: [";
    else
        std::cout << "\n\tTop Frequent element: [";

    for (auto x: ret)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
