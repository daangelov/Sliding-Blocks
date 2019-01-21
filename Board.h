#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Matrix.h"

class Board
{

private:
    Matrix field;
    unsigned int zeroX;
    unsigned int zeroY;

    int eval;
    int depth;
    int manhattanDist;
    vector<string> path;

public:


    Board(Matrix, unsigned int, unsigned int);
    //~Board();

    void setDepth(int);
    void calcManhattanDist();
    void calcEval();

    Matrix getField() const;
    unsigned int getZeroX() const;
    unsigned int getZeroY() const;
    int getDepth() const;
    int getManhattanDist() const;
    int getEval() const;
    vector<string> getPath() const;

    void printBoard() const;


    bool isSolvable() const;
    bool isEqualTo(const Board*) const;


    void swapValues(unsigned int, unsigned int, unsigned int, unsigned int);

    bool canSlideUp() const;
    bool canSlideDown() const;
    bool canSlideRight() const;
    bool canSlideLeft() const;

    void slideUp();
    void slideDown();
    void slideRight();
    void slideLeft();

    vector<Board*> getChildren() const;
};

Board::Board(Matrix field, unsigned int zeroX, unsigned int zeroY)
{
    this->field = field;
    this->zeroX = zeroX;
    this->zeroY = zeroY;

    this->depth = 0;
    this->manhattanDist = 0;
    this->eval = 0;
}

void Board::setDepth(int depth)
{
    this->depth = depth;
}

void Board::calcManhattanDist()
{
    int size = this->field.getSize();

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int targetX, targetY;
            if (this->field[i][j] == 0)
                targetX = targetY = size - 1;
            else
            {
                targetX = (this->field[i][j] - 1) / size;
                targetY = (this->field[i][j] - 1) % size;
            }
            this->manhattanDist += abs(i - targetX) + abs(j - targetY);
        }
    }
}
void Board::calcEval()
{
    this->eval = this->depth + this->manhattanDist;
}

Matrix Board::getField() const
{
    return this->field;
}

unsigned int Board::getZeroX() const
{
    return this->zeroX;
}

unsigned int Board::getZeroY() const
{
    return this->zeroY;
}

int Board::getDepth() const
{
    return this->depth;
}

int Board::getManhattanDist() const
{
    return this->manhattanDist;
}

int Board::getEval() const
{
    return this->eval;
}

vector<string> Board::getPath() const
{
    return this->path;
}

void Board::printBoard() const
{
    this->field.printMatrix();
}

bool Board::isSolvable() const
{
    int size = this->field.getSize();
    int length = size * size;

    int* line = new int[length];
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            line[i * size + j] = this->field[i][j];
        }
    }

    int inversions = 0;
    for (int i = 0; i < length - 1; ++i)
    {
        for (int j = i + 1; j < length; ++j)
        {
            if (line[i] && line[j] && line[i] > line[j])
                inversions++;
        }
    }

    delete[] line;

    if (size % 2 == 1)
        return (inversions % 2 == 0);
    else
    {
        int posX;
        for (int i = size - 1; i >= 0; i--)
        {
            for (int j = size - 1; j >= 0; j--)
            {
                if (this->field[i][j] == 0)
                    posX = size - i;
            }
        }

        if (posX % 2 == 1)
            return (inversions % 2 == 0);
        else
            return (inversions % 2 == 1);
    }
}

bool Board::isEqualTo(const Board* other) const
{
    return this->field.isEqualTo(other->field);
}

void Board::swapValues(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    int temp = this->field[x1][y1];
    this->field[x1][y1] = this->field[x2][y2];
    this->field[x2][y2] = temp;
}

bool Board::canSlideUp() const
{
    if (this->zeroX != 0)
    {
        if (this->path.size())
        {
            return (this->path.back().compare("up") != 0);
        }
        return true;
    }
    return false;

    //return (this->zeroX != 0);
}

bool Board::canSlideDown() const
{
    if (this->zeroX != this->field.getSize() - 1)
    {
        if (this->path.size())
        {
            return (this->path.back().compare("down") != 0);
        }
        return true;
    }
    return false;

    //return (this->zeroX != this->field.getSize() - 1);
}

bool Board::canSlideRight() const
{
    if (this->zeroY != this->field.getSize() - 1)
    {
        if (this->path.size())
        {
            return (this->path.back().compare("right") != 0);
        }
        return true;
    }
    return false;

    //return (this->zeroY != this->field.getSize() - 1);
}

bool Board::canSlideLeft() const
{
    if (this->zeroY != 0)
    {
        if (this->path.size())
        {
            return (this->path.back().compare("left") != 0);
        }
        return true;
    }
    return false;

    //return (this->zeroY != 0);
}

void Board::slideUp()
{
    this->swapValues(this->zeroX, this->zeroY, this->zeroX - 1, this->zeroY);
    this->zeroX -= 1;
}

void Board::slideDown()
{
    this->swapValues(this->zeroX, this->zeroY, this->zeroX + 1, this->zeroY);
    this->zeroX += 1;
}

void Board::slideRight()
{
    this->swapValues(this->zeroX, this->zeroY, this->zeroX, this->zeroY + 1);
    this->zeroY += 1;
}

void Board::slideLeft()
{
    this->swapValues(this->zeroX, this->zeroY, this->zeroX, this->zeroY - 1);
    this->zeroY -= 1;
}

std::vector<Board*> Board::getChildren() const
{
    std::vector<Board*> children;

    if (this->canSlideUp())
    {
        Board* childUp = new Board(this->field, this->zeroX, this->zeroY);
        childUp->path = this->path;
        childUp->slideUp();
        childUp->path.push_back("down");
        childUp->setDepth(this->depth + 1);
        childUp->calcManhattanDist();
        childUp->calcEval();
        children.push_back(childUp);
    }
    if (this->canSlideDown())
    {
        Board* childDown = new Board(this->field, this->zeroX, this->zeroY);
        childDown->path = this->path;
        childDown->slideDown();
        childDown->path.push_back("up");
        childDown->setDepth(this->depth + 1);
        childDown->calcManhattanDist();
        childDown->calcEval();
        children.push_back(childDown);
    }
    if (this->canSlideRight())
    {
        Board* childRight = new Board(this->field, this->zeroX, this->zeroY);
        childRight->path = this->path;
        childRight->slideRight();
        childRight->path.push_back("left");
        childRight->setDepth(this->depth + 1);
        childRight->calcManhattanDist();
        childRight->calcEval();
        children.push_back(childRight);
    }
    if (this->canSlideLeft())
    {
        Board* childLeft = new Board(this->field, this->zeroX, this->zeroY);
        childLeft->path = this->path;
        childLeft->slideLeft();
        childLeft->path.push_back("right");
        childLeft->setDepth(this->depth + 1);
        childLeft->calcManhattanDist();
        childLeft->calcEval();
        children.push_back(childLeft);
    }

    return children;
}

#endif // BOARD_H
