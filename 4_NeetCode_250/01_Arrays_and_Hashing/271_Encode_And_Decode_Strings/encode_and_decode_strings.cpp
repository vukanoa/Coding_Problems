/*
    ***************
    *** PREMIUM ***
    ***************
*/

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    659) Encode & Decode Strings
    ============================

    ============
    Description:
    ============

    Design an algorithm to encode a list of strings to a string. The encoded
    string is then sent over the network and is decoded back to the original
    list of strings.

    Please implement "encode" and "decode".

    ===============================
    CLASS:
    class Codec {
    public:
        string encode(vector<string>& strs)
        {

        }

        vector<string> decode(string s)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  ["lint", "code", "love", "you"]
    Output: ["lint", "code", "love", "you"]
    Explanation:
    One possible encode method is: "lint:;code:;love:;you"

    *** Constraints ***
    Any ASCII character can be found in string!  // (Difficulty lies there)

*/

#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The tricky part is going to be that the basic assumption is that in our
    input we could have any possible ASCII character in the input. Not just
    limited to lowercase english letters!

    The difficult thing is going to be - How do we create some kind of
    delimiter between each word? How do we know when one word ends and the next
    one begins?

    Let's consider an example. Suppose we're given this example:

        Input: ["leet", "code"]

    And we want to convert it to a single string. The naive way would be
    something like this:
        "leetcode"

    Now the problem is - how do we decode this back into the original vector
    of strings, i.e. ["leet", "code"]?

    There is no way for us to determine where one string ends and where the
    other one begins.

    So, we can clearly see that we need some kind of delimiter or something to
    separate words.

    What if we used a '#' sign to separate words in our encoded string?
    We'd have:
        "leet#code"

    In this case it works out. We processing character by character in the
    input and once we get to the '#' sign, we'll say that that the current
    words ends and we'll store it in decode_str vector of strings.

    So at the end our decode_str would look like:
        ["leet", "code"]

    That works out in this case, but the assumption we're using here is that
    our delimiter, a '#' sign, is never going to actually show up in any words.

    What happens if we have this Input:
        ["leet", "co#de"]

    In that case, if we do the same thing for encoding, we'd get an encoded_str
    that looks like this:
        "leet#co#de"

    Now if we try to decode this, we'd get:
        ["leet", "co", "de"]

    which isn't correct.


    So wouldn't it be nice if in the encoded string we somehow already knew
    how many characters already go in the first word, how many characters go
    in the second word, etc.

    If we had an additional array or vector, which would have corresponding
    lengths of the words, respectively:
        [4, 5]

    But where are we going to store these? In the description of a problem,
    they don't want us to store any kind of "state variable". This "encode" and
    "decode" must be stateless.

    So, we cannot store it in a separate array or vector.
    Is it possible to store it in the encoded string itself?

    Using our 2nd Example:
        ["leet", "co#de"]

    Intuitively something like this comes to mind:
        "4leet5co#de"

    However this won't work if we had an Input with digits within words:
        ["2leet", "12co#de"]

    Since our encoded string would look like:
        "52leet712co#de"

    We wouldn't be able to tell how many digits in the front are only the
    indicators of the length of the word, and how many digits are the part of
    the word itself.

    Therefore, we need another delimiter.

    The encoded string, before each of the words, is going to start with a
    digit or multiple digits(if the word has 10 or more characters in it)
    followed by a delimiter of our choice. Let's say that, again, it's the '#'
    sign.

    Input: ["2leet", "14co#de"]

    Would be encoded like this:
        "4#leet7#14co#de"

    It may seem suspicious. It may seem as if we're going to have a similar
    problem because we're using a '#' sign while that sign itself can be a part
    of the word.

    However, if you look closely, you'll see that it's impossible to confuse
    the delimiter from the character of the word itself.

    How?
    Well, we'll always start by collecting the digits up until the point when
    we stumble upon a first '#' sign. At that point we'll want to take the
    next <number> character EXCLUDING the '#' we stumbled upon. We're just
    going to ignore that '#' sign and take <number> characters and put it in
    our decode_str vector.

    We'll repeat the process for all the remaining characters.

*/

/* Time  Complexity: O(M) */ // Where 'M' is the TOTAL number of characters
/* Space Complexity: O(M) */
class Codec {
public:
    string encode(vector<string>& strs)
    {
        ostringstream out;

        for (int i = 0; i < strs.size(); i++)
            out << strs[i].size() << '#' << strs[i];

        return out.str();
    }

    // 4#lint4#code4#love3#you

    vector<string> decode(string s)
    {
        vector<string> strs;

        int i = 0;
        while (i < s.length())
        {
            ostringstream out;

            while (s[i] != '#')
                out << s[i++];
            i++; // Skip the '#' itself

            int characters = stoi(out.str());
            strs.push_back(s.substr(i, characters));

            i += characters;
        }

        return strs;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it. This one is slightly faster because we've
    eliminated the "ostringstream" overhead.

    std::string is optimized enough for this problem, so it is probably better
    to use it, rather then using ostringstream.

    Especially because of the concept of "SSO"(small stirng operations) in C++.

*/

/* Time  Complexity: O(M) */ // Where 'M' is the TOTAL number of characters
/* Space Complexity: O(M) */
class Codec_Faster {
public:
    string encode(vector<string>& strs)
    {
        // O(M) (entire block)
        string encoded_str;
        for (const string& str : strs)
            encoded_str += to_string(str.size()) + "#" + str; // Amortized O(1)

        return encoded_str;
    }

    vector<string> decode(string s)
    {
        const int LEN = s.size();
        vector<string> original_strs;

        // O(M) (entire block)
        int i = 0;
        while (i < LEN)
        {
            string str_content_size;
            while (s[i] != '#')
                str_content_size += s[i++]; // Amortized O(1)
            i++; // Skip the '#' itself

            int content_size    = stoi(str_content_size);
            string original_str = s.substr(i, content_size);

            original_strs.push_back(original_str); // Amortized O(1)

            // Increment
            i += content_size;
        }

        return original_strs;
    }
};
