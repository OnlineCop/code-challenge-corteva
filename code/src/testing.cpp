#include "../include/testing.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../include/debugging.h"
#include "../include/maxproduct.h"

namespace {

constexpr char TEST_NO_RESULT1[]{ "" };
constexpr char TEST_NO_RESULT2[]{ "0" };
constexpr char TEST_NO_RESULT3[]{ "123" };
constexpr char TEST_NO_RESULT4[]{ "1230" };
constexpr char TEST_NO_RESULT5[]{ "abcd" };
constexpr char TEST_NO_RESULT6[]{ "abcd1230999" };

constexpr char TEST_WITH_RESULT1[]{ "1234" };
constexpr char TEST_WITH_RESULT2[]{ "1111abcd2222" };
constexpr char TEST_WITH_RESULT3[]{ "5432109876" };
constexpr char TEST_WITH_RESULT4[]{ "9999999999999" };

} // anonymous namespace

namespace Debugging {
namespace Testing {

void runTests()
{
    // Set to 'true' to show the value within the original string, or 'false' to suppress it.
    constexpr bool showOriginalString{ true };

    using StringAndNumDigits = std::pair<std::string, size_t>;

    // Test that lengths without sufficiently-long runs are shown an error message.
    std::vector<StringAndNumDigits> testFailures;
    testFailures.push_back(std::make_pair(TEST_NO_RESULT1, 4));
    testFailures.push_back(std::make_pair(TEST_NO_RESULT2, 4));
    testFailures.push_back(std::make_pair(TEST_NO_RESULT3, 4));
    testFailures.push_back(std::make_pair(TEST_NO_RESULT4, 4));
    testFailures.push_back(std::make_pair(TEST_NO_RESULT5, 4));
    testFailures.push_back(std::make_pair(TEST_NO_RESULT6, 4));

    std::cout << "*** The following should not yield results ***\n" << std::endl;

    for (size_t i = 0; i < testFailures.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << "---" << std::endl;
        }

        std::vector<Hpc::NonZeroRun> nonZeroRuns = Hpc::getNonZeroRuns(testFailures[i].first, testFailures[i].second);
        Hpc::MaxProduct maxProduct(testFailures[i].first, testFailures[i].second);

        for (Hpc::NonZeroRun run : nonZeroRuns)
        {
            maxProduct.calculateRun(run);
        }

        displayFound(maxProduct, showOriginalString);
    }

    // Test that long-enough runs show a success message and the original string in which it was found.
    std::vector<StringAndNumDigits> testSuccesses;
    testSuccesses.push_back(std::make_pair(TEST_WITH_RESULT1, 4));
    testSuccesses.push_back(std::make_pair(TEST_WITH_RESULT2, 4));
    testSuccesses.push_back(std::make_pair(TEST_WITH_RESULT3, 4));
    testSuccesses.push_back(std::make_pair(TEST_WITH_RESULT4, 13));

    std::cout << "\n*** The following should yield results ***\n" << std::endl;

    for (size_t i = 0; i < testSuccesses.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << "---" << std::endl;
        }

        std::vector<Hpc::NonZeroRun> nonZeroRuns = Hpc::getNonZeroRuns(testSuccesses[i].first, testSuccesses[i].second);
        Hpc::MaxProduct maxProduct(testSuccesses[i].first, testSuccesses[i].second);

        for (Hpc::NonZeroRun run : nonZeroRuns)
        {
            maxProduct.calculateRun(run);
        }

        displayFound(maxProduct, showOriginalString);
    }
}

} // namespace Testing
} // namespace Debugging
