
#pragma once

class Rect {
  private:
    int _x;
    int _y;
    int _w;
    int _h;

  public:
    Rect(int x, int y, int w, int h) : _x(x), _y(y), _w(w), _h(h) {}
    Rect() : Rect(0, 0, 0, 0) {}

    int getX() const { return _x; }
    int getY() const { return _y; }
    int getW() const { return _w; }
    int getH() const { return _h; }

    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    void setW(int w) { _w = w; }
    void setH(int h) { _h = h; }

    friend bool operator==(const Rect &a, const Rect &b) {
        return a._x == b._x && a._y == b._y && a._w == b._w && a._h == b._h;
    }
};
