#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <iostream>
#include <vector>
#include <limits.h>
#include <stdio.h>

struct Vertex {
    std::pair<int,int> coords;
    int distance;

    Vertex(int, int, int);
    Vertex();
};

class PathFinder {
    private:
        std::vector<std::vector<char>> maze;

        Vertex start;
        Vertex destination;

        std::vector<Vertex> visited;
        std::vector<Vertex> adjacent;

        std::vector<Vertex> getAdjacents(Vertex vertex);
        void addAdjacents(Vertex vertex);
        void addVisited(Vertex v);
        int getVisitedDistanceFromCoords(int, int);
        bool hasVisitedCharacter(char);

    public:
        PathFinder(std::vector<std::vector<char>> mazeVec);
        PathFinder();
        
        void setMaze(std::vector<std::vector<char>>);
        void setStart();
        void setDestination();
        void printMaze();
        bool isViable();
        int computeShortestPath();
        bool hasMazeSet();
};

#endif