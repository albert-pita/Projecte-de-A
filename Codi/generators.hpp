
#ifndef GENERATORS_HH
#define GENERATORS_HH

#include <vector>
#include <cmath>

#include "utilities.hpp"

typedef std::vector<std::vector<unsigned int>> Graph;
typedef std::pair<double, double> Coord;

/* ----- Random Binomial Graph Generator ----- */

static void generate_RBG(Graph& graph, unsigned int n, double p)
{
    graph = Graph(n);

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = i+1; j < n; j++)
        {
            double v = getRandomDouble();
            if (v < p)
            {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
}

/* ----- Random Geometric Graph Generator ----- */

static double distance(const Coord& c1, const Coord& c2)
{
    double x = std::pow(c1.first-c2.first, 2);
    double y = std::pow(c1.second-c2.second, 2);

    return x+y;
}

static void generate_RGG(Graph& graph, unsigned int n, double r)
{
    graph = Graph(n);
    std::vector<Coord> coords(n);

    for(unsigned int i = 0; i < n; i++)
    {
        coords[i] = Coord(getRandomDouble(), getRandomDouble());
    }

    for(unsigned int i = 0; i < n; i++)
    {
        for(unsigned int j = i+1; j < n; j++)
        {
            if(distance(coords[i], coords[j]) < r*r)
            {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
}

#endif
