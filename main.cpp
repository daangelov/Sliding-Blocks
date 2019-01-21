#include <iostream>
#include <algorithm>
#include <ctime>

#include "Matrix.h"
#include "Board.h"

#include "functions.h"

using namespace std;

/*
vector<string> astar(Board* start)
{
    // Create priority queue with the initial board
    vector<Board*> pqueue;
    pqueue.push_back(start);

    do {
		Board* top = pqueue.front(); // Get top board

        if (top->getManhattanDist() == 0)
		{
			return top->getPath();
		}
		else
		{
			vector<Board*> children = top->getChildren();
			for (vector<Board*>::iterator it = children.begin(); it != children.end(); it++)
			{
				pqueue.push_back(*it);
			}
			sort(pqueue.begin(), pqueue.end(), [](Board*& left, Board*& right) {
                return (left->getEval() < right->getEval());
            });
		}

    } while(!pqueue.empty());
}
*/

vector<string> astar(Board* start)
{
    vector<Board*> open;
    vector<Board*> closed;
    open.push_back(start);

    while (!open.empty())
    {
        Board* best = open.front();
        //best->printBoard();
        //cout << best->getEval() << endl;
        int index = 0;
        int indexToBeErased = 0;
        for (vector<Board*>::iterator it = open.begin(); it != open.end(); it++)
        {
            if (best->getEval() > (*it)->getEval())
            {
                best = (*it);
                indexToBeErased = index;
            }
            index++;
        }
        open.erase(open.begin() + indexToBeErased);

        vector<Board*> children = best->getChildren();
        for (vector<Board*>::iterator it = children.begin(); it != children.end(); it++)
        {
            if ((*it)->getManhattanDist() == 0) return (*it)->getPath();

            bool checkOpen = true, checkClosed = true;
            for (vector<Board*>::iterator jt = open.begin(); jt != open.end(); jt++)
            {
                if ((*it)->isEqualTo(*jt))
                {
                    if ((*it)->getEval() > (*jt)->getEval())
                    {
                        checkOpen = false;
                    }
                }
            }

            for (vector<Board*>::iterator jt = closed.begin(); jt != closed.end(); jt++)
            {
                if ((*it)->isEqualTo(*jt))
                {
                    if ((*it)->getEval() > (*jt)->getEval())
                    {
                        checkClosed = false;
                    }
                }
            }

            if (checkOpen && checkClosed) open.push_back(*it);
        }
        closed.push_back(best);
    }

    vector<string> thisShouldNotHappen;
    thisShouldNotHappen.push_back("Couldn't do it :(");
    return thisShouldNotHappen;
}

int main()
{
    int n;
    cout << "Enter n: "; // User is prompt to enter n
    cin >> n; // User enters n
    int size = sqrt(n + 1);

    // User is prompt to enter matrix
    cout << "Enter a matrix " << size << "x" << size << endl;

    // User enters matrix
    int temp, zeroX = -1, zeroY = -1;
    Matrix start(size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cin >> temp;
            start[i][j] = temp;
            if (start[i][j] == 0)
            {
                zeroX = i;
                zeroY = j;
            }
        }
    }

    if (zeroX == -1 || zeroY == -1)
    {
        cout << "Invalid board(no zero point). Please run again with a different board!" << endl;
        return 0;
    }

    Board* initialBoard = new Board(start, zeroX, zeroY);

    if (!initialBoard->isSolvable())
    {
        cout << "This board can not be solved. Please run again with a different board!" << endl;
        return 0;
    }

    initialBoard->calcManhattanDist();
    initialBoard->calcEval();

    if (initialBoard->getEval() == 0)
    {
        cout << "This puzzle is already solved!" << endl;
        return 0;
    }

    clock_t startTime, endTime;
    startTime = clock();
    vector<string> result = astar(initialBoard);
    endTime = clock();
    cout << "Number of steps: " << result.size() << endl;
    for (vector<string>::iterator it = result.begin(); it != result.end(); it++)
    {
        cout << (*it) << " ";
    }
    cout << endl << "Time: " << (endTime - startTime) / (double) CLOCKS_PER_SEC << endl;
}
