/*
Copyright 2018, Michael Otte

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string>
#include <iostream>

#include "heap.h"
#include "heap.cpp"

#include "graph.h"

//Algorithms: Dijkstra, A_star
std::string ALGORITHM = "A_star";

// returns random number between 0 and 1
float rand_f()
{
    return (float)rand() / (float)RAND_MAX;
}


// does the node expand operation (note: we are
// using a very dumb random walk)
void expand(Heap<Node> &H, Node* thisNode, double thisNodeCost, Node* goalNode)
{
    for(int n = 0; n < thisNode->numOutgoingEdges; n++)
    {
        Edge* thisEdge = thisNode->outgoingEdges[n];  // pointer to this edge
        Node* neighborNode = thisEdge->endNode;  // pointer to the node on the
        double heuristic = 0;
        double thisNodeHeuristic = 0;
        if(ALGORITHM == "A_star") {
            heuristic = sqrt(pow(neighborNode->x - goalNode->x, 2) + pow(neighborNode->y - goalNode->y, 2));
            thisNodeHeuristic = sqrt(pow(thisNode->x - goalNode->x, 2) + pow(thisNode->y - goalNode->y, 2));
        }
        double thisNodeCostToStart = thisNodeCost - thisNodeHeuristic;
        // other end of this edge

        if(neighborNode->status == 0)  // neighbor has not yet been visited
        {
            // add the neighbor to the heap (with a random key)
            // double neighborKey = rand_f();
            double neighborKey = thisNodeCostToStart + thisEdge->edgeCost + heuristic;
            H.addToHeap(neighborNode, neighborKey);

            // remember this node as its parent
            neighborNode->parentNode = thisNode;

            // make sure it is in the open list
            neighborNode->status = 1;
        }
        else if(neighborNode->status == 1)  // neighbor is in the open list
        {                                   // (but not the closed list)
            if(H.heapCost[neighborNode->heapIndex] > thisNodeCostToStart + thisEdge->edgeCost + heuristic)
            {
//                std::cout << H.heapCost[neighborNode->heapIndex] << std::endl;
//                std::cout << cost_to_start << ";   " << thisEdge->edgeCost << std::endl;
                double newNeighborKey = thisNodeCostToStart + thisEdge->edgeCost + heuristic;
                H.updateNodeInHeap(neighborNode, newNeighborKey);

                // remember this node as its parent
                neighborNode->parentNode = thisNode;
            }
        }
    }

    thisNode->status = 2;    // now this node is in the closed list
}



int main()
{
    int start_ids[5] = {9, 88, 30, 38, 38};
    int end_ids[5] = {5, 9, 95, 502, 5002};

    std::string root_path = "../test_cases";
    int test_id = 1;
    std::string nodes_file = root_path + "/nodes_" + std::to_string(test_id) + ".txt";
    std::string edges_file = root_path + "/edges_with_costs_" + std::to_string(test_id) + ".txt";

    srand(time(NULL)); // seed random number generator
    Graph G;
    G.readGraphFromFiles(nodes_file.c_str(), edges_file.c_str());
    // G.printGraph();

    // we want to find a path that goes from here to here
    int startNodeIndex = start_ids[test_id-1] - 1;
    int goalNodeIndex = end_ids[test_id-1] - 1;

    Heap<Node> H(100); // this is the heap (start's with space for 100 items
    // but will grow automatically as needed).

    // these are pointers to the start and end nodes
    Node* startNode = &G.nodes[startNodeIndex];
    Node* goalNode = &G.nodes[goalNodeIndex];

    // we'll do a random walk search, but we'll do it
    // by assigning nodes a random key in the heap
    // this way it can be showen how the heap works

    // double key = rand_f();
    double key = 0;
    if(ALGORITHM == "A_star")
        key += sqrt(pow(startNode->x - goalNode->x, 2) + pow(startNode->y - goalNode->y, 2));
    H.addToHeap(startNode, key);
    H.printHeap();
    startNode->status = 1;    // now the start node is in the open list

    // while there are nodes left in the heap
    // (note that a better stopping criteria should be used in
    // most "real" algorithms, but this will cause us to generate
    // a random spanning tree over the graph, which is kind of cool)
    while(H.topHeap() != NULL)
    {
        double cost_to_start = H.heapCost[0];
        Node* thisNode = H.popHeap();
        thisNode->status = 2;

        std::cout << "after pop" << std::endl;
        H.printHeap();

        if(thisNode == goalNode)
            break;

        expand(H, thisNode, cost_to_start, goalNode);
        std::cout << "after expand" << std::endl;
        H.printHeap();
    }

    // now we want to save files that contain the search tree that we build
    // and also the best path that we found (NOTE, these add 1 to indicies
    // to make them compativle with the graph file that was used as input for
    // the search)


    std::string path_file = root_path + "/output_path_" + std::to_string(test_id) + "_" + ALGORITHM + ".txt";
    std::string tree_file = root_path + "/search_tree_" + std::to_string(test_id) + "_" + ALGORITHM + ".txt";
    G.savePathToFile(path_file.c_str(), goalNode);
    G.saveSearchTreeToFile(tree_file.c_str());

    return 0;
}
