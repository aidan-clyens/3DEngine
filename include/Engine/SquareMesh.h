#pragma once 

// Includes
#include "Engine/ECS/Mesh.h"

// Defines
#define SQUARE_NUM_VERTICES     6


/* SquareMesh
 */
class SquareMesh : public Mesh {
    public:
        SquareMesh();
        virtual ~SquareMesh();
};