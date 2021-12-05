/**
 * TODO: Doxygen
 * 
 * 
 */

#include "geometry.hpp"
#include <vector>
#include <iostream>


/**
 * @brief Common superclass for geometry objects.
 *
 */

class Geometry {

    std::vector<VertexNormal> *GetGeometry() {
        std::cerr << "ERROR: Pulling geometry from unspecified object." << std::endl;
        return nullptr;
    }

};

/**
 * @brief Geometry class for six-faced blocks.
 */
class Block : Geometry {

    private:
        float w; // width
        float h; // height
        float d; // depth

        VertexNormal * const mesh[36] = (VertexNormal * const)nullptr;

    public:
        Block() {
            this->w = 5.0f;
            this->h = 5.0f;
            this->d = 5.0f;
            this->UpdateGeometry();
        }

        Block(float w, float h, float d) {
            this->w = w;
            this->h = h;
            this->d = d;
            this->UpdateGeometry();
        }

    void UpdateGeometry() {
        // origin position: Front bottom right
        // width and height into positive
        // depth into negative

        /*
                
              H +--------+ G
               /        /|
            E /        / |
             +--------+ F|
             |  (D)   |  + C
             |        | /
             |        |/
             +--------+
            A          B

        */

        std::vector<VertexNormal> v = {
            // front face
            (struct VertexNormal){{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
            (struct VertexNormal){{ this->w,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
            (struct VertexNormal){{ this->w,  this->h, 0.f    }, { 0.f,  0.f,  1.f}},
            (struct VertexNormal){{ this->w,  this->h, 0.f    }, { 0.f,  0.f,  1.f}},
            (struct VertexNormal){{ 0.f    ,  this->h, 0.f    }, { 0.f,  0.f,  1.f}},
            (struct VertexNormal){{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
            // right face
            (struct VertexNormal){{ this->w,  0.f    , 0.f    }, { 1.f,  0.f,  0.f}},
            (struct VertexNormal){{ this->w,  0.f    ,-this->d}, { 1.f,  0.f,  0.f}},
            (struct VertexNormal){{ this->w,  this->h,-this->d}, { 1.f,  0.f,  0.f}},
            (struct VertexNormal){{ this->w,  this->h,-this->d}, { 1.f,  0.f,  0.f}},
            (struct VertexNormal){{ this->w,  this->h, 0.f    }, { 1.f,  0.f,  0.f}},
            (struct VertexNormal){{ this->w,  0.f    , 0.f    }, { 1.f,  0.f,  0.f}},
            // back face
            (struct VertexNormal){{ this->w,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ 0.f    ,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ 0.f    ,  this->h,-this->d}, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ 0.f    ,  this->h,-this->d}, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ this->w,  this->h,-this->d}, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ this->w,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            // left face
            (struct VertexNormal){{ 0.f    ,  0.f    ,-this->d}, {-1.f,  0.f,  0.f}},
            (struct VertexNormal){{ 0.f    ,  0.f    , 0.f    }, {-1.f,  0.f,  0.f}},
            (struct VertexNormal){{ 0.f    ,  this->h, 0.f    }, {-1.f,  0.f,  0.f}},
            (struct VertexNormal){{ 0.f    ,  this->h, 0.f    }, {-1.f,  0.f,  0.f}},
            (struct VertexNormal){{ 0.f    ,  this->h,-this->d}, {-1.f,  0.f,  0.f}},
            (struct VertexNormal){{ 0.f    ,  0.f    ,-this->d}, {-1.f,  0.f,  0.f}},
            // top face
            (struct VertexNormal){{ 0.f    ,  this->h, 0.f    }, { 0.f,  1.f,  0.f}},
            (struct VertexNormal){{ this->w,  this->h, 0.f    }, { 0.f,  1.f,  0.f}},
            (struct VertexNormal){{ this->w,  this->h,-this->d}, { 0.f,  1.f,  0.f}},
            (struct VertexNormal){{ this->w,  this->h,-this->d}, { 0.f,  1.f,  0.f}},
            (struct VertexNormal){{ 0.f    ,  this->h,-this->d}, { 0.f,  1.f,  0.f}},
            (struct VertexNormal){{ 0.f    ,  this->h, 0.f    }, { 0.f,  1.f,  0.f}},
            // bot face
            (struct VertexNormal){{ 0.f    ,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ this->w,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ this->w,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ this->w,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
            (struct VertexNormal){{ 0.f    ,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}}
        };

        this->mesh = v;
    }

    std::vector<VertexNormal> *GetGeometry() {
        return this->mesh;
    }

    void PrintSize() {
        std::cout << "w: " << this->w << std::endl;
        std::cout << "h: " << this->h << std::endl;
        std::cout << "d: " << this->d << std::endl;
    }

};

int main(int argc, char *argv[]) {

    Block b = Block();

    b.PrintSize();

    std::cout << "Hello world?" << std::endl;
}