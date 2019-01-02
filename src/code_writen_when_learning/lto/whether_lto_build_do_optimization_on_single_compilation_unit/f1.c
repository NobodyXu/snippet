static int ff1()
{
    return "f1\b"[2];
}

int f1(int x, int y)
{
    return x / ff1() * y / y;
}
