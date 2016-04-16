#include "catch.hpp"
#include "imui/Kit.hpp"
#include "imui/backend/Test.hpp"
#include <bitset>
using namespace std;

TEST_CASE("imui::Kit tests", "[ut][kit]")
{
    S("test");
    using Kit = imui::Kit<imui::backend::Test>;

    imui::backend::test::Native backend(100, 200);
    Kit::Context ctx(backend);

    Kit::Scope scope(ctx);

    SECTION("Init event should occur only once")
    {
        bitset<2> bs;
        auto &reactor = scope(42);
        reactor.on(imui::Init(), [&](Kit::Tile &){bs.set(0);});
        reactor.on(imui::Init(), [&](Kit::Tile &){bs.set(1);});
        REQUIRE(bs[0]);
        REQUIRE(!bs[1]);
    }
    auto &reactor = scope(42);
    REQUIRE(ctx.process());
}
