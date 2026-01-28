/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    71) Simplify Path
    ===========================

    ============
    Description:
    ============

    Given a string path, which is an absolute path (starting with a slash '/')
    to a file or directory in a Unix-style file system, convert it to the
    simplified canonical path.

    In a Unix-style file system, a period '.' refers to the current directory,
    a double period '..' refers to the directory up a level, and any multiple
    consecutive slashes (i.e. '//') are treated as a single slash '/'. For this
    problem, any other format of periods such as '...' are treated as
    file/directory names.

    The canonical path should have the following format:

        The path starts with a single slash '/'.  Any two directories are
        separated by a single slash '/'.  The path does not end with a trailing
        '/'.  The path only contains the directories on the path from the root
        directory to the target file or directory (i.e., no period '.' or
        double period '..')

    Return the simplified canonical path.

    ===========================================
    FUNCTION: string simplifyPath(string path);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: path = "/home/"
    Output: "/home"
    Explanation: Note that there is no trailing slash after the last directory
                 name.


    --- Example 2 ---
    Input: path = "/../"
    Output: "/"
    Explanation: Going one level up from the root directory is a no-op, as the
                 root level is the highest level you can go.


    --- Example 3 ---
    Input: path = "/home//foo/"
    Output: "/home/foo"
    Explanation: In the canonical path, multiple consecutive slashes are
                 replaced by a single one.



    *** Constraints ***
    1 <= path.length <= 3000
    path consists of English letters, digits, period '.', slash '/' or '_'.
    path is a valid absolute Unix path.

*/

#include <stack>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Good examples:
        1. /home//foo/..////hehe/.

        2. /../abc//./def

*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.40% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string simplifyPath(string path)
    {
        const int N = path.size();
        string result;
        result.reserve(N); // At most N, this will prevent reallocations

        stack<string> stack;

        for (int i = 0; i < N; i++)
        {
            if (path[i] == '/')
                continue;

            string tmp;
            while (i < N && path[i] != '/')
            {
                tmp += path[i];
                i++;
            }

            if (tmp == ".")
                continue;

            if (tmp == "..")
            {
                if ( ! stack.empty())
                    stack.pop();
            }
            else
                stack.push(tmp);
        }

        // Adding all the stack elements to result with a '/' inbetween
        while( ! stack.empty())
        {
            result = "/" + stack.top() + result;
            stack.pop();
        }

        return result.empty() ? "/" : result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses "istringstream" implementation which is VERY beneficial when
    solving String problems in C++.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.86% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    string simplifyPath(string path)
    {
        const int N = path.size();

        string result;
        result.reserve(N); // At most N, this will prevent reallocations

        istringstream iss(path);
        string file;

        vector<string> files;
        while (getline(iss, file, '/'))
        {
            if (file.empty() || file == ".")
                continue;

            if (file == "..")
            {
                if ( ! files.empty())
                    files.pop_back();
            }
            else
                files.push_back(file);
        }

        for (const string& file : files)
            result += "/" + file;

        return result.empty() ? "/" : result;
    }
};
