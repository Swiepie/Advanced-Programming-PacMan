//
// Created by Siebe Haché on 15/10/2025.
//

#include "Wall.h"
void Wall::accept(Visitor& visitor) { visitor.visit(*this); }