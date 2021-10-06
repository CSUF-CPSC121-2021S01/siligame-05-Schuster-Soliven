#include "game.h"

void Game::CreateOpponents() {
  // creates 9 Opponent Objects
  for (int i = 0; i < 9; i++) {
    Cult_.push_back(std::make_unique<Opponent>(50 * i + 15, 50));
  }
}

void Game::Init() {
  board_.AddMouseEventListener(*this);
  board_.AddAnimationEventListener(*this);
  Amelia_.SetX(10);
  Amelia_.SetY(board_.GetHeight() - 75);
  // initial position bot left
}

void Game::UpdateScreen() {
  // board_.DrawRectangle(0, 0, 800, 600, 102, 102, 255);
  board_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  board_.DrawText(10, 10, std::to_string(score_), 35, 0, 0, 0);
  for (int i = 0; i < Cult_.size(); i++) {
    if (Cult_[i]->GetIsActive() == true) {
      Cult_[i]->Draw(board_);
    }
  }
  for (int i = 0; i < Glob_.size(); i++) {
    if (Glob_[i]->GetIsActive() == true) {
      Glob_[i]->Draw(board_);
    }
  }
  for (int i = 0; i < Barrage_.size(); i++) {
    if (Barrage_[i]->GetIsActive() == true) {
      Barrage_[i]->Draw(board_);
    }
  }
  if (Amelia_.GetIsActive() == true) {
    Amelia_.Draw(board_);
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < Barrage_.size(); i++) {
    Barrage_[i]->Move(board_);
  }
  for (int i = 0; i < Glob_.size(); i++) {
    Glob_[i]->Move(board_);
  }
  for (int i = 0; i < Cult_.size(); i++) {
    Cult_[i]->Move(board_);
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < Cult_.size(); i++) {
    if (Cult_[i]->GetIsActive() && Amelia_.GetIsActive() &&
        Amelia_.IntersectsWith(Cult_[i].get())) {
      Cult_[i]->SetIsActive(false);
      Amelia_.SetIsActive(false);
    } else {
      for (int j = 0; j < Barrage_.size(); j++) {
        if (Cult_[i]->GetIsActive() && Barrage_[j]->GetIsActive() &&
            Barrage_[j]->IntersectsWith(Cult_[i].get())) {
          if (Amelia_.GetIsActive()) {
            score_++;
          }
          Cult_[i]->SetIsActive(false);
          Barrage_[j]->SetIsActive(false);
        }
      }
    }
  }
  for (int i = 0; i < Glob_.size(); i++) {
    if (Glob_[i]->GetIsActive() && Amelia_.GetIsActive() &&
        Amelia_.IntersectsWith(Glob_[i].get())) {
      Glob_[i]->SetIsActive(false);
      Amelia_.SetIsActive(false);
    }
  }
}

void Game::OnMouseEvent(const graphics::MouseEvent& mouse) {
  if (mouse.GetX() > 0 && mouse.GetY() > 0 &&
      mouse.GetX() < board_.GetWidth() && mouse.GetY() < board_.GetHeight()) {
    Amelia_.SetX(mouse.GetX() - 25);
    Amelia_.SetY(mouse.GetY() - 25);
  }
  if (mouse.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> Bullet =
        std::make_unique<PlayerProjectile>(mouse.GetX(), mouse.GetY() + 25);
    Barrage_.push_back(std::move(Bullet));
  }
  if (mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> Bullet =
        std::make_unique<PlayerProjectile>(mouse.GetX(), mouse.GetY() + 25);
    Barrage_.push_back(std::move(Bullet));
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < Cult_.size(); i++) {
    if (Cult_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> Ink;
      Ink = std::make_unique<OpponentProjectile>();
      Ink->SetX(Cult_[i]->GetX());
      Ink->SetY(Cult_[i]->GetY());
      Glob_.push_back(std::move(Ink));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = Barrage_.size() - 1; i >= 0; i--) {
    if (!Barrage_[i]->GetIsActive()) {
      Barrage_.erase(Barrage_.begin() + i);
    }
  }
  for (int i = Glob_.size() - 1; i >= 0; i--) {
    if (!Glob_[i]->GetIsActive()) {
      Glob_.erase(Glob_.begin() + i);
    }
  }
  for (int i = Cult_.size() - 1; i >= 0; i--) {
    if (!Cult_[i]->GetIsActive()) {
      Cult_.erase(Cult_.begin() + i);
    }
  }
}

void Game::OnAnimationStep() {
  if (Cult_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  board_.Flush();
}
