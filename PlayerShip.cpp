#include "PlayerShip.h"
#include "Switch.h"


const unsigned short bullet[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

int32_t min(int32_t a, int32_t b){
    return (a <= b) ? a : b;
}

int32_t max(int32_t a, int32_t b){
    return (a >= b) ? a : b;
}

/**
 * @brief Construct a new Player Ship:: Player Ship object
 *
 * @param x Position x
 * @param y Position y
 * @param w Width
 * @param h Height
 * @param a
 * @param images
 */
// Assuming FPVector2D has methods to handle fixed-point assignments
PlayerShip::PlayerShip(int16_t x, int16_t y, int16_t w, int16_t h, int32_t angle, const uint16_t **images, FPVector2D initialVelocity, int totalSprites, BoundaryMode boundaryMode)
    : _position(x << FP_SHIFT, y << FP_SHIFT), // Assume constructor of FPVector2D shifts internally if needed
      _velocity(initialVelocity), // Use the initialVelocity provided
      _size(w << FP_SHIFT, h << FP_SHIFT), // Assume constructor of FPVector2D shifts internally if needed
      _angle(angle),
      _sprites(images),
      _totalSprites(totalSprites),
      _boundaryMode(boundaryMode), // Store the boundary mode
      _inputLeft(false),
      _inputRight(true)
{
    updateSpriteIndex(); // Calculate the initial sprite index
}

void PlayerShip::updateSpriteIndex()
{
    // Ensuring angle is within the valid range
    int normalizedAngle = _angle % 360;
    if (normalizedAngle < 0)
        normalizedAngle += 360;

    // Calculating sprite index based on the total number of sprites
    _spriteIndex = _angle / 15;
}

#define DRIFT_FACTOR 0.05  // This controls the rate of change of the velocity toward the desired direction

void PlayerShip::update() {
    int angleIndex = _angle % 360;  // Ensure angle is within range
    int32_t sin_value = SIN_LUT[angleIndex];
    int32_t cos_value = COS_LUT[angleIndex];

    // Calculate the desired velocity based on the current angle
    int32_t desired_vel_x = (cos_value * PLAYERSPEED) / 1024;
    int32_t desired_vel_y = (-sin_value * PLAYERSPEED) / 1024;

    // Gradually adjust the current velocity towards the desired velocity
    _velocity.x = _velocity.x + DRIFT_FACTOR * (desired_vel_x - _velocity.x);
    _velocity.y = _velocity.y + DRIFT_FACTOR * (desired_vel_y - _velocity.y);

    // Update position based on the new velocity
    _position += _velocity;

    // Other updates
    updateSpriteIndex();
    // Boundary checks
    _position.x = max(0, min(_position.x, (SCREENWIDTH << FP_SHIFT) - _size.x));
    _position.y = max(0, min(_position.y, (SCREENHEIGHT << FP_SHIFT) - _size.y));
}



void PlayerShip::applyForce(const FPVector2D& force) {
    _acceleration += force;
}

void PlayerShip::draw(const uint16_t* bg) {
    // Calculate minimal update area
    int minX = min(_previousPosition.x, _position.x) >> FP_SHIFT;
    int minY = min(_previousPosition.y, _position.y) >> FP_SHIFT;
    int maxX = max(_previousPosition.x + _size.x, _position.x + _size.x) >> FP_SHIFT;
    int maxY = max(_previousPosition.y + _size.y, _position.y + _size.y) >> FP_SHIFT;

    // Redraw only the necessary area
    for (int y = minY; y < maxY && y < SCREENHEIGHT; ++y) {
        for (int x = minX; x < maxX && x < SCREENWIDTH; ++x) {
            // Check if within previous or current sprite bounds to decide on background or sprite pixel
            bool isPrevBound = x >= (_previousPosition.x >> FP_SHIFT) && x < ((_previousPosition.x + _size.x) >> FP_SHIFT) &&
                               y >= (_previousPosition.y >> FP_SHIFT) && y < ((_previousPosition.y + _size.y) >> FP_SHIFT);
            bool isCurrBound = x >= (_position.x >> FP_SHIFT) && x < ((_position.x + _size.x) >> FP_SHIFT) &&
                               y >= (_position.y >> FP_SHIFT) && y < ((_position.y + _size.y) >> FP_SHIFT);

            uint16_t color;
            if (isCurrBound) {
                int pixelIndex = ((y - (_position.y >> FP_SHIFT)) * (_size.x >> FP_SHIFT)) + (x - (_position.x >> FP_SHIFT));
                color = _sprites[_spriteIndex][pixelIndex];
                if (color == 0x0) { // If transparent, get background
                    color = bg[(SCREENHEIGHT - y - 1) * SCREENWIDTH + x];
                }
            } else if (isPrevBound) {
                color = bg[(SCREENHEIGHT - y - 1) * SCREENWIDTH + x]; // Clear previous position with background
            } else {
                continue; // No need to redraw this pixel
            }
            ST7735_DrawPixel(x, y, color);
        }
    }
    // Update previous position for next frame
    _previousPosition = _position;
}


void PlayerShip::handleInput() {
    if (_inputLeft) {
        _angle -= 15;
        if (_angle < 0) _angle += 360;  // Wrap around to keep angle within range
    }
    if (_inputRight) {
        _angle += 15;
        if (_angle >= 360) _angle -= 360;
    }
    updateSpriteIndex();  // Update sprite based on the new angle
}

void PlayerShip::shoot() {
    int angleIndex = _angle % 360;
    int32_t sin_value = SIN_LUT[angleIndex];
    int32_t cos_value = COS_LUT[angleIndex];
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (!projectiles[i].active) {
                FPVector2D projectileVelocity(cos_value * (PLAYERSPEED << 2) / 1024, -sin_value * (PLAYERSPEED << 2) / 1024);
                projectiles[i].init(_position, projectileVelocity, bullet);
                break;
            }
        }
    }

void PlayerShip::updateProjectiles(const uint16_t* bg) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) {
            projectiles[i].clear(bg);
            projectiles[i].update();
            projectiles[i].draw(bg);
        }
    }
}
