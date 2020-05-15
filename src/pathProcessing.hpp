#ifndef PATHPROCESSING_HPP
#define PATHPROCESSING_HPP

#define INF 999999

#include <iomanip>
#include <queue>

#include "./adjacencyList.hpp"
#include "./linkedList.hpp"
#include "./structs/edge.hpp"
#include "./structs/embarkData.hpp"
#include "./structs/path.hpp"
#include "./structs/vert.hpp"

class PathProcessing {
    private:
        bool isNotVisited(vert* x, Path path) { 
            for (int i = 0; i < path.verts.size(); i++)  
                if (path.verts[i] == x->name)  
                    return false;  
            return true; 
        } 

    public:
        std::vector<Path> findPaths(AdjacencyList graph, embarkData trip) {
            std::queue<Path> q;
            std::vector<Path> paths;

            Path path;
            path.c = path.t = 0;
            path.verts.push_back(trip.origin);
            q.push(path);
            while (!q.empty()) {
                path = q.front();
                q.pop();
                std::string last = path.verts[path.verts.size() - 1];

                if (last == trip.dest) {
                    paths.push_back(path);
                }
                for(int i = 0; i < graph.find(last)->edges.size(); i++) {
                    edge* e = graph.find(last)->edges.findIndex(i);
                    vert* v = graph.find(e->name);
                    if (isNotVisited(v, path)) {
                        Path newPath;
                        newPath.verts = path.verts;
                        newPath.c += e->c;
                        newPath.t += e->t;
                        newPath.verts.push_back(v->name);
                        q.push(newPath);
                    }   
                }
            }
            return paths;
        }
        /**
        std::vector<Path> fW (AdjacencyList graph, embarkData trip) {
            std::vector<std::string> allVerts = graph.getAllVerts();
            std::vector<Path> paths;

            int i, j, k;
            int numV = allVerts.size();
            
            float dist[numV][numV], cost[numV][numV];

            // convert sorted adjList to matrix
            for (i = 0; i < numV; i++) { // row
                for (j = 0; j < numV; j++) { // col
                    if (i == j) {
                        cost[i][j] = dist[i][j] = 0;
                    } else {
                        vert *o = graph.find(allVerts[i]);
                        edge *curEdge = o->edges.firstEdge();
                        while (curEdge != NULL) {
                            if (curEdge->name == allVerts[j]) {
                                dist[i][j] = curEdge->t;
                                cost[i][j] = curEdge->c;
                                if (allVerts[i] == trip.origin && allVerts[j] == trip.dest) {
                                    Path newPath;
                                    newPath.verts.push_back(trip.origin);
                                    newPath.verts.push_back(trip.dest);
                                    newPath.t = dist[i][j];
                                    newPath.c = cost[i][j];
                                    paths.push_back(newPath);
                                }
                                
                                break;
                            } else {
                                curEdge = curEdge->next;
                            }
                            dist[i][j] = INF;
                            cost[i][j] = INF;
                        }    
                    }
                }
            }

            // END convert sorted adjList to matrix
            int firstTwoNodesCost, firstTwoNodesDist;
            firstTwoNodesCost = firstTwoNodesDist = 0;
            std::string currentVert = trip.origin;
            vert *cur, *intermed;
            std::vector<std::string> interVerts;
            for (k = 0; k < numV; k++) {
                intermed = graph.find(allVerts[k]);
                for (i = 0; i < numV; i++) {
                    cur = graph.find(allVerts[i]);
                    for (j = 0; j < numV; j++) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                        if (cost[i][k] + cost[k][j] < cost[i][j]) {
                            cost[i][j] = cost[i][k] + cost[k][j];
                        }
                        if (i != j && allVerts[k] != trip.origin && allVerts[k] != trip.dest && allVerts[i] == currentVert && allVerts[j] == trip.dest && cur != NULL && cur->edges.hasEdge(allVerts[k]) && intermed->edges.hasEdge(trip.dest)) {
                            std::cout << allVerts[k] << std::endl;
                            firstTwoNodesDist += dist[i][k];
                            firstTwoNodesCost += cost[i][k];
                            
                            Path newPath;
                            newPath.verts.push_back(trip.origin);
                            
                            currentVert = allVerts[k];
                            interVerts.push_back(allVerts[k]);
                            
                            for (int l = 0; l < interVerts.size(); l++) {
                                newPath.verts.push_back(interVerts[l]);
                            }                        
                            newPath.verts.push_back(trip.dest);
                            
                            if (newPath.verts.size() <= 2) {
                                newPath.t = dist[i][j];
                                newPath.c = cost[i][j];
                            } else {
                                newPath.t = firstTwoNodesDist + dist[k][j];
                                newPath.c = firstTwoNodesCost + cost[k][j];                                
                            }
                            paths.push_back(newPath);
                        }
                    }
                }
            }
            return paths;
        }
        */
};
#endif