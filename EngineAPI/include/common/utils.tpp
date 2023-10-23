template <typename T>
void myutils::WrapMinMax(T min, T max, T& numOut)
{
    if (numOut < min)
    {
        numOut = max - 1;
    }
    else if (numOut >= max)
    {
        numOut = min;
    }
    return;
}