#include "game_element.h"

// GameElement parameter is now a pointer
// which means you will need to pass a GameElement Reference
bool GameElement::IntersectsWith(GameElement* entity) {
  return !(GetX() > entity->GetX() + entity->GetWidth() ||
           entity->GetX() > GetX() + GetWidth() ||
           GetY() > entity->GetY() + entity->GetHeight() ||
           entity->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image& image) {
  /* checks if left or right side of Game Element object
   * is out of bounds
   * also checks if the bottom or top of Game Element object
   * goes out of bounds
   */
  if (GetX() < 0 || GetX() + GetWidth() > image.GetWidth()) {
    return true;
  } else if (GetY() < 0 || GetY() + GetHeight() > image.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
