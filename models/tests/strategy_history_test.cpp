//
// Created by Dmitry Khrykin on 2019-07-06.
//

#include <catch2/catch.hpp>
#include "strategy.h"

TEST_CASE("Strategy history", "[strategy][history]") {
    auto strategy = stg::strategy();
    auto initialActivity = stg::activity("Some 1");

    strategy.add_activity(initialActivity);

    SECTION("activity addition") {
        strategy.add_activity(stg::activity("Some 2"));

        SECTION("undo") {
            strategy.undo();
            REQUIRE(strategy.activities().size() == 1);
        }

        SECTION("redo") {
            strategy.add_activity(stg::activity("Some 3"));
            strategy.undo();
            strategy.undo();
            strategy.redo();

            REQUIRE(strategy.activities().size() == 2);
        }
    }

    SECTION("activity editing") {
        const auto editedActivity = stg::activity("Some 1 Edited");
        strategy.edit_activity(0, editedActivity);

        SECTION("undo") {
            strategy.undo();
            REQUIRE(strategy.activities()[0] == initialActivity);
        }

        SECTION("redo") {
            strategy.undo();
            strategy.undo();
            strategy.redo();
            REQUIRE(strategy.activities()[0] == initialActivity);
        }
    }

    SECTION("activity removal") {
        const auto editedActivity = stg::activity("Some 1 Edited");
        strategy.add_activity(stg::activity("Some 2"));
        strategy.delete_activity(0);

        SECTION("undo") {
            strategy.undo();
            REQUIRE(strategy.activities().size() == 2);
        }

        SECTION("redo") {
            strategy.undo();
            strategy.undo();
            strategy.redo();

            REQUIRE(strategy.activities().size() == 2);
        }

    }

    SECTION("activity removal while present in slots") {
        strategy.place_activity(0, {0});
        strategy.place_activity(0, {1});

        strategy.delete_activity(0);

        strategy.undo();
        REQUIRE(strategy.activities()[0] == initialActivity);
        REQUIRE(strategy.sessions()[0].length() == 2);

    }

    SECTION("time slots change") {
        strategy.place_activity(0, {0, 1});
        strategy.place_activity(0, {2});

        strategy.undo();

        REQUIRE(strategy.sessions()[0].length() == 2);
    }
}