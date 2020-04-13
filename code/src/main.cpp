#include "../include/debugging.h"
#include "../include/maxproduct.h"
#include "../include/testing.h"

#include <iostream>
#include <string>

namespace {

const std::string hpcString{
    "37665812358859416220545400502284475141627778694123"
    "07699482907769113268717216818322831603491835999456"
    "01530691500919666142759145290987121421979248577608"
    "72532863869459426639499562803023773889717142364156"
    "05168862773550156548824873689737766284562457836197"
    "90267499773473790838765037184440800942110091405076"
    "55218277816551828061290585223528384729896526885716"
    "83680665438395803243794489830567998343203397981373"
    "55264430987979595732288302067190166929070449775168"
    "58705395755436321776237250287268408700164295035643"
    "54896057020404025619555440159796686935523081354355"
    "11938776620189520237114790711277888496926653928093"
    "54520037126389704223408907919622445290174946515502"
    "89995762505866212386393472458374741386036991340760"
    "97032702244710650271125767170818208783169867713007"
    "79277316264661950215131319523227626594093024527187"
    "43061757527857578831917621650745174966732316231446"
    "87060553443156897487857600601202693945524717448604"
    "06030964956461822175572004233802373135873698360785"
    "74982810508277521659834594761360129982400036745363"
};

struct ParseInputs
{
    bool runTests{ false };
    bool showHelp{ false };
    size_t numDigitsToParse{ 4 };
    std::pair<bool, std::string> parseExternalFile{};
    std::pair<bool, std::string> userSuppliedNumber{};
};

ParseInputs doParse(int argc, char** argv)
{
    ParseInputs parseInputs{};

    for (int arg = 0; arg < argc; ++arg)
    {
        std::string argvString = argv[arg];
        if (argvString == "-t" || argvString == "--test")
        {
            parseInputs.runTests = true;
            continue;
        }

        if (argvString == "-h" || argvString == "--help")
        {
            parseInputs.showHelp = true;
        }

        if (argvString == "-d" && arg + 1 < argc)
        {
            parseInputs.numDigitsToParse = strtoul(argv[arg + 1], nullptr, 0);
            if ((parseInputs.numDigitsToParse == LLONG_MAX || parseInputs.numDigitsToParse == LLONG_MIN) &&
                errno == ERANGE)
            {
                // Invalid number; ignore it.
                parseInputs.numDigitsToParse = 4;
            }
            ++arg;
            continue;
        }

        if (argvString == "-f" && arg + 1 < argc)
        {
            parseInputs.parseExternalFile = std::make_pair(true, argv[arg + 1]);
            ++arg;
            continue;
        }

        if (argvString == "-n" && arg + 1 < argc)
        {
            // User will provide number on command line.
            parseInputs.userSuppliedNumber = std::make_pair(true, argv[arg + 1]);
            ++arg;
            continue;
        }
    }

    return parseInputs;
}

} // anonymous namespace

int main(int argc, char** argv)
{
    ParseInputs parseInputs = doParse(argc, argv);

    if (parseInputs.runTests)
    {
        Debugging::Testing::runTests();
        return 0;
    }

    if (parseInputs.showHelp)
    {
        std::cout << "Sorry; the help file isn't ready yet. Try '-f [filename]' or '-d 8' for now." << std::endl;
        return 0;
    }

    if (parseInputs.parseExternalFile.first == true)
    {
        // TODO: Read number in from a file.

        // STUB
        std::string fileContents = "1234005567091110999901111";
    }

    std::string stringToParse{ hpcString };
    if (parseInputs.userSuppliedNumber.first == true)
    {
        stringToParse = parseInputs.userSuppliedNumber.second;
    }


    // Step 1: Split the number into runs NOT containing 0's, since we know their product will equal 0.
    std::vector<Hpc::NonZeroRun> nonZeroRun = Hpc::getNonZeroRuns(stringToParse, parseInputs.numDigitsToParse);

    Hpc::MaxProduct maxProduct(stringToParse, parseInputs.numDigitsToParse);


    // Step 2: For each of the runs returned, scan [numDigitsToParse] digits at a time and calculate their product.
    for (Hpc::NonZeroRun run : nonZeroRun)
    {
        maxProduct.calculateRun(run);
    }


    // Step 3: Display the [numDigitsToParse] digits that produced the largest product.
    constexpr bool showOriginalNumber{ true };
    Debugging::displayFound(maxProduct, showOriginalNumber);

    return 0;
}
