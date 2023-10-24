#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <sstream>

extern "C" {
    #include "../src/keyfilter.h"
}

TEST_CASE( "Test Standard Output", "[stdout]") {
    const char * str01 = "./keyfilter Pra Praha\nBrno\nBratislava\nBeroun";
    
    std::stringstream capturedOutput;
    std::streambuf* originalOutput = std::cout.rdbuf();

    // Redirect stdout to a stringstream
    std::cout.rdbuf(capturedOutput.rdbuf());

    system(str01);

    // Restore original stdout
    std::cout.rdbuf(originalOutput);

    std::string output = capturedOutput.str();

    // Use CAPTURE macro to capture output for reporting
    CAPTURE(output);

    // Make assertions on the captured output
    REQUIRE(output == "Hello, Catch2!\n"); // Replace with the expected output
}