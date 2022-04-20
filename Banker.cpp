#include <iostream>
#include <fstream>
#include <vector>



int numOfProcesses = 0;
int numOfResources = 0;

std::vector<int> resources;
std::vector<std::vector<int>> allocationMatrix;
std::vector<std::vector<int>> maxMatrix;
std::vector<std::vector<int>> need;
std::vector<int> available;
std::vector<bool> finished;
std::vector<int> sequence;



std::vector<int> split(std::string s, std::string delimiter) {
    size_t pos = 0;
    std::string token;
    std::vector<int> temp;

    while((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        temp.push_back(std::stoi(token));
        s.erase(0, pos + delimiter.length());
    }
   return temp;
}


// Reads input file
void readFile() {
    std::ifstream file;
    std::string line;


    file.open("system.txt");
    while(getline(file, line)) {

        if(line == "Resources") {
            getline(file, line);
            resources = split(line, " ");
            numOfResources = int(resources.size() + 1);

        } else if(line == "Allocation Matrix") {
            getline(file, line);
            while(!line.empty()) {
                numOfProcesses++;
                std::vector<int> row = split(line, " ");
                allocationMatrix.push_back(row);
                getline(file, line);
            }

        } else if(line == "Max Matrix") {
            getline(file, line);
            while(!line.empty()) {
                std::vector<int> row = split(line, " ");
                maxMatrix.push_back(row);
                getline(file, line);
            }

        } else if(line == "Available") {
            getline(file, line);
            available = split(line, " ");
        }
    }
    file.close();
}



// Return is system is safe
void isSafe() {
    std::vector<int> work;

    // Init sequence
    for(int i = 0; i < numOfProcesses; i++) {
        sequence.push_back(0);
    }

    // Initializes work = available
    for(int i = 0; i < numOfResources; i++) {
        work.push_back(available[i]);
    }

    // Initilizes all processes to not finished
    for(int i = 0; i < numOfProcesses; i++) {
        finished.push_back(false);
    }

    int c = 0;
    while(c < numOfProcesses) {
        bool canAllocate = false;

        for(int i = 0; i < numOfProcesses; i++) {

            if(finished[i] == false) {
                int j = 0;
                while (j < numOfResources) {
                    if(work[j] < need[i][j]) {
                        break;
                    }
                    j++;
                }

                if(j == numOfResources) {
                    for(int j = 0; j < numOfResources; j++) {
                        work[j] += allocationMatrix[i][j];
                    }

                    sequence[c++] = i;
                    finished[i] = true;
                    canAllocate = true;
                }
            }
        }
        if(canAllocate == false) {
            std::cout << "System is not safe. \n";
            return;
        }
    }
    std::cout << "System is safe\n";
    std::cout << "Safe sequence: ";
    for(int i = 0; i < numOfProcesses; i++) {
        std::cout << sequence[i] << " ";
    }
    std::cout << "\n";
}



int main() {

    readFile();

    // Calculate the number of needed instances
    for(int i = 0; i < numOfProcesses; i++) {
        std::vector<int> tempj;
        for(int j = 0; j < numOfResources; j++) {
            tempj.push_back(maxMatrix[i][j] - allocationMatrix[i][j]);
        }
        need.push_back(tempj);
    }

    isSafe();
}