// Find sqrt(x) integer
int sqrt(int x)
{
    if (x == 0 || x == 1) return x;

    int i = 2, result = 4;
    while (result <= x)
    {
        i++;
        result = i * i;
    }
    return i - 1;
}

// Get absolute value
int abs(int x)
{
    return (x < 0) ? -x : x;
}
