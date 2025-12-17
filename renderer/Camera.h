//
// Created by siebe on 12/12/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
private:

    // world meegeven aan camera
public:
    ~Camera() = default;
    sf::Vector2f normalizeToScreen(float x, float y, float screenWidth, float screenHeight, bool flag, float h,
                                   float w) const {
        float whitespaceH = (screenHeight - h) / 2.0f;
        float whitespaceW = (screenWidth - w) / 2.0f;

        if (!flag) {
            float px = (x + 1.0f) * 0.5f * w + whitespaceW;
            float py = (y + 1.0f) * 0.5f * h;
            return {px, py};
        } else {
            float px = (x + 1.0f) * 0.5f * w;
            float py = (y + 1.0f) * 0.5f * h + whitespaceH;
            return {px, py};
        }
    }
};

#endif // CAMERA_H
