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

    REQUIRE(ctx.reduce());

    {
        auto &reactor = scope(42);
    }

    REQUIRE(ctx.reduce());

    {
        L("Initialization");
        bitset<2> bs;
        auto &reactor = scope(42);
        reactor.on(imui::Init(), [&](Kit::Tile &tile){bs.set(0);tile.set_aabb(0,0, 1,1);});
        reactor.on(imui::Init(), [&](Kit::Tile &){bs.set(1);});
        REQUIRE(bs[0]);
        REQUIRE(!bs[1]);
    }

    REQUIRE(ctx.reduce());

    {
        L("Check for hot");
        auto &reactor = scope(42);
        bool is_hot = false;
        reactor.on(imui::Hot(), [&](Kit::Tile &){is_hot = true;});
        REQUIRE(!is_hot);
    }

    REQUIRE(ctx.reduce());

    {
        L("Check for hot again");
        auto &reactor = scope(42);
        bool is_hot = false;
        reactor.on(imui::Hot(), [&](Kit::Tile &){is_hot = true;});
        REQUIRE(is_hot);
    }

    REQUIRE(ctx.reduce());
}
