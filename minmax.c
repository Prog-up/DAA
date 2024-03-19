int *getMinMax(int arr[], int n) {
  int min, max;

  if (n == 1) {
    max = arr[0];
    min = arr[0];
  } else if (n == 2) {
    if (arr[0] > arr[1]) {
      max = arr[0];
      min = arr[1];
    } else {
      max = arr[1];
      min = arr[0];
    }
  } else {
    for (int i = 2; i < n; i++) {
      if (arr[i] > max)
        max = arr[i];

      else if (arr[i] < min)
        min = arr[i];
    }
  }

  int res[] = {min, max};
  return res;
}