#include "../include/debugging.h"

#include <iomanip>
#include <iostream>

#include "../include/maxproduct.h"

namespace Debugging {

void displayFound(const Hpc::MaxProduct& maxProduct, const bool showOriginalNumber)
{
    const Hpc::NonZeroRun& range = maxProduct.getMaxProductRange();
    const std::string& originalString = maxProduct.getOriginalStringRef();

    // If the range is invalid, no [n]-length digits were found in the original string.
    if (range.first == originalString.end())
    {
        std::cerr << "No " << maxProduct.getRunLength() << "-digit number containing only 1..9 found."
            << std::endl;
        if (showOriginalNumber)
        {
            std::cerr << "The original string was: " << std::quoted(originalString) << std::endl;
        }
    }
    else
    {
        // Display the [n]-length numbers, whose digits resulted in the largest product, along with their offsets.
        std::cout << "The " << maxProduct.getRunLength() << "-digit number "
            << std::quoted(std::string(range.first, range.second))
            << " has the largest product found at offset " << (range.first - originalString.begin())
            << " with the value of " << maxProduct.getMaxProduct() << "." << std::endl;

        if (showOriginalNumber)
        {
            // This prints the entire string of numbers with the range highlighted.
            // Example:
            //   "5432109876" would show "543210[ 9876 ]"

            std::cout << "The original string was: "
                << std::quoted(
                    std::string(originalString.begin(), range.first) +
                    "[ " + std::string(range.first, range.second) + " ]"
                    + std::string(range.second, originalString.end())) << std::endl;
        }
    }
}

} // namespace Debugging
