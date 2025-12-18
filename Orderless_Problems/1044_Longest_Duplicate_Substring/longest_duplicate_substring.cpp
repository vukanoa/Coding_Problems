/*
    ============
    === HARD ===
    ============

    =================================
    1044) Longest Duplicate Substring
    =================================

    ============
    Description:
    ============

    Given a string s, consider all duplicated substrings: (contiguous)
    substrings of s that occur 2 or more times. The occurrences may overlap.

    Return any duplicated substring that has the longest possible length. If s
    does not have a duplicated substring, the answer is "".

    ===============================================
    FUNCTION: string longestDupSubstring(string s);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "banana"
    Output: "ana"

    --- Example 2 ---
    Input: s = "abcd"
    Output: ""


    *** Constraints ***
    2 <= s.length <= 3 * 10^4
    s consists of lowercase English letters.

*/

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Binary Search + Rabin Karp)

*/

/* Time  Beats: 91.94% */
/* Space Beats: 77.12% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    string result = "";

    string longestDupSubstring(string s)
    {
        const int N = s.size();

        vector<unsigned long long> power(N, 1);
        for (int i = 1; i < N; i++)
            power[i] = power[i-1] * 131;

        int low  = 0;
        int high = N; // high = N for left-leaning style
        while (low < high)
        {
            int mid = low + (high - low) / 2; // LEFT-leaning

            if (rabin_karp_rolling_hash(mid, s, mid == 0 ? 1 : power[mid-1]))
                low = mid + 1; // mid length exists,        try: low  = mid+1
            else
                high = mid;    // mid length DOESN'T exist, try: high = mid
        }

        return result;
    }

private: 
    bool rabin_karp_rolling_hash(int len, string& s, unsigned long long power)
    {
        if (len == 0)
            return false;

        const int N = s.size();

        int start = 0;
        unordered_set<unsigned long long> uset;

        unsigned long long curr_hash = 0;
        for (int i = 0; i < len; i++)
            curr_hash = curr_hash * 131 + s[i];
        
        uset.insert(curr_hash);

        for (int j = len; j < N; j++)
        {
            curr_hash = (curr_hash - power * s[start]) * 131 + s[j];
            start++;

            if (uset.find(curr_hash) != uset.end())
            {
                string curr_substr = s.substr(start, len);

                if (curr_substr.size() > result.size())
                    result = curr_substr;

                return true;
            }

            uset.insert(curr_hash);
        }

        return false;
    }
};
