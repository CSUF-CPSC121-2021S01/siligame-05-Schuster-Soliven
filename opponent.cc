#include "opponent.h"

// Opponent Functions
void Opponent::Draw(graphics::Image& canvas) {
  graphics::Image Takodachi;
  Takodachi.Load("Takodachi_.bmp");
  for (int i = 0; i < Takodachi.GetHeight(); i++) {
    for (int j = 0; j < Takodachi.GetWidth(); j++) {
      canvas.SetColor(GetX() + j, GetY() + i, Takodachi.GetColor(j, i));
    }
  }
}

void Opponent::Move(const graphics::Image& image) {
  SetY(GetY() + 5);
  SetX(GetX() + 10);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  // change rate_of_fire_counter to be preferred ROF
  // bigger #, longer rate of fire
  if (rate_of_fire_counter >= 10) {
    rate_of_fire_counter = 0;
    std::unique_ptr<OpponentProjectile> Ink =
        std::make_unique<OpponentProjectile>(GetX() + 25, GetY() + 25);
    return std::move(Ink);
  } else {
    rate_of_fire_counter++;
    return nullptr;
  }
}

//  Opponent Projectile Functions
void OpponentProjectile::Draw(graphics::Image& canvas) {
  graphics::Image Goo;
  Goo.Load("Ink_.bmp");
  for (int i = 0; i < Goo.GetHeight(); i++) {
    for (int j = 0; j < Goo.GetWidth(); j++) {
      canvas.SetColor(GetX() + j, GetY() + i, Goo.GetColor(j, i));
    }
  }
}

void OpponentProjectile::Move(const graphics::Image& image) {
  SetY(GetY() + 5);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}
