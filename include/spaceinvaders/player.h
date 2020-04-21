// Copyright (c) 2020 Saurav Rgahavendra. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_


namespace spaceinvaders {

class Player {
 public:
  Player();

  void MoveLeft();

  void MoveRight();

  void Shoot();

 private:
  int health_;

};

}  // namespace spaceinvaders


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
