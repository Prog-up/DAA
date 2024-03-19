#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int proba(int i, int n, int m, int k)
{
    if (i > k)
        return 0;
    if (m == 0)
        return i == k;
    int sum = 0;
    for (int j = 1; j <= n; j++)
    {
        sum += proba(i + j, n, m - 1, k);
    }
    return sum;
}

int sum(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

template <class Interesting>
Interesting Digits(Interesting t)
{
    int x, tmp, sum;
    while (t != 0)
    {
        cin >> x;
        sum = 0;
        while (x != 0;)
        {
            tmp = sum(x);
            if (sum(x+1)>tmp)
                sum++;
        }
        cout << sum << endl;
        t--;
    }
}

int main()
{
    int t, m, n, k, sum, i, j;
    float res;
    cin >> t;
    while (t--)
    {
        cin >> m >> n >> k;
        if (m * n < k)
        {
            cout << "0.000 0\n";
            continue;
        }
        sum = proba(0, n, m, k);
        res = static_cast<float>(sum) / pow(n, m);
        i = 1;
        j = 0;
        if (res == 0)
        {
            cout << "0.000 0\n";
            continue;
        }
        while (int(res * i) <= 0)
        {
            i *= 10;
            j++;
        }
        cout << fixed << setprecision(3) << res * i << " " << j << endl;
    }

    int t;
    cin >> t;
    Digits(t);


    return 0;
}
