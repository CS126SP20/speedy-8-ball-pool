//
// Created by lilyl on 4/17/2020.
//

#include "mylibrary/table.h"
class Table {
    int posX, posY;
    /*
    Texture background;
    Rect r[6] {};  // Rect colliders for walls
    Ball b[12] {}; // Ball colliders to simulate pocket sides
    SDL_Point pocket_sensors[6] {}; // Check if ball in the pocket
    */
public:
    //Table(CollisionObserver* c = nullptr);

    void render();
    //bool is_pocketed(const Ball& b);

    //double  getWidth() const noexcept {return background.getWidth(); }
    //double getHeight() const noexcept {return background.getHeight();}
    int         getX() const noexcept {return posX;}
    int         getY() const noexcept {return posY;}
};

