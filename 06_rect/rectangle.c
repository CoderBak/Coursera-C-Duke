#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// I've provided "min" and "max" functions in
// case they are useful to you
int min (int a, int b) {
    return (a > b) ? b : a;
}
int max (int a, int b) {
    return (a > b) ? a : b;
}
int abs(int a) {
    return (a < 0) ? - a : a;
}

// Declare your rectangle structure here!
struct rectangle {
    int x, y, width, height;
};
typedef struct rectangle rectangle;

struct segment {
    int s, t;
};
typedef struct segment segment;

// A very clever idea: consider the project
// of rectangle to x-axis and y-axis.

// s > t yields invalid intersection
segment intersect(segment a, segment b) {
    segment c;
    if (a.t < b.s || b.t < a.s) {
        c.s = 1;
        c.t = 0;
        return c;
    }
    c.s = max(a.s, b.s);
    c.t = min(a.t, b.t);
    return c;
}

rectangle canonicalize(rectangle r) {
    r.x = (r.width < 0) ? r.x + r.width : r.x;
    r.y = (r.height < 0) ? r.y + r.height : r.y;
    r.width = abs(r.width);
    r.height = abs(r.height);
    return r;
}
int check(segment x) {
    return (x.s > x.t) ? 0 : 1; 
}
rectangle intersection(rectangle r1, rectangle r2) {
    r1 = canonicalize(r1);
    r2 = canonicalize(r2);
    segment x1, x2, y1, y2, x3, y3;
    x1.s = r1.x;
    x1.t = r1.x + r1.width;
    x2.s = r2.x;
    x2.t = r2.x + r2.width;
    y1.s = r1.y;
    y1.t = r1.y + r1.height;
    y2.s = r2.y;
    y2.t = r2.y + r2.height;
    x3 = intersect(x1, x2);
    y3 = intersect(y1, y2);
    rectangle r3;
    if (check(x3) && check(y3)) {
        r3.x = x3.s;
        r3.width = x3.t - x3.s;
        r3.y = y3.s;
        r3.height = y3.t - y3.s;
    } else {
        r3.width = r3.height = 0;
    }
    return r3;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
    r = canonicalize(r);
    if (r.width == 0 && r.height == 0) {
        printf("<empty>\n");
    }
    else {
        printf("(%d,%d) to (%d,%d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
    }
}

int main (void) {
    rectangle r1;
    rectangle r2;
    rectangle r3;
    rectangle r4;

    r1.x = 2;
    r1.y = 3;
    r1.width = 5;
    r1.height = 6;
    printf("r1 is ");
    printRectangle(r1);

    r2.x = 4;
    r2.y = 5;
    r2.width = -5;
    r2.height = -7;
    printf("r2 is ");
    printRectangle(r2);
  
    r3.x = -2;
    r3.y = 7;
    r3.width = 7;
    r3.height = -10;
    printf("r3 is ");
    printRectangle(r3);

    r4.x = 0;
    r4.y = 7;
    r4.width = -4;
    r4.height = 2;
    printf("r4 is ");
    printRectangle(r4);

    //test everything with r1
    rectangle i = intersection(r1,r1);
    printf("intersection(r1,r1): ");
    printRectangle(i);

    i = intersection(r1,r2);
    printf("intersection(r1,r2): ");
    printRectangle(i);
  
    i = intersection(r1,r3);
    printf("intersection(r1,r3): ");
    printRectangle(i);

    i = intersection(r1,r4);
    printf("intersection(r1,r4): ");
    printRectangle(i);

    //test everything with r2
    i = intersection(r2,r1);
    printf("intersection(r2,r1): ");
    printRectangle(i);

    i = intersection(r2,r2);
    printf("intersection(r2,r2): ");
    printRectangle(i);
  
    i = intersection(r2,r3);
    printf("intersection(r2,r3): ");
    printRectangle(i);

    i = intersection(r2,r4);
    printf("intersection(r2,r4): ");
    printRectangle(i);

    //test everything with r3
    i = intersection(r3,r1);
    printf("intersection(r3,r1): ");
    printRectangle(i);

    i = intersection(r3,r2);
    printf("intersection(r3,r2): ");
    printRectangle(i);
  
    i = intersection(r3,r3);
    printf("intersection(r3,r3): ");
    printRectangle(i);

    i = intersection(r3,r4);
    printf("intersection(r3,r4): ");
    printRectangle(i);

    //test everything with r4
    i = intersection(r4,r1);
    printf("intersection(r4,r1): ");
    printRectangle(i);

    i = intersection(r4,r2);
    printf("intersection(r4,r2): ");
    printRectangle(i);

    i = intersection(r4,r3);
    printf("intersection(r4,r3): ");
    printRectangle(i);

    i = intersection(r4,r4);
    printf("intersection(r4,r4): ");
    printRectangle(i);


    return EXIT_SUCCESS;
}
