#include <iostream>
using namespace std;

int main() {
    int N;
    int answer = 0;

    cin >> N;

    int field[20][20];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> field[i][j];
        }
    }

    for (int i = 0; i <= N - 3; i++) {
        for (int j = 0; j <= N - 3; j++) {

            int count = 0;

            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    count += field[i + k][j + l];
                }
            }

            if (count > answer)
                answer = count;
        }
    }

    cout << answer;

    return 0;
}