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

    Kit::ReactorMgr mgr(ctx);

    {
        Kit::DrawSentry draw_sentry(ctx);
        auto &reactor = mgr(42);
    }

    {
        Kit::DrawSentry draw_sentry(ctx);
        L("Initialization");
        bitset<2> bs;
        auto &reactor = mgr(42);
        reactor.on(imui::Init(), [&](){bs.set(0); reactor.tile.set_aabb(0,0, 1,1);});
        reactor.on(imui::Init(), [&](){bs.set(1);});
        REQUIRE(bs[0]);
        REQUIRE(!bs[1]);
    }

    {
        Kit::DrawSentry draw_sentry(ctx);
        L("Check for hot");
        auto &reactor = mgr(42);
        bool is_hot = false;
        reactor.on(imui::Hot(), [&](){is_hot = true;});
        REQUIRE(!is_hot);
    }

    {
        Kit::DrawSentry draw_sentry(ctx);
        L("Check for hot again");
        auto &reactor = mgr(42);
        bool is_hot = false;
        reactor.on(imui::Hot(), [&](){is_hot = true;});
        REQUIRE(is_hot);
    }
}
