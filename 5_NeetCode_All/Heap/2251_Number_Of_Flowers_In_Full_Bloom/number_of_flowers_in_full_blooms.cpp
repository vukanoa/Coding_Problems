#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <queue>

/*
    ============
    === HARD ===
    ============

    =====================================
    2251) Number of Flowers in Full Bloom
    =====================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D integer array flowers, where flowers[i] =
    [starti, endi] means the ith flower will be in full bloom from starti to
    endi (inclusive). You are also given a 0-indexed integer array people of
    size n, where people[i] is the time that the ith person will arrive to see
    the flowers.

    Return an integer array answer of size n, where answer[i] is the number of
    flowers that are in full bloom when the ith person arrives.

    ==========================================================================================
    FUNCTION: vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people);
    ==========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
    Output: [1,2,2,2]
    Explanation: The figure above shows the times when the flowers are in full
                 bloom and when the people arrive. For each person, we return
                 the number of flowers in full bloom during their arrival.

    --- Example 2 ---
    Input: flowers = [[1,10],[3,3]], people = [3,3,2]
    Output: [2,2,1]
    Explanation: The figure above shows the times when the flowers are in full
                 bloom and when the people arrive. For each person, we return
                 the number of flowers in full bloom during their arrival.


    *** Constraints ***
    1 <= flowers.length <= 5 * 10^4
    flowers[i].length == 2
    1 <= starti <= endi <= 10^9
    1 <= people.length <= 5 * 10^4
    1 <= people[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 34.96% */
/* Space Beats: 22.47% */

/* Time  Complexity: O((m + n) * log(m + n)) */
/* Space Complexity: O(m + n)                */
class Solution_Unordered_Map {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people)
    {
        unordered_map<int,int> umap; // No ordering
        vector<int> umap_key;

        for (int p : people)
        {
            if (umap.count(p) == 0)
            {
                umap[p] = 0;
                umap_key.push_back(p);
            }
        }

        for (auto& fl: flowers)
        {
            int start_time = fl[0];
            int end_time   = fl[1] + 1;

            if (umap.count(start_time))
                umap[start_time]++;
            else
            {
                umap[start_time] = 1;
                umap_key.push_back(start_time);
            }

            if (umap.count(end_time))
                umap[end_time]--;
            else
            {
                umap[end_time] = -1;
                umap_key.push_back(end_time);
            }
        }

        sort(umap_key.begin(), umap_key.end());

        int bloom = 0;
        for (int k : umap_key) // Compute bloom according to sorted umap_key
        {
            umap[k] += bloom;
            bloom = umap[k];
        }

        int n = people.size();
        vector<int> result(n);

        for (int i = 0; i < n; i++)
           result[i] = umap[people[i]];

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 13.82% */
/* Space Beats: 22.47% */

/* Time  Complexity: O((m + n) * log(m + n)) */
/* Space Complexity: O(m + n)                */
class Solution_Map {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people)
    {
        map<int, int> map; // Keep the ordering

        for (int p : people)
            map[p] = 0;

        for (auto& fl : flowers)
        {
            int start_time = fl[0];
            int end_time   = fl[1] + 1;

            if (map.count(start_time))
                map[start_time]++;
            else
                map[start_time] = 1;

            if (map.count(end_time))
                map[end_time]--;
            else
                map[end_time] = -1;
        }

        int bloom = 0;
        for (auto& [time, bloom_count] : map) // map has an ordered traversal
        {
            bloom_count += bloom;
            bloom = bloom_count;
        }

        int n = people.size();
        vector<int> result(n);

        for (int i = 0; i < n; i++)
            result[i] = map[people[i]];

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 71.55% */
/* Space Beats: 67.53% */

/* Time  Complexity: O((m + n) * logm) */
/* Space Complexity: O(m + n)          */
class Solution_Min_Heap {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people)
    {
        const int n = people.size();

        vector<pair<int, int>> people_idx(n);

        for (int i = 0; i < n; i++)
            people_idx[i] = {people[i], i};

        // Sort
        sort(people_idx.begin(), people_idx.end());

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> min_heap;

        for (const auto& fl: flowers)
        {
            int start_time = fl[0];
            int end_time   = fl[1]+1;

            min_heap.emplace(start_time, 1); // emplace because it's pair<int, int>
            min_heap.emplace(end_time,  -1); // emplace because it's pair<int, int>
        }

        vector<int> result(n);
        int j = 0;
        int bloom = 0;

        for (int i = 0; i < n; i++)
        {
            auto [peo, idx] = people_idx[i];

            while ( ! min_heap.empty() && min_heap.top().first <= peo)
            {
                bloom += min_heap.top().second;
                min_heap.pop();
            }
            result[idx] = bloom;
        }

        return result;
    }
};
