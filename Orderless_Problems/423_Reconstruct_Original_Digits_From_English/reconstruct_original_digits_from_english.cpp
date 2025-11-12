/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    423) Reconstruct Original Digits from English
    =============================================

    ============
    Description:
    ============

    Given a string s containing an out-of-order English representation of
    digits 0-9, return the digits in ascending order.

    ==========================================
    FUNCTION: string originalDigits(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "owoztneoer"
    Output: "012"

    --- Example 2 ---
    Input: s = "fviefuro"
    Output: "45"

    *** Constraints ***
    1 <= s.length <= 105
    s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
    s is guaranteed to be valid.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Think of it as a directed dependency graph based on letter overlaps:
        'z' --> 0
        'w' --> 2
        'u' --> 4
           \
            \
             --> 'o' --> 1  (depends on 0, 2, 4)

        'x' --> 6
        's' --> 7  (depends on 6)
        'g' --> 8
        'h' --> 3  (depends on 8)
        'f' --> 5  (depends on 4)
        'i' --> 9  (depends on 5, 6, 8)

*/

/* Time  Beats: 55.58% */
/* Space Beats: 10.29% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string originalDigits(string s)
    {
        const int N = s.length();
        int nums[10]; // {0, 1, 2, ... 9}

        vector<int> freq(26);
        for (const char& chr : s)
            freq[chr - 'a']++;

        nums[0] = freq['z' - 'a'];                               // 'z' is unique to zero
        nums[2] = freq['w' - 'a'];                               // 'w' is unique to two
        nums[4] = freq['u' - 'a'];                               // 'u' is unique to four
        nums[5] = freq['f' - 'a'] - nums[4];                     // 'f' indluces: five & four
        nums[6] = freq['x' - 'a'];                               // 'x' is unique to six
        nums[8] = freq['g' - 'a'];                               // 'g' is unique to eight
        nums[1] = freq['o' - 'a'] - nums[0] - nums[2] - nums[4]; // 'o' indluces: zero & one & two & four
        nums[3] = freq['h' - 'a'] - nums[8];                     // 'h' includes: three & eight
        nums[7] = freq['s' - 'a'] - nums[6];                     // 's' includes: seven & six
        nums[9] = freq['i' - 'a'] - nums[6] - nums[8] - nums[5]; // 'i' includes: nine  & six & eight & five

        string result;
        result.reserve(10); // Avoid Reallocations. C++'s SSO.
        for (int i = 0; i < 10; i++)
        {
            if (nums[i] != 0)
                result += string(nums[i], '0' + i);
        }

        return result;
    }
};
