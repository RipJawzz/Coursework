#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point
{
	int x, y;
}Point;

int compareX(const void*,const void*);
int compareY(const void*,const void*);
float dist(Point, Point);
float min(float, float);
float stripClosest(Point[],int,float);
float closestUtil(Point[],int);


void main()
{
  int n,a,b;
  printf("Enter the number of points\n");
  scanf("%d",&n);
  Point P[n];
  printf("Enter the x,y cordinates of the points\n");
  for(int i=0;i<n;i++){
    scanf("%d %d",&a,&b);
    Point p;
    p.x=a;
    p.y=b;
    P[i]=p;
  }
	qsort(P, n, sizeof(Point), compareX);
	printf("The smallest distance is %f ", closestUtil(P, n));
}

float closestUtil(Point P[], int n)
{
	if (n==1)
		return FLT_MAX;
  if (n==2)
    return dist(P[0],P[1]);

	int mid = n/2,j=0;
	float dl = closestUtil(P, mid),dr = closestUtil(P + mid, n-mid),d = min(dl, dr);
	Point midPoint = P[mid],strip[n];

	for (int i = 0; i < n; i++)
		if (abs(P[i].x - midPoint.x) < d)
			strip[j] = P[i], j++;

	return min(d, stripClosest(strip, j, d) );
}

float stripClosest(Point strip[], int size, float min)
{
	qsort(strip, size, sizeof(Point), compareY);

	for (int i = 0; i < size; ++i)
		for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
			if (dist(strip[i],strip[j]) < min)
				min = dist(strip[i], strip[j]);

	return min;
}

int compareX(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->x - p2->x);
}

int compareY(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->y - p2->y);
}

float dist(Point p1, Point p2)
{
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +(p1.y - p2.y)*(p1.y - p2.y));
}

float min(float x, float y)
{
	return (x < y)? x : y;
}
