#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <sgg/graphics.h>
#include "Miscallenious.h"

class RandomBrush {
private:
    std::vector<graphics::Brush*> elements; // Store dynamically allocated elements

public:
    RandomBrush() {};

    void setup(std::string directoryAndName,int numberOfTextures) {
        graphics::Brush *temp;
        for (int i = 0; i < numberOfTextures; i++) {
            temp = new graphics::Brush;
            temp->outline_opacity = 0.0f;
            temp->texture = directoryAndName + std::to_string(i) + ".png";
            elements.push_back(temp);
        }
        
    }

    graphics::Brush * random() const {
        if (elements.empty()) {
            return nullptr; 
        }
        
        return elements[randomInt(0, elements.size()-1 )];
    }

    ~RandomBrush() {
        for (auto *element : elements) {
            delete element;
        }
    }


};
