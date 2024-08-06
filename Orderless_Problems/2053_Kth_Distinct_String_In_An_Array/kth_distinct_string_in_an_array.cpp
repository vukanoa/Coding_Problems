#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

/*
    ============
    === EASY ===
    ============

    =====================================
    2053) Kth Distinct String in an Array
    =====================================

    ============
    Description:
    ============

    A distinct string is a string that is present only once in an array.

    Given an array of strings arr, and an integer k, return the kth distinct
    string present in arr. If there are fewer than k distinct strings, return
    an empty string "".

    =====
    Note: Note that the strings are considered in the order in which they
          appear in the array.
    =====

    =========================================================
    FUNCTION: string kthDistinct(vector<string>& arr, int k);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = ["d","b","c","b","c","a"], k = 2
    Output: "a"
    Explanation:
    The only distinct strings in arr are "d" and "a".
    "d" appears 1st, so it is the 1st distinct string.
    "a" appears 2nd, so it is the 2nd distinct string.
    Since k == 2, "a" is returned.


    --- Example 2 ---
    Input: arr = ["aaa","aa","a"], k = 1
    Output: "aaa"
    Explanation:
    All strings in arr are distinct, so the 1st string "aaa" is returned.


    --- Example 3 ---
    Input: arr = ["a","b","a"], k = 3
    Output: ""
    Explanation: The only distinct string is "b". Since there are fewer than 3
                 distinct strings, we return an empty string "".


    *** Constraints ***
    1 <= k <= arr.length <= 1000
    1 <= arr[i].length <= 5
    arr[i] consists of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 30.77% */
/* Space Beats:  5.44% */

/* Time  Complexity: O(n + k*logn) */
/* Space Complexity: O(n)          */
class Solution {
public:
    string kthDistinct(vector<string>& arr, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        unordered_map<string, pair<int, int>> umap;

        /* O(n) */
        for (int i = 0; i < arr.size(); i++)
        {
            if (umap.find(arr[i]) == umap.end())
                umap.insert( {arr[i], {1, i} } );
            else
                umap[arr[i]].first++;
        }

        /* O(n) */
        vector<pair<int, string>> distinct;
        for (const auto& entry : umap)
        {
            string str = entry.first;

            int freq = entry.second.first;
            int idx  = entry.second.second;

            if (freq == 1)
                distinct.push_back( {idx, str} );
        }


        /* O(n) */
        std::priority_queue<pair<int, string>,
                            vector<pair<int, string>>,
                            greater<pair<int, string>>> min_heap(distinct.begin(), distinct.end());


        /* O(k * logn) */
        while ( ! min_heap.empty() && k > 1)
        {
            min_heap.pop(); // O(logn)
            k--;
        }

        return min_heap.empty() ? "" : min_heap.top().second;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 84.08% */
/* Space Beats: 20.16% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Elegant {
public:
    string kthDistinct(vector<string>& arr, int k)
    {
        unordered_map<string, int> counter;

        for (auto& str : arr)
            counter[str]++;

        for (auto& str : arr)
        {
            if (counter[str] == 1)
            {
                k--;

                if (k == 0)
                    return str;
            }
        }

        return "";
    }
};
