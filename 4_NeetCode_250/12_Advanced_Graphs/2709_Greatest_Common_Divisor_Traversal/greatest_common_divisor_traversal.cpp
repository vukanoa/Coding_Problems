/*
    ============
    === HARD ===
    ============

    =======================================
    2709) Greatest Common Divisor Traversal
    =======================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums, and you are allowed to
    traverse between its indices. You can traverse between index i and index j,
    i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest
    common divisor.

    Your task is to determine if for every pair of indices i and j in nums,
    where i < j, there exists a sequence of traversals that can take us from i
    to j.

    Return true if it is possible to traverse between all such pairs of
    indices, or false otherwise.

    ======================================================
    FUNCTION: bool canTraverseAllPairs(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,6]
    Output: true
    Explanation: In this example, there are 3 possible pairs of indices: (0,
                 1), (0, 2), and (1, 2).  To go from index 0 to index 1, we can
                 use the sequence of traversals 0 -> 2 -> 1, where we move from
                 index 0 to index 2 because gcd(nums[0], nums[2]) = gcd(2, 6) =
                 2 > 1, and then move from index 2 to index 1 because
                 gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.  To go from index 0
                 to index 2, we can just go directly because gcd(nums[0],
                 nums[2]) = gcd(2, 6) = 2 > 1. Likewise, to go from index 1 to
                 index 2, we can just go directly because gcd(nums[1], nums[2])
                 = gcd(3, 6) = 3 > 1.


    --- Example 2 ---
    Input: nums = [3,9,5]
    Output: false
    Explanation: No sequence of traversals can take us from index 0 to index 2
                 in this example. So, we return false.


    --- Example 3 ---
    Input: nums = [4,3,12,8]
    Output: true
    Explanation: There are 6 possible pairs of indices to traverse between: (0,
                 1), (0, 2), (0, 3), (1, 2), (1, 3), and (2, 3). A valid
                 sequence of traversals exists for each pair, so we return
                 true.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <unordered_set>
#include <vector>
#include <unordered_map>
using namespace std;

class DSU {
private:
    vector<int> rank;
    vector<int> parent;
    int components;

public:
    DSU (int n)
    {
        components = n;

        rank.resize(n);
        parent.resize(n);

        for (int i = 0; i < n; i++)
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman */
            parent[node] = parent[parent[node]];
            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        components--;

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true;
    }

    int number_of_components()
    {
        return components;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    In practice this one is LESS optimal, but for didactic purposes it is
    beneficial to read this Solution first as it shows by-the-book
    implementation of prime-factoriazation and it's more explicit.

*/

/* Time  Beats: 5.17% */
/* Space Beats: 5.17% */

/* Time  Complexity: O(N * sqrt(max(nums))) */
/* Space Complexity: O(N * sqrt(max(nums))) */
class Solution_DSU_Explicit {
public:
    bool canTraverseAllPairs(vector<int>& nums)
    {
        const int N = nums.size();

        unordered_map<int, unordered_set<int>> factors_to_indices;
        // O(N * sqrt(max(nums))) (entire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            for (int f = 1; f * f <= nums[i]; f++) // O(sqrt(max(nums)))
            {
                // We do NOT have to worry about (f * f == nums[i]) case
                // because we're working with a HashSet.
                if (nums[i] % f == 0)
                {
                    factors_to_indices[f].insert(i);
                    factors_to_indices[nums[i] / f].insert(i);
                }
            }
        }

        // O(N)
        DSU dsu(N);

        // O(N * sqrt(max(nums)))
        for (const auto& [factor, indices]: factors_to_indices)
        {
            if (factor == 1)
                continue;

            auto iter = next(indices.begin());

            while (iter != indices.end())
            {
                dsu.union_components(*indices.begin(), *iter);
                iter++;
            }
        }

        return dsu.number_of_components() == 1;
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    This one does "Union" part on-the-fly, i.e. it does it in a Single-Pass.

    In practice this one is more optimal, but for didactic purposes, it is
    beneficial to read the above Solution first as it shows by-the-book
    implementation of prime-factoriazation.

*/

/* Time  Beats: 43.10% */
/* Space Beats: 51.38% */

/* Time  Complexity: O(N * sqrt(max(nums))) */
/* Space Complexity: O(N * sqrt(max(nums))) */
class Solution_DSU_Optimized {
public:
    bool canTraverseAllPairs(vector<int>& nums)
    {
        const int N = nums.size();

        // O(N)
        DSU dsu(N);
        unordered_map<int, int> factor__to__root_idx;

        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            for (int f = 1; f * f <= num; f++)
            {
                if (num % f != 0)
                    continue;

                int f1 = f;
                int f2 = num / f;

                if (f1 > 1)
                {
                    if (factor__to__root_idx.count(f1))
                        dsu.union_components(i, factor__to__root_idx[f1]);
                    else
                        factor__to__root_idx[f1] = i;
                }

                if (f2 > 1)
                {
                    if (factor__to__root_idx.count(f2))
                        dsu.union_components(i, factor__to__root_idx[f2]);
                    else
                        factor__to__root_idx[f2] = i;
                }
            }
        }

        return dsu.number_of_components() == 1;
    }
};




/* Time  Beats: 90.75% */
/* Space Beats: 52.74% */

/* Time  Complexity: O() */
/* Space Complexity: O(N + max_value(nums)) */
class Sieve_DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    Sieve_DSU (const int& N, int max_value)
    {
        const int SIZE = N + max_value + 1;

        rank.resize(SIZE);
        parent.resize(SIZE);

        for (int i = 0; i < SIZE; i++)
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman */
            parent[node] = parent[parent[node]];
            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true;
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    SPF(i.e. "Smallest Prime Factor") using Sieve of Eratosthenes + DSU.

    (Not very difficult if you know SPF_using_Sieve and if you know DSU)

    However, you really need to comfortable with both in order to write this
    bug-free. But it's not too bad.

    TODO detailed explanation.

*/

/* Time  Beats: 82.41% */
/* Space Beats: 64.14% */

/* Time  Complexity: O(M * loglogM  +  N * logM * alpha(N + M)) */
/* Space Complexity: O(N + M)                                   */
class Solution {
public:
    bool canTraverseAllPairs(vector<int>& nums)
    {
        const int N = nums.size();
        if (N == 1)
            return true;

        for (const int& num : nums)
        {
            if (num == 1)
                return false;
        }

        /*
            The inner for-loop runs ONLY when f is PRIME.

            Therefore, instead of thinking "every f"(and there are sqrt(M) of
            them), think:
                "for every prime p <= sqrt(M), mark its multiples"

            Now count total work.

            For a fixed prime p, the inner loop runs about:
                M / p times (we jump by p each inner iteration).

            So total work is:
                M/2 + M/3 + M/5 + M/7 + ... over all primes p

            Factor out M:
                M * (1/2 + 1/3 + 1/5 + 1/7 + ...)

            A fact from Number Theory:
                Sum over primes of (1/p) = log log M + O(1)

            So total work becomes:
                Time Complexity: O(M * log log M)
        */
        int max_value = *max_element(nums.begin(), nums.end());
        vector<int> sieve_SPF(max_value + 1, 0); // SPF - Smallest Prime Factor

        for (int f = 2; f * f <= max_value; f++)
        {
            if (sieve_SPF[f] == 0)
            {
                for (int composite = f * f; composite <= max_value; composite += f)
                {
                    if (sieve_SPF[composite] == 0)
                        sieve_SPF[composite] = f; // Assign first prime factor
                }
            }
        }

        auto is_prime = [&](int num) -> bool {
            return sieve_SPF[num] == 0;
        };

        Sieve_DSU dsu(N, max_value);

        // O(N * logM * alpha(N + M)) (enire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            int num = nums[i];

            while (num > 1)
            {
                int prime_factor = (is_prime(num) ? num : sieve_SPF[num]);

                // Union node 'i'(i.e. the INDEX of a number in "nums") with
                // its SMALLEST PRIME FACTOR
                //
                //
                // DSU nodes [0..N-1] represent nums indices.
                //
                // DSU nodes [N + p]  represent:
                //    (N + 0) idx represents "prime factor 0", which we ignore
                //    (N + 1) idx represents "prime factor 1", which we ignore
                //    (N + 2) idx represents  prime factor 2
                //     ...
                dsu.union_components(i, N + prime_factor); // O(alpha(N + M))

                // Remove ALL occurrences of this prime_factor from num so that
                // each distinct prime is processed ONLY ONCE
                // O(logM)
                while (num % prime_factor == 0)
                    num /= prime_factor;
            }
        }

        int root = dsu.find_root(0);
        for (int i = 1; i < N; i++)
        {
            if (dsu.find_root(i) != root)
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however instead of unioning components, we create an
    Adjacency List and then simply go through the entire UNIDRECTED graph
    starting form node 0. If we end up visiting the first N nodes, then that
    means they're connected.

    We're using DFS instead of DSU here.

*/

/* Time  Beats: 42.19% */
/* Space Beats: 25.58% */

/* Time  Complexity: O(M * loglogM  +  N * logM) */ // M <==> max_value(nums)
/* Space Complexity: O(N + M)                    */
class Solution_Sieve_of_Eratosthenes__plus__DFS {
public:
    bool canTraverseAllPairs(vector<int>& nums)
    {
        const int N = nums.size();

        if (N == 1)
            return true;

        for (const int& num : nums)
        {
            if (num == 1)
                return false;
        }

        /*
            The inner for-loop runs ONLY when f is PRIME.

            Therefore, instead of thinking "every f"(and there are sqrt(M) of
            them), think:
                "for every prime p <= sqrt(M), mark its multiples"

            Now count total work.

            For a fixed prime p, the inner loop runs about:
                M / p times (we jump by p each inner iteration).

            So total work is:
                M/2 + M/3 + M/5 + M/7 + ... over all primes p

            Factor out M:
                M * (1/2 + 1/3 + 1/5 + 1/7 + ...)

            A fact from Number Theory:
                Sum over primes of (1/p) = log log M + O(1)

            So total work becomes:
                Time Complexity: O(M * log log M)
        */
        int max_value = *max_element(nums.begin(), nums.end());
        vector<int> sieve_SPF(max_value + 1, 0); // SPF - Smallest Prime Factor

        for (int f = 2; f * f <= max_value; f++)
        {
            if (sieve_SPF[f] == 0)
            {
                for (int composite = f * f; composite <= max_value; composite += f)
                {
                    if (sieve_SPF[composite] == 0)
                        sieve_SPF[composite] = f; // Assign first prime factor
                }
            }
        }

        auto is_prime = [&](int num) -> bool {
            return sieve_SPF[num] == 0;
        };

        // O(N * logM) (enire block)
        unordered_map<int, vector<int>> adj_list;
        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            while (num > 1)
            {
                int prime_factor = (is_prime(num) ? num : sieve_SPF[num]);

                int curr_node  = i;
                int prime_node = N + prime_factor;

                /* Undirected edge */
                adj_list[curr_node].push_back(prime_node);
                adj_list[prime_node].push_back(curr_node);

                // Remove ALL occurrences of this prime_factor from num so that
                // each distinct prime is processed ONLY ONCE
                // O(logM)
                while (num % prime_factor == 0)
                    num /= prime_factor;
            }
        }

        unordered_set<int> visited;
        /* DFS */
        // M  = max_value(nums)
        // P <= number of distinct primes up to M
        // V  = N + P
        // E  = N * logM
        // O(V + E) --> O(N + P  +  N * logM) ---> O(N * logM)
        dfs(0, visited, adj_list);

        for (int i = 0; i < N; i++)
        {
            if ( ! visited.count(i))
                return false; // All must've been visited through a single DFS
        }

        return true;
    }

private:
    void dfs(int node,
             unordered_set<int>& visited,
             unordered_map<int, vector<int>>& adj_list)
    {
        visited.insert(node);

        for (int& neighbor : adj_list[node])
        {
            if ( ! visited.count(neighbor))
                dfs(neighbor, visited, adj_list);
        }
    }
};
