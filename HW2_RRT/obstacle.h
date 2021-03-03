//
// Created by Peihong Yu on 3/2/21.
//

#ifndef RRT_SEARCH_OBSTACLE_H
#define RRT_SEARCH_OBSTACLE_H

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

#include "vector2d.h"

struct disc
{
    Vector2D center;
    double radius;
};

class ObstacleList
{
public:
    std::vector<disc> obstacleList;

    void readObstacleFromFile(const char* filename)
    {
        FILE * pFile;
        int numObstacles = 0;
        float x, y, r;

        // open the obstacle file
        pFile = fopen (filename , "r");
        if(pFile==NULL)
        {
            printf("unable to open file %s\n", filename);
            return;
        }

        // read the number of obstacles
        if(fscanf(pFile, "%d\n", &numObstacles) < 1)
        {
            printf("problem reading obstacles number from file\n");
            return;
        }

        obstacleList.resize(numObstacles);

        // now read the obstacles one at a time
        for(int n = 0; n < numObstacles; n++)
        {
            if(fscanf(pFile, "%f, %f, %f\n", &x, &y, &r) < 3)
            {
                printf("problem reading the %d-th node from file\n",n);
                return;
            }
            // allocate the node
            obstacleList[n].center.x = x;
            obstacleList[n].center.y = y;
            obstacleList[n].radius = r;

            // printf("read node: [(%f, %f), %f] from file\n", obstacleList[n].x, obstacleList[n].y, obstacleList[n].r);
        }

        // close the node file
        fclose(pFile);
    }

    // Reference: https://blog.csdn.net/SongBai1997/article/details/86599879
    bool checkCollision(Vector2D start, Vector2D end)
    {
        for(int i = 0; i < obstacleList.size(); i++) {
            if (distance(end, obstacleList[i].center) < obstacleList[i].radius)
                return true;
            else {
                double A, B, C, dist1, dist2, angle1, angle2;
                A = start.y - end.y;
                B = end.x - start.x;
                C = start.x * end.y - end.x * start.y;
                dist1 = A * obstacleList[i].center.x + B * obstacleList[i].center.y + C;
                dist1 *= dist1;
                dist2 = (A * A + B * B) * obstacleList[i].radius * obstacleList[i].radius;
                if (dist1 < dist2) {
                    angle1 = (obstacleList[i].center.x - start.x) * (end.x - start.x) +
                             (obstacleList[i].center.y - start.y) * (end.y - start.y);
                    angle2 = (obstacleList[i].center.x - end.x) * (start.x - end.x) +
                             (obstacleList[i].center.y - end.y) * (start.y - end.y);
                    if (angle1 > 0 && angle2 > 0)
                        return true;
                }
            }
        }
        return false;
    }


};




#endif //RRT_SEARCH_OBSTACLE_H
