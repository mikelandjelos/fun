#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace miscellaneous
{
    template <typename T, typename Stream>
    void printVector(const std::vector<T> &vec, Stream &os)
    {
        os << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            os << vec[i];
            if (i < vec.size() - 1)
            {
                os << ", ";
            }
        }
        os << "]" << std::endl;
    }
}