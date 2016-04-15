#include "catch.hpp"
#include "imui/Kit.hpp"
#include "imui/backend/Test.hpp"

TEST_CASE("imui::Kit tests", "[ut][kit]")
{
    using Kit = imui::Kit<imui::backend::Test>;

    imui::backend::test::Native backend(100, 200);
    Kit::Context ctx(backend);

    Kit::Scope scope(ctx);

    Kit::Tile tile(scope);
}
