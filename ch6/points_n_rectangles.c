//example program from section 6.2; functions used to manipulate point and rect structs

#include <stdio.h>

#define XMAX 480
#define YMAX 480

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
	int x;
	int y;
};

struct rect {
	struct point pt1;
	struct point pt2;
};


struct point makepoint(int, int);
struct point addpoint(struct point, struct point);

int main(){
	struct rect screen;
	struct point middle;
	screen.pt1 = makepoint(0,0);
	screen.pt2 = makepoint(XMAX, YMAX);
	middle = makepoint((screen.pt1.x + screen.pt2.x)/2, 
					   (screen.pt1.y + screen.pt2.y)/2);
}

struct point makepoint(int x, int y)
{
	struct point temp;

	temp.x = x;
	temp.y = y;
	return temp;
}

struct point addpoint(struct point pt1, struct point pt2)
{
	pt1.x += pt2.x;
	pt1.y += pt2.y;
	return pt1;
}

int ptinrect(struct point pt, struct rect r)
{
	return pt.x >= r.pt1.x && pt.y > r.pt1.y &&
		   pt.x <= r.pt2.x && pt.y < r.pt2.y;
}

struct rect canonrect(struct rect r)
{
	struct rect temp;

	temp.pt1.x = min(r.pt1.x, r.pt2.x);
	temp.pt1.y = min(r.pt1.y, r.pt2.y);
	temp.pt2.x = max(r.pt1.x, r.pt2.x);
	temp.pt2.y = max(r.pt1.y, r.pt2.y);
	return temp;
}
