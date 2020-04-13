#include "../include/maxproduct.h"

namespace Hpc {

std::vector<NonZeroRun> getNonZeroRuns(const std::string& input, const size_t minRunLength)
{
    // STUB
    (void)input;
    (void)minRunLength;

    return {};
}

MaxProduct::MaxProduct(const std::string& originalString, const size_t runLength)
    : originalStringRef_{ originalString }
    , runLength_{ runLength }
    , productMaxValue_{ 0 }
    , productMaxRange_{ originalString.end(), originalString.end() }
{
}

void MaxProduct::calculateRun(const NonZeroRun& run)
{
    // STUB
    (void)run;
}

void MaxProduct::updateMax(const uint64_t product, const NonZeroRun& range)
{
    if (product > productMaxValue_)
    {
        productMaxRange_ = std::make_pair(range.first, range.second);
        productMaxValue_ = product;
    }
}

uint64_t MaxProduct::getMaxProduct() const
{
    return productMaxValue_;
}

NonZeroRun MaxProduct::getMaxProductRange() const
{
    return productMaxRange_;
}

const std::string& MaxProduct::getOriginalStringRef() const
{
    return originalStringRef_;
}

size_t MaxProduct::getRunLength() const
{
    return runLength_;
}

} // namespace Hpc
