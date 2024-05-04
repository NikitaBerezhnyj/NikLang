int a = 10;
int b = 5;
int c = input();
int res = (a + b) * c;
print(res);

func MakeNegative(int res)
{
    return res * -1;
}

int resNegative = MakeNegative(res);
print(resNegative);