// TODO: Header file
#include "collision.hpp"

// TODO: Hitbox class
// Make subclass of GameObject
class Hitbox
{
    public:
        Hitbox()
        {

        }
};

class SquareHitbox: public Hitbox
{
    public:
        SquareHitbox(unsigned int width, unsigned int height )
        {
            // unsigned int this.width = width;
            // unsigned int this.height = height;
        }
};

class CircleHitbox: public Hitbox
{
    public:
        CircleHitbox(unsigned int radius)
        {

        }
};


// TODO: Square/circle/line subclasses

// TODO: Collision detection