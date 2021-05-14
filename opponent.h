#include <memory>
#include "game_element.h"

#ifndef OPPONENT_H
#define OPPONENT_H

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  OpponentProjectile() : GameElement(0, 0, 5, 5) {}

  ~OpponentProjectile() {}

  void Draw(graphics::Image& board);

  void Move(const graphics::Image& image);
};

class Opponent : public GameElement {
 public:
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  Opponent() : GameElement(0, 0, 50, 50) {}

  ~Opponent() {}

  void Draw(graphics::Image& board);

  void Move(const graphics::Image& image);

  std::unique_ptr<OpponentProjectile> LaunchProjectile();
  // returns a unique pointer to projectile and will delete itself
  // under a condition. Every 10 times it is called, it will shoot
  // a projectile from the bottom center of the opponent

 private:
  int rate_of_fire_counter = 0;
};

#endif
