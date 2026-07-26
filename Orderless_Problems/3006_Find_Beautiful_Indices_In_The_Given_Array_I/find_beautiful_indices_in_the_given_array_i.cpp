/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3006) Find the Beautiful Indices in the Given Array I
    =====================================================

    ============
    Description:
    ============

    You are given a 0-indexed string s, a string a, a string b, and an integer
    k.

    An index i is beautiful if:

        0 <= i <= s.length - a.length

        s[i..(i + a.length - 1)] == a

        There exists an index j such that:
            0 <= j <= s.length - b.length
            s[j..(j + b.length - 1)] == b
            |j - i| <= k

    Return the array that contains beautiful indices in sorted order from
    smallest to largest.

    ============================================================================
    FUNCTION: vector<int> beautifulIndices(string s, string a, string b, int k);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "isawsquirrelnearmysquirrelhouseohmy", a = "my", b = "squirrel", k = 15
    Output: [16,33]
    Explanation: There are 2 beautiful indices: [16,33].
    - The index 16 is beautiful as s[16..17] == "my" and there exists an index 4 with s[4..11] == "squirrel" and |16 - 4| <= 15.
    - The index 33 is beautiful as s[33..34] == "my" and there exists an index 18 with s[18..25] == "squirrel" and |33 - 18| <= 15.
    Thus we return [16,33] as the result.

    --- Example 2 ---
    Input: s = "abcd", a = "a", b = "a", k = 4
    Output: [0]
    Explanation: There is 1 beautiful index: [0].
    - The index 0 is beautiful as s[0..0] == "a" and there exists an index 0 with s[0..0] == "a" and |0 - 0| <= 4.
    Thus we return [0] as the result.


    *** Constraints ***
    1 <= k <= s.length <= 10^5
    1 <= a.length, b.length <= 10
    s, a, and b contain only lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 16.09% */
/* Space Beats: 49.79% */

/* Time  Complexity: O(N * (|a| + |b|) + A * B) */
/* Space Complexity: O(A + B + R)               */
class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k)
    {
        // Lengths of strings
        int N = s.size();
        int A_SIZE = a.size();
        int B_SIZE = b.size();

        vector<int> result;
        
        vector<int> indices_a;
        vector<int> indices_b;
        
        // Find indices of occurrences of string 'a'
        for (int i = 0; i <= N - A_SIZE; i++)
        {
            if (s.substr(i, A_SIZE) == a)
                indices_a.push_back(i);
        }
        
        // Find indices of occurrences of string 'b'
        for (int j = 0; j <= N - B_SIZE; j++)
        {
            if (s.substr(j, B_SIZE) == b)
                indices_b.push_back(j);
        }

        const int INDICES_A_SIZE = indices_a.size();
        const int INDICES_B_SIZE = indices_b.size();
        
        // Check conditions and add beautiful indices to "result"
        for (int i = 0; i < INDICES_A_SIZE; i++)
        {
            for (int j = 0; j < INDICES_B_SIZE; j++)
            {
                // Check if substrings match and absolute difference <= k
                if (abs(indices_a[i] - indices_b[j]) <= k)
                {
                    result.push_back(indices_a[i]);
                    break;
                }
            }
        }
        
        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Optimized by using: (KMP + TwoPointers)

*/

/* Time  Beats: 95.28% */
/* Space Beats: 18.03% */

/* Time  Complexity: O(N + A + B) */
/* Space Complexity: O(N + A + B + R) */
class KMP {
public:
    vector<int> kmp_algo(string s, string pattern)
    {
        const int N = s.size();
        const int M = pattern.size();

        vector<int> result;

        /* Populate LPS */
        vector<int> LPS = calculate_LPS(pattern);

        int i = 0;
        int j = 0;

        while (i < N)
        {
            if (s[i] == pattern[j])
            {
                i++;
                j++;

                if (j == M)
                {
                    result.push_back(i - M);
                    j = LPS[j - 1];
                }
            }
            else
            {
                if (j > 0)
                    j = LPS[j - 1];
                else
                    i++;
            }
        }

        return result;
    }

private:
    vector<int> calculate_LPS(string& pattern)
    {
        const int PATTERN_SIZE = pattern.size();

        /* Initialize with ZEROES */
        vector<int> LPS(PATTERN_SIZE, 0);

        int prefix_len = 0;
        int i          = 1;

        while (i < PATTERN_SIZE)
        {
            if (pattern[prefix_len] == pattern[i])
            {
                LPS[i] = prefix_len + 1;
                prefix_len++;
                i++;
            }
            else
            {
                if (prefix_len > 0)
                    prefix_len = LPS[prefix_len - 1];
                else
                    i++;
            }
        }

        return LPS;
    }
};

class Solution_KMP {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k)
    {
        KMP kmp;

        vector<int> indices_a = kmp.kmp_algo(s, a);
        vector<int> indices_b = kmp.kmp_algo(s, b);

        vector<int> result;

        int i = 0;
        int j = 0;

        while (i < indices_a.size() && j < indices_b.size())
        {
            if (abs(indices_a[i] - indices_b[j]) <= k)
            {
                result.push_back(indices_a[i]);
                i++;
            }
            else if (indices_b[j] - indices_a[i] > k)
            {
                i++;
            }
            else
            {
                j++;
            }
        }

        return result;
    }
};
