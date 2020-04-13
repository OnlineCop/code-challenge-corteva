#include "../include/maxproduct.h"

namespace Hpc {

std::vector<NonZeroRun> getNonZeroRuns(const std::string& input, const size_t minRunLength)
{
    const auto inputEnd = input.end();
    std::vector<NonZeroRun> nonZeroRuns{};
    NonZeroRun currentRun = std::make_pair(input.begin(), input.begin());

    while (currentRun.first < inputEnd)
    {
        // Skip any values NOT between 1..9.
        while (currentRun.first < inputEnd && (*currentRun.first < '1' || *currentRun.first > '9'))
        {
            ++currentRun.first;
        }

        currentRun.second = currentRun.first;

        // Scan until we reach any value NOT between 1..9.
        while (currentRun.second < inputEnd && *currentRun.second >= '1' && *currentRun.second <= '9')
        {
            ++currentRun.second;
        }

        // Add to the collection only if the run length is long enough.
        if (static_cast<size_t>(currentRun.second - currentRun.first) >= minRunLength)
        {
            nonZeroRuns.push_back(std::make_pair(currentRun.first, currentRun.second));
        }

        // Bump ahead to avoid re-parsing the same values again.
        currentRun.first = currentRun.second;
    }

    return nonZeroRuns;
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
    std::string::const_iterator iter = run.first;
    while (iter <= run.second - runLength_)
    {
        uint64_t product = 1;

        for (size_t digitsCalculated = 0; digitsCalculated < runLength_; ++digitsCalculated)
        {
            char digitString = *(iter + digitsCalculated);
            // Convert this digit from ASCII to a numerical value 1..9.
            uint64_t converted = digitString - '0';

            product *= converted;
        }

        updateMax(product, std::make_pair(iter, iter + runLength_));

        ++iter;
    }
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
