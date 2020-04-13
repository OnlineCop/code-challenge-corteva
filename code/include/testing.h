#pragma once

namespace Debugging {
namespace Testing {

/**
 * Run a variety of tests to ensure ranges returned are working.
 *
 * This isn't quite on par with a unit test, since we're not EXPECTing or ASSERTing anything here.
 */
void runTests();

} // namespace Testing
} // namespace Debugging
