#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cstring> // memset

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1233) Remove Sub-Folders from the Filesystem
    ============================================

    ============
    Description:
    ============


    Given a list of folders folder, return the folders after removing all
    sub-folders in those folders. You may return the answer in any order.

    If a folder[i] is located within another folder[j], it is called a
    sub-folder of it. A sub-folder of folder[j] must start with folder[j],
    followed by a "/". For example, "/a/b" is a sub-folder of "/a", but "/b" is
    not a sub-folder of "/a/b/c".

    The format of a path is one or more concatenated strings of the form: '/'
    followed by one or more lowercase English letters.

    For example, "/leetcode" and "/leetcode/problems" are valid paths while an
    empty string and "/" are not.

    ==================================================================
    FUNCTION: vector<string> removeSubfolders(vector<string>& folder);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
    Output: ["/a","/c/d","/c/f"]
    Explanation: Folders "/a/b" is a subfolder of "/a" and "/c/d/e" is inside
                 of folder "/c/d" in our filesystem.


    --- Example 2 ---
    Input: folder = ["/a","/a/b/c","/a/b/d"]
    Output: ["/a"]
    Explanation: Folders "/a/b/c" and "/a/b/d" will be removed because they are
                 subfolders of "/a".


    --- Example 3 ---
    Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
    Output: ["/a/b/c","/a/b/ca","/a/b/d"]


    *** Constraints ***
    1 <= folder.length <= 4 * 10^4
    2 <= folder[i].length <= 100
    folder[i] contains only lowercase letters and '/'.
    folder[i] always starts with the character '/'.
    Each folder name is unique.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Since we're asked to remove subfolder and since we're told that:
        "/a/b" is a sub-folder of "/a"

    Then it's not very hard to come up with an idea of Sorting, is it?

    If we are supposed to remove "/a/b" because it's a sub-folder of "/a", then
    it makes sense to check, and put in the Hashset, shortest ones first since
    they are certainly NOT sub-folder of any other path in vector "folder".

    Let's take the very first Example and add another string to it to make a
    point:

        Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f", "/a/b/c/"]
        Output: ["/a","/c/d","/c/f"]

    Both "/a/b" and "/a/b/c" are sub-folders or "/a/" and, therefore, should be
    removed.

    So, all we need to do is - Sort the vector "folder" by the length of the
    string in ascending order(shorter strings first) and then iterate through
    the vector one-by-one:

        If at any point we find that some prefix of this string already exists
        in the HashSet, that indicates that this current path is a sub-folder
        of that existing one in HashSet and therefore we should remove it.

        (However, we won't be removing since that would be a O(n) operations
        for a vector and we could, potentially, need to remove n-1 elements
        which would result in an O(n^2) Time Complexity. To avoid that, we'll
        simply put valid_paths in another vector "result" which will be
        returned at the very end, i.e. we'll just ignore the sub-folder paths)


        Else, put that valid_path in "result" vector.

    That's the entire Solution. It's that simple.

*/

using namespace std;

/* Time  Beats: 92.31% */
/* Space Beats: 55.22% */

/* Time  Complexity: O(n * logn * average_length(string_path)) */
/* Space Complexity: O(n * average_length(string_path))        */
class Solution_Verbose {
public:
    vector<string> removeSubfolders(vector<string>& folder)
    {
        // Sort by length in ascending order (shorter strings first)
        std::sort(folder.begin(), folder.end(), [](const std::string& a, const std::string& b) {
            return a.size() < b.size();
        });

        unordered_set<string> uset;

        for (const string& curr_path : folder)
        {
            std::ostringstream upper_part_of_path;
            upper_part_of_path << "/";
            bool need_removal = false;

            for (int i = 1; i < curr_path.length(); i++)
            {
                while (i < curr_path.length() && curr_path[i] != '/')
                    upper_part_of_path << curr_path[i++];

                string tmp_upper = upper_part_of_path.str();
                if (uset.find(tmp_upper) != uset.end()) // It exists in the HashSet
                {
                    need_removal = true;
                    break;
                }
                else
                    upper_part_of_path << '/'; // It won't matter it at the very end we add '/'
            }

            if ( ! need_removal)
            {
                string valid_path = upper_part_of_path.str();
                valid_path.pop_back(); // Pop back the redundant '/' from the very end

                uset.insert(valid_path);
            }
        }

        vector<string> result;
        for (const string& valid_path : uset)
            result.push_back(valid_path);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's equivalent to the above Solution, though it is written in a much more
    elegant and concise way, however if you haven't been able to solve it
    yourself, I highly suggest to read the Solution_Verbose since it's much
    more explicit.

*/

/* Time  Beats: 92.86% */
/* Space Beats: 67.31% */

/* Time  Complexity: O(n * logn * average_length(string_path)) */
/* Space Complexity: O(n * average_length(string_path))        */
class Solution_Elegant {
public:
    vector<string> removeSubfolders(vector<string>& folder)
    {
        const int n = folder.size();

        // Default sort will do the trick
        sort(folder.begin(), folder.end());

        vector<string> result = { folder[0] };

        string prev = folder[0];
        for (int i = 1; i < n; i++)
        {
            string curr_path = folder[i];

            if (curr_path.find(prev + '/') != 0)
            {
                result.push_back(curr_path);
                prev = curr_path;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 67.03% */
/* Space Beats: 13.46% */

/* Time  Complexity: O(n * logn * average_length(string_path)) */
/* Space Complexity: O(n * average_length(string_path))        */
struct Trie {
    Trie* links[27];
    bool  is_end = 0;// 26 letters + 1 for '/'


    Trie() {
        memset(links, 0, sizeof(links));
    }

    // Insert folder into trie returning position for last '/'
    int insert(string_view path)
    {
        Trie* node = this;
        int size = path.size();
        int position = 0;

        for (int i = 0; i < size; i++)
        {
            char c = path[i];
            int idx = (c == '/') ? 26 : c-'a'; // Use 26 for '/'

            if (idx == 26)
                position = i;

            if ( ! node->links[idx])
                node->links[idx] = new Trie();

            node = node->links[idx];
        }
        node->is_end = 1;

        return position;
    }

    // Check if this folder is a subfolder of an already inserted folder
    bool isSubfolder(const string& path, int position)
    {
        if (position == 0)
            return 0; // Each folder name is unique.

        Trie* node = this;
        for (int i = 0; i < position; i++)
        {
            char c = path[i];
            int idx = (c=='/')?26:c - 'a';
            node = node->links[idx];

            // It is a subfolder
            if (path[i+1] == '/' && node->is_end)
                return 1;
        }

        return 0;
    }
};

class Solution {
public:
    Trie trie;
    vector<string> removeSubfolders(vector<string>& folder)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        // First pass: Insert all folder paths into the trie
        int n = folder.size();
        int i = 0;
        vector<int> positions(n);
        for (string_view path : folder)
            positions[i++] = trie.insert(path);

        vector<string> result;

        // Second pass: Check each folder to see if it's a subfolder
        for (int i = 0; i < n; i++)
        {
            string path = folder[i];
            if ( ! trie.isSubfolder(path, positions[i]))
                result.push_back(path);
        }

        return result;
    }
};
