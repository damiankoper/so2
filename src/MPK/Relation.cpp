#include "Relation.hpp"

std::vector<Vector2i> Relation::getPoints()
{
    int shift = 40;
    std::vector<Vector2i> points = std::vector<Vector2i>();

    for (size_t i = 1; i < stops.size() - 1; i++)
    {
        Stop *current = stops[i];
        Stop *next = stops[i + 1];

        // Horizontal
        if (abs(current->position.x - next->position.x) <= abs(current->position.y - next->position.y))
        {
            points.push_back(Vector2i(current->position.x - shift, current->position.y));
            points.push_back(Vector2i(current->position.x + shift, current->position.y));
        }
        // Vertical
        else
        {
            points.push_back(Vector2i(current->position.x, current->position.y - shift));
            points.push_back(Vector2i(current->position.x, current->position.y + shift));
        }
    }
    return points;
}