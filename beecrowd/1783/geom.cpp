#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

Point solve(Point A, Point C, Point B, Point D) {
    Point midAC = {(A.x + C.x) / 2, (A.y + C.y) / 2};
    Point midBD = {(B.x + D.x) / 2, (B.y + D.y) / 2};

    double slopeAC, slopeBD;
    bool isVerticalAC = false, isVerticalBD = false;

    if (C.x != A.x)
        slopeAC = (C.y - A.y) / (C.x - A.x);
    if (C.x == A.x || slopeAC == 0)
      isVerticalAC = true;

    if (D.x != B.x)
        slopeBD = (D.y - B.y) / (D.x - B.x);
    if (D.x == B.x || slopeBD == 0)
        isVerticalBD = true;

    double perpSlopeAC, perpSlopeBD;
    if (!isVerticalAC) {
        perpSlopeAC = -1 / slopeAC;
    }
    if (!isVerticalBD) {
        perpSlopeBD = -1 / slopeBD;
    }

    Point center;
    if (isVerticalAC) {
        center.x = midAC.x;
        if (isVerticalBD) {
            center.y = midBD.y;
        } else {
            center.y = perpSlopeBD * (center.x - midBD.x) + midBD.y;
        }
    } else if (isVerticalBD) {
        center.x = midBD.x;
        center.y = perpSlopeAC * (center.x - midAC.x) + midAC.y;
    } else {
        double bAC = midAC.y - perpSlopeAC * midAC.x;
        double bBD = midBD.y - perpSlopeBD * midBD.x;
        center.x = (bBD - bAC) / (perpSlopeAC - perpSlopeBD);
        center.y = perpSlopeAC * center.x + bAC;
    }

    return center;
}

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; ++t) {
        Point old1, new1, old2, new2;
        cin >> old1.x >> old1.y >> old2.x >> old2.y >> new1.x >> new1.y >> new2.x >> new2.y;
        
        auto [x, y] = solve(old1, new1, old2, new2);
        printf("Caso #%d: %.2lf %.2lf\n", t, x, y);
    }
    
    return 0;
}
