#include <u.h>
#include <libc.h>
#include <draw.h>

// From: http://ix.io/1svR

typestr Point _Point;

void
main(void)
{
	fmtinstall('P', Pfmt);

	Point a = Pt(1, -2);
	Point b = Pt(-5, 3);

	Point c;
	c = addpt(a, b);	USED(c);
	c = a + b;	USED(c);

	Rectangle r;
	c = addpt(a, b);

	r.min = c;

	r.max = a + b;

	print("%P\n", a+b);
	print("%P\n", addpt(a,b));
}


Point
Point_add_(Point a, Point b)
{
	Point r;

	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

