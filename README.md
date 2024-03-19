# DAA
 Design and Architecture Algorithme

 ```c
int n, k;
int* x;
for (int i = 0; i < n; i++) {
    if (place(k, i))
        x[k] = i;
    else if (k == n)
        write(x, 1, n);
    else
        nqueens(k + 1, n);
}
```
