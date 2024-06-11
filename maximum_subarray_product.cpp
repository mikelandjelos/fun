#include <vector>
#include <iostream>
#include <cmath>

class Solution
{
public:
    static int maxProduct(std::vector<int> &nums)
    {
        int max_product_overall = *nums.begin();
        int max_product_so_far = max_product_overall;
        int min_product_so_far = max_product_overall;

        for (auto current = ++nums.begin(); current != nums.end(); ++current)
        {
            int temp = *current * max_product_so_far;
            max_product_so_far =
                std::max(*current, std::max(temp, *current * min_product_so_far));
            min_product_so_far =
                std::min(*current, std::min(temp, *current * min_product_so_far));

            if (max_product_so_far > max_product_overall)
                max_product_overall = max_product_so_far;
        }

        return max_product_overall;
    }
};

int main(int argc, char **argv)
{
    std::vector<int> testcase = {-4, -3, -2};
    std::cout << Solution::maxProduct(testcase) << std::endl;
    return 0;
}