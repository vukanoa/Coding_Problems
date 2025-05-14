/*
    ============
    === HARD ===
    ============

    =========================================================
    3337) Total Characters in String After Transformations II
    =========================================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters, an
    integer t representing the number of transformations to perform, and an
    array nums of size 26. In one transformation, every character in s is
    replaced according to the following rules:

        Replace s[i] with the next nums[s[i] - 'a'] consecutive characters in
        the alphabet. For example, if s[i] = 'a' and nums[0] = 3, the character
        'a' transforms into the next 3 consecutive characters ahead of it,
        which results in "bcd".

        The transformation wraps around the alphabet if it exceeds 'z'. For
        example, if s[i] = 'y' and nums[24] = 3, the character 'y' transforms
        into the next 3 consecutive characters ahead of it, which results in
        "zab".

    Return the length of the resulting string after exactly t transformations.

    Since the answer may be very large, return it modulo 109 + 7.

    =============================================================================
    FUNCTION: int lengthAfterTransformations(string s, int t, vector<int>& nums);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
    Output: 7
    Explanation:
        First Transformation (t = 1):
            'a' becomes 'b' as nums[0] == 1
            'b' becomes 'c' as nums[1] == 1
            'c' becomes 'd' as nums[2] == 1
            'y' becomes 'z' as nums[24] == 1
            'y' becomes 'z' as nums[24] == 1
            String after the first transformation: "bcdzz"

        Second Transformation (t = 2):
            'b' becomes 'c' as nums[1] == 1
            'c' becomes 'd' as nums[2] == 1
            'd' becomes 'e' as nums[3] == 1
            'z' becomes 'ab' as nums[25] == 2
            'z' becomes 'ab' as nums[25] == 2
            String after the second transformation: "cdeabab"
        Final Length of the string: The string is "cdeabab", which has 7 characters.


    --- Example 2 ---
    Input: s = "azbk", t = 1, nums = [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
    Output: 8
    Explanation:
        First Transformation (t = 1):
            'a' becomes 'bc' as nums[0] == 2
            'z' becomes 'ab' as nums[25] == 2
            'b' becomes 'cd' as nums[1] == 2
            'k' becomes 'lm' as nums[10] == 2
            String after the first transformation: "bcabcdlm"

        Final Length of the string: The string is "bcabcdlm", which has 8 characters.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of lowercase English letters.
    1 <= t <= 10^9
    nums.length == 26
    1 <= nums[i] <= 25

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

/* Time  Beats: 8.33% */
/* Space Beats: 6.25% */

/* Time  Complexity: O(logT * 26) */
/* Space Complexity: O(26^2)      */
using ll = long long;
class Solution {
public:
    const int mod = 1e9 + 7;
    int lengthAfterTransformations(string s, int t, vector<int>& nums)
    {
        vector<vector<ll>> transform(26, vector<ll>(26, 0));

        for (int i = 0; i < 26; i++)
        {
            for (int shift = 0; shift < nums[i]; shift++)
            {
                transform[i][(i + 1 + shift) % 26]++;
            }
        }

        transform = power_matrix(transform, t);

        vector<vector<ll>> freq(1, vector<ll>(26, 0));
        for (const char& chr : s)
            freq[0][chr - 'a']++;


        freq = multiplying_matrices(freq, transform);
        int total_length = 0;
        for (int count : freq[0])
        {
            total_length += count;

            if (total_length >= mod)
                total_length -= mod;
        }

        return total_length;
    }

private:
    vector<vector<ll>> multiplying_matrices(const vector<vector<ll>> &A, const vector<vector<ll>> &B)
    {
        int rowsA = A.size();
        int colsA = A[0].size();
        int colsB = B[0].size();
        vector<vector<__int128_t>> temp(rowsA, vector<__int128_t>(colsB, 0));
        vector<vector<ll>> result(rowsA, vector<ll>(colsB, 0));

        for (int i = 0; i < rowsA; i++)
        {
            for (int j = 0; j < colsB; j++)
            {
                for (int k = 0; k < colsA; k++)
                {
                    temp[i][j] += A[i][k] * B[k][j];
                }

                result[i][j] = temp[i][j] % mod;
            }
        }

        return result;
    }

    vector<vector<ll>> power_matrix(vector<vector<ll>> matrix, ll exponent)
    {
        vector<vector<ll>> result(matrix.size(), vector<ll>(matrix.size(), 0));

        for (int i = 0; i < matrix.size(); i++)
            result[i][i] = 1;

        while (exponent > 0)
        {
            if (exponent % 2 == 1)
                result = multiplying_matrices(result, matrix);

            matrix = multiplying_matrices(matrix, matrix);
            exponent /= 2;
        }

        return result;
    }
};
