#include "../src/matrix.hpp"
#include <catch2/catch_test_macros.hpp>

namespace forge {
    constexpr bool foo() { return true; }
}

TEST_CASE("Tests such that foo returns true", "[foo]") {
    REQUIRE(forge::foo() == true);
}

TEST_CASE("Tests something that fails", "[bar]") {
    REQUIRE(forge::foo() == false);
}