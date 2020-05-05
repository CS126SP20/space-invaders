// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>

#include <catch2/catch.hpp>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}