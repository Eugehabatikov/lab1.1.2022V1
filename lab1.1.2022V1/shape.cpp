// ѕополнение и использование библиотеки фигур
#include <iostream>
#include "screen.h"
#include "shape.h"

void down(shape& _shape, const shape& target) {
    point n = target.south();
    point s = _shape.north();
    _shape.move(n.x - s.x, n.y - s.y);
}

void add_rigth(shape& _shape, const shape& target) {
    point n = target.east();
    point s = _shape.west();
    _shape.move(n.x - s.x, n.y - s.y);
}

void add_left(shape& _shape, const shape& target) {
    point n = target.west();
    point s = _shape.east();
    _shape.move(n.x - s.x, n.y - s.y);
}

//в этом месте создаем фигуру треугольник перечеркнутый крестом. 
//2 и 3 Ч бакенбарды,14 Ч шишак. ќтражение и поворот


 /* nw(a) ------ n ------ ne
       |		       |
       |		       |
       w	   c            e
       |		       |
       |		       |
       sw(b) ------- s ------ se(c) */


class crossedOutTriangle : public rectangle, public reflectable, public rotatable {
protected:
   // point nw, se;
public:
    crossedOutTriangle(point nw, point se) : rectangle(nw, se) { };
    
    bool isVertFlip = false;
    bool isHorisontFlip = false;
    bool isLeftRotate = false;
    bool isRightRotate = false;
    
    point sw = swest();//point(nw.x, se.y);
    point ne = neast();//point(nw.y, se.x);
    point w = west();
    point e = east();
    point n = north();
    point s = south();
    point nw = nwest();
    point se = seast();
    point c = point(nw.x + (se.x - nw.x) / 2, se.y + (nw.y - se.y) / 2);
    //  void flip_horisontally();
     // void flip_vertically();
      //void rotate_left();
      //void rotate_right();
      //int lengthx = abs(seast().y - nwest().y);
     // int lengthy = abs(nwest().x - seast().x);
    

    void rotate_left() {
        isLeftRotate = true;
    };
    void rotate_right() {
        isRightRotate = true;
    };
    void flip_horisontally() {
        isHorisontFlip = true;
    };
    void flip_vertically() {
        isVertFlip = true;
    };

    void draw()
    {
       if(isHorisontFlip)
        {
            point stor;
            stor = ne; ne = nw; nw = stor;
            stor = sw; sw = se; se = stor;
        }

       if (isVertFlip)
        {
            point stor;
            stor = ne; ne = se; se = stor;
            stor = sw; sw = nw; nw = stor;
        }
        
       if (isRightRotate)
        {
            int len = (ne.x - nw.x) / 2;// половина длинны 
            int h = (nw.y - sw.y) / 2;// половина высоты
            nw.x += len, nw.y += h;
            /**n.y = ne.y - h, e.y = se.y - h, s.y = sw.y - h, w.y = nw.y - h;
            n.x = ne.x, e.x = se.x, s.x = sw.x, w.x = nw.x;
            nw.x = se.x - ((sqrt(pow(se.x - nw.x, 2) + pow(nw.y - se.y, 2))));
            sw.x = c.x;
            sw.y = c.y - h * 2;**/
            nw.y = se.y;
        }

        if (isLeftRotate)
        {

            int len = (ne.x - nw.x) / 2;// половина длинны 
            int h = (nw.y - sw.y) / 2;// половина высоты
            nw.x += len, nw.y += h;
            se.x -= len, se.y -= h;
            sw.x -= len, sw.y += h;
           /** int len = (ne.x - nw.x) / 2;
            n.y = ne.y, e.y = se.y, s.y = sw.y, w.y = nw.y;
            n.x = ne.x + len, e.x = se.x + len, s.x = sw.x + len, w.x = nw.x + len;
            nw.y = se.y + ((sqrt(pow(se.x - nw.x, 2) + pow(nw.y - se.y, 2)))) / 2;
            sw = c;
            nw.x = se.x;**/
        }
        put_line(nw, se);
        put_line(sw, se);
        put_line(nw, sw);
       // put_line(n, s);
       // put_line(w, e);
    }

    void move(int a, int b) {
        draw();
        nw.x += a, nw.y += b;
        se.x += a, se.y += b;
        ne.x += a, ne.y += b;
        sw.x += a, sw.y += b;
        n.x += a,  n.y += b;
        w.x += a, w.y += b;
        s.x += a, s.y += b;
        e.x += a, e.y += b;
    };
};
void topright(shape& p, const shape& q)
    {
        point n = q.seast();
        point s = p.swest();
        p.move(n.x - s.x + 1, n.y - s.y + 2);
    }


void topleft(shape& p, const shape& q)
{ 
       point n = q.swest();
       point s = p.seast();
       p.move(n.x - s.x, n.y - s.y + 2);
}


// Cборна€ пользовательска€ фигура - физиономи€
class myshape : public rectangle { // ћо€ фигура я¬Ћя≈“—я
    int w, h;                         //        пр€моугольником
    line l_eye; // левый глаз Ц мо€ фигура —ќƒ≈–∆»“ линию
    line r_eye; // правый глаз
    line mouth; // рот
public:
    myshape(point, point);

    void draw();

    void move(int, int);

    void resize(int) {}
};

myshape::myshape(point a, point b)
    : rectangle(a, b),    //»нициализаци€ базового класса
    w(neast().x - swest().x + 1), // »нициализаци€ данных
    h(neast().y - swest().y + 1), // - строго в пор€дке объ€влени€!
    l_eye(point(swest().x + 2, swest().y + h * 3 / 4), 2),
    r_eye(point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
    mouth(point(swest().x + 2, swest().y + h / 4), w - 4) {}

void myshape::draw() {
    rectangle::draw(); // онтур лица (глаза и нос рисуютс€ сами!)
    int a = (swest().x + neast().x) / 2;
    int b = (swest().y + neast().y) / 2;
    put_point(point(a, b)); // Ќос Ц существует только на рисунке!
}

void myshape::move(int a, int b) {
    rectangle::move(a, b);
    l_eye.move(a, b);
    r_eye.move(a, b);
    mouth.move(a, b);
}

class crossed_arc : public rectangle, public reflectable {

    // Ќаправление выпуклости дуги
    enum DIRECTION {
        NORTH = 0,
        EAST = 1,
        SOUTH = 2,
        WEST = 3
    };

private:
    DIRECTION bearing;

    void draw_arc(const int X0, const int Y0, const int R) const {
        // R - радиус, X0, Y0 - координаты центра
        int x = 0;
        int y = R;
        int delta = 1 - 2 * R;
        int error = 0;
        while (y >= x) {
            switch (bearing) {
            case NORTH: {
                put_point(X0 + x, Y0 + y);
                put_point(X0 - x, Y0 + y);
                put_point(X0 + y, Y0 + x);
                put_point(X0 - y, Y0 + x);
            }
                      break;
            case SOUTH: {
                put_point(X0 + x, Y0 - y);
                put_point(X0 - x, Y0 - y);
                put_point(X0 + y, Y0 - x);
                put_point(X0 - y, Y0 - x);
            }
                      break;
            case EAST: {
                put_point(X0 + x, Y0 + y);
                put_point(X0 + x, Y0 - y);
                put_point(X0 + y, Y0 + x);
                put_point(X0 + y, Y0 - x);
            }
                     break;
            case WEST: {
                put_point(X0 - x, Y0 + y);
                put_point(X0 - x, Y0 - y);
                put_point(X0 - y, Y0 + x);
                put_point(X0 - y, Y0 - x);
            }
                     break;
            default:
                std::cerr << "Impossible bearing" << std::endl;
                return;
            }
            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0)) {
                delta += 2 * ++x + 1;
                continue;
            }
            if ((delta > 0) && (error > 0)) {
                delta -= 2 * --y + 1;
                continue;
            }
            delta += 2 * (++x - --y);
        }
    }

public:
    crossed_arc(point sw, point ne) : rectangle(sw, ne), bearing(NORTH) {
    }

    void flip_vertically() override {
        switch (bearing) {
        case NORTH:
            bearing = SOUTH;
            break;
        case SOUTH:
            bearing = NORTH;
            break;
        case EAST:
        case WEST:
        default:
            break;
        }
    }

    void flip_horisontally() override {
        switch (bearing) {
        case EAST:
            bearing = WEST;
            break;
        case WEST:
            bearing = EAST;
            break;
        case NORTH:
        case SOUTH:
        default:
            break;
        }
    }

    void rotate_right() override {
        rectangle::rotate_right();
        unsigned int iB = bearing;
        bearing = (DIRECTION)((iB + 1) % 4);
    }

    void rotate_left() override {
        rectangle::rotate_left();
        unsigned int iB = bearing;
        bearing = (DIRECTION)((iB - 1) % 4);
    }

    void draw() override {

        //  рест всегда одинаковый
        put_line(west(), east());
        put_line(north(), south());

        // ќпредел€ем положение центра дуги и ее радиус
        int X1 = 0;
        int Y1 = 0;
        int R = 0;
        switch (bearing) {
        case NORTH:
            X1 = south().x;
            Y1 = south().y;
            R = (seast().x - swest().x) / 2;
            put_line(swest(), seast());
            break;
        case EAST:
            X1 = west().x;
            Y1 = west().y;
            R = (nwest().y - swest().y) / 2;
            put_line(nwest(), swest());
            break;
        case SOUTH:
            X1 = north().x;
            Y1 = north().y;
            R = (neast().x - nwest().x) / 2;
            put_line(nwest(), neast());
            break;
        case WEST:
            X1 = east().x;
            Y1 = east().y;
            R = (neast().y - seast().y) / 2;
            put_line(neast(), seast());
            break;
        default:
            std::cerr << "Impossible bearing" << std::endl;
            return;
        }
        draw_arc(X1, Y1, R);
    }
};

int main() {
    screen_init();
    //== 1.ќбъ€вление набора фигур ==
    crossed_arc collar(point(45, 10), point(57, 15));
    crossed_arc left_horn(point(30, 2), point(42, 7));
    crossed_arc right_horn(point(60, 2), point(72, 7));
    rectangle hat(point(0, 0), point(14, 5));
    line brim(point(0, 15), 17);
    myshape face(point(18, 10), point(30, 18));
    crossedOutTriangle leftSideburn(point(50, 30), point(60, 35));
    crossedOutTriangle rightSideburn(point(73, 30), point(83, 35));
    crossedOutTriangle shishak(point(96, 30), point(106, 35));
    shape_refresh();
    std::cout << "=== Generated... ===\n";
    std::cin.get(); //—мотреть исходный набор
//== 2.ѕодготовка к сборке ==
    hat.rotate_left();
    leftSideburn.flip_horisontally();
    rightSideburn.flip_vertically();
    leftSideburn.flip_vertically();
    shishak.flip_vertically();
    shishak.rotate_left();
    hat.rotate_right();
    brim.resize(2);
    left_horn.rotate_right();
    right_horn.rotate_left();
    face.resize(2);
    collar.flip_vertically();
    shape_refresh();
    std::cout << "=== Prepared... ===\n";
 //   std::cin.get(); //—мотреть результат поворотов/отражений
//== 3.—борка изображени€ ==
    up(brim, face);
    topleft(leftSideburn, face);
    topright(rightSideburn, face);
    up(hat, brim);
    down(collar, face);
    add_left(left_horn, hat);
    add_rigth(right_horn, hat);
    shape_refresh();
    std::cout << "=== Ready! ===\n";
    std::cin.get(); //—мотреть результат
    screen_destroy();
    return 0;
}
