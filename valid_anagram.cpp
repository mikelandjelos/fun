/*
 *
 * Is Anagram:
 *   Given two strings s and t, return true if the two strings are anagrams of each other, otherwise return false.
 *   An anagram is a string that contains the exact same characters as another string, but the order of the characters can be different.
 *
 *   Example 1:
 *      Input: s = "racecar", t = "carrace"
 *      Output: true
 *
 *   Example 2:
 *      Input: s = "jar", t = "jam"
 *      Output: false
 *
 * Constraints:
 *      s and t consist of lowercase English letters.
 *
 */

#include <iostream>
#include <string>
#include <unordered_map>

class Solution
{
public:
    // O(3n) == O(n)
    bool isAnagram(std::string s, std::string t) // O(n)
    {
        if (s.size() != t.size())
            return false;

        std::unordered_map<char, unsigned int> firstLetterCounter;
        std::unordered_map<char, unsigned int> secondLetterCounter;

        // O(n)
        for (const auto &letter : s)
        {
            auto count = firstLetterCounter.find(letter); // O(1)

            if (count == firstLetterCounter.end())     // If nothing found
                firstLetterCounter.emplace(letter, 1); // O(1)
            else
                (*count).second++;
        }

        // O(n)
        for (const auto &letter : t)
        {
            // Minor optimization - if current letter can't be found in first string - surely false
            if (firstLetterCounter.find(letter) == firstLetterCounter.end())
                return false;

            auto count = secondLetterCounter.find(letter); // O(1)

            if (count == secondLetterCounter.end())     // If nothing found
                secondLetterCounter.emplace(letter, 1); // O(1)
            else
                (*count).second++;
        }

        // O(n)
        for (const auto &[firstLetter, firstLetterCount] : firstLetterCounter)
        {
            const auto &[secondLetter, secondLetterCount] = *secondLetterCounter.find(firstLetter);

            if (firstLetterCount != secondLetterCount)
                return false;
        }

        return true;
    }
};

int main(int argc, char **argv)
{
    Solution solution;
    std::string testcase11 = "racecar", testcase12 = "carrace";
    std::string testcase21 = "jar", testcase22 = "jam";
    std::string testcase31 = "bbcc", testcase32 = "ccbc";

    std::cout << solution.isAnagram(testcase11, testcase12) << std::endl;
    std::cout << solution.isAnagram(testcase21, testcase22) << std::endl;
    std::cout << solution.isAnagram(testcase31, testcase32) << std::endl;

    return 0;
}