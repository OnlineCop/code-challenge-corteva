#pragma once

#include <string>
#include <vector>

#include "maxproduct.h"

namespace Hpc {

// Forward-declared so we don't have to #include its header.
class MaxProduct;

}

namespace Debugging {

/**
 * Output the [n]-digit number which resulted in the largest product.
 *
 * If none was found (due to invalid input), output an error to stderr instead.
 *
 * @param maxProduct Object containing the product (and its offsets) within the original string.
 */
void displayFound(const Hpc::MaxProduct& maxProduct, bool showOriginalNumber);

} // namespace Debugging
