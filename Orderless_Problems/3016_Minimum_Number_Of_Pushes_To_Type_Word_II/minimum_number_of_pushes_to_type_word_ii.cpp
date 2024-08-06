#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    3016) Minimum Number of Pushes to Type Word II
    ==============================================

    ============
    Description:
    ============

    You are given a string word containing lowercase English letters.

    Telephone keypads have keys mapped with distinct collections of lowercase
    English letters, which can be used to form words by pushing them. For
    example, the key 2 is mapped with ["a","b","c"], we need to push the key
    one time to type "a", two times to type "b", and three times to type "c" .

    It is allowed to remap the keys numbered 2 to 9 to distinct collections of
    letters. The keys can be remapped to any amount of letters, but each letter
    must be mapped to exactly one key. You need to find the minimum number of
    times the keys will be pushed to type the string word.

    Return the minimum number of pushes needed to type word after remapping the
    keys.

    An example mapping of letters to keys on a telephone keypad is given below.
    Note that 1, *, #, and 0 do not map to any letters.


    +-------+-------+-------+
    | 1     | 2 abc | 3 def |
    +-------+-------+-------+
    | 4 ghi | 5 jkl | 6 mno |
    +-------+-------+-------+
    | 7 pqrs| 8 tuv | 9 wxyz|
    +-------+-------+-------+
    |   *   |   0   |   #   |
    +-------+-------+-------+

    =========================================
    FUNCTION: int minimumPushes(string word);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "abcde"
    Output: 5
    Explanation: The remapped keypad given in the image provides the minimum
    cost.
    "a" -> one push on key 2
    "b" -> one push on key 3
    "c" -> one push on key 4
    "d" -> one push on key 5
    "e" -> one push on key 6
    Total cost is 1 + 1 + 1 + 1 + 1 = 5.
    It can be shown that no other mapping can provide a lower cost.


    --- Example 2 ---
    Input: word = "xyzxyzxyzxyz"
    Output: 12
    Explanation: The remapped keypad given in the image provides the minimum
    cost.
    "x" -> one push on key 2
    "y" -> one push on key 3
    "z" -> one push on key 4
    Total cost is 1 * 4 + 1 * 4 + 1 * 4 = 12
    It can be shown that no other mapping can provide a lower cost.
    Note that the key 9 is not mapped to any letter: it is not necessary to map
    letters to every key, but to map all the letters.


    --- Example 3 ---
    Input: word = "aabbccddeeffgghhiiiiii"
    Output: 24
    Explanation: The remapped keypad given in the image provides the minimum
    cost.
    "a" -> one push on key 2
    "b" -> one push on key 3
    "c" -> one push on key 4
    "d" -> one push on key 5
    "e" -> one push on key 6
    "f" -> one push on key 7
    "g" -> one push on key 8
    "h" -> two pushes on key 9
    "i" -> one push on key 9
    Total cost is 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 2 * 2
    + 6 * 1 = 24.
    It can be shown that no other mapping can provide a lower cost.



    *** Constraints ***
    1 <= word.length <= 10^5
    word consists of lowercase English letters.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We don't really care about at which digit(i.e. button) will any letter bi
    assigned to.

    We only care about the relative poisition within that digit(i.e. button).

    The solution is pretty simple: Count the frequence of occurrence of each
    letter in the string word.

    Once we have that, we can create a Heap since that will be in O(1) because
    we only have 26 lowercase English letters.

    Now that we have a Max Heap {frequence, letter}, and since we have exactly
    8 MAPPABLE_BUTTONS(buttons: 2,3,4,5,6,7,8,9) we are going to take first
    8 letters off of the Heap top and we'll assign them 1st place, meaning if
    any of those letters is wanted to be typed, it needs to be typed only once.

    After the first 8 letters, now we are filling 2nd positions within the
    buttons. And so on.

    (Final positions are going to be stored in vector "times_to_type")

    Now all we have to do is go through string word and add the "times_to_type"
    values for each letter we stumble upon.

    That's the entire Solution.

*/

/* Time  Beats: 98.45% */
/* Space Beats: 40.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1), because LETTERS_IN_ALPHABET is a constant */
class Solution {
public:
    int minimumPushes(string word)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int MAPPABLE_BUTTONS    = 8;
        const int LETTERS_IN_ALPHABET = 26;

        vector<int> freq(LETTERS_IN_ALPHABET, 0);

        /* O(n) */
        for (const char& chr : word)
            freq[chr - 'a']++;

        /* O(26) -> O(1), because LETTERS_IN_ALPHABET is a constant */
        priority_queue<pair<int, char>, vector<pair<int, char>>> max_heap;
        for (int i = 0; i < LETTERS_IN_ALPHABET; i++)
        {
            char letter = i + 'a';
            max_heap.push( {freq[i], letter} );
        }

        vector<int> times_to_type(LETTERS_IN_ALPHABET, 0);

        /* O(26 * log26) -> O(1), because LETTERS_IN_ALPHABET is a constant */
        int place = 1;
        while ( ! max_heap.empty())
        {
            char letter = max_heap.top().second;
            max_heap.pop();

            times_to_type[letter - 'a'] = ceil(1.0*place / MAPPABLE_BUTTONS);
            place++;
        }

        /* O(n) */
        int result = 0;
        for (const char& chr : word)
            result += times_to_type[chr - 'a'];

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Pretty much the same as above, but written in another way.

*/

/* Time  Beats: 99.00% */
/* Space Beats: 98.11% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int minimumPushes(string& word)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int MAPPABLE_BUTTONS    = 8;
        const int LETTERS_IN_ALPHABET = 26;

        vector<int> freq(LETTERS_IN_ALPHABET, 0);

        /* O(n) */
        for (const char& chr : word)
            freq[chr - 'a']++;

        /* O(26) -> O(1) */
        sort(freq.begin(), freq.end(), greater<int>());

        int position = 1;
        int result   = 0;

        /* O(26) -> O(1) */
        for(int i = 0; i < LETTERS_IN_ALPHABET && freq[i] > 0; i++)
        {
            if (i >= MAPPABLE_BUTTONS && i % MAPPABLE_BUTTONS == 0)
                position++;

            result += freq[i] * position;
        }

        return result;
    }
};
