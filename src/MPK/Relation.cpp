#include "Relation.hpp"

void Relation::addStop(Stop *stop, bool count)
{
    stops.push_back(stop);
    if (count)
    {
        stop->relationsCount++;
    }
}

/* Vector2i Relation::getNthShift(int nth)
{
} */

std::vector<Vector2i> Relation::getPoints(int nth)
{
    std::vector<Vector2i> points = std::vector<Vector2i>();

    Vector2i firstOutputDir, prevOutputDir;

    for (size_t i = 0; i < stops.size() - 1; i++)
    {
        Stop *current = stops[i];
        Stop *next = stops[i + 1];
        int currentStopNth = std::min(nth, current->relationsCount - 1);
        int nextStopNth = std::min(nth, next->relationsCount - 1);
        prevOutputDir = addPointsForPositions(
            points,
            current->position.add(Vector2i(0, currentStopNth * 15)),
            next->position.add(Vector2i(0, nextStopNth * 15)),
            prevOutputDir);
    }

    int stopNth = std::min(nth, stops[stops.size() - 1]->relationsCount);
    points.push_back(stops[stops.size() - 1]->position.add(Vector2i(0, stopNth * 15)));
    return points;
}

Vector2i Relation::addPointsForPositions(
    std::vector<Vector2i> &points,
    Vector2i from,
    Vector2i to,
    Vector2i prevOutputDirection)
{
    int minShift = 40;
    int deltaX = to.x - from.x;
    int sX = deltaX == 0 ? 0 : deltaX < 0 ? -1 : 1;
    int deltaY = to.y - from.y;
    int sY = deltaY == 0 ? 0 : deltaY < 0 ? -1 : 1;

    if (prevOutputDirection.length() == 0)
    {
        prevOutputDirection = Vector2i(sX, 0);
    }

    points.push_back(Vector2i(from.x, from.y));

    // Horizontal
    if (deltaY == 0 && sX == prevOutputDirection.x)
    {
        return prevOutputDirection;
    }
    // Horizontal same Y U-turn
    else if (deltaY == 0 && sX != prevOutputDirection.x)
    {
        addPointsForPositions(
            points,
            Vector2i(from.x, from.y),
            Vector2i(from.x, from.y - 3 * minShift),
            prevOutputDirection);

        return addPointsForPositions(
            points,
            Vector2i(from.x, from.y - 3 * minShift),
            Vector2i(to.x, to.y),
            -prevOutputDirection);
    }
    // Horizontal curve
    else if (abs(deltaX) > abs(deltaY) + 2 * minShift && sX == prevOutputDirection.x)
    {
        // current out
        points.push_back(Vector2i(from.x + (minShift * prevOutputDirection.x), from.y));

        //next in
        points.push_back(Vector2i(from.x + (minShift + abs(deltaY)) * prevOutputDirection.x, to.y));

        return prevOutputDirection;
    }
    // Horizontal to horizontal vertical - U-turn
    else if (abs(deltaX) <= abs(deltaY) + 2 * minShift || (deltaX * prevOutputDirection.x < 0))
    {
        if (deltaX * prevOutputDirection.x > 0)
        {
            return addPointsForPositions(points, Vector2i(to.x, from.y), to, prevOutputDirection);
        }
        else if (deltaX * prevOutputDirection.x < 0)
        {
            return addPointsForPositions(points, from, Vector2i(from.x, to.y), prevOutputDirection);
        }
        else if (deltaX == 0)
        {
            // current out
            points.push_back(Vector2i(from.x + minShift * prevOutputDirection.x, from.y));

            // current out turn 1
            points.push_back(Vector2i(
                from.x + (2 * minShift * prevOutputDirection.x),
                from.y + (minShift * sY)));

            // current out turn 2
            points.push_back(Vector2i(
                from.x + (2 * minShift * prevOutputDirection.x),
                to.y + (minShift * sY * -1)));

            //next in
            points.push_back(Vector2i(to.x + (minShift * prevOutputDirection.x), to.y));

            return -prevOutputDirection;
        }
    }

    return prevOutputDirection;
}
