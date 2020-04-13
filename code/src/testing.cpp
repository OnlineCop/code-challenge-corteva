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

constexpr char TEST_EULER_PROBLEM_8_STRING[]{
    "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843"
    "8586156078911294949545950173795833195285320880551112540698747158523863050715693290963295227443043557"
    "6689664895044524452316173185640309871112172238311362229893423380308135336276614282806444486645238749"
    "3035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776"
    "6572733300105336788122023542180975125454059475224352584907711670556013604839586446706324415722155397"
    "5369781797784617406495514929086256932197846862248283972241375657056057490261407972968652414535100474"
    "8216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586"
    "1786645835912456652947654568284891288314260769004224219022671055626321111109370544217506941658960408"
    "0719840385096245544436298123098787992724428490918884580156166097919133875499200524063689912560717606"
    "0588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450"
};

constexpr char TEST_LONG_HPC_STRING[]{
    "3766581235885941622054540050228447514162777869412307699482907769113268717216818322831603491835999456"
    "0153069150091966614275914529098712142197924857760872532863869459426639499562803023773889717142364156"
    "0516886277355015654882487368973776628456245783619790267499773473790838765037184440800942110091405076"
    "5521827781655182806129058522352838472989652688571683680665438395803243794489830567998343203397981373"
    "5526443098797959573228830206719016692907044977516858705395755436321776237250287268408700164295035643"
    "5489605702040402561955544015979668693552308135435511938776620189520237114790711277888496926653928093"
    "5452003712638970422340890791962244529017494651550289995762505866212386393472458374741386036991340760"
    "9703270224471065027112576717081820878316986771300779277316264661950215131319523227626594093024527187"
    "4306175752785757883191762165074517496673231623144687060553443156897487857600601202693945524717448604"
    "0603096495646182217557200423380237313587369836078574982810508277521659834594761360129982400036745363"
};

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

    // Test that long-enough runs within very long text show a success message, without the original string.
    std::vector<StringAndNumDigits> testLongSuccesses;
    testLongSuccesses.push_back(std::make_pair(TEST_EULER_PROBLEM_8_STRING, 4));
    testLongSuccesses.push_back(std::make_pair(TEST_EULER_PROBLEM_8_STRING, 8));
    testLongSuccesses.push_back(std::make_pair(TEST_EULER_PROBLEM_8_STRING, 13));
    testLongSuccesses.push_back(std::make_pair(TEST_LONG_HPC_STRING, 4));
    testLongSuccesses.push_back(std::make_pair(TEST_LONG_HPC_STRING, 8));
    testLongSuccesses.push_back(std::make_pair(TEST_LONG_HPC_STRING, 13));

    std::cout << "\n*** The following should yield results, but no original string ***\n" << std::endl;

    for (size_t i = 0; i < testLongSuccesses.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << "---" << std::endl;
        }

        std::vector<Hpc::NonZeroRun> nonZeroRuns = Hpc::getNonZeroRuns(testLongSuccesses[i].first, testLongSuccesses[i].second);
        Hpc::MaxProduct maxProduct(testLongSuccesses[i].first, testLongSuccesses[i].second);

        for (Hpc::NonZeroRun run : nonZeroRuns)
        {
            maxProduct.calculateRun(run);
        }

        displayFound(maxProduct, !showOriginalString);
    }
}

} // namespace Testing
} // namespace Debugging
