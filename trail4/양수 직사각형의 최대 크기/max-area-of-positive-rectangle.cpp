
#include <iostream>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    int arr[20][20];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }

    int ret = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {

            for (int k = i; k < N; k++) {
                for (int l = j; l < M; l++) {

                    bool valid = true;

                    for (int x = i; x <= k; x++) {
                        for (int y = j; y <= l; y++) {

                            if (arr[x][y] <= 0) {
                                valid = false;
                            }
                        }
                    }

                    if (valid) {
                        int area = (k - i + 1) * (l - j + 1);

                        if (area > ret) {
                            ret = area;
                        }
                    }
                }
            }
        }
    }

    cout << ret;

    return 0;
}
