#pragma once

#include "Vec2.h"
#include <SFML/Graphics.hpp>

class CTransform
{
public:
    Vec2 pos = {0.0, 0.0};
    Vec2 vel = {0.0, 0.0};
    float angle = 0;

    CTransform(const Vec2 &pos, const Vec2 &vel, float angle)
        : pos(pos), vel(vel), angle(angle) {}
};

class CShape
{
public:
    sf::CircleShape circle;
    CShape(float radius, int points, const sf::Color &fill, const sf::Color &outline, float thickness)
        : circle(radius, points)
    {

        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

class CCollider
{
public:
    float radius = 0;
    CCollider(float radius) : radius(radius)
    {
    }
};

class CScore
{
public:
    int score = 0;
    CScore(int score) : score(score) {}
};

class CLifespan
{
public:
    int remaining = 0;
    int total = 0;
    CLifespan(int total) : remaining(total), total(total) {}
};

class CInput
{
public:
    bool up = false;
    bool left = false;
    bool down = false;
    bool right = false;
    bool shot = false;

    CInput() {}
};
