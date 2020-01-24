
#ifndef UTILITIES_HH
#define UTILITIES_HH

#include <iostream>
#include <stack>
#include <queue>
#include <random>
#include <ctime>

typedef std::vector<std::vector<unsigned int>> Graph;

/* ----- Random Generator ----- */

static std::mt19937 randomEngine(time(NULL));
static std::uniform_real_distribution<double> distribution(0.0, 1.0);

static double getRandomDouble()
{
    return distribution(randomEngine);
}

/* ----- Property Checkers ----- */

static void property_connectedComponents(const Graph& graph, unsigned int &cc, unsigned int &lcc)
{
    int n = graph.size();
    cc = lcc = 0;

    std::vector<bool> visited(n, false);
    std::stack<int> stack;

    for (unsigned int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            cc++;
            stack.push(i);

            int size = 0;
            while (!stack.empty())
            {
                int v = stack.top();
                stack.pop();
                if (!visited[v])
                {
                    visited[v] = true;
                    size++;
                    for (int i = 0; i < graph[v].size(); ++i)
                    {
                        stack.push(graph[v][i]);
                    }
                }
            }

            if (size > lcc) lcc = size;
        }
    }
}

    // TO DO: Faltaria fer que, si un graf no es connex o es nota alguna desconnexió, directament surti sense comprovar
    // la resta, donant com a d = -1 o algo semblant, per aixi no haver de comprovar-ho tot. Potser comprovant si es o
    // connex abans de fer el BFS serviria. 

static void BFS(const Graph& graph, unsigned int node_i, unsigned int& d) 
{
    unsigned int n = graph.size();
    std::vector<bool> visited(n);
    std::queue<unsigned int> queue;

    std::vector<unsigned int> dist(n);

    for (unsigned int i = 0; i < n; i++)
	{
        visited[i] = false;
        dist[i] = -1;
    }

    d = 0;

    visited[node_i] = true;
    dist[node_i] = 0;
    queue.push(node_i);

    while (!queue.empty())
	{
        unsigned int u = queue.front();
        queue.pop();
        for (unsigned int i = 0; i < graph[u].size(); i++)
		{
            if (visited[graph[u][i]] == false)
			{
                visited[graph[u][i]] = true;
                dist[graph[u][i]] = dist[u] + 1;
                if (dist[graph[u][i]] > d) d = dist[graph[u][i]];
                queue.push(graph[u][i]);
            }
        }
    }
}

static void property_diameter(const Graph& graph, unsigned int& d)
{
    unsigned int n = graph.size();
    d = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        unsigned int td = 0;
        BFS(graph, i, td);
        if (td > d) d = td;
    }
}

/* ----- Graph IO ----- */

static void printGraph(const Graph& graph)
{
    std::cout << "vertex\tadjecencies" << std::endl;
    for(unsigned int i = 0; i < graph.size(); i++)
    {
        std::cout << i << '\t';
        for(unsigned int j = 0; j < graph[i].size(); j++)
        {
            std::cout << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

#endif
