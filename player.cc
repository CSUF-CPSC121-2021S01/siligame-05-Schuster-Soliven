#include "player.h"

// Player functions
void Player::Draw(graphics::Image& canvas) {
  graphics::Image Amelia;
  Amelia.Load("Amelia_.bmp");
  for (int i = 0; i < Amelia.GetHeight(); i++) {
    for (int j = 0; j < Amelia.GetWidth(); j++) {
      canvas.SetColor(GetX() + j, GetY() + i, Amelia.GetColor(j, i));
    }
  }
}

void Player::Move(const graphics::Image& image) {
  // empty
}

// Player Projectile functions
void PlayerProjectile::Draw(graphics::Image& canvas) {
  graphics::Image Grenade;
  Grenade.Load("Bullet_.bmp");
  for (int i = 0; i < Grenade.GetHeight(); i++) {
    for (int j = 0; j < Grenade.GetWidth(); j++) {
      canvas.SetColor(GetX() + j, GetY() + i, Grenade.GetColor(j, i));
    }
  }
}

void PlayerProjectile::Move(const graphics::Image& image) {
  SetY(GetY() - 3);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}
