#include "bmplib.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

#define PI 3.1415926

double xl = 0, yl = 0, zl = 0;
double maximumDistance = 0;

class Vector3 {
public:
	double x, y, z;
	Vector3(double x = 0, double y = 0, double z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3 normalize() {
		double r = sqrt(x * x + y * y + z * z);
		return Vector3(x / r, y / r, z / r);
	}
	double operator*(const Vector3& r) {
		double ans = 0;
		ans += x * r.x + y * r.y + z * r.z;
		return ans;
	}
	Vector3 operator-(const Vector3& r) {
		return Vector3(x - r.x,y - r.y,z - r.z);
	}
	Vector3 operator+(const Vector3& r) {
		return Vector3(x + r.x, y + r.y, z + r.z);
	}
	double length() const{
		return x * x + y * y + z * z;
	}
	bool operator>(const Vector3& r) {
		if (length() > r.length()) {
			return true;
		}
		return false;
	}
	Vector3 crossProduct(Vector3 b) {
		Vector3 c;
		c.x = y * b.z - z * b.y;
		c.y = z * b.x - x * b.z;
		c.z = x * b.y - y * b.x;
		return c;
	}
	Vector3 operator-() {
		return Vector3(-x, -y, -z);
	}
};

class Object {
protected:
	double x0, y0, z0;
public:
	Color col;
	virtual bool intersect(double, double, double, double, double, double, double&, bool&) = 0;
	virtual Color pixelColor(double, double, double) = 0;
};

vector<Object*> objs;

class Sphere : public Object {
	double R;
public:
	Sphere(double x0, double y0, double z0, double R, Color col = Color(255,0,0)) {
		this->x0 = x0;
		this->y0 = y0;
		this->z0 = z0;
		this->R = R;
		this->col = col;
	}
	bool intersect(double A, double B, double C, double xc, double yc, double zc, double& ans, bool& isKas) override {
		double d1 = ((x0-xc) * A / B + (y0-yc) + (z0-zc) * C / B) * ((x0-xc) * A / B + (y0-yc) + (z0-zc) * C / B) - (A * A / (B * B) + 1 + C * C / (B * B)) * ((x0-xc) * (x0-xc) + (y0-yc) * (y0-yc) + (z0-zc) * (z0-zc) - R * R);
		if (d1 >= 0) {
			double y1 = (((x0-xc) * A / B + (y0-yc) + (z0-zc) * C / B) + sqrt(d1)) / (A * A / (B * B) + 1 + C * C / (B * B));
			double y2 = (((x0-xc) * A / B + (y0-yc) + (z0-zc) * C / B) - sqrt(d1)) / (A * A / (B * B) + 1 + C * C / (B * B));
			if (d1 == 0) {
				isKas = true;
			}
			else {
				isKas = false;
			}
			ans = min(y1, y2);
			return true;
		}
		ans = 0;
		isKas = 0;
		return false;
	}
	Color pixelColor(double x, double y, double z) override {
		Vector3 n(2 * (x - x0), 2 * (y - y0), 2 * (z - z0));
		n = n.normalize();
		Vector3 a(xl - x, yl - y, zl - z);
		a = a.normalize();
		double ottenok = 255 - 255 * (sqrt(Vector3(x,y,z).length()) / maximumDistance);
		if (ottenok < 0) ottenok = 0;
		Color c(ottenok, ottenok, ottenok);
		double osv = n * a;
		if (osv < 0) {
			osv = 0;
		}
		c.red = static_cast<int>(min(c.red * osv + 10,255.0));
		c.green = static_cast<int>(min(c.green * osv + 10, 255.0));
		c.blue = static_cast<int>(min(c.blue * osv + 10, 255.0));
		return c;
	}
};

class Polygon : public Object {
	double x1, y1, z1;
	double x2, y2, z2;
	double Ap, Bp, Cp, Dp;
public:
	Polygon(double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2, Color col = Color(255, 0, 0)) {
		this->x0 = x0;
		this->y0 = y0;
		this->z0 = z0;
		this->x1 = x1;
		this->y1 = y1;
		this->z1 = z1;
		this->x2 = x2;
		this->y2 = y2;
		this->z2 = z2;
		this->col = col;
		Ap = (y1 - y0) * (z2 - z0) - (z1 - z0) * (y2 - y0);
		Bp = (z1 - z0) * (x2 - x0) - (x1 - x0) * (z2 - z0);
		Cp = (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
		Dp = -Ap * x0 - Bp * y0 - Cp * z0;
	}
	bool intersect(double A, double B, double C, double xc, double yc, double zc, double& ans, bool& isKas) override {
		double aaa = (Ap * A + Bp * B + Cp * C);
		if (abs(aaa) < DBL_MIN) {
			return false;
		}
		double t = -Dp / aaa;
		double xo = A * t;
		double yo = B * t;
		double zo = C * t;
		Vector3 o(xo, yo, zo);
		Vector3 a(x0, y0, z0);
		Vector3 b(x1, y1, z1);
		Vector3 c(x2, y2, z2);
		Vector3 n1 = (o - a).crossProduct(b - a);
		Vector3 n2 = (o - b).crossProduct(c - b);
		Vector3 n3 = (o - c).crossProduct(a - c);
		if (n1 * n2 < 0 || n1 * n3 < 0 || n2 * n3 < 0) {
			ans = 0;
			isKas = false;
			return false;
		}
		ans = yo;
		isKas = false;
		return true;
	}
	Color pixelColor(double x, double y, double z) override {
		Vector3 n(Ap, Bp, Cp);
		n = n.normalize();
		Vector3 a(xl - x, yl - y, zl - z);
		if (a * n < 0) {
			n = -n;
		}
		a = a.normalize();
		double ottenok = 255 - 255 * (sqrt(Vector3(x, y, z).length()) / maximumDistance);
		if (ottenok < 0) ottenok = 0;
		Color c(ottenok, ottenok, ottenok);
		double osv = n * a;
		if (osv < 0) {
			osv = 0;
		}
		c.red = static_cast<int>(min(c.red * osv + 10, 255.0));
		c.green = static_cast<int>(min(c.green * osv + 10, 255.0));
		c.blue = static_cast<int>(min(c.blue * osv + 10, 255.0));
		return c;
	}
};

int main() {
	double fov;
	int x, y;
	ifstream in("conf.txt");
	in >> fov >> x >> y;
	in >> maximumDistance;
	if (x % 2 != 0) {
		x++;
	}
	if (y % 2 != 0) {
		y++;
	}
	bitMapImage im(x, y);
	double ekrY = sqrt(static_cast<double>(x * x) / (2 * (1 - cos(fov / 180 * PI))) - static_cast<double>(x * x) / 4);
	in >> xl >> yl >> zl;
	while (!in.eof()) {
		std::string name;
		in >> name;
		if (name == "sphere") {
			double x, y, z, r;
			in >> x >> y >> z >> r;
			objs.push_back(new Sphere(x, y, z, r));
		}
		else if (name == "poly") {
			double x1, y1, z1, x2, y2, z2, x3, y3, z3;
			in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			objs.push_back(new Polygon(x1, y1, z1, x2, y2, z2, x3, y3, z3));
		}
	}
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
#pragma omp parallel for
	for (int i = -y / 2; i < y / 2; i++) {
#pragma omp parallel for
		for (int j = -x / 2; j < x / 2; j++) {
			bool pixelSet = false;
			for (Object* o : objs) {
				double yx;
				bool isKas;
				if (o->intersect(j, ekrY, i, 0, 0, 0, yx, isKas)) {
					Color c = o->pixelColor(static_cast<double>(j) * yx / ekrY, yx, static_cast<double>(i) * yx / ekrY);
					im.setPixel(x / 2 + j, y / 2 + i, c);
					pixelSet = true;
				}
			}
			if (!pixelSet) {
				im.setPixel(x / 2 + j, y / 2 + i, Color(0, 0, 0));
			}
		}
	}
	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	int elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	std::cout << "Work time: " << elapsed_ms << " ms\n";
	im.saveToFile("out.bmp");
}