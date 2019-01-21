#ifndef MATRIX_H
#define MATRIX_H
using namespace std;
class Matrix
{
private:

    int** values;
    unsigned int size;

public:

    Matrix();              // Default constructor
    Matrix(unsigned int);  // Constructor
    ~Matrix();             // Destructor

    Matrix(const Matrix&); // Copy constructor

    unsigned int getSize() const;
    int** getValues() const;
    void init();

    int* operator[] (unsigned int) const;
    Matrix& operator= (const Matrix&);
    int getValueAt(unsigned int, unsigned int) const;
    bool isEqualTo(const Matrix&) const;

    void printMatrix() const;
};

Matrix::Matrix()
{
    this->size = 0;
}

Matrix::Matrix(unsigned int size)
{
    this->size = size;
    this->values = new int*[size];
    for (unsigned int i = 0; i < size; ++i)
    {
        this->values[i] = new int[size];
    }
}

void Matrix::init()
{
    for (unsigned int i = 0; i < this->size; ++i)
    {
        for (unsigned int j = 0; j < this->size; ++j)
        {
            this->values[i][j] = (i * this->size) + j + 1;
        }
    }
    this->values[this->size - 1][this->size - 1] = 0;
}

Matrix::~Matrix()
{
    if (this->values)
    {
        for (unsigned int i = 0; i < this->size; ++i)
            delete[] values[i];
    }
    delete[] values;
}

Matrix::Matrix(const Matrix& other)
{
    this->size = other.size;
    if (other.values)
    {
        this->values = new int*[this->size];
        for (unsigned int i = 0; i < this->size; ++i)
        {
            this->values[i] = new int[this->size];
        }

        for (unsigned int i = 0; i < this->size; ++i)
        {
            for (unsigned int j = 0; j < this->size; ++j)
            {
                this->values[i][j] = other.values[i][j];
            }
        }
    }
}
Matrix& Matrix::operator= (const Matrix& other)
{
    this->size = other.size;
    if (other.values)
    {
        this->values = new int*[this->size];
        for (unsigned int i = 0; i < this->size; ++i)
        {
            this->values[i] = new int[this->size];
        }

        for (unsigned int i = 0; i < this->size; ++i)
        {
            for (unsigned int j = 0; j < this->size; ++j)
            {
                this->values[i][j] = other.values[i][j];
            }
        }
    }
    return *this;
}

unsigned int Matrix::getSize() const
{
    return this->size;
}

int** Matrix::getValues() const
{
    return this->values;
}

int* Matrix::operator[] (unsigned int x) const
{
    return this->values[x];
}

bool Matrix::isEqualTo(const Matrix& other) const
{
    for (unsigned int i = 0; i < this->size; ++i)
    {
        for (unsigned int j = 0; j < this->size; ++j)
        {
            if (this->values[i][j] != other.values[i][j]) return false;
        }
    }
    return true;
}

void Matrix::printMatrix() const
{
    for (unsigned int i = 0; i < this->size; ++i)
    {
        for (unsigned int j = 0; j < this->size; ++j)
        {
            std::cout << this->values[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
#endif // MATRIX_H
