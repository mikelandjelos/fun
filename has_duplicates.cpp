/*  Duplicate Integer:
 *  Given an integer array nums, return true if any value appears more than once in the array, otherwise return false.
 *  Example 1:
 *      Input: nums = [1, 2, 3, 3]
 *      Output: true
 *  Example 2:
 *      Input: nums = [1, 2, 3, 4]
 *      Output: false
 */
#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    bool hasDuplicate(std::vector<int> &nums) // O(n)
    {
        std::unordered_set<int> seen;

        for (auto num : nums)
        {
            if (seen.find(num) != seen.end()) // O(1)
                return true;
            seen.insert(num);
        }

        return false;
    }
};

int main(int argc, char **argv)
{
    Solution solution;
    std::vector<int> testcase1 = {1, 2, 3, 3};
    std::vector<int> testcase2 = {1, 2, 3, 4};

    std::cout << solution.hasDuplicate(testcase1) << std::endl;
    std::cout << solution.hasDuplicate(testcase2) << std::endl;

    return 0;
}