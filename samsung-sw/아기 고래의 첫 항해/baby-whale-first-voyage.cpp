#include <iostream>
#include <queue>

using namespace std;

#define MAX_SIZE 51
#define INF 1000000000

// 방향
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


// 현재 고래 위치와 방향
int r, c, d;


// 방향별 행, 열 변화량
// 1 = 위
// 2 = 아래
// 3 = 왼쪽
// 4 = 오른쪽
int dr[5] = {
    0,
    -1,     // UP
    1,      // DOWN
    0,      // LEFT
    0       // RIGHT
};

int dc[5] = {
    0,
    0,      // UP
    0,      // DOWN
    -1,     // LEFT
    1       // RIGHT
};


// 현재 방향에 따른 탐색 우선순위
//
// 문제 조건:
// 직진 -> 왼쪽 -> 오른쪽 -> 뒤쪽
//
// 예를 들어 현재 방향이 UP(1)이면
// UP -> LEFT -> RIGHT -> DOWN
int directionOrder[5][4] = {

    {0, 0, 0, 0},

    // 현재 방향 UP
    {UP, LEFT, RIGHT, DOWN},

    // 현재 방향 DOWN
    {DOWN, RIGHT, LEFT, UP},

    // 현재 방향 LEFT
    {LEFT, DOWN, UP, RIGHT},

    // 현재 방향 RIGHT
    {RIGHT, UP, DOWN, LEFT}
};


// BFS로 목표까지 이동할 때
// 최단 경로가 여러 개일 경우의 우선순위
//
// 왼쪽 -> 아래 -> 오른쪽 -> 위
int pathOrder[4] = {
    LEFT,
    DOWN,
    RIGHT,
    UP
};


// pair 대신 사용할 구조체
struct Point {
    int r;
    int c;
};


// -----------------------------------------------------
// 입력
// -----------------------------------------------------

void init(int sea[][MAX_SIZE], int& s) {

    cin >> s >> r >> c >> d;

    // 문제의 좌표가 1부터 시작하므로
    // 배열도 1 ~ N 사용
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= s; j++) {
            cin >> sea[i][j];
        }
    }
}


// -----------------------------------------------------
// 지도 밖인지 확인
// -----------------------------------------------------

bool inRange(int row, int col, int s) {

    if (row < 1 || row > s)
        return false;

    if (col < 1 || col > s)
        return false;

    return true;
}


// -----------------------------------------------------
// 1단계
//
// 현재 위치 주변의 미방문 바다를 찾는다.
//
// 직진
// ↓
// 왼쪽
// ↓
// 오른쪽
// ↓
// 뒤쪽
//
// 순으로 확인한다.
// -----------------------------------------------------

bool move(
    int sea[][MAX_SIZE],
    bool visited[][MAX_SIZE],
    int s
) {

    // 총 4방향 검사
    for (int i = 0; i < 4; i++) {

        // 현재 방향을 기준으로
        // 이번에 확인할 방향
        int nextDir = directionOrder[d][i];

        // 이동했을 때 좌표
        int nr = r + dr[nextDir];
        int nc = c + dc[nextDir];


        // 1. 지도 밖이면 못 감
        if (!inRange(nr, nc, s))
            continue;


        // 2. 암초면 못 감
        if (sea[nr][nc] == 1)
            continue;


        // 3. 이미 방문한 곳이면
        // 1단계에서는 가지 않음
        if (visited[nr][nc])
            continue;


        // ---------------------------
        // 여기까지 왔다면 이동 가능
        // ---------------------------

        r = nr;
        c = nc;

        // 고래가 바라보는 방향도
        // 실제 이동 방향으로 변경
        d = nextDir;


        // 방문 처리
        visited[r][c] = true;


        // 처음 방문한 위치 출력
        cout << r << " " << c << '\n';


        // 한 칸 이동했으므로 함수 종료
        return true;
    }


    // 주변에 이동할 미방문 바다가 없음
    return false;
}


// -----------------------------------------------------
// 2단계 - 1
//
// 현재 위치에서 BFS를 돌려서
// 가장 가까운 '미방문 바다'를 찾는다.
//
// 조건:
//
// 1. 거리가 가장 가까운 곳
// 2. 거리가 같으면 행이 작은 곳
// 3. 행도 같으면 열이 작은 곳
//
// targetR, targetC에 결과 저장
// -----------------------------------------------------

bool findNearest(
    int sea[][MAX_SIZE],
    bool visited[][MAX_SIZE],
    int s,
    int& targetR,
    int& targetC
) {

    // BFS용 거리 배열
    int dist[MAX_SIZE][MAX_SIZE];


    // 아직 방문하지 않았다는 의미로 -1
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= s; j++) {
            dist[i][j] = -1;
        }
    }


    queue<Point> q;


    // 현재 고래 위치부터 BFS 시작
    q.push({r, c});

    dist[r][c] = 0;


    int bestDistance = INF;

    targetR = -1;
    targetC = -1;


    while (!q.empty()) {

        Point current = q.front();
        q.pop();

        int cr = current.r;
        int cc = current.c;

        int currentDistance = dist[cr][cc];


        // -------------------------------------
        // 아직 실제로 방문하지 않은 바다인가?
        // -------------------------------------

        if (!visited[cr][cc]) {

            // 더 가까운 바다 발견
            if (currentDistance < bestDistance) {

                bestDistance = currentDistance;

                targetR = cr;
                targetC = cc;
            }

            // 거리가 같다면
            else if (currentDistance == bestDistance) {

                // 행이 작은 곳 우선
                if (cr < targetR) {

                    targetR = cr;
                    targetC = cc;
                }

                // 행이 같다면 열이 작은 곳
                else if (cr == targetR && cc < targetC) {

                    targetR = cr;
                    targetC = cc;
                }
            }
        }


        // -------------------------------------
        // 주변 4방향 BFS
        // -------------------------------------

        for (int dir = 1; dir <= 4; dir++) {

            int nr = cr + dr[dir];
            int nc = cc + dc[dir];


            // 지도 밖
            if (!inRange(nr, nc, s))
                continue;


            // 암초
            if (sea[nr][nc] == 1)
                continue;


            // BFS에서 이미 확인함
            if (dist[nr][nc] != -1)
                continue;


            dist[nr][nc] = currentDistance + 1;

            q.push({nr, nc});
        }
    }


    // targetR == -1 이면
    // 더 이상 방문할 바다가 없다는 뜻
    if (targetR == -1)
        return false;


    return true;
}


// -----------------------------------------------------
// 목표 지점에서 BFS
//
// 각 칸에서 목표까지 거리가 몇 칸인지 계산
//
// 예:
//
// 3 2 1
// 2 1 0   <- 목표
// 3 2 1
//
// 이런 식으로 만들어놓으면
// 현재 거리보다 1 작은 곳으로 계속 이동하면
// 최단 경로를 따라갈 수 있다.
// -----------------------------------------------------

void makeDistanceMap(
    int sea[][MAX_SIZE],
    int dist[][MAX_SIZE],
    int s,
    int targetR,
    int targetC
) {

    // -1 초기화
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= s; j++) {
            dist[i][j] = -1;
        }
    }


    queue<Point> q;


    // 목표 위치에서 BFS 시작
    q.push({targetR, targetC});

    dist[targetR][targetC] = 0;


    while (!q.empty()) {

        Point current = q.front();
        q.pop();

        int cr = current.r;
        int cc = current.c;


        for (int dir = 1; dir <= 4; dir++) {

            int nr = cr + dr[dir];
            int nc = cc + dc[dir];


            // 지도 밖
            if (!inRange(nr, nc, s))
                continue;


            // 암초
            if (sea[nr][nc] == 1)
                continue;


            // 이미 BFS에서 확인함
            if (dist[nr][nc] != -1)
                continue;


            dist[nr][nc] = dist[cr][cc] + 1;

            q.push({nr, nc});
        }
    }
}


// -----------------------------------------------------
// 2단계 - 2
//
// BFS로 찾은 목표 위치까지 실제로 이동
//
// 목표까지 거리가 1씩 줄어드는 방향으로 간다.
//
// 여러 최단경로가 존재하면
//
// 왼쪽 -> 아래 -> 오른쪽 -> 위
//
// 순서로 선택
// -----------------------------------------------------

void moveToTarget(
    int sea[][MAX_SIZE],
    bool visited[][MAX_SIZE],
    int s,
    int targetR,
    int targetC
) {

    int dist[MAX_SIZE][MAX_SIZE];


    // 목표를 기준으로 거리 지도 생성
    makeDistanceMap(
        sea,
        dist,
        s,
        targetR,
        targetC
    );


    // 목표에 도착할 때까지 반복
    while (r != targetR || c != targetC) {

        bool moved = false;


        // 왼쪽 -> 아래 -> 오른쪽 -> 위
        for (int i = 0; i < 4; i++) {

            int nextDir = pathOrder[i];

            int nr = r + dr[nextDir];
            int nc = c + dc[nextDir];


            if (!inRange(nr, nc, s))
                continue;


            if (sea[nr][nc] == 1)
                continue;


            // 현재 위치보다
            // 목표까지 거리가 정확히 1 작은 곳이면
            //
            // 최단 경로의 일부라는 뜻
            if (dist[nr][nc] == dist[r][c] - 1) {

                // 실제 이동
                r = nr;
                c = nc;

                // 현재 방향 변경
                d = nextDir;


                // 처음 방문한 칸인지 저장
                bool firstVisit = !visited[r][c];


                // 실제 이동했으므로 방문 처리
                visited[r][c] = true;


                // 처음 방문한 경우에만 출력
                //
                // 이미 지나갔던 칸을 다시 지나가는 경우
                // 또 출력하지 않는다.
                if (firstVisit) {
                    cout << r << " " << c << '\n';
                }


                moved = true;
                break;
            }
        }


        // 정상적인 경우 발생하지 않음
        // 무한루프 방지용
        if (!moved)
            return;
    }
}


// -----------------------------------------------------
// 전체 시뮬레이션
// -----------------------------------------------------

void start(
    int sea[][MAX_SIZE],
    bool visited[][MAX_SIZE],
    int s
) {

    // 시작 위치 방문 처리
    visited[r][c] = true;


    // 시작 위치 출력
    cout << r << " " << c << '\n';


    while (true) {

        // ==========================================
        // 1단계
        //
        // 바로 주변에서 아직 방문하지 않은
        // 바다를 찾는다.
        // ==========================================

        bool moved = move(
            sea,
            visited,
            s
        );


        // 이동에 성공했다면
        // 다시 1단계부터 시작
        if (moved) {
            continue;
        }


        // ==========================================
        // 여기까지 왔다는 뜻:
        //
        // 주변에 미방문 바다가 없음
        //
        // 따라서 BFS 필요
        // ==========================================


        int targetR;
        int targetC;


        // ==========================================
        // 2단계
        //
        // 가장 가까운 미방문 바다 찾기
        // ==========================================

        bool found = findNearest(
            sea,
            visited,
            s,
            targetR,
            targetC
        );


        // 방문할 바다가 더 이상 없다
        if (!found) {
            break;
        }


        // ==========================================
        // 찾은 위치까지 최단경로로 이동
        // ==========================================

        moveToTarget(
            sea,
            visited,
            s,
            targetR,
            targetC
        );
    }
}


// -----------------------------------------------------
// main
// -----------------------------------------------------

int main() {

    // 0 = 바다
    // 1 = 암초
    int sea[MAX_SIZE][MAX_SIZE] = {};


    // 실제로 고래가 탐험했는지 여부
    //
    // false = 아직 안 감
    // true  = 방문함
    bool visited[MAX_SIZE][MAX_SIZE] = {};


    int N = 0;


    // 맵 입력
    init(sea, N);


    // 시뮬레이션 시작
    start(
        sea,
        visited,
        N
    );


    return 0;
}