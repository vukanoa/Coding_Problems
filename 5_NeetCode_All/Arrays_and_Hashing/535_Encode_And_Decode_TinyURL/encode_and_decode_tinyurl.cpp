/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    535) Encode and Decode TinyURL
    ==============================

    ============
    Description:
    ============

    Note: This is a companion problem to the System Design problem: Design
    TinyURL.

    TinyURL is a URL shortening service where you enter a URL such as
    https://leetcode.com/problems/design-tinyurl and it returns a short URL
    such as http://tinyurl.com/4e9iAk. Design a class to encode a URL and
    decode a tiny URL.

    There is no restriction on how your encode/decode algorithm should work.
    You just need to ensure that a URL can be encoded to a tiny URL and the
    tiny URL can be decoded to the original URL.

    Implement the Solution class:

    Solution() Initializes the object of the system.  String encode(String
    longUrl) Returns a tiny URL for the given longUrl.  String decode(String
    shortUrl) Returns the original long URL for the given shortUrl. It is
    guaranteed that the given shortUrl was encoded by the same object.

    ===============================
    FUNCTION:
    string encode(string longUrl)
    {
    }

    string decode(string shortUrl)
    {
    }
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: url = "https://leetcode.com/problems/design-tinyurl"
    Output: "https://leetcode.com/problems/design-tinyurl"

    Explanation:
    Solution obj = new Solution();
    string tiny = obj.encode(url); // returns the encoded tiny url.
    string ans = obj.decode(tiny); // returns the original url after decoding
    it.


    *** Constraints ***
    1 <= url.length <= 10^4
    url is guranteed to be a valid URL.

*/

#include <unordered_map>
#include <sstream>
using namespace std;

/* Time  Beats:  100% */
/* Space Beats: 5.15% */
class Solution_1 {
public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl)
    {
        std::ostringstream base;
        base << "http://tinyurl.com/";

        if (umap_long.find(longUrl) == umap_long.end()) // Doesn't exist
        {
            base << std::to_string(count);

            umap_long.insert({longUrl, base.str()});
            umap_short.insert({base.str(), longUrl});

            count++;
        }

        return umap_long[longUrl];
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl)
    {
        return umap_short[shortUrl];
    }

private:
    std::unordered_map<std::string, std::string> umap_long;
    std::unordered_map<std::string, std::string> umap_short;
    int count = 0;
};




/* Time  Beats:   100% */
/* Space Beats: 14.68% */
class Solution_2 {
public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl)
    {
        std::string shortUrl = "http://tinyurl.com/" + std::to_string(count++);
        umap[shortUrl] = longUrl;

        return shortUrl;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl)
    {
        return umap[shortUrl];
    }

private:
    std::unordered_map<std::string, std::string> umap;
    int count = 0;
};


// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
