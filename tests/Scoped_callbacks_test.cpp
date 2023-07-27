#include "eventi/Event.h"
#include "eventi/Scoped_callbacks.h"

#include <catch2/catch.hpp>

using namespace eventi;

TEST_CASE("Scoped callbacks are removed when the scope object is destroyed") {
    Event<> event;
    int counter = 0;
    {
        Scoped_callbacks scope;
        Callback_ref callback = event.add_callback([&] {
            counter++;
        });
        scope.add_to_scope(callback);
        event();
        CHECK(counter == 1);
    }

    event();
    CHECK(counter == 1);
}
