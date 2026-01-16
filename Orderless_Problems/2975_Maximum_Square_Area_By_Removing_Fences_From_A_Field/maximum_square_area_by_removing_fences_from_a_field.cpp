/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    2975) Maximum Square Area by Removing Fences From a Field
    =========================================================

    ============
    Description:
    ============

    There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1)
    and (m, n) containing some horizontal and vertical fences given in arrays
    hFences and vFences respectively.

    Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i],
    n) and vertical fences are from the coordinates (1, vFences[i]) to (m,
    vFences[i]).

    Return the maximum area of a square field that can be formed by removing
    some fences (possibly none) or -1 if it is impossible to make a square
    field.

    Since the answer may be large, return it modulo 109 + 7.

    =====
    Note: The field is surrounded by two horizontal fences from the coordinates
          (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from
          the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences
          cannot be removed. 
    =====

    ===========================================================================================
    FUNCTION: int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
    Output: 4
    Explanation: Removing the horizontal fence at 2 and the vertical fence at 2
                 will give a square field of area 4.

    --- Example 2 ---
    Input: m = 6, n = 7, hFences = [2], vFences = [4]
    Output: -1
    Explanation: It can be proved that there is no way to create a square field
                 by removing fences.

    *** Constraints ***
    3 <= m, n <= 10^9
    1 <= hFences.length, vFences.length <= 600
    1 < hFences[i] < m
    1 < vFences[i] < n
    hFences and vFences are unique.

*/

#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.03% */

/* Time  Complexity: O(H^2 * logH + V^2 * logV) */
/* Space Complexity: O(H^2)                     */
class Solution {
public:
    const int MOD = 1e9 + 7;

    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences)
    {
        if (hFences.size() > vFences.size())
            return maximizeSquareArea(n, m, vFences, hFences);

        const int H_SIZE = hFences.size();
        const int V_SIZE = vFences.size();

        hFences.push_back(1);
        hFences.push_back(m);

        vFences.push_back(1);
        vFences.push_back(n);

        vector<int> seen_lengths;
        seen_lengths.reserve(H_SIZE * (H_SIZE - 1));

        collect_or_match_lengths(hFences, seen_lengths, false, max_len);

        /* Sort */
        sort(seen_lengths.begin(), seen_lengths.end());
        seen_lengths.erase(unique(seen_lengths.begin(), seen_lengths.end()), seen_lengths.end());

        collect_or_match_lengths(vFences, seen_lengths, true, max_len);

        if (max_len == 0)
            return -1;

        return 1LL * max_len * max_len % MOD;
    }

private:
    int max_len = 0;

    int my_lower_bound(vector<int>& nums, int low, int high, int target)
    {
        while (low < high)
        {
            int mid = low + (high - low) / 2; // Left-leaning mid

            if (target > nums[mid])
                low = mid + 1;
            else
                high = mid;
        }

        return high;
    }

    void collect_or_match_lengths(vector<int>& fences, vector<int>& seen_lengths, bool should_match, int& max_len_ref)
    {
        const int SIZE = fences.size();

        /* Sort */
        sort(fences.begin(), fences.end());

        for (int L = 0; L < SIZE-1; L++)
        {
            int base = fences[L];

            for (int R = L+1; R < SIZE; R++)
            {
                int len = fences[R] - base;

                if (should_match)
                {
                    int idx = my_lower_bound(seen_lengths, 0, seen_lengths.size(), len);
                    if (idx < seen_lengths.size() && seen_lengths[idx] == len && len > max_len_ref)
                        max_len_ref = len;
                }
                else
                {
                    seen_lengths.push_back(len);
                }
            }
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.03% */
/* Space Beats: 36.89% */

/* Time  Complexity: O(H^2 * logH + V^2 * logV) */
/* Space Complexity: O(H^2)                     */
class Solution_Set {
public:
    const int MOD = 1e9 + 7;

    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences)
    {
        const int H_SIZE = hFences.size() + 2;
        const int V_SIZE = vFences.size() + 2;

        if (H_SIZE > V_SIZE)
            return maximizeSquareArea(n, m, vFences, hFences);

        hFences.push_back(1);
        hFences.push_back(m);

        vFences.push_back(1);
        vFences.push_back(n);

        seen.reserve(H_SIZE * (V_SIZE - 1));

        collect_or_match_lengths(hFences, H_SIZE, false);
        collect_or_match_lengths(vFences, V_SIZE, true);

        if (max_len == 0)
            return -1;

        return 1LL * max_len * max_len % MOD;
    }

private:
    unordered_set<int> seen;
    int max_len = 0;

    void collect_or_match_lengths(vector<int>& fences, int SIZE, bool should_match)
    {
        /* Sort */
        sort(fences.begin(), fences.end());

        for (int L = 0; L < SIZE - 1; L++)
        {
            int base = fences[L];

            for (int R = L + 1; R < SIZE; R++)
            {
                int len = fences[R] - base;

                if (should_match)
                {
                    if (len > max_len && seen.count(len))
                        max_len = len;
                }
                else
                {
                    seen.insert(len);
                }
            }
        }
    }
};
