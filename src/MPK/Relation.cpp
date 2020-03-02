#include "Relation.hpp"
#include <algorithm>
void Relation::addStop(Stop *stop, bool count)
{
    stops.push_back(stop);
    if (count)
    {
        stop->relations.push_back(this);
    }
}

std::vector<Vector2i> Relation::getPoints()
{
    std::vector<Vector2i> points = std::vector<Vector2i>();

    Vector2i firstOutputDir, prevOutputDir;

    for (size_t i = 0; i < stops.size() - 1; i++)
    {
        Stop *current = stops[i];
        Stop *next = stops[i + 1];
        auto currentMatch = std::find(current->relations.begin(), current->relations.end(), this);
        auto nextMatch = std::find(next->relations.begin(), next->relations.end(), this);

        int currentStopNth = currentMatch - current->relations.begin();
        int nextStopNth = nextMatch - next->relations.begin();
        prevOutputDir = addPointsForPositions(
            points,
            current->position.add(Vector2i(0, currentStopNth * 15)),
            next->position.add(Vector2i(0, nextStopNth * 15)),
            prevOutputDir);
    }

    Stop *lastStop = stops[stops.size() - 1];
    auto stopMatch = std::find(lastStop->relations.begin(), lastStop->relations.end(), this);
    int stopNth = stopMatch - lastStop->relations.begin();
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

std::vector<Vector2i> Relation::getSubPoints(int start, int length)
{
    std::vector<Vector2i> points = getPoints();
    std::vector<Vector2i> subPoints = std::vector<Vector2i>();

    float travelledLength = 0;
    size_t startIndex = 0;

    while (travelledLength < start)
    {
        Vector2i prev = points[startIndex];
        Vector2i next = points[startIndex + 1];
        float distance = prev.sub(next).length();
        travelledLength += distance;
        startIndex++;
    }

    size_t endIndex = startIndex+1;

    while (travelledLength < start+length)
    {
        Vector2i prev = points[startIndex];
        Vector2i next = points[startIndex + 1];
        float distance = prev.sub(next).length();
        travelledLength += distance;
    }


}
