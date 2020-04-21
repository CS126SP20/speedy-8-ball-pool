//
// Created by lilyl on 4/20/2020.
//

#ifndef FINALPROJECT_BOX2D_UTILITY_H
#define FINALPROJECT_BOX2D_UTILITY_H

#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>

namespace myapp {
    const float METERS_TO_POINTS = 100;
    const float POINTS_TO_METERS = 0.01f;

    class Box2DUtility
    {
    public:
        static float metersToPoints(float var) { return var * METERS_TO_POINTS; }
        static vec2 metersToPoints(const vec2& var) { return var * METERS_TO_POINTS; }
        static float pointsToMeters(float var) { return var * POINTS_TO_METERS; }
        static vec2 pointsToMeters(const vec2& var) { return var * POINTS_TO_METERS; }
        static b2Vec2 pointsToMeters(const b2Vec2& var) { return POINTS_TO_METERS * var; }
        static float getPointsPerMeter() { return METERS_TO_POINTS; }
        static float getMetersPerPoint() { return POINTS_TO_METERS; }
        static vec2 toCinder(const b2Vec2& vec) { return vec2(vec.x, vec.y); }
        static Color toCinder(const b2Color& color) { return Color(color.r, color.g, color.b); }
    };
}
#endif //FINALPROJECT_BOX2D_UTILITY_H
