#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ===========================
    125) Valid Palindrome
    ===========================

    ============
    Description:
    ============

    A phrase is a palindrome if, after converting all uppercase letters into
    lowercase letters and removing all non-alphanumeric characters, it reads
    the same forward and backward. Alphanumeric characters include letters and
    numbers.

    Given a string s, return true if it is a palindrome, or false otherwise.

    =================================
    FUNCTION: isPalindrome(string s);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "A man, a plan, a canal: Panama"
    Output: true
    Explanation: "amanaplanacanalpanama" is a palindrome.


    --- Example 2 ---
    Input: s = "race a car"
    Output: false
    Explanation: "raceacar" is not a palindrome.


    --- Example 3 ---
    Input: s = " "
    Output: true
    Explanation: s is an empty string "" after removing non-alphanumeric
    characters. Since an empty string reads the same forward and backward, it
    is a palindrome.

    *** Constraints ***
    1 <= s.length <= 2 * 105
    s consists only of printable ASCII characters.

*/


/*
    ------------
    --- IDEA ---
    ------------

    Make a new vector and fill it only with alphanumeric characters from the
    string 's'.

    Use Two pointers at the end toe check if the vector "vec" is a palindrome.

*/

/* Time  Beats: 33.48% */
/* Space Beats: 46.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_1{
public:
    bool isPalindrome(std::string& s)
    {
        std::vector<char> vec;

        for (int i = 0; i < s.length(); i++)
        {
            if (isupper(s[i]))       // Uppercase letter
            {
                vec.push_back(s[i] + 32); // Convert to lowercase
            }
            else if (islower(s[i]) || isdigit(s[i])) // Lowercase letter
            {
                vec.push_back(s[i]);
            }
            else
            {
                continue;
            }
        }

        int left  = 0;
        int right = vec.size() - 1;

        if (vec.size() % 2 == 0)
        {
            while (left < right)
            {
                if (vec[left++] != vec[right--])
                    return false;
            }
        }
        else
        {
            int mid = (left + right) / 2;

            while (left != mid) // Or right
            {
                if (vec[left++] != vec[right--])
                    return false;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Make a new vector and fill it only with alphanumeric characters from the
    string 's'.

    Reverse that string and compare the original copy and the reverse copy.

*/

/* Time  Beats: 14.22% */
/* Space Beats:  7.92% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2{
public:
    bool isPalindrome(std::string& s)
    {
        std::vector<char> str;
        std::vector<char> rev_str;

        for (char& c : s)
        {
            if (isalnum(c))
                str.push_back(isdigit(c) ? c : islower(c) ? c : c+32);
        }

        rev_str = str;
        std::reverse(str.begin(), str.end());

        return str == rev_str;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses completely different approach than other Solutions, so I
    wanted to include it in this file.

    Idea is that non-alphanum characters are jumped over and once we are on a
    alphanum characters, then there are 8 options.

        1. s[left] = Lowercase Letter; s[right] = Lowercase Letter;
        2. s[left] = Uppercase Letter; s[right] = Uppercase Letter;

        3. s[left] = Lowercase Letter; s[right] = Uppercase Letter;
        4. s[left] = Uppercase Letter; s[right] = Lowercase Letter;

        5. s[left] = Digit;            s[right] = Lowercase Letter;
        6. s[left] = Lowercase Letter; s[right] = Digit;

        7. s[left] = Digit;            s[right] = Uppercase Letter;
        8. s[left] = Uppercase Letter; s[right] = Digit;


    As for:
        1, 2:
            Absolute difference is 0 if they are the same and non-0 is they are
            different.  Absolute difference is 0 if they are the same and non-0
            is they are different.

        3, 4:
            Absolute difference is 32 if they represent the same letter and
            it's not 32 if they are different.

        5, 6, 7, 8:
            Aboslute difference can be 32 and they are still NOT the same.
            Example: '0' and 'P'. abs(48 - 80) = 32 In that case if they are
            equal to 32, we have to check if they are of the different types
            (Digit | Alpha). If they are, return false.


        So, that's why:
            if (diff != 32 && diff != 0)
                return false;

        We immediately return false;
        However, if they ARE 32, then it's only okay if they are both letters,
        if they are of different types, meaning one is Digit and the other is
        a Letter, then we shall, also, return false,

*/

/* Time  Beats:  7.52% */
/* Space Beats: 25.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_3 {
public:
    bool isPalindrome(std::string s)
    {
        int left  = 0;
        int right = s.length() - 1;

        while (left < right)
        {
            while (left < right && left < s.length() && !std::isalnum(s[left]) )
                left++;

            while (left < right && right >= 0 && !std::isalnum(s[right]) )
                right--;

            if (left == right)
                return true;

            int diff = std::abs(s[left] - s[right]);

            if (diff != 32 && diff != 0)
                return false;
            else if (diff == 32 && different_types(s[left], s[right]))
                return false;

            left++;
            right--;
        }

        return true;
    }

private:
    // s[left]='0' && s[right]='P', difference is 32, but they are not the same
    bool different_types(char& chr_left, char& chr_right)
    {
        return std::isdigit(chr_left)  && std::isalpha(chr_right) ||
               std::isdigit(chr_right) && std::isalpha(chr_left);
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    We don't have to make a new String. Just use Two Pointers within string s
    and "jump over" non-alphanumberic characters.

*/

/* Time  Beats:   100% */
/* Space Beats: 63.24% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient{
public:
    bool isPalindrome(std::string s)
    {
        int left  = 0;
        int right = s.length() - 1;

        while (left < right)
        {
            while (left < right && !alpha_num(s[left]))
                left++;

            while (right > left && !alpha_num(s[right]))
                right--;

            if (std::tolower((s[left])) != std::tolower((s[right])))
                return false;

            left++;
            right--;
        }

        return true;
    }

private:
    bool alpha_num(char& c)
    {
        return (c >= 65 && c <= 90)  ||
               (c >= 97 && c <= 122) ||
               (c >= 48 && c <= 57);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is the most Efficient as the one above, but instead of using a
    custom function "alpha_num", we are using std::isalnum().

    It's important to know about this function, but it's also important to know
    how to write it yourself. That's why I keep both of these Solution here.

*/

/* Time  Beats: 80.25% */
/* Space Beats: 83.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient_STD {
public:
    bool isPalindrome(std::string s)
    {
        int i = 0;
        int j = s.length() - 1;

        while (i < j)
        {
            while (i < j && !(std::isalnum(s[i])))
                i++;

            while (i < j && !(std::isalnum(s[j])))
                j--;

            if (std::tolower(s[i]) != std::tolower(s[j]))
                return false;

            i++;
            j--;
        }

        return true;
    }
};


int
main()
{
    Solution_1             sol_1;
    Solution_2             sol_2;
    Solution_3             sol_3;
    Solution_Efficient     sol_eff;
    Solution_Efficient_STD sol_std;


    /* Example 1 */
    std::string s = "A man, a plan, a canal: Panama";

    /* Example 2 */
    // std::string s = "race a car";

    /* Example 3 */
    // std::string s = " ";


    std::cout << "\n\t========================";
    std::cout << "\n\t=== VALID PALINDROME ===";
    std::cout << "\n\t========================\n";


    /* Write Input */
    std::cout << "\n\tString: \"" << s << "\"\n";


    /* Solution */
    // bool result = sol_eff.isPalindrome(s);
    bool result = sol_std.isPalindrome(s);


    /* Write Output */
    if (result)
        std::cout << "\n\tOutput: Palindrome!";
    else
        std::cout << "\n\tOutput: NOT a Palindrome!";
    std::cout << "\n\n";


    return 0;
}
