#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve(int chessboard[10][10], int sr, int sc, int dr, int dc, string psf, bool visited[10][10], vector<string>& res, char currDir) {
    // Base Condition
    // Negative Base Case
    if (sr < 1 || sc < 1 || sr >= 10 || sc >= 10) {
        return;
    }
    // Positive Base Case
    if (sr == dr && sc == dc) {
        psf += "Arrive (" + to_string(sc) + "," + to_string(sr) + ")";
        res.push_back(psf);
        return;
    }
    visited[sr][sc] = true;
    if (chessboard[sr][sc] == 1) { // Cell contains soldier
        // Kill
        chessboard[sr][sc] = 0;
        if (currDir == 'D') {
            solve(chessboard, sr, sc + 1, dr, dc, psf + "Kill (" + to_string(sc) + "," + to_string(sr) + "). Turn Left\n", visited, res, 'R');
        } else if (currDir == 'R') {
            solve(chessboard, sr - 1, sc, dr, dc, psf + "Kill (" + to_string(sc) + "," + to_string(sr) + "). Turn Left\n", visited, res, 'T');
        } else if (currDir == 'T') {
            solve(chessboard, sr, sc - 1, dr, dc, psf + "Kill (" + to_string(sc) + "," + to_string(sr) + "). Turn Left\n", visited, res, 'L');
        } else {
            solve(chessboard, sr + 1, sc, dr, dc, psf + "Kill (" + to_string(sc) + "," + to_string(sr) + "). Turn Left\n", visited, res, 'D');
        }
        chessboard[sr][sc] = 1;

        // Jump
        if (currDir == 'D') {
            solve(chessboard, sr + 1, sc, dr, dc, psf + "Jump (" + to_string(sc) + "," + to_string(sr) + ")\n", visited, res, 'D');
        } else if (currDir == 'R') {
            solve(chessboard, sr, sc + 1, dr, dc, psf + "Jump (" + to_string(sc) + "," + to_string(sr) + ")\n", visited, res, 'R');
        } else if (currDir == 'T') {
            solve(chessboard, sr - 1, sc, dr, dc, psf + "Jump (" + to_string(sc) + "," + to_string(sr) + ")\n", visited, res, 'T');
        } else {
            solve(chessboard, sr, sc - 1, dr, dc, psf + "Jump (" + to_string(sc) + "," + to_string(sr) + ")\n", visited, res, 'L');
        }
    } else { // Cell does not contain soldier
        if (currDir == 'D') {
            solve(chessboard, sr + 1, sc, dr, dc, psf, visited, res, 'D');
        } else if (currDir == 'R') {
            solve(chessboard, sr, sc + 1, dr, dc, psf, visited, res, 'R');
        } else if (currDir == 'T') {
            solve(chessboard, sr - 1, sc, dr, dc, psf, visited, res, 'T');
        } else {
            solve(chessboard, sr, sc - 1, dr, dc, psf, visited, res, 'L');
        }
    }
    visited[sr][sc] = false;
}

int main() {
    vector<pair<int, int>> soldiers;
    cout << "Find my home castle soldiers: ";
    int numberOfSoldiers;
    cin >> numberOfSoldiers;
    for (int i = 0; i < numberOfSoldiers; i++) {
        cout << "Enter coordinates for soldier " << (i + 1) << ": ";
        int x, y;
        cin >> x >> y;
        soldiers.push_back({x, y});
    }
    int chessboard[10][10] = {0};
    for (const auto& coordinate : soldiers) {
        int x = coordinate.first;
        int y = coordinate.second;
        chessboard[y][x] = 1;
    }
    cout << "Enter the coordinates for your “special” castle: ";
    int startX, startY;
    cin >> startX >> startY;
    bool visited[10][10] = {false};
    vector<string> res;
    solve(chessboard, startY + 1, startX, startY, startX, "Start: (" + to_string(startX) + "," + to_string(startY) + ")\n", visited, res, 'D');
    for (size_t i = 0; i < res.size(); i++) {
        cout << "Path " << (i + 1) << "\n=======\n";
        cout << res[i] << "\n";
    }
    return 0;
}



