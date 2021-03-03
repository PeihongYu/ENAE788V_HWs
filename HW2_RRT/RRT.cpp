//
// Created by Peihong Yu on 3/2/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>

#include "graph.h"
#include "vector2d.h"
#include "obstacle.h"

bool reachGoalRegion(double x, double y, double * goalRegion)
{
    // goalRegion: (x,y,radius)
    double curDistance = sqrt(pow(goalRegion[0] - x, 2) + pow(goalRegion[1] - y, 2));
    std::cout << ">>>>" << x << ", " << y << ";  distance to goal: " << curDistance << std::endl;

    if(curDistance < goalRegion[2])
        return true;
    else
        return false;
}


int main()
{
    std::string root_path = "../test_cases";
    std::string obstacle_file = "../obstacles.txt";
    ObstacleList obslist;
    obslist.readObstacleFromFile(obstacle_file.c_str());

    // problem 1
//    int test_id = 1;
//    double start[2] = {0, 0};
//    double goalRegion[3] = {-38, 20, 10};  //x,y,radius
//    double epsilon = 10;
    // problem 2
//    int test_id = 2;
//    double start[2] = {27, 30};
//    double goalRegion[3] = {-48, 20, 10};  //x,y,radius
//    double epsilon = 5;
    // problem 3
//    int test_id = 3;
//    double start[2] = {45, -45};
//    double goalRegion[3] = {-45, 45, 15};  //x,y,radius
//    double epsilon = 5;
    // problem 4
//    int test_id = 4;
//    double start[2] = {-16, 10};
//    double goalRegion[3] = {18, -45, 5};  //x,y,radius
//    double epsilon = 2;
    // problem 5
    int test_id = 5;
    double start[2] = {39, 5};
    double goalRegion[3] = {38, -8, 3};  //x,y,radius
    double epsilon = 1;

    Graph G;
    G.addNode(start[0], start[1], 0);

    Vector2D randomSample, epos;
    epos.x = start[0];
    epos.y = start[1];
    while(!reachGoalRegion(epos.x, epos.y, goalRegion))
    {
        randomSample.x = rand() % 101 - 50;
        randomSample.y = rand() % 101 - 50;

        int nearestNodeId = G.findNearestNodeId(randomSample.x, randomSample.y);
        Vector2D spos(G.nodes[nearestNodeId].x, G.nodes[nearestNodeId].y);
        Vector2D dir = (randomSample - spos);
        if(vectorMag(dir) <= epsilon)
            epos = spos + dir;
        else{
            dir.normalize();
            epos = spos + dir * epsilon;
        }

        if(!obslist.checkCollision(spos, epos))
        {
            G.addNode(epos.x, epos.y, nearestNodeId);
        }
    }

    std::string path_file = root_path + "/output_path_" + std::to_string(test_id) + ".txt";
    std::string tree_file = root_path + "/search_tree_" + std::to_string(test_id) + ".txt";
    Node* goalNode = &G.nodes.back();
    G.savePathToFile(path_file.c_str(), goalNode);
    G.saveSearchTreeToFile(tree_file.c_str());

    return 0;
}