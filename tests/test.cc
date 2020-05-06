// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "spaceinvaders/invader.h"
#include "spaceinvaders/projectile.h"

using spaceinvaders::Invader;
using spaceinvaders::Projectile;

TEST_CASE("Invader move test", "[invader][move][position]") {
  spaceinvaders::Invader invader({250, 250});
  invader.Move(10, 10);
  REQUIRE(invader.GetPosition().x == 260);
  REQUIRE(invader.GetPosition().y == 260);
}

TEST_CASE("Invader make alive test", "[invader][make-alive]") {
  Invader invader({250, 250});
  invader.MakeAlive();
  REQUIRE(invader.IsAlive());
}

TEST_CASE("Invader make alive position test",
          "[invader][move][make-alive][position]") {
  Invader invader({250, 250});
  invader.Move(20, 20);
  invader.MakeAlive();
  REQUIRE(invader.GetPosition().x == 250);
  REQUIRE(invader.GetPosition().y == 250);
}

TEST_CASE("Projectile position test", "[projectile][position]") {
  Projectile projectile({250, 250}, Projectile::Direction::Up);
  REQUIRE(projectile.GetPosition().x == 250);
  REQUIRE(projectile.GetPosition().y == 250);
}

TEST_CASE("Projectile destroy test", "[projectile][destroy][is-active]") {
  Projectile projectile({250, 250}, Projectile::Direction::Up);
  projectile.Destroy();
  REQUIRE(!projectile.IsActive());
}

TEST_CASE("Projectile ID Test", "[projectile][id]") {
  Projectile projectile({250, 250}, Projectile::Direction::Up);
  REQUIRE(projectile.GetID() == 0);
}
