#include<iostream>
#include<vector>

#include<queue>
#include<unordered_set>

enum DIRECTION {DOWN = 0, UP = 1, RIGHT = 3, LEFT = 4};
struct Point {
	Point() = default;
	Point(int x, int y) : x(x), y(y) {}
	int x, y;
};

#define MAX 3

int reCords(int x, int y) {
	return x * MAX + (y + 1);
}

Point freeSpace(std::vector<std::vector<int>>& arr) {
	for(int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[i].size(); j++) {
			if (arr[i][j] == 0)
				return Point(i, j);
		}
	return Point(-1, -1);
}

bool isSolved(std::vector < std::vector<int>> arr) {
	for(int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[i].size(); j++) {
			if (arr[i][j] != reCords(i, j) && reCords(i,j) != MAX*MAX)
				return false;
		}
	return true;
}

Point cords[] = { {-1,0}, {1,0}, {0, 1}, {0,-1} };
std::unordered_set<std::string> visited;

struct Board {
	Board() = default;

	Board(std::vector<std::vector<int>> arr, int level, std::string instructions)
		: arr(arr), level(level), instructions(instructions) {}
	std::vector<std::vector<int>> arr;
	int level = 0;
	std::string instructions;
};

int bfs(std::vector<std::vector<int>> start) {
	std::queue<Board> queue;
	std::vector<std::vector<bool>> isVisited(MAX*MAX+1, std::vector<bool>(MAX*MAX+1));
	queue.push({ start, 0, "" });

	int steps = 0;
	while (!queue.empty()) {
		auto curr = queue.front();
		queue.pop();

		for (int i = 0; i < 4; i++) {
			std::string instructions = "";
			int x = cords[i].x, y = cords[i].y;
			Point currCords = freeSpace(curr.arr);

			if (i == DIRECTION::UP)
				instructions = " up ";
			else if (i == DIRECTION::DOWN)
				instructions = " down ";
			else if (i == DIRECTION::LEFT)
				instructions = " left ";
			else if (i == DIRECTION::RIGHT)
				instructions = " right ";

			int Xnext = currCords.x - x, Ynext = currCords.y - y;
			if (Xnext < 0 || Xnext >= MAX || Ynext < 0 || Ynext >= MAX)
				continue;

			if (isVisited[reCords(Xnext, Ynext)][reCords(currCords.x, currCords.y)] == true)
				continue;


			std::swap(curr.arr[currCords.x][currCords.y], curr.arr[Xnext][Ynext]);

			queue.push({ curr.arr, curr.level + 1, curr.instructions + instructions });


			if (isSolved(curr.arr)) {
				std::cout << "Solved!\n";
				std::cout << curr.instructions+instructions << std::endl;
				return curr.level+1;
			}

			std::swap(curr.arr[currCords.x][currCords.y], curr.arr[Xnext][Ynext]);
		}
	}
}

int main() {
	std::vector<std::vector<int>> arr;

	arr.resize(MAX, std::vector<int>(MAX));

	for (int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[i].size(); j++)
			std::cin >> arr[i][j];

	std::cout << bfs(arr);
}
