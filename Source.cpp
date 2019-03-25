#include <chrono>
#include "Node.h"
#include "AStarSearch.h"
#pragma warning(disable:4996)
#define MAX 105

int operations(const char*,bool,bool,bool,int);
void printSolution(aStarSearch &starSearch, const Node &Start, const Node &Goal) {
	auto now = Goal;
	vector<Node> Path;
	while (starSearch.visited[now].parent_ != EOF) {
		Path.push_back(now);
		now = now.getNode(starSearch.visited[now].parent_);
	}
	Path.push_back(Start);
	reverse(Path.begin(), Path.end());
	for (auto &i : Path) cout << i;
}

void executeSearch(const Node &Start, const Node &Goal, int heuristic,
	bool solseqCommandConfig,bool pcostCommandConfig,bool nvisitedCommandConfig) {

	auto *starSearch = new aStarSearch();
	starSearch->setHeuristic(heuristic);
	int nExpanded = starSearch->AStarSearch(Start, Goal);

	if(pcostCommandConfig)
		cout << "Number of steps: " << (int)starSearch->visited[Goal].cost_ << endl;
	if(nvisitedCommandConfig)
        cout << "Number of Nodes visited: " << nExpanded << endl;
	fflush(stdout);

	if (solseqCommandConfig) printSolution(*starSearch, Start, Goal);
	delete starSearch;
}


int main(int argc, char* argv[]) {
	char inputCommand[] = "-input";
	bool input = true;
	char solseqCommand[] = "-solseq";
	bool solseqCommandConfig = false;
	char pcostCommand[] = "-pcost";
	bool pcostCommandConfig = false;
	char nvisitedCommand[] = "-nvisited";
	bool nvisitedCommandConfig = false;
	char hCommand[] = "-h";
	int h = 0;
	//std::cout << "You have entered " << argc
	//	<< " arguments:" << "\n";
	if (argc < 2) {
		std::cout << "Not enough paramters";
		return 0;
	}
	if (argc > 8) {
		std::cout << "Too many paramters";
		return 0;
	}

	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], solseqCommand) == 0) {
			//std::cout << "-solseqCommand\n";
			solseqCommandConfig = true;
		}
		else if (strcmp(argv[i], pcostCommand) == 0) {
			//std::cout << "-pcostCommand\n";
			pcostCommandConfig = true;
		}
		else if (strcmp(argv[i], nvisitedCommand) == 0) {
			//std::cout << "-nvisitedCommand\n";
			nvisitedCommandConfig = true;
		}
		else if (strcmp(argv[i], hCommand) == 0) {
			//std::cout << "-hCommand\n";
			if (argc >= (i + 1)) {
				char oneHeuristic[] = "1";
				char twoHeuristic[] = "2";

				if (strcmp(argv[i + 1], oneHeuristic) != 0 && strcmp(argv[i + 1], twoHeuristic) != 0) {
					std::cout << "Choose one heuristic out of the two " << oneHeuristic << " " << twoHeuristic << endl;
					return 0;
				}
				else {
					string converter(argv[i + 1]);
					h = stoi(converter);
				}
			}
			else {
				std::cout << "Wrong command Config example:\n";
				return 0;
			}
		}
	}



	if (strcmp(argv[1], inputCommand) == 0) {
		operations(argv[2],solseqCommandConfig,pcostCommandConfig,nvisitedCommandConfig,h);
	}
	else
	{
		operations("", solseqCommandConfig, pcostCommandConfig, nvisitedCommandConfig, h);
	}
	return 0;
}
int operations(const char* filename, bool solseqCommandConfig, bool pcostCommandConfig, bool nvisitedCommandConfig,
	int heuristicConfig) {
	const char* tempFileName = "";
	if (strcmp(filename, tempFileName) != 0) {
		freopen(filename, "r", stdin);
	}
	else
	{
		std::cout << "Enter the puzzle for example \n3\n1 0 4\n5 6 7\n8 2 3\nYour puzzle:\n";
	}
	int boardSqSize = 3;
	cin >> boardSqSize;
	Node::boardSqSize = boardSqSize;

	Node Goal;
	for (int i = 0; i < boardSqSize; i++)
		for (int j = 0; j < boardSqSize; j++)
			Goal.A[i][j] = static_cast<puzzle_t>(i * Node::boardSqSize + j + 1);
	Goal.A[Node::boardSqSize - 1][Node::boardSqSize - 1] = 0;

	Node Start;
	int x;
	for (int i = 0; i < boardSqSize; i++)
		for (int j = 0; j < boardSqSize; j++)
			cin >> x, Start.A[i][j] = static_cast<puzzle_t>(x);


	if (!Start.isSolveAble()) {
		cout << "No Solution" << endl;
	}
	else {
		{
			if (heuristicConfig == 1) {
				cout << "Hamming distance heuristics: " << endl;
				executeSearch(Start, Goal, HAMMING_DISTANCE, solseqCommandConfig, pcostCommandConfig, nvisitedCommandConfig);
			}
			else {
				cout << "ManHattan distance heuristics: " << endl;
				executeSearch(Start, Goal, MANHATTAN_DISTANCE, solseqCommandConfig, pcostCommandConfig, nvisitedCommandConfig);
			}
		}
	}
	return 0;
}