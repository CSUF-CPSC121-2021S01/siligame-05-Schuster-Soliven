#include <memory>
#include <vector>
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  // default constructor
  Game() { board_.Initialize(800, 600); }

  // constructor with parameters
  Game(int width, int height) { board_.Initialize(width, height); }

  graphics::Image& GetGameScreen() { return board_; }

  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles() {
    return Barrage_;
  }

  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles() {
    return Glob_;
  }

  std::vector<std::unique_ptr<Opponent>>& GetOpponents() { return Cult_; }

  Player& GetPlayer() { return Amelia_; }

  int GetScore() { return score_; }

  bool HasLost() { return !Amelia_.GetIsActive(); }

  void Start(graphics::Image& game) { game.ShowUntilClosed(); }

  void CreateOpponents();

  void Init();

  void UpdateScreen();

  void MoveGameElements();

  void FilterIntersections();

  void OnAnimationStep() override;

  void OnMouseEvent(const graphics::MouseEvent& mouse) override;

  void LaunchProjectiles();

  void RemoveInactive();

 private:
  graphics::Image board_;
  std::vector<std::unique_ptr<PlayerProjectile>> Barrage_;
  std::vector<std::unique_ptr<OpponentProjectile>> Glob_;
  std::vector<std::unique_ptr<Opponent>> Cult_;
  Player Amelia_;
  int score_ = 0;
  bool HasLost_;
};

#endif
