#include "Screen.h"
#include <numeric>
using namespace std;

struct vec3
{
	float x, y, z;
};

struct connection
{
	int a, b;
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1) 
{
	float rad = 0;
	rad = x; 
	point.y = cos(rad) * point.y - sin(rad) * point.z;
	point.z = sin(rad) * point.y + cos(rad) * point.z;

	rad = y;
	point.x = cos(rad) * point.x - sin(rad) * point.z;
	point.z = sin(rad) * point.x + cos(rad) * point.z;

	rad = z;
	point.x = cos(rad) * point.x - sin(rad) * point.y;
	point.y = sin(rad) * point.x + cos(rad) * point.y;


}



void line(Screen& screen, float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1; 
	float dy = y2 - y1;

	float length = sqrt(dx * dx + dy * dy);
	float angle = atan2(dy, dx);


	for (float i = 0; i < length; i++)
	{
		screen.pixel(x1 + cos(angle) * i, y1 + sin(angle) * i);
	}
}

int main(int argc, char* argv[])
{
	Screen screen;

	vector<vec3> points{
		{100,100,100},
		{200,100,100},
		{200,200,100},
		{100,200,100},

		{100,100,200},
		{200,100,200},
		{200,200,200},
		{100,200,200}

	};

	vector<connection> connections{
		{0, 4},
		{1, 5},
		{2, 6},
		{3, 7},

		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},

		{4, 5},
		{5, 6},
		{6, 7},
		{7, 4}
	};

	// calculate centroid

	vec3 c{ 0, 0, 0, };
	for (auto& p : points)
	{
		c.x += p.x;
		c.y += p.y;
		c.z += p.z;
	}

	c.x /= points.size();
	c.y /= points.size();
	c.z /= points.size();

	while (true)
	{
		for (auto& p : points) 
		{
			p.x -= c.x;
			p.y -= c.y;
			p.z -= c.z;
			rotate(p, 0.02, 0.01, 0.04);
			p.x += c.x;
			p.y += c.y;
			p.z += c.z;
			screen.pixel(p.x, p.y);
		}

		for (auto& conn : connections)
		{
			line(screen, points[conn.a].x,
				points[conn.a].y,
				points[conn.b].x,
				points[conn.b].y);
		}

		screen.show();
		screen.clear();
		screen.input();
		SDL_Delay(30);

	}
	return 0;
}