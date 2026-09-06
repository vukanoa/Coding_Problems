/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    1409) Queries on a Permutation With Key
    =======================================

    ============
    Description:
    ============

    Given the array queries of positive integers between 1 and m, you have to
    process all queries[i] (from i=0 to i=queries.length-1) according to the
    following rules:

        + In the beginning, you have the permutation P=[1,2,3,...,m].

        + For the current i, find the position of queries[i] in the permutation
          P (indexing from 0) and then move this at the beginning of the
          permutation P. Notice that the position of queries[i] in P is the
          result for queries[i].

    Return an array containing the result for the given queries.

    ==================================================================
    FUNCTION: vector<int> processQueries(vector<int>& queries, int m);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: queries = [3,1,2,1], m = 5
    Output: [2,1,2,1] 
    Explanation: The queries are processed as follow: 
    For i=0: queries[i]=3, P=[1,2,3,4,5], position of 3 in P is 2, then we move 3 to the beginning of P resulting in P=[3,1,2,4,5]. 
    For i=1: queries[i]=1, P=[3,1,2,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,3,2,4,5]. 
    For i=2: queries[i]=2, P=[1,3,2,4,5], position of 2 in P is 2, then we move 2 to the beginning of P resulting in P=[2,1,3,4,5]. 
    For i=3: queries[i]=1, P=[2,1,3,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,2,3,4,5]. 
    Therefore, the array containing the result is [2,1,2,1].  

    --- Example 2 ---
    Input: queries = [4,1,2,2], m = 4
    Output: [3,1,2,0]

    --- Example 3 ---
    Input: queries = [7,5,5,8,3], m = 8
    Output: [6,5,0,7,5]


    *** Constraints ***
    1 <= m <= 10^3
    1 <= queries.length <= m
    1 <= queries[i] <= m

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.96% */
/* Space Beats:  8.43% */

/* Time  Complexity: O((m + Q) * log(m)) */
/* Space Complexity: O(m)                */
class Sum_Fenwick { // 1-based
private:
    vector<long long> sum_fenwick;
    int n;

public:
    Sum_Fenwick(int n)
        : n(n), sum_fenwick(n + 1, 0)
    {}

    long long sum(int L, int R)
    {
        return sum(R) - sum(L - 1);
    }

    long long sum(int i)
    {
        long long sum = 0;

        while (i > 0)
        {
            sum += sum_fenwick[i];

            // Clear Last SET-bit
            i -= i & -i;
        }

        return sum;
    }


    void update(int idx, long long delta)
    {
        int i = idx;
        while (i <= n)
        {
            sum_fenwick[i] += delta;

            // Add Last SET-bit
            i += i & -i;
        }
    }
};

class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m)
    {
        vector<int> result;

        Sum_Fenwick fenwick_tree(2 * m);
        unordered_map<int, int> umap;
        
        // Initialize positions: [1 to m] are now at positions  [m+1 to 2m]
        for (int i = 1; i <= m; i++)
        {
            umap[i] = m + i;
            fenwick_tree.update(m + i, 1);
        }

        for (const int& query : queries)
        {
            // Get current position and calculate sum BEFORE it
            result.push_back(fenwick_tree.sum(umap[query] - 1));
            
            // Remove from current position
            fenwick_tree.update(umap[query], -1);
            
            // Add to front position (position m)
            fenwick_tree.update(m, 1);
            umap[query] = m;

            // Decrement
            --m;
        }  

        return result;     
    }
};
