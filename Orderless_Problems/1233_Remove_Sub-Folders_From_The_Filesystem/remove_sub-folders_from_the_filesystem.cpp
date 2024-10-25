#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

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

/* Time  Beats: 92.31% */
/* Space Beats: 55.22% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
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
