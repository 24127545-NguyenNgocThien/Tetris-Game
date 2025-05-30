#include "../include/color.h"

const Color cyan    = {0, 255, 255, 255};      // I-block
const Color blue    = {0, 0, 255, 255};        // J-block
const Color orange  = {255, 165, 0, 255};      // L-block
const Color yellow  = {255, 255, 0, 255};      // O-block
const Color green   = {0, 255, 0, 255};        // S-block
const Color purple  = {160, 0, 255, 255};      // T-block
const Color red     = {255, 0, 0, 255};        // Z-block
const Color space_blue = {10, 10, 40, 255}; 
const Color light_gray = {230, 230, 230, 255};
const Color glaucous = {108, 132, 213, 255};

std::vector<Color> Bang_Mau()
{
    return {light_gray, cyan, blue, orange, yellow, green, purple, red};
}