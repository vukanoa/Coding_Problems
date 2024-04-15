#include <iostream>
#include <vector>
#include <climits>

/*
    ============
    === HARD ===
    ============

    ============================
    76) Minimum Window Substring
    ============================

    ============
    Description:
    ============

    Given two strings 's' and 't' lengths 'm' and 'n' respectively, return the
    minimum window substring of 's' such that every character in 't'(including
    duplicates) is included in the window. If there is no such substring,
    return the empty string "".

    =====
    Node: The testcases will be generated such that the answer is unique.
    =====

    ================================================
    FUNCTION: string minWindow(string s, string t);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "ADOBECODEBANC", t = "ABC"
    Output: "BANC"

    --- Example 2 ---
    Input:  s = "a", t = "a"
    Output: "a"

    --- Example 3 ---
    Input:  s = "a", t = "aa"
    Output: ""

    *** Constraints ***
    m == s.length
    n == t.length
    1 <= m, n <= 10^5
    s and t consist of uppercase and lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Idea is pretty intuitive, it's a basic Sliding Window approach.

    Important things:
        1. If certain letter in string s doesn't appear in string t, we don't
           increment its value in our Hash Map s_map.

        2. Because of the first point - If certain letter in string s doesn't
           appear in string t, we won't decrease value in our Hash Map s_map
           before we move our left pointer. It's already zero guaranteed.

        3. Function same_hash_maps is operating in O(1) since 128 is a constant

*/

/* Time  Beats:  8.27% */
/* Space Beats: 39.16% */

/*
    Time  Complexity: O(m + n)

    Technically, this is indeed O(m + n) because "same_hash_map" works in O(1)
    since it's always 128 characters and that's a constant.

    However, the "wall-clock time" is going to be a lot more than necessary.
*/
/*
    Space Complexity: O(1)

    Same thing - We'll always keep only two vectors of exactly 128 characters
    and since 128 is a constant, the overall Space Complexity is O(1)
*/
class Solution_Basic_Sliding_Window {
public:
    std::string minWindow(std::string s, std::string t)
    {
        int m = s.length();
        int n = t.length();

        if (m < n)
            return "";

        std::vector<int> s_map(128, 0);
        std::vector<int> t_map(128, 0);

        for (const char& c : t)
            t_map[c]++;

        int left  = 0;
        int right = 0;

        int start = -1;;
        int min_window_size = INT_MAX;

        while (right < s.length())
        {
            if (t_map[s[right]] > 0) // Only if it exists in 't'
                s_map[s[right]]++;

            while (same_hash_maps(s_map, t_map))
            {
                // Update minimum String
                if (right - left + 1 < min_window_size)
                {
                    min_window_size = right - left + 1;
                    start = left;
                }

                // 'Cause have been incrementing only letters present in t
                if (s_map[s[left]] > 0)
                    s_map[s[left]]--;

                left++;
            }

            right++;
        }

        return start == -1 ? "" : s.substr(start, min_window_size);
    }

private:
    bool same_hash_maps(std::vector<int>& s_map, std::vector<int>& t_map)
    {
        for (int i = 0; i < 128; i++)
        {
            if (s_map[i] < t_map[i])
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can use basic "Sliding Window" approach to solve this problem.

    In any sliding window based problem we have two pointers. One "right"
    pointer,  whose job is to expand the current window, and we have the "left"
    pointer whose job is to contract a given window. At any point in time only
    one of these pointers move and the other one remains fixed.

    We keep expanding the window by moving the right pointer. When the window
    has all the desired characters(remaining == 0), we contract(if possible)
    and save the smallest window up to this point.

    The answer is the smallest desirable window.

    Example:
    s = "ABAACBAB"
    t = "ABC"

    Output is "ACB".


    Algorithm:
        1. We start two pointers, "left" and "right" initially pointing to the
           first element of the string 's'.

        2. We use the "right" pointer to expand the window until we get a
           desirable window i.e. a window that contains all of the characters
           of 't'.

        3. Once we have a window with all the characters, we can move the left
           pointer ahead one by one. If the window is still a desirable one we
           keep on updating the minimum window size.

        4. If the window is not the desired one anymore, we repeat from step 2
           onward.


    1)
        A B A A C B A B
        0 1 2 3 4 5 6 7
        l
        r


    2)
        A B A A C B A B
        0 1 2 3 4 5 6 7
        l r


    3)
        A B A A C B A B
        0 1 2 3 4 5 6 7
        l   r


    4)
        A B A A C B A B
        0 1 2 3 4 5 6 7
        l     r


    5)
        A B A A C B A B   // min_length = 5
        0 1 2 3 4 5 6 7
        l       r


    6)
        A B A A C B A B   // min_length = 4
        0 1 2 3 4 5 6 7
            l     r


    7)
        A B A A C B A B   // min_length = 3
        0 1 2 3 4 5 6 7
                l   r


    8)
        A B A A C B A B
        0 1 2 3 4 5 6 7
                  l   r


    9)
        A B A A C B A B
        0 1 2 3 4 5 6 7
                  l     r
                        ^
                        |
                        |_______ Out Of Bounds

*/


/* Time  Beats: 97.70% */
/* Space Beats: 45.37% */

/* Time  Complexity: O(s + t)
   In the worst case we might end up visiting every element of string 's'
   twice, once by left pointer and once by right pointer.
*/
/*
    Space Complexity: O(1)
*/
class Solution{
public:
    std::string minWindow(std::string s, std::string t)
    {
        std::vector<int> occurrences(128, 0);

        for (const char& c : t)
            occurrences[c]++;

        int remaining = t.length();

        int left  = 0;
        int right = 0;
        int min_start  = 0;
        int min_length = INT_MAX;

        while (right < s.length())
        {
            if (--occurrences[s[right++]] >= 0)
                remaining--;

            while (remaining == 0)
            {
                if (right - left < min_length)
                {
                    min_start  = left;
                    min_length = right - left;
                }

                if (++occurrences[s[left++]] > 0)
                    remaining++;
            }
        }

        return min_length < INT_MAX ? s.substr(min_start, min_length) : "";
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely equivalent to the above Solution, just a bit more readable.

*/


/* Time  Beats: 97.70% */
/* Space Beats: 45.37% */

/* Time  Complexity: O(s + t)
   In the worst case we might end up visiting every element of string 's'
   twice, once by left pointer and once by right pointer.
*/
/*
    Space Complexity: O(1)
*/
class Solution_Readable {
public:
    std::string minWindow(std::string s, std::string t)
    {
        std::vector<int> occurrences(128, 0);

        for (const char& c : t)
            occurrences[c]++;

        int remaining = t.length();

        int left  = 0;
        int right = 0;
        int min_start  = 0;
        int min_length = INT_MAX;

        while (right < s.length())
        {
            if (occurrences[s[right]] > 0)
                remaining--;

            occurrences[s[right]]--;

            while (remaining == 0)
            {
                if (right - left + 1 < min_length)
                {
                    min_start  = left;
                    min_length = right - left + 1;
                }

                if (occurrences[s[left]] >= 0)
                    remaining++;

                occurrences[s[left]]++;
                left++;
            }

            right++;
        }

        return min_length < INT_MAX ? s.substr(min_start, min_length) : "";
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 13.51% */
/* Space Beats: 9.47% */

/* Time  Complexity: O(m * 58 + n) --> O(m + n) */
/* Space Complexity: O(58) ----------> O(1)     */
class Solution_M58_N {
public:
    string minWindow(string s, string t)
    {
        if (s.length() < t.length())
            return "";

        std::vector<int> letters_s(58, 0);
        std::vector<int> letters_t(58, 0);

        for (auto letter : t)
            letters_t[letter - 'A']++;

        int min_window = INT_MAX;
        int min_window_start_idx = -1;

        int left  = 0;
        int right = 0;
        while (right < s.length())
        {
            if (letters_t[s[right] - 'A'] > 0)
                letters_s[s[right] - 'A']++;

            while (same(letters_s, letters_t))
            {
                int curr_window_len = right - left + 1;

                if (curr_window_len < min_window)
                {
                    min_window_start_idx = left;
                    min_window = curr_window_len;
                }

                if (letters_s[s[left] - 'A'] > 0)
                    letters_s[s[left] - 'A']--;

                left++;
            }

            right++;
        }

        return min_window == INT_MAX ? "" : s.substr(min_window_start_idx, min_window);
    }

private:
    bool same(std::vector<int>& letters_s, std::vector<int>& letters_t)
    {
        for (int i = 0; i < 58; i++)
        {
            if (letters_s[i] - letters_t[i] < 0)
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 24.14% */
/* Space Beats:  5.50% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution_Neat {
public:
    std::string minWindow(std::string s, std::string t)
    {
        if (t == "")
            return "";

        std::unordered_map<char, int> t_map;
        std::unordered_map<char, int> window_map;

        for (char chr : t)
            t_map[chr] = 1 + (t_map.count(chr) ? t_map[chr] : 0);

        int have = 0;
        int need = t_map.size();

        int start = -1;
        int min_window_len = INT_MAX;

        int left  = 0;
        int right = 0;
        while (right < s.length())
        {
            char chr = s[right];
            window_map[chr] = 1 + (window_map.count(chr) ? window_map[chr] : 0);

            if (t_map.count(chr) && window_map[chr] == t_map[chr])
                have++;

            while (have == need)
            {
                // current_window_length = right - left + 1
                if (right - left + 1 < min_window_len)
                {
                    start = left;
                    min_window_len = right - left + 1;
                }

                // Pop from the left of our window
                window_map[s[left]]--;
                if (t_map.count(s[left]) && window_map[s[left]] < t_map[s[left]])
                    have--;

                left++;
            }

            right++;
        }

        return min_window_len != INT_MAX ? s.substr(start, min_window_len) : "";
    }
};




int
main()
{
    Solution sol;

    /* Example 1 */
    std::string s = "ADOBECODEBANC";
    std::string t = "ABC";

    /* Example 2 */
    // std::string s = "a";
    // std::string t = "a";

    /* Example 3 */
    // std::string s = "a";
    // std::string t = "aa";

    /* Example 4 */
    // std::string s = "ABAACBAB";
    // std::string t = "ABC";

    /* Example 5 */
    // std::string s = "CBAEBBSSBECCA";
    // std::string t = "SEC";

    std::cout << "\n\t================================";
    std::cout << "\n\t=== MINIMUM WINDOW SUBSTRING ===";
    std::cout << "\n\t================================\n";


    /* Write Input */
    std::cout << "\n\tString s: \"" << s << "\"";
    std::cout << "\n\tString t: \"" << t << "\"";


    /* Solution */
    std::string str = sol.minWindow(s, t);


    /* Write Output */
    std::cout << "\n\n\tMinimum Substring: \"" << str << "\"\n\n";


    return 0;
}
