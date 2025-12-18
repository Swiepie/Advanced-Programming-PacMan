//
// Created by siebe on 12/12/2025.
//

#include "Camera.h"
Camera& Camera::getInstance() {
    static Camera instance;
    return instance;
}
void Camera::initialize(float w, float h) {
    width = w;
    height = h;
}
Camera::ScreenInfo Camera::getScreenInfo(float windowWidth, float windowHeight) const {
    ScreenInfo info;
    info.rectSize = std::min(windowWidth / width, windowHeight / height);

    if (width / height <= windowWidth / windowHeight) {
        info.h = windowHeight;
        info.w = width * windowHeight / height;
        info.heightFlag = false;
    } else {
        info.h = (height / width) * windowWidth;
        info.w = windowWidth;
        info.heightFlag = true;
    }

    return info;
}
sf::Vector2f Camera::normalizeToScreen(float x, float y, float windowWidth, float windowHeight, bool heightFlag,
                                       float h, float w) {
    float whitespaceH = (windowHeight - h) / 2.f;
    float whitespaceW = (windowWidth - w) / 2.f;

    if (!heightFlag) {
        float px = (x + 1.0f) * 0.5f * w + whitespaceW;
        float py = (y + 1.0f) * 0.5f * h;
        return {px, py};
    } else {
        float px = (x + 1.0f) * 0.5f * w;
        float py = (y + 1.0f) * 0.5f * h + whitespaceH;
        return {px, py};
    }
}
sf::Vector2f Camera::worldToScreen(float x, float y, const ScreenInfo& info, float windowWidth, float windowHeight) {
    return normalizeToScreen(x, y, windowWidth, windowHeight, info.heightFlag, info.h, info.w);
}