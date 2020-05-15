#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "./adjacencyList.hpp"
#include "./pathProcessing.hpp"
#include "./quickSort.hpp"
#include "./structs/embarkData.hpp"
#include "./structs/flightData.hpp"


using namespace std;

AdjacencyList buildAdjList(fstream&);
vector<embarkData> parsePaths(fstream&, AdjacencyList);

int main(int argc, char** argv) {
    fstream flightsData, desiredPaths, output;
    PathProcessing graphProcessing;
    vector<Path> paths;
  
    if (argc != 4) {
        cout << "You have entered " << argc << " arguments" << endl; 
        cout << "Please format run command correctly. Command should look like:" << endl;
        cout << "\"./flightPlan <./path/to/FlightDataFile> <./path/to/CalculateFile> <OutputFile>\"" << endl;
    } else {
        flightsData.open(argv[1]);
        desiredPaths.open(argv[2]);
        output.open(argv[3], ios::out);
    }
    QuickSort qSort;

    AdjacencyList graph = buildAdjList(flightsData);
    graph.display();
    vector<embarkData> tripsData = parsePaths(desiredPaths, graph);
    for (int i = 0; i < tripsData.size(); i++) {
        cout << endl;
        paths = graphProcessing.findPaths(graph, tripsData[i]);
        paths = qSort.sort(paths, tripsData[i].weightType);
        output << "Flight " << i + 1 << ": " << tripsData[i].origin << ", " << tripsData[i].dest << " (" << tripsData[i].weightType << ")\n";
        cout << "Flight " << i + 1 << ": " << tripsData[i].origin << ", " << tripsData[i].dest << " (" << tripsData[i].weightType << ")\n";
        for (int j = 0; j < paths.size() && j < 3; j++) {
            output << "Path " << j + 1 << ": ";
            cout << "Path " << j + 1 << ": ";
            for (int l = 0; l < paths[j].verts.size(); l++) {
                if (l < paths[j].verts.size() - 1) {
                    output << paths[j].verts[l] << " -> ";
                    cout << paths[j].verts[l] << " -> ";

                } else {
                    output << paths[j].verts[l] << ". ";
                    cout << paths[j].verts[l] << ". ";
                }
            }
            output << "Time: " << paths[j].t << " Cost: " << paths[j].c << endl;
            cout << "Time: " << paths[j].t << " Cost: " << paths[j].c << endl;
        }
        output << endl;
    }

    flightsData.close();
    desiredPaths.close();
    output.close();
    return 0; 
}

AdjacencyList buildAdjList(fstream &flightsData) {
    AdjacencyList flightGraph;
    int numPaths = 0;

    if (flightsData.is_open()) {
        string word, origin, destination, line = "";
        int numPaths = 0;

        while(getline(flightsData, line)) {
            word = origin = destination = "";
            float time, cost;
            int inputCounter = 0;

            stringstream lS(line);

            while(getline(lS, word, '|')) {
                switch (inputCounter) {
                    case 0: {
                        if (line == word) {
                            stringstream p(word);
                            p >> numPaths;
                        } else {
                            origin = word;
                            inputCounter++;
                        }
                        break;
                    } case 1: {
                        destination = word;
                        inputCounter++;
                        break;
                    } case 2: {
                        stringstream fs(word);
                        fs >> cost;
                        inputCounter++;
                        break;
                    } case 3: {
                        stringstream fs(word);
                        fs >> time;
                        inputCounter++;
                        break;      
                    } default: {
                        break;
                    }
                }
            }
            if (inputCounter == 4) {
                flightData newFlight = flightData(origin, destination, cost, time);
                flightGraph.insert(newFlight);
                // uncomment next two lines for undirected graph
                flightData newFlightBack = flightData(destination, origin, cost, time);
                flightGraph.insert(newFlightBack); 
            }
        }
    }
    return flightGraph;
}

vector<embarkData> parsePaths(fstream &tripPaths, AdjacencyList graph) {
    vector<embarkData> trips;

    if (tripPaths.is_open()) {
        string word, origin, destination, weightType, line = "";
        int numPathsToCalc = 0;

        while (getline(tripPaths, line)) {
            word = origin = destination = weightType = "";
            int inputCounter = 0;
            stringstream lS(line);

            while (getline(lS, word, '|')) {
                switch (inputCounter) {
                    case 0: 
                        if (line == word) {
                            stringstream p(word);
                            p >> numPathsToCalc;
                        } else {
                            origin = word;
                            inputCounter++;
                        }
                        break;
                    case 1:
                        destination = word;
                        inputCounter++;
                        break;
                    case 2:
                        if (word == "T") {
                            weightType = "Time";
                        } else if (word == "C") {
                            weightType = "Cost";
                        }
                        inputCounter++;
                        break;
                    default:
                        break;
                }
            }
            if (inputCounter == 3) {
                embarkData newToAndFrom = embarkData(origin, destination, weightType);
                trips.push_back(newToAndFrom);
            } 
        }
    }
    return trips;
}