#pragma once

#include <string>
#include <vector>

namespace Hpc {

/**
* A non-zero run is any number 1..9 until (but not including) a 0.
*
* Products that multiply a '0' will always be 0, so to avoid unnecessary calculations, this points to the
* start and end of a long-enough run (where the length is determined by the caller).
*
* @param1 starting offset, inclusive
* @param2 ending offset, exclusive
*/
using NonZeroRun = std::pair<std::string::const_iterator, std::string::const_iterator>;

/**
* Get a collection of start-and-end iterators of a run of non-zero numbers.
*
* @param input String to parse from.
* @param minRunLength The minimum number of sequential non-zero digits to add to the collection.
* @return Array of ranges within the given input string corresponding to non-zero runs.
*/
std::vector<NonZeroRun> getNonZeroRuns(const std::string& input, const size_t minRunLength);


/**
 * Object to hold the range where the product of the numbers yields the maximum value.
 */
class MaxProduct
{
public:
    /**
     * Constructor.
     *
     * @param originalString Reference to the start of the string.
     * @param runLength Number of digits to calculate in the product.
     */
    MaxProduct(const std::string& originalString, const size_t runLength);

    /**
     * Default destructor.
     */
    ~MaxProduct() = default;

    MaxProduct(const MaxProduct& copy) = default;
    MaxProduct(MaxProduct&& move) = default;
    MaxProduct& operator=(const MaxProduct& copy) = default;
    MaxProduct& operator=(MaxProduct&& move) = default;

    /**
     * Calculate the max product of numbers within a given a range of digits.
     *
     * @param run Range of digits within the original string to calculate a max product from.
     */
    void calculateRun(const NonZeroRun& run);

    /**
     * Update the current max product, if a higher value is found.
     *
     * @param product Product of digits to replace, if higher than current max.
     * @param range Range of digits within the original string where this product was found.
     */
    void updateMax(uint64_t product, const NonZeroRun& range);

    /**
     * Get the current max product value.
     *
     * @returns 0 if no digits had been calculated, else the value of the highest product found.
     */
    uint64_t getMaxProduct() const;

    /**
     * Get the range where the max product value had been found.
     *
     * @returns start and end iterators within the original string where the max product was found;
     * if no max was found, both iterators point past the end of the original string.
     */
    NonZeroRun getMaxProductRange() const;

    /**
     * Get a read-only reference to the original string where the digits are found.
     *
     * @returns a read-only reference to the input string.
     */
    const std::string& getOriginalStringRef() const;

    /**
     * Get the number of digits per product calculation.
     *
     * @returns number of digits to calculate in the product.
     */
    size_t getRunLength() const;

private:
    const std::string& originalStringRef_;
    size_t runLength_;

    uint64_t productMaxValue_;
    NonZeroRun productMaxRange_;
};

} // namespace Hpc
