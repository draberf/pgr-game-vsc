/**
 * TODO: Doxygen
 * 
 * 
 */

#include <vector>
#include <iostream>

/**
*  @brief Structure for a vertex position/normal combination.
* 
*/
struct VertexNormal {
    float vertex[3];
    float normal[3];
};

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

        VertexNormal * mesh;

    public:
        Block() {
            this->w = 5.0f;
            this->h = 5.0f;
            this->d = 5.0f;
            mesh = (VertexNormal*)malloc(36 * sizeof(VertexNormal));
            UpdateGeometry();
        }

        Block(float w, float h, float d) {
            this->w = w;
            this->h = h;
            this->d = d;
            mesh = (VertexNormal*)malloc(36 * sizeof(VertexNormal));
            UpdateGeometry();
        }

        ~Block() {
            free(mesh);
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

        VertexNormal v[36] = {
            // front face
            {{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
            {{ this->w,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
            {{ this->w,  this->h, 0.f    }, { 0.f,  0.f,  1.f}},
            {{ this->w,  this->h, 0.f    }, { 0.f,  0.f,  1.f}},
            {{ 0.f    ,  this->h, 0.f    }, { 0.f,  0.f,  1.f}},
            {{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
            // right face
            {{ this->w,  0.f    , 0.f    }, { 1.f,  0.f,  0.f}},
            {{ this->w,  0.f    ,-this->d}, { 1.f,  0.f,  0.f}},
            {{ this->w,  this->h,-this->d}, { 1.f,  0.f,  0.f}},
            {{ this->w,  this->h,-this->d}, { 1.f,  0.f,  0.f}},
            {{ this->w,  this->h, 0.f    }, { 1.f,  0.f,  0.f}},
            {{ this->w,  0.f    , 0.f    }, { 1.f,  0.f,  0.f}},
            // back face
            {{ this->w,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            {{ 0.f    ,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            {{ 0.f    ,  this->h,-this->d}, { 0.f,  0.f, -1.f}},
            {{ 0.f    ,  this->h,-this->d}, { 0.f,  0.f, -1.f}},
            {{ this->w,  this->h,-this->d}, { 0.f,  0.f, -1.f}},
            {{ this->w,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            // left face
            {{ 0.f    ,  0.f    ,-this->d}, {-1.f,  0.f,  0.f}},
            {{ 0.f    ,  0.f    , 0.f    }, {-1.f,  0.f,  0.f}},
            {{ 0.f    ,  this->h, 0.f    }, {-1.f,  0.f,  0.f}},
            {{ 0.f    ,  this->h, 0.f    }, {-1.f,  0.f,  0.f}},
            {{ 0.f    ,  this->h,-this->d}, {-1.f,  0.f,  0.f}},
            {{ 0.f    ,  0.f    ,-this->d}, {-1.f,  0.f,  0.f}},
            // top face
            {{ 0.f    ,  this->h, 0.f    }, { 0.f,  1.f,  0.f}},
            {{ this->w,  this->h, 0.f    }, { 0.f,  1.f,  0.f}},
            {{ this->w,  this->h,-this->d}, { 0.f,  1.f,  0.f}},
            {{ this->w,  this->h,-this->d}, { 0.f,  1.f,  0.f}},
            {{ 0.f    ,  this->h,-this->d}, { 0.f,  1.f,  0.f}},
            {{ 0.f    ,  this->h, 0.f    }, { 0.f,  1.f,  0.f}},
            // bot face
            {{ 0.f    ,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            {{ this->w,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}},
            {{ this->w,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
            {{ this->w,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
            {{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
            {{ 0.f    ,  0.f    ,-this->d}, { 0.f,  0.f, -1.f}}
        };

        memcpy(mesh, v, 36 * sizeof(VertexNormal));
    }

    VertexNormal * const GetGeometry() {
        return this->mesh;
    }

    void GetFloatArray() {}

    void PrintSize() {
        std::cout << "w: " << this->w << std::endl;
        std::cout << "h: " << this->h << std::endl;
        std::cout << "d: " << this->d << std::endl;
    }

};

struct VertexNormal const constblock[36] = {
    // front face
    {{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
    {{ 1.f    ,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
    {{ 1.f    ,  1.f    , 0.f    }, { 0.f,  0.f,  1.f}},
    {{ 1.f    ,  1.f    , 0.f    }, { 0.f,  0.f,  1.f}},
    {{ 0.f    ,  1.f    , 0.f    }, { 0.f,  0.f,  1.f}},
    {{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f,  1.f}},
    // right face
    {{ 1.f    ,  0.f    , 0.f    }, { 1.f,  0.f,  0.f}},
    {{ 1.f    ,  0.f    ,-1.f    }, { 1.f,  0.f,  0.f}},
    {{ 1.f    ,  1.f    ,-1.f    }, { 1.f,  0.f,  0.f}},
    {{ 1.f    ,  1.f    ,-1.f    }, { 1.f,  0.f,  0.f}},
    {{ 1.f    ,  1.f    , 0.f    }, { 1.f,  0.f,  0.f}},
    {{ 1.f    ,  0.f    , 0.f    }, { 1.f,  0.f,  0.f}},
    // back face
    {{ 1.f    ,  0.f    ,-1.f    }, { 0.f,  0.f, -1.f}},
    {{ 0.f    ,  0.f    ,-1.f    }, { 0.f,  0.f, -1.f}},
    {{ 0.f    ,  1.f    ,-1.f    }, { 0.f,  0.f, -1.f}},
    {{ 0.f    ,  1.f    ,-1.f    }, { 0.f,  0.f, -1.f}},
    {{ 1.f    ,  1.f    ,-1.f    }, { 0.f,  0.f, -1.f}},
    {{ 1.f    ,  0.f    ,-1.f    }, { 0.f,  0.f, -1.f}},
    // left face
    {{ 0.f    ,  0.f    ,-1.f    }, {-1.f,  0.f,  0.f}},
    {{ 0.f    ,  0.f    , 0.f    }, {-1.f,  0.f,  0.f}},
    {{ 0.f    ,  1.f    , 0.f    }, {-1.f,  0.f,  0.f}},
    {{ 0.f    ,  1.f    , 0.f    }, {-1.f,  0.f,  0.f}},
    {{ 0.f    ,  1.f    ,-1.f    }, {-1.f,  0.f,  0.f}},
    {{ 0.f    ,  0.f    ,-1.f    }, {-1.f,  0.f,  0.f}},
    // top face
    {{ 0.f    ,  1.f    , 0.f    }, { 0.f,  1.f,  0.f}},
    {{ 1.f    ,  1.f    , 0.f    }, { 0.f,  1.f,  0.f}},
    {{ 1.f    ,  1.f    ,-1.f    }, { 0.f,  1.f,  0.f}},
    {{ 1.f    ,  1.f    ,-1.f    }, { 0.f,  1.f,  0.f}},
    {{ 0.f    ,  1.f    ,-1.f    }, { 0.f,  1.f,  0.f}},
    {{ 0.f    ,  1.f    , 0.f    }, { 0.f,  1.f,  0.f}},
    // bot face
    {{ 0.f    ,  0.f    ,-1.f    }, { 0.f,  0.f, -1.f}},
    {{ 1.f    ,  0.f    ,-1.f    }, { 0.f,  0.f, -1.f}},
    {{ 1.f    ,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
    {{ 1.f    ,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
    {{ 0.f    ,  0.f    , 0.f    }, { 0.f,  0.f, -1.f}},
    {{ 0.f    ,  0.f    ,-1.f    }, { 0.f,  0.f, -1.f}}
};