#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <memory>

class Camera {
private:
    float width;
    float height;

    // Private constructor for singleton
    Camera() : width(0), height(0) {}

    // Delete copy constructor and assignment operator


public:
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
    ~Camera() = default;

    // Singleton instance getter

    static Camera& getInstance();

    // Initialize with dimensions

    void initialize(float w, float h);

    // Get dimensions
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    // Helper struct for screen calculations
    struct ScreenInfo {
        float w;
        float h;
        bool heightFlag;
        float rectSize;
    };

    // Calculate screen information based on window size
    ScreenInfo getScreenInfo(float windowWidth, float windowHeight) const;

    // Normalize coordinates to screen position
    static sf::Vector2f normalizeToScreen(float x, float y, float windowWidth, float windowHeight, bool heightFlag,
                                          float h, float w);

    // Convenience method that uses ScreenInfo
    static sf::Vector2f worldToScreen(float x, float y, const ScreenInfo& info, float windowWidth, float windowHeight);
};

#endif // CAMERA_H