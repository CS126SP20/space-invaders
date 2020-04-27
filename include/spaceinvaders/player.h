// Copyright (c) 2020 Saurav Rgahavendra. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_


namespace spaceinvaders {

class Player {
 public:
  Player();

  void AddToScore(int points);

  auto GetScore() -> int { return score_; }

  void SubtractFromScore(int points);

  void RemoveLife();

 private:
  int lives_;
  int score_;
};

}  // namespace spaceinvaders


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
