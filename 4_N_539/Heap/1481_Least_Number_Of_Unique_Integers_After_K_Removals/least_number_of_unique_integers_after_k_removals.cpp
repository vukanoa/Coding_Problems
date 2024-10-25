#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================
    1481) Least Number of Unique Integers after K Removals
    ======================================================

    ============
    Description:
    ============

    Given an array of integers arr and an integer k. Find the least number of
    unique integers after removing exactly k elements.

    ================================================================
    FUNCTION: int findLeastNumOfUniqueInts(vector<int>& arr, int k);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [5,5,4], k = 1
    Output: 1
    Explanation: Remove the single 4, only 5 is left.

    --- Example 2 ---
    Input: arr = [4,3,1,1,3,3,2], k = 3
    Output: 2
    Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3
                 will be left.


    *** Constraints ***
    1 <= arr.length <= 10^5
    1 <= arr[i] <= 10^9
    0 <= k <= arr.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is the most intuitive problem ever if you're reading it carefully.

    We're told:"Find the least number of unique integers after removing exactly
    k elements"

    Imagine that we have this:

        arr = [5, 5, 5, 5, 5, 5, 3], k = 1

    We must remove exactly ONE element. Which one should we remove in order to
    MINIMIZE the number of unique elements we're left with after that?

    Obviously, we ought to remove 3 since after that we're only left with a
    bunch of 5's, i.e. with a single unique element in the entire array.

    Had we remove some instance of 5, we would be left with:

        arr = [5, 5, 5, X, 5, 5, 3], k = 0


    We're already ready to solve this problem. We should obtain a occurrence
    for each unique number in the arr and then sort in ascending order by
    occurring times.


    Let's suppose we've had something like this:

        Input: arr = [4,3,1,1,3,3,2], k = 3

    After the sort, we'd have something like this:

        vec_counter = [ {2,1}, {4,1}, {1,2}, {3,3} ]
                           ^      ^      ^      ^
                           |      |      |      |
                           |      |      |      |
                      [   1,      1,     2,     3  ]

    Start removing from the beginning, from the least occuring number and once
    you remove all instances of some number, i.e. the count becomes 0, then
    decrement "result" by one. (initially "result" is set to number of unique
    elements in arr)

    In this example, because k = 3, we would remove:

        One instance of number 2, which would mean we're left with 0 2s.
        One instance of number 4, which would mean we're left with 0 4s.
        One instance of number 1, which would mean we're left with 1 1s.

    Initially we have 4 unique numbers in arr: 2, 4, 1 and 3.

    After removing k elements, we're left with: 1 and 3

    Meaning - The minimum amount of unique elements after k removal is 2.

*/

/* Time  Beats: 18.21% */
/* Space Beats: 43.50% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_Sorting {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k)
    {
        // Count occurrences using a map(TreeMap in Java, ordered one)
        std::map<int, int> map_counter;
        for (int num : arr)
            map_counter[num]++;

        // Transfer map data to a vector of pairs
        std::vector<std::pair<int, int>> vec_counter(map_counter.begin(), map_counter.end());

        // Sort the vector by the occurrence count
        std::sort(vec_counter.begin(), vec_counter.end(),
                [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                    return a.second < b.second; // Sort by occurrence count
                });

        int result = vec_counter.size();
        int i = 0;
        while (k > 0)
        {
            vec_counter[i].second--;

            if (vec_counter[i].second == 0)
            {
                result--;
                i++;
            }

            k--;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Essentially the same as the above Solution, but instead of sorting
    explicitly, we're using a Heap data structure.

*/

/* Time  Beats: 65.01% */
/* Space Beats: 34.52% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n )       */
class Solution_Heap {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;

        unordered_map<int, int> umap_counter;

        for (auto elem : arr)
            umap_counter[elem]++;

        for (auto item : umap_counter)
            min_heap.push({item.second, item.first});

        while (k > 0)
        {
            auto top = min_heap.top();
            min_heap.pop();

            top.first--;

            if (top.first)
                min_heap.push(top);

            k--;
        }

        return min_heap.size();
    }
};
