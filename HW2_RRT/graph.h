/*  Copyright Michael Otte, 2018
 *
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  Basic random graph with nodes and edges
 *
 *  Note: that this reads nodes from file with 1-based indexing and
 *  switches node IDs to use 0-based indexing. In other words,
 *  nodes from a file have their IDs reduced by 1 within this code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <vector>

// this is a basic graph node for a 2D graph
struct Node
{
    int id;     // this is the id of the node
    // it is alos the position in the node array in the
    // graph data structure where this node is stored

    double x;   // physical x location
    double y;   // physical y location

    int parentNodeId;      // used for graph search, this is a pointer to this node's parent

};


// this is the graph data structure
class Graph
{
public:
    int numNodes;    // the number of nodes in the graph

    std::vector<Node> nodes;     // an array that contains all of the nodes
    // nodes[i] contains the node with id i

    // default constructor
    Graph()
    {
        printf("building a default graph\n");
        numNodes = 0;
        std::vector<Node> nodes;
    }

    // default destructor
    ~Graph()
    {
        printf("deleting a graph\n");
        if(!nodes.empty())
        {
            nodes.clear();
        }
        numNodes = 0;
    }


    int findNearestNodeId(double x, double y)
    {
        double min_distance = RAND_MAX;
        int min_id = 0;
        for(int i = 0; i < nodes.size(); i++)
        {
            double cur_distance = sqrt(pow(nodes[i].x - x, 2) + pow(nodes[i].y - y, 2));
            if(cur_distance < min_distance)
            {
                min_distance = cur_distance;
                min_id = i;
            }
        }
        return min_id;
    }

    void addNode(double x, double y, int id)
    {
        // create node
        Node tempNode;
        tempNode.id = numNodes;  // NOTE: switches to c++ 0-based indexing!!!
        tempNode.x = x;
        tempNode.y = y;

        if(nodes.empty())
        {
            tempNode.parentNodeId = numNodes;
            nodes.push_back(tempNode);
        }
        else
        {
            tempNode.parentNodeId = id;
            nodes.push_back(tempNode);

        }
        if(tempNode.parentNodeId == tempNode.id)
            std::cout << "new node: " << tempNode.id << ", " << tempNode.x << ", " << tempNode.y << "; no parent" << std::endl;
        else
            std::cout << "new node: " << tempNode.id << ", " << tempNode.x << ", " << tempNode.y << "; parent: " << tempNode.parentNodeId << std::endl;
        numNodes ++;
    }


    // saves the path to a file, extracts it backward from the goal node
    // note that 1 is added to the indicies so that the result is compatible
    // with any 1-indexed input files that may have been used
    // returns true on success
    bool savePathToFile(const char* pathFile, Node* goalNode)
    {
        FILE * pFile = fopen(pathFile,"w");
        if(pFile == NULL)
        {
            return false;
        }

        Node* thisNode = goalNode;
        while(thisNode->parentNodeId != thisNode->id)
        {
            // format is id, x, y
            // NOTE: incrimenting ids by 1 to convert to 1-based-indexing
            fprintf(pFile, "%d, %f, %f\n",thisNode->id+1, float(thisNode->x), float(thisNode->y));
            thisNode = &nodes[thisNode->parentNodeId];
        }
        fprintf(pFile, "%d, %f, %f\n",thisNode->id+1, float(thisNode->x), float(thisNode->y));

        fclose(pFile);
        printf("saved path in %s\n", pathFile);

        return true;
    }


    // saves the search tree to a file
    // note that 1 is added to the indicies so that the result is compatible
    // with any 1-indexed input files that may have been used
    // returns true on success
    bool saveSearchTreeToFile(const char* searchTreeFile)
    {
        FILE * pFile = fopen(searchTreeFile,"w");
        if(pFile == NULL)
        {
            return false;
        }

        for(int n = 0; n < numNodes; n++)
        {
            Node* thisNode = &nodes[n];
            if(thisNode->parentNodeId != thisNode->id)
            {
                // format is id1, x1, y1, id2, x2, y2
                // NOTE: incrimenting ids by 1 to convert to 1-based-indexing
                Node* parentNode = &nodes[thisNode->parentNodeId];
                fprintf(pFile, "%d, %f, %f, %d, %f, %f\n",
                        thisNode->id+1, thisNode->x, thisNode->y,
                        parentNode ->id+1, parentNode->x, parentNode->y);
            }
        }
        fclose(pFile);
        printf("saved search tree in %s\n", searchTreeFile);

        return true;
    }


};








