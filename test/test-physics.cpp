

#include <LunatiX/Lunatix.hpp>
#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace LX_Physics;

void test_euclide(void);
void test_collisionPointCircle(void);
void test_collisionPointRect(void);
void test_collision2Circle(void);
void test_collision2Rect(void);
void test_collisionRectCircle(void);

void testLine();
void test_Vector2D(void);
void testPolygon(void);

void test_collisionSeg(void);
void test_collisionPointPolygon(void);
void test_collisionCirclePolygon(void);
void test_collisionRectPolygon(void);
void test_collision2Polygon(void);
void test_collision2PolygonAgain(void);

void test_move(void);
void test_assignment(void);
void test_operator(void);

void test_VectorPlusMinusOp(void);
void test_VectorOpposite(void);
void test_VectorIncDec(void);
void test_VectorCollinear(void);
void test_VectorLambda(void);

using namespace LX_Physics;

void displayPoly(LX_Polygon& poly);

int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(!err)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - LX_Init() failed");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The LunatiX library has been initialized with success");

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Physics ==== \n");

    test_euclide();
    test_collisionPointCircle();
    test_collisionPointRect();
    test_collision2Circle();
    test_collision2Rect();
    test_collisionRectCircle();

    testLine();
    test_Vector2D();
    testPolygon();

    test_collisionSeg();
    test_collisionPointPolygon();
    test_collisionCirclePolygon();
    test_collisionRectPolygon();
    test_collision2Polygon();
    test_collision2PolygonAgain();

    test_move();
    test_assignment();
    test_operator();

    test_VectorPlusMinusOp();
    test_VectorOpposite();
    test_VectorIncDec();
    test_VectorCollinear();
    test_VectorLambda();

    LX_Quit();
    LX_Log::log(" ==== END Physics ==== \n");
    return EXIT_SUCCESS;
}


// Test the euclidean functions
void test_euclide(void)
{
    LX_Point A = {1,1};
    LX_Point B = {10,1};
    LX_Point C = {0,0};
    LX_Point D = {10,10};

    LX_Log::log(" = TEST EUCLIDE = ");
    LX_Log::log("A(%d,%d)",A.x,A.y);
    LX_Log::log("B(%d,%d)",B.x,B.y);
    LX_Log::log("C(%d,%d)",C.x,C.y);
    LX_Log::log("D(%d,%d)",D.x,D.y);
    LX_Log::log("Square distance AB");

    float d = euclide_square_distance(A,B);

    if(d != 81.0f)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Bad square distance AB - expected: 81; Got: %f",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Good square distance AB: %f",d);

    LX_Log::log("Distance between A and B");
    d = euclide_distance(A,B);

    if(d != 9.0f)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Bad distance AB - expected: 9; Got: %f",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Good distance AB: %f",d);

    // Test CD
    LX_Log::log("Square distance CD");
    d = euclide_square_distance(C,D);

    if(d != 200.0f)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Bad square distance CD - expected: 81; Got: %f",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Good square distance CD: %f",d);

    LX_Log::log("Distance between C and D");
    d = euclide_distance(C,D);

    if(static_cast<int>(d) != static_cast<int>(sqrt(200)))
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Bad distance CD - expected: %f; Got: %f",
                        static_cast<float>(sqrt(200)),d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Good square distance CD: %f",d);

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointCircle(void)
{
    LX_Circle circle(LX_Point(100,100),10);

    LX_Point A = {100,100};
    LX_Point B = {50,50};
    LX_Point C = {105,105};
    LX_Point D = {100,125};

    LX_Log::log(" = TEST POINT/CIRCLE = ");
    LX_Log::log("A(%d,%d)",A.x,A.y);
    LX_Log::log("B(%d,%d)",B.x,B.y);
    LX_Log::log("C(%d,%d)",C.x,C.y);
    LX_Log::log("D(%d,%d)",D.x,D.y);

    LX_Log::log("Collision Point A/Circle");
    bool d = collisionPointCircle(A.x,A.y,circle);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: TRUE; Got: %d",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is in the circle: %d",d);

    LX_Log::log("Collision Point B/Circle");
    d = collisionPointCircle(B.x,B.y,circle);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is not in the circle");

    LX_Log::log("Collision Point C/Circle");
    d = collisionPointCircle(C,circle);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is in the circle");

    LX_Log::log("Collision Point D/Circle");
    d = collisionPointCircle(D,circle);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is not in the circle");

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointRect(void)
{
    LX_Point A,B;
    LX_AABB aabb;

    A = {100,100};
    B = {50,50};
    aabb = {40,40,30,30};

    LX_Log::log(" = TEST POINT/AABB = ");
    LX_Log::log("A(%d,%d)",A.x,A.y);
    LX_Log::log("B(%d,%d)",B.x,B.y);
    LX_Log::log("AABB{(%d,%d),%d,%d}",aabb.x,aabb.y,aabb.w,aabb.h);

    LX_Log::log("Collision Point A/AABB");
    bool d = collisionPointRect(A.x,A.y,aabb);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is out of the rectangle");

    LX_Log::log("Collision Point B/AABB");
    d = collisionPointRect(B.x,B.y,aabb);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is into the rectangle");

    LX_Log::log(" = END TEST = ");
}


void test_collision2Circle(void)
{
    LX_Circle A(LX_Point(10,10),5);
    LX_Circle B(LX_Point(13,12),3);
    LX_Circle C(LX_Point(100,100),50);

    LX_Log::log(" = TEST CIRCLE/CIRCLE = ");
    LX_Log::log("A{(%d,%d),%d}", A.center.x, A.center.y, A.radius);
    LX_Log::log("B{(%d,%d),%d}", B.center.x, B.center.y, B.radius);
    LX_Log::log("C{(%d,%d),%d}", C.center.x, C.center.y, C.radius);

    LX_Log::log("Collision Circles A/B");
    bool d = collisionCircle(A,B);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE -collision A/B expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision between two circles A and B");

    LX_Log::log("Collision Circles C/B");
    d = collisionCircle(C,B);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collisoon C/B expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - no collision between two circles C and B");

    LX_Log::log("Collision Circles A/C");
    d = collisionCircle(A,C);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collisoon C/B expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - no collision between two circles A and C");

    LX_Log::log(" = END TEST = ");
}


void test_collision2Rect(void)
{
    LX_AABB R1,R2,R3;

    R1 = {0,0,50,25};
    R2 = {40,21,32,25};
    R3 = {64,32,10,100};

    LX_Log::log(" = TEST RECT/RECT = ");
    LX_Log::log("R1{(%d,%d),%d,%d}", R1.x, R1.y, R1.w, R1.h);
    LX_Log::log("R2{(%d,%d),%d,%d}", R2.x, R2.y, R2.w, R2.h);
    LX_Log::log("R3{(%d,%d),%d,%d}", R3.x, R3.y, R3.w, R3.h);

    LX_Log::log("Collision AABB R1/R2");
    bool d = collisionRect(R1,R2);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE -collision R1/R2 expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision R1/R2 OK");

    LX_Log::log("Collision AABB R2/R3");
    d = collisionRect(R2,R3);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE -collision R2/R3 expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision R2/R3 OK");

    LX_Log::log("Collision AABB R3/R1");
    d = collisionRect(R3,R1);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collisoon R3/R1 expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - no collision R3/R1 OK");

    LX_Log::log(" = END TEST = ");
}


void test_collisionRectCircle(void)
{
    LX_AABB R1;

    R1 = {0,0,50,25};
    LX_Circle A(LX_Point(10,10),5);
    LX_Circle B(LX_Point(51,26),15);
    LX_Circle C(LX_Point(100,100),40);

    LX_Log::log(" = TEST RECT/CIRCLE = ");
    LX_Log::log("R1{(%d,%d),%d,%d}", R1.x, R1.y, R1.w, R1.h);
    LX_Log::log("A{(%d,%d),%d}", A.center.x, A.center.y, A.radius);
    LX_Log::log("B{(%d,%d),%d}", B.center.x, B.center.y, B.radius);
    LX_Log::log("C{(%d,%d),%d}", C.center.x, C.center.y, C.radius);

    LX_Log::log("Collision Circle/Rect AABB A/R1");
    bool d = collisionCircleRect(A,R1);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collision A/R1 expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision A/R1 OK");

    LX_Log::log("Collision Circle/Rect AABB B/R1");
    d = collisionCircleRect(B,R1);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collision B/R1 expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision B/R1 OK");

    LX_Log::log("Collision Circle/Rect AABB C/R1");
    d = collisionCircleRect(C,R1);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collision C/R1 expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision C/R1 OK");

    LX_Log::log(" = END TEST = ");
}


void testPolygon(void)
{
    LX_Polygon poly;
    LX_Point p, q, r;

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);

    LX_Log::log(" = TEST POLYGON = ");
    LX_Log::log("Number of edges");
    unsigned long d = poly.numberOfEdges();

    if(d != 3)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - number of real edges expected: 3; Got: %u",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - number of real edges: %u",d);

    displayPoly(poly);

    p = poly.getPoint(0);
    LX_Log::log("poly.getPoint(0): (%d,%d)", p.x, p.y);

    if(p.x != 10)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - x position expected: 10; Got: %d",p.x);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - x = %d",p.x);

    if(p.y != 5)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - y position expected: 5; Got: %d",p.y);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - y = %d",p.y);

    // Is the triangle convex ?
    LX_Log::log("Test the convexity of the polygon.");
    if(poly.isConvex() == false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - A triangle is not a non-convex polygon");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The triangle is a convex polygon, well done !");

    {
        LX_AABB b = poly.getEnclosingBox();
        LX_Log::log("enclosing box {%d, %d, %d, %d}", b.x, b.y, b.w, b.h);
    }

    // Now we have a polygon with 4 edges
    q = {7,2};
    LX_Log::log("add point p(%d,%d)", q.x, q.y);
    poly.addPoint(q);

    // It must be convex
    LX_Log::log("Test the convexity of the polygon with the new point.");
    if(poly.isConvex() == false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Expected: convex; Got: non-convex");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Added (7,2). This is still a convex polygon, well done !");

    // New edge
    r = {6,5};
    LX_Log::log("add point p(%d,%d)", r.x, r.y);
    poly.addPoint(6,5);

    // It must be non-convex
    LX_Log::log("Test the convexity of the polygon with the new point (again).");
    if(poly.isConvex() == true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Expected: non-convex; Got: convex");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Added (6,5). This is not a convex polygon");

    {
        LX_AABB b = poly.getEnclosingBox();
        LX_Log::log("enclosing box {%d, %d, %d, %d}", b.x, b.y, b.w, b.h);
    }

    LX_Log::log(" = END TEST = ");
}


void testLine()
{
    LX_Log::log("= TEST Vector2D =");

    LX_Vector2D v{0.0f,4.0f};
    LX_Vector2D u{0.0f,42.0f};
    LX_Vector2D w{21.0f,0.0f};
    LX_Line l1(LX_Point(1,1), v);
    LX_Line l2(LX_Point(5,21), u);
    LX_Line l3(LX_Point(1,1), w);

    LX_Log::log("line #1: (%d, %d) - (%f, %f)", l1.o.x, l1.o.y, l1.v.vx.v, l1.v.vy.v);
    LX_Log::log("line #2: (%d, %d) - (%f, %f)", l2.o.x, l2.o.y, l2.v.vx.v, l2.v.vy.v);
    LX_Log::log("line #3: (%d, %d) - (%f, %f)", l3.o.x, l3.o.y, l3.v.vx.v, l3.v.vy.v);

    if(l1.isParralelWith(l2))
        LX_Log::log("SUCCESS - parralel: l1 and l2");
    else
        LX_Log::log("FAILURE - expected: parralel");

    if(!l1.isParralelWith(l3))
        LX_Log::log("SUCCESS - not parralel: l1 and l3");
    else
        LX_Log::log("FAILURE - expected: not parralel");

    if(l1.isPerpendicularTo(l3))
        LX_Log::log("SUCCESS - perpendicular: l1 and l3");
    else
        LX_Log::log("FAILURE - expected: perpendicular");

    if(!l1.isPerpendicularTo(l2))
        LX_Log::log("SUCCESS - not perpendicular: l1 and l2");
    else
        LX_Log::log("FAILURE - expected: not perpendicular");

    if(intersectLine(l1, l3))
        LX_Log::log("SUCCESS - intersection: l1 and l3");
    else
        LX_Log::log("FAILURE - expected: intersection");

    if(intersectLine(l2, l3))
        LX_Log::log("SUCCESS - intersection: l2 and l3");
    else
        LX_Log::log("FAILURE - expected: intersection");

    LX_Log::log("= END TEST =");
}


void test_Vector2D(void)
{
    LX_Point p(1,2), q(2,-1);

    LX_Vector2D v{1.0f,2.0f};
    LX_Vector2D u{2.0f,-1.0f};
    LX_Vector2D z{0.0f,0.0f};
    LX_Vector2D w{q.x - p.x, q.y - p.y};

    LX_Log::log(" = TEST Vector2D = ");
    LX_Log::log("v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("z(%f,%f)", z.vx.v, z.vy.v);
    LX_Log::log("w(%f,%f)", w.vx.v, w.vy.v);
    LX_Log::log("scalar product (v,u)");
    float d = scalar_product(v,u);

    if(d != 0.0f)
        LX_Log::log("FAILURE - scalar product v(1,2).u(2,-1) expected: 0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - scalar product v(1,2).u(2,-1) = 0");

    LX_Log::log("scalar product (z,z)");
    d = scalar_product(z,z);

    if(d != 0.0f)
        LX_Log::log("FAILURE - scalar product z.z (z is a null vector) expected: 0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - scalar product z.z = 0");

    LX_Log::log("norm of z");
    d = vector_norm(z);

    if(d != 0.0f)
        LX_Log::log("FAILURE - norm of z (z is a null vector) expected: 0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - norm of z = 0");


    LX_Log::log("norm of v");
    d = vector_norm(v);

    if(static_cast<int>(d) != static_cast<int>(sqrtf(5)))
        LX_Log::log("FAILURE - norm of v (z is a null vector) expected: %f; Got: %f",
                    sqrtf(5), d);
    else
        LX_Log::log("SUCCESS - norm of v = %f", d);


    LX_Log::log("vector product (v,u)");
    d = vector_product(v,u);

    if(static_cast<int>(d) != static_cast<int>(-5.0f))
        LX_Log::log("FAILURE - vector product v(1,2).u(2,-1) expected: -5.0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - vector product v(1,2).u(2,-1) = %f", d);


    d = vector_product(u,v);

    if(d != 5.0f)
        LX_Log::log("FAILURE - vector product u(2,-1).v(1,2) expected: 5.0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - vector product u(2,-1).v(1,2) = %f", d);


    d = vector_product(z,z);

    if(d != 0.0f)
        LX_Log::log("FAILURE - vector product z.z (z is a null vector) expected: 0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - vector product z.z = 0");

    LX_Log::log(" = END TEST = ");
}


void test_collisionSeg(void)
{
    LX_Point A,B,C,D,E,F;
    bool d;

    A.x =  5;
    A.y =  5;
    B.x = 10;
    B.y = 10;
    C.x =  5;
    C.y = 10;
    D.x = 10;
    D.y =  5;
    E.x = 20;
    E.y =  5;
    F.x = 15;
    F.y =  5;

    LX_Log::log(" = TEST Collision Segment = ");
    LX_Log::log("A(%d,%d)", A.x, A.y);
    LX_Log::log("B(%d,%d)", B.x, B.y);
    LX_Log::log("C(%d,%d)", C.x, C.y);
    LX_Log::log("D(%d,%d)", D.x, D.y);
    LX_Log::log("E(%d,%d)", E.x, E.y);
    LX_Log::log("F(%d,%d)", F.x, F.y);
    LX_Log::log("collision segement [AB]/[CD]");

    d = intersectSegment(A,B,C,D);

    if(d != true)
        LX_Log::log("FAILURE - intersect [AB]/[CD] expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - intersect [AB]/[CD] OK");


    LX_Log::log("collision segement [AC]/[BD]");
    d = intersectSegment(A,C,B,D);

    if(d != false)
        LX_Log::log("FAILURE - intersect [AC]/[BD] expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - no intersect [AC]/[BD] OK");

    LX_Log::log("collision segement [AB]/[AD]");
    d = intersectSegment(A,B,A,D);

    if(d != true)
        LX_Log::log("FAILURE - intersect [AB]/[AD] expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - intersect [AB]/[AD] OK");

    LX_Log::log("collision segement [AD]/[AE]");
    d = intersectSegment(A,D,A,E);

    if(d != true)
        LX_Log::log("FAILURE - intersect [AD]/[AE] expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - intersect [AD]/[AE] OK");

    LX_Log::log("collision segement [AD]/[FE]");
    d = intersectSegment(A,D,F,E);

    if(d != true)
        LX_Log::log("FAILURE - intersect [AD]/[FE] expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - no intersect [AD]/[FE] OK");

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointPolygon(void)
{
    /*
        Be careful, if the coordinates of a point
        are to high, you will have incorrect results
    */
    LX_Polygon poly, polyc2;

    LX_Point N = {12,7};
    LX_Point O = {9,7};
    LX_Point P = {6,5};
    LX_Point Q = {6,4};
    LX_Point R = {1024,2048};
    LX_Point S = {2,2};
    LX_Point T = {10,5};

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    polyc2.addPoint(12,5);
    polyc2.addPoint(12,12);
    polyc2.addPoint(4,5);
    polyc2.addPoint(7,0);

    LX_Log::log(" = TEST Collision Point/Polygon = ");
    displayPoly(poly);
    LX_Log::log("N(%d,%d)", N.x, N.y);
    LX_Log::log("O(%d,%d)", O.x, O.y);
    LX_Log::log("P(%d,%d)", P.x, P.y);
    LX_Log::log("Q(%d,%d)", Q.x, Q.y);
    LX_Log::log("R(%d,%d)", R.x, R.y);
    LX_Log::log("S(%d,%d)", S.x, S.y);
    LX_Log::log("T(%d,%d)", T.x, T.y);

    LX_Log::log("collision Point N/Polygon");
    bool d = collisionPointPoly(N,poly);

    if(d != false)
        LX_Log::log("FAILURE - N in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - N not in the polygon OK");

    LX_Log::log("collision Point O/Polygon");
    d = collisionPointPoly(O,poly);

    if(d != true)
        LX_Log::log("FAILURE - N not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - N in the polygon OK");

    LX_Log::log("collision Point P/Polygon");
    d = collisionPointPoly(P,poly);

    if(d != true)
        LX_Log::log("FAILURE - P not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - P in the polygon OK");

    LX_Log::log("collision Point Q/Polygon");
    d = collisionPointPoly(Q,poly);

    if(d != true)
        LX_Log::log("FAILURE - Q not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - Q in the polygon OK");

    LX_Log::log("collision Point R/Polygon");
    d = collisionPointPoly(R,poly);

    if(d != false)
        LX_Log::log("FAILURE - R in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - R not in the polygon OK");

    LX_Log::log("collision Point S/Polygon");
    d = collisionPointPoly(S,poly);

    if(d != false)
        LX_Log::log("FAILURE - S in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - S not in the polygon OK");

    LX_Log::log("collision Point T/Polygon");
    d = collisionPointPoly(T,polyc2);

    if(d != true)
        LX_Log::log("FAILURE - T not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - T in the polygon OK");

    LX_Log::log(" = END TEST = ");
}


void test_collisionCirclePolygon(void)
{
    LX_Circle M(LX_Point(12,7),1);
    LX_Circle N(LX_Point(12,7),2);
    LX_Circle O(LX_Point(9,7),10);
    LX_Circle S(LX_Point(2,2),2);
    LX_Polygon poly;

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    LX_Log::log(" = TEST Collision Circle/Polygon = ");

    LX_Log::log("M{(%d,%d),%d}", M.center.x, M.center.y, M.radius);
    LX_Log::log("N{(%d,%d),%d}", N.center.x, N.center.y, N.radius);
    LX_Log::log("O{(%d,%d),%d}", O.center.x, O.center.y, O.radius);
    LX_Log::log("S{(%d,%d),%d}", S.center.x, S.center.y, S.radius);
    displayPoly(poly);

    LX_Log::log("Collision Circle M/Polygon");
    bool d = collisionCirclePoly(M,poly);

    if(d != false)
        LX_Log::log("FAILURE - M in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - M not in the polygon OK");

    LX_Log::log("Collision Circle S/Polygon");
    d = collisionCirclePoly(S,poly);

    if(d != false)
        LX_Log::log("FAILURE - S in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - S not in the polygon OK");

    LX_Log::log("Collision Circle N/Polygon");
    d = collisionCirclePoly(N,poly);

    if(d != true)
        LX_Log::log("FAILURE - N not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - N in the polygon OK");

    LX_Log::log("Collision Circle O/Polygon");
    d = collisionCirclePoly(O,poly);

    if(d != true)
        LX_Log::log("FAILURE - O not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - O in the polygon OK");

    LX_Log::log(" = END TEST = ");
}


void test_collisionRectPolygon(void)
{
    LX_AABB R1,R2,R3,R4,R5;
    LX_Polygon poly;

    R1 = {1,1,2,2};
    R2 = {8,3,10,4};
    R3 = {2,7,20,2};
    R4 = {8,6,1,1};
    R5 = {2,0,16,16};

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    LX_Log::log(" = TEST Collision Rect/Polygon = ");
    LX_Log::log("R1{(%d,%d),%d,%d}", R1.x, R1.y, R1.w, R1.h);
    LX_Log::log("R2{(%d,%d),%d,%d}", R2.x, R2.y, R2.w, R2.h);
    LX_Log::log("R3{(%d,%d),%d,%d}", R3.x, R3.y, R3.w, R3.h);
    LX_Log::log("R4{(%d,%d),%d,%d}", R4.x, R4.y, R4.w, R4.h);
    LX_Log::log("poly");
    displayPoly(poly);

    bool d = collisionRectPoly(R1,poly);

    if(d != false)
        LX_Log::log("FAILURE - test R1 not in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - R1 not in the polygon OK");

    // A point of R2 in the polygon
    d = collisionRectPoly(R2,poly);

    if(d != true)
        LX_Log::log("FAILURE - test R2 touch the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - R2 touch the polygon OK");

    // Some Segments of R3 in the polygon (no point inside)
    d = collisionRectPoly(R3,poly);

    if(d != true)
        LX_Log::log("FAILURE - test R3 touch the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - R3 touch the polygon OK");

    // R4 into the polygon
    d = collisionRectPoly(R4,poly);

    if(d != true)
        LX_Log::log("FAILURE - test R4 touch the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - R4 touch the polygon OK");

    // The polygon into R5
    d = collisionRectPoly(R5,poly);

    if(d != true)
        LX_Log::log("FAILURE - test polygon into R5. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - polygon into R5 OK");

    LX_Log::log(" = END TEST = ");
}

void test_collision2Polygon(void)
{
    LX_Polygon poly_empty1, poly_empty2;
    LX_Polygon polyc, polyc2, polync, polync2;
    LX_Polygon poly, poly2, poly3, poly4;

    // Convex polygon
    polyc.addPoint(10,5);
    polyc.addPoint(10,10);
    polyc.addPoint(5,5);
    polyc.addPoint(7,2);

    // Non-convex polygon
    polync.addPoint(1000,500);
    polync.addPoint(1000,1000);
    polync.addPoint(500,500);
    polync.addPoint(700,200);
    polync.addPoint(600,500);

    // Non-convex polygon (again)
    polync2.addPoint(10,5);
    polync2.addPoint(10,10);
    polync2.addPoint(5,5);
    polync2.addPoint(7,2);
    polync2.addPoint(6,5);

    polyc2.addPoint(12,5);
    polyc2.addPoint(12,12);
    polyc2.addPoint(4,5);
    polyc2.addPoint(7,0);

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    poly2.addPoint(9,6);
    poly2.addPoint(9,9);
    poly2.addPoint(6,4);
    poly2.addPoint(6,3);
    poly2.addPoint(5,6);

    poly3.addPoint(0,0);
    poly3.addPoint(32,32);
    poly3.addPoint(0,32);

    poly4.addPoint(2,2);
    poly4.addPoint(2,3);
    poly4.addPoint(3,4);

    LX_Log::log(" = TEST Collision Polygon/Polygon = ");

    LX_Log::log("poly");
    displayPoly(poly);
    LX_Log::log("poly2");
    displayPoly(poly2);
    LX_Log::log("poly3");
    displayPoly(poly3);
    LX_Log::log("poly4");
    displayPoly(poly4);
    LX_Log::log("polyc");
    displayPoly(polyc);
    LX_Log::log("polyc2");
    displayPoly(polyc2);
    LX_Log::log("polync");
    displayPoly(polync);
    LX_Log::log("polync2");
    displayPoly(polync2);

    bool d = collisionPoly(poly,poly2);

    if(d != true)
        LX_Log::log("FAILURE - no collision poly/poly2. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision poly/poly2");


    d = collisionPoly(poly,poly3);

    if(d != true)
        LX_Log::log("FAILURE - no collision poly/poly3. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision poly/poly3");


    d = collisionPoly(poly,poly4);

    if(d != false)
        LX_Log::log("FAILURE - no collision poly/poly4. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision poly/poly4");

    // Empty polygons
    LX_Log::log("collision between two empty polygons");
    try
    {
        collisionPoly(poly_empty1,poly_empty2);
        LX_Log::log("FAILURE - this collision cannot be calculated");
    }
    catch(std::invalid_argument&)
    {
        LX_Log::log("SUCCESS - std::invalid_argument exception occured");
    }
    catch(...)
    {
        LX_Log::log("FAILURE - unknown exception occurred");
    }

    LX_Log::log("collision between two convex polygons");
    d = collisionPoly(polyc,polyc2);

    if(d != true)
        LX_Log::log("FAILURE - no collision polyc/polyc2. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision polyc/polyc2");

    // convex/non-convex
    LX_Log::log("collision between a convex polygon and a non-convex polygon");
    d = collisionPoly(polyc2,polync);

    if(d == true)
        LX_Log::log("FAILURE - collision polyc2/polycnc. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - no collision polyc2/polync");

    // Another test
    LX_Log::log("collision between a convex polygon and a non-convex polygon (again)");
    d = collisionPoly(polyc2,polync2);

    if(d != true)
        LX_Log::log("FAILURE - no collision polyc2/polync2. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision polyc2/polync2");

    // convex/triangle (that is convex)
    LX_Log::log("collision between a convex polygon and a triangle");
    d = collisionPoly(polyc2,poly3);

    if(d != true)
        LX_Log::log("FAILURE - no collision polyc2/poly3. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision polyc2/poly3");

    LX_Log::log(" = END TEST = ");
}

void test_collision2PolygonAgain(void)
{
    const long N = 100000;
    const long M = 1000;
    LX_Polygon poly1, poly2;
    LX_Polygon poly3, poly4;
    unsigned int t1,t2;

    LX_Log::log(" = TEST Collision BIG Polygon/Polygon = ");
    LX_Random::initRand();

    LX_Log::log("Generate two random polygons with %d sides",N);
    for(unsigned int i = 0; i < N; i++)
    {
        poly1.addPoint(LX_Random::xorshiftRand()%M, LX_Random::xorshiftRand()%M);
        poly2.addPoint(LX_Random::xorshiftRand()%M, LX_Random::xorshiftRand()%M);
    }

    LX_Log::log("Calculate the collision #1");
    t1 = SDL_GetTicks();
    bool d = collisionPoly(poly1, poly2);
    t2 = SDL_GetTicks();
    LX_Log::log("Result:%s collision between the two random polygons", (d ? "":" No"));
    LX_Log::log("Calculation done in %d ms", t2-t1);

    LX_Log::log("Generate two other random polygons with %d sides in two different areas",N);
    for(unsigned int i = 0; i < N; i++)
    {
        poly3.addPoint(LX_Random::xorshiftRand()%M, LX_Random::xorshiftRand()%M);
        poly4.addPoint(LX_Random::xorshiftRand()%M+N, LX_Random::xorshiftRand()%M+N);
    }

    LX_Log::log("Calculate the collision #2");
    t1 = SDL_GetTicks();
    d = collisionPoly(poly3,poly4);
    t2 = SDL_GetTicks();
    LX_Log::log("t1: %d; t2: %d",t1,t2);
    LX_Log::log("Result:%s collision between the two random polygons",(d ? "":" No"));
    LX_Log::log("Calculation done in %d ms",t2-t1);

    LX_Log::log(" = END TEST = ");
}


void test_move(void)
{
    LX_Point P = {1,2};
    LX_AABB R = {8,4,10,10};

    const int X = -4;
    const int Y = 8;

    LX_Polygon poly;
    LX_Polygon expoly;

    poly.addPoint(24,32);
    poly.addPoint(48,32);
    poly.addPoint(128,64);
    poly.addPoint(64,64);
    poly.addPoint(32,32);
    // expected polygon
    expoly.addPoint(24+X,32+Y);
    expoly.addPoint(48+X,32+Y);
    expoly.addPoint(128+X,64+Y);
    expoly.addPoint(64+X,64+Y);
    expoly.addPoint(32+X,32+Y);

    LX_Log::log(" = TEST Move = ");

    LX_Log::log("P(%d,%d)", P.x, P.y);
    LX_Log::log("R{(%d,%d),%d,%d}", R.x, R.y, R.w, R.h);
    LX_Log::log("poly");
    displayPoly(poly);
    LX_Log::log("expoly");
    displayPoly(expoly);

    LX_Log::log("Point");

    LX_Point expected_point = {P.x +1, P.y +1};
    movePoint(P,1,1);

    if(P.x == expected_point.x && P.y == expected_point.y)
        LX_Log::log("Point P(%d,%d)", P.x, P.y);
    else
        LX_Log::log("FAILURE - expected : Point P(2,3); Got: P(%d,%d)", P.x, P.y);

    LX_Log::log("Rectangle");

    LX_AABB expected_aabb = {R.x +2, R.y +3, R.w, R.h};
    moveRect(R,2,3);

    if(R.x == expected_aabb.x && R.y == expected_aabb.y)
        LX_Log::log("SUCCESS - Rectangle R{(%d,%d),%d,%d}", R.x, R.y, R.w, R.h);
    else
        LX_Log::log("FAILURE - expected : Rectangle R(3,6,10,10); got: R{(%d,%d),%d,%d}",
                    R.x, R.y, R.w, R.h);

    movePoly(poly,X,Y);
    const unsigned long n = poly.numberOfEdges();
    const unsigned long m = expoly.numberOfEdges();

    LX_Log::log("expected polygon");
    displayPoly(expoly);
    LX_Log::log("got");
    displayPoly(poly);

    if(n != m)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - ≠ degree. #edges expected: %d, got: %d",m,n);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - these polygons have the same degree");

    try
    {
        bool ok = true;
        for(unsigned int j = 0; j < n; j++)
        {
            LX_Point p1 = poly.getPoint(j);
            LX_Point p2 = expoly.getPoint(j);
            if(p1 != p2)
            {
                LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - at j = %d → ≠ point; expected: (%d,%d); got: (%d,%d)",
                                j,p2.x,p2.y,p1.x,p1.y);
                ok = false;
                break;
            }
        }

        if(ok)
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The 2 polygons are identical");
    }
    catch(...)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - uncaught exception at %s:%d",__FILE__,__LINE__);
    }

    // reset
    movePoly(poly,-X,-Y);
    LX_AABB box = expoly.getEnclosingBox();
    LX_Point q(box.x + box.w/2, box.y + box.h/2);

    movePolyTo(poly, q.x, q.y);
    LX_AABB b = poly.getEnclosingBox();
    LX_Point s(b.x + b.w/2, b.y + b.h/2);
    LX_Log::log("centroid of poly: s(%d,%d)", s.x, s.y);
    LX_Log::log("centroid of expoly: q(%d,%d)", q.x, q.y);

    LX_Log::log(" = END TEST = ");
}


void test_assignment(void)
{
    LX_Log::log(" = TEST Assignement = ");

    LX_Point P = {1,2};
    LX_Point Q;

    LX_Log::log("P(%d,%d)", P.x, P.y);

    Q = P;  // assignment

    if(Q == P)
        LX_Log::log("SUCCESS - Point Q(%d,%d)", Q.x, Q.y);
    else
        LX_Log::log("FAILURE - expected: Q(1,2); Got: Q(%d,%d)", Q.x, Q.y);

    LX_Circle C(LX_Point(4,9),10);

    LX_Log::log("C{(%d,%d),%d}; square radius: %d", C.center.x, C.center.y,
                C.radius, C.square_radius);

    LX_Circle D = C;  // assignment

    if(D == C)
        LX_Log::log("SUCCESS - Circle D{(%d,%d),%d}; square radius =  %d", D.center.x, D.center.y,
                    D.radius, D.square_radius);
    else
        LX_Log::log("FAILURE - expected: Circle D{{4,9},10} with suare radius = 100; Got: D{(%d,%d),%d}; square radius = %d",
                    D.center.x, D.center.y, D.radius, D.square_radius);

    LX_Vector2D v = {3.14f,1.59f};
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);

    LX_Vector2D u = v;  // assignment

    if(u == v)
        LX_Log::log("SUCCESS - Vector2D v(%f,%f)", u.vx.v, u.vy.v);
    else
        LX_Log::log("FAILURE - expected: u(3.14,1.59); Got: u(%f,%f)", u.vx.v, u.vy.v);

    LX_Vector2D t{0.0f,0.0f}, w{0.0f,0.0f};

    if(t == w)
        LX_Log::log("SUCCESS - Vector2D t(%f,%f)", t.vx.v, t.vy.v);
    else
        LX_Log::log("FAILURE - expected: w(0.0f,0.0f); Got: u(%f,%f)", w.vx.v, w.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_operator(void)
{
    LX_Circle C(LX_Point(2,3),10);
    LX_Circle E(LX_Point(4,9),32);
    LX_Circle F(LX_Point(8,21),10);

    /// @todo TEST FAILURE

    LX_Vector2D v{-3.14f, 1.59f};
    LX_Vector2D u = v;
    LX_Vector2D w{3.140001f,1.590001f};
    LX_Vector2D i{2.56f,1.59f};
    LX_Vector2D j{-0.14f,-1.28f};

    LX_Log::log(" = TEST operators = ");

    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("C{(%d,%d),%d}; square radius = %d", C.center.x, C.center.y,
                C.radius, C.square_radius);
    LX_Log::log("E{(%d,%d),%d}; square radius = %d", E.center.x, E.center.y,
                E.radius, E.square_radius);
    LX_Log::log("F{(%d,%d),%d}; square radius = %d", F.center.x, F.center.y,
                F.radius, F.square_radius);
    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("Vector2D w(%f,%f)", w.vx.v, w.vy.v);
    LX_Log::log("Vector2D i(%f,%f)", i.vx.v, i.vy.v);
    LX_Log::log("Vector2D j(%f,%f)", j.vx.v, j.vy.v);

    if(E > C)
        LX_Log::log("SUCCESS - E > C");
    else
        LX_Log::log("FAILURE - E ≤ C");

    if(C < E)
        LX_Log::log("SUCCESS - C < E");
    else
        LX_Log::log("FAILURE - C ≥ E");

    if(E >= C)
        LX_Log::log("SUCCESS - E ≥ C");
    else
        LX_Log::log("FAILURE - E < C");

    if(C <= E)
        LX_Log::log("SUCCESS - C ≤ E");
    else
        LX_Log::log("FAILURE - C > E");

    if(F >= C)
        LX_Log::log("SUCCESS - F ≥ C");
    else
        LX_Log::log("FAILURE - F < C");

    if(C <= F)
        LX_Log::log("SUCCESS - C ≤ F");
    else
        LX_Log::log("FAILURE - C > F");

    if(!(E < C))
        LX_Log::log("SUCCESS - !(E < C)");
    else
        LX_Log::log("FAILURE - E < C");

    LX_Log::log("E ≠ C ?");
    if(E != C)
        LX_Log::log("SUCCESS - E ≠ C");
    else
        LX_Log::log("FAILURE - E == C");

    LX_Log::log(" !(E == C) ?");
    if(!(E == C))
        LX_Log::log("SUCCESS - !(E == C)");
    else
        LX_Log::log("FAILURE - E == C");

    if(u == v)
        LX_Log::log("SUCCESS - u == v");
    else
        LX_Log::log("FAILURE - expected: u == v; Got: u(%f,%f) ≠ v(%f,%f)",
                    u.vx.v, u.vy.v, v.vx.v, v.vy.v);

    if(v == w)
        LX_Log::log("FAILURE - expected: v ≠ w; Got: v(%f,%f) ≠ w(%f,%f)",
                    v.vx.v, v.vy.v, w.vx.v, w.vy.v);
    else
        LX_Log::log("SUCCESS - v ≠ w");

    if(v != i)
        LX_Log::log("SUCCESS - v ≠ i");
    else
        LX_Log::log("FAILURE - expected: v ≠ i; Got: v(%f,%f) ≠ i(%f,%f)",
                    v.vx.v, v.vy.v, i.vx.v, i.vy.v);

    if(j != i)
        LX_Log::log("SUCCESS - j ≠ i");
    else
        LX_Log::log("FAILURE - expected: j ≠ i; Got: j(%f,%f) ≠ i(%f,%f)",
                    j.vx.v, j.vy.v, i.vx.v, i.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorPlusMinusOp(void)
{
    LX_Vector2D w;
    LX_Vector2D u = {3.14f,1.59f};
    LX_Vector2D v = {-1.28f,5.12f};
    LX_Vector2D z = {-2.56f,10.24f};

    LX_Vector2D a = {3.14f,2.048f};
    LX_Vector2D b = {1.28f,0.64f};
    LX_Vector2D c = {-2.56f,10.24f};
    LX_Vector2D d;

    LX_Vector2D exp_sum_vec = {u.vx + v.vx , u.vy + v.vy};
    LX_Vector2D exp_add_vec = {u.vx + z.vx , u.vy + z.vy};

    LX_Vector2D exp_diff_vec = {a.vx - b.vx , a.vy - b.vy};
    LX_Vector2D exp_sub_vec = {a.vx - c.vx , a.vy - c.vy};

    LX_Log::log(" = TEST Vector arithmetic = ");
    LX_Log::log(" '+','+=','-','-='");

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("w = u + v;");

    w = u + v;
    LX_Log::log("Vector2D w(%f,%f)", w.vx.v, w.vy.v);

    if(w == exp_sum_vec)
        LX_Log::log("SUCCESS - w(%f,%f) as expected", w.vx.v, w.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: w(%f,%f)",
                    exp_sum_vec.vx.v, exp_sum_vec.vy.v, w.vx.v, w.vy.v);

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("u += z;");

    u += z;

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);

    if(u == exp_add_vec)
        LX_Log::log("SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: u(%f,%f)",
                    exp_add_vec.vx.v, exp_add_vec.vy.v, u.vx.v, u.vy.v);

    LX_Log::log("Vector2D a(%f,%f)", a.vx.v, a.vy.v);
    LX_Log::log("Vector2D b(%f,%f)", b.vx.v, b.vy.v);
    LX_Log::log("d = a - b;");

    d = a - b;

    LX_Log::log("Vector2D d(%f,%f)", d.vx.v, d.vy.v);

    if(d == exp_diff_vec)
        LX_Log::log("SUCCESS - d(%f,%f) as expected", d.vx.v, d.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: d(%f,%f)",
                    exp_diff_vec.vx.v, exp_diff_vec.vy.v, d.vx.v, d.vy.v);


    LX_Log::log("Vector2D a(%f,%f)", a.vx.v, a.vy.v);
    LX_Log::log("Vector2D b(%f,%f)", b.vx.v, b.vy.v);
    LX_Log::log("a -= c;");

    a -= c;

    if(a == exp_sub_vec)
        LX_Log::log("SUCCESS - a(%f,%f) as expected", a.vx.v, a.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: a(%f,%f)",
                    exp_sub_vec.vx.v, exp_sub_vec.vy.v, a.vx.v, a.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorOpposite(void)
{
    LX_Log::log(" = TEST Vector Opposite = ");

    LX_Vector2D u = {3.14f,-2.56f};
    LX_Vector2D expected_vec = {-u.vx.v,-u.vy};

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("-u;");

    if(expected_vec == (-u) )
        LX_Log::log("SUCCESS - u(%f,%f) as expected", (-u).vx.v, (-u).vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: u(%f,%f)",
                    expected_vec.vx.v, expected_vec.vy.v, (-u).vx.v, (-u).vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorIncDec(void)
{
    LX_Log::log(" = TEST Vector Increment and decrement = ");

    LX_Vector2D u = {1.41f,-5.92f};
    LX_Vector2D v = u;
    LX_Vector2D exp_inc_pre_vec = {u.vx + 1.0f,u.vy + 1.0f};
    LX_Vector2D exp_inc_post_vec = {u.vx + 1.0f,u.vy + 1.0f};
    LX_Vector2D exp_dec_pre_vec = {u.vx - 1.0f,u.vy - 1.0f};
    LX_Vector2D exp_dec_post_vec = {u.vx - 1.0f,u.vy - 1.0f};

    LX_Log::log("Increment");
    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("++u;");

    ++u;

    if(u == exp_inc_pre_vec)
        LX_Log::log("SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: u(%f,%f)",
                    exp_inc_pre_vec.vx.v, exp_inc_pre_vec.vy.v, u.vx.v, u.vy.v);

    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("v++;");

    v++;

    if(v == exp_inc_post_vec)
        LX_Log::log("SUCCESS - v(%f,%f) as expected", v.vx.v, v.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: v(%f,%f)",
                    exp_inc_post_vec.vx.v, exp_inc_post_vec.vy.v, v.vx.v, v.vy.v);

    u = {1.41f,-5.92f};
    v = u;

    LX_Log::log("Decrement");
    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("--u;");

    --u;

    if(u == exp_dec_pre_vec)
        LX_Log::log("SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: u(%f,%f)",
                    exp_dec_pre_vec.vx.v, exp_dec_pre_vec.vy.v, u.vx.v, u.vy.v);

    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("v--;");

    v--;

    if(v == exp_dec_post_vec)
        LX_Log::log("SUCCESS - v(%f,%f) as expected", v.vx.v, v.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: v(%f,%f)",
                    exp_dec_post_vec.vx.v, exp_dec_post_vec.vy.v, v.vx.v, v.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorCollinear(void)
{
    LX_Log::log(" = TEST Vector collinearity = ");

    LX_Vector2D u = {1.41f, -2.48f};
    LX_Vector2D v = {u.vx *2.0f, u.vy *2.0f};
    LX_Vector2D w = u;
    LX_Vector2D o = {0.0f, 0.0f};
    LX_Vector2D t = {2.01f, 4.12f};

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("Vector2D w(%f,%f)", w.vx.v, w.vy.v);
    LX_Log::log("Vector2D o(%f,%f)", o.vx.v, o.vy.v);
    LX_Log::log("Vector2D t(%f,%f)", t.vx.v, t.vy.v);

    LX_Log::log("test: zero vector");

    if(isNullVector(o))
        LX_Log::log("SUCCESS - o is a zero vector: o(%f,%f)", o.vx.v, o.vy.v);
    else
        LX_Log::log("FAILURE - o is not a zero vector: o(%f,%f)", o.vx.v, o.vy.v);

    if(!isNullVector(t))
        LX_Log::log("SUCCESS - t is not a zero vector: t(%f,%f)", t.vx.v, t.vy.v);
    else
        LX_Log::log("FAILURE - t is a zero vector: t(%f,%f)", t.vx.v, t.vy.v);

    LX_Log::log("test: collinearity between u and v");

    if(collinear(u,v))
        LX_Log::log("SUCCESS - u and v are colinear");
    else
        LX_Log::log("FAILURE - expected: u and v must be colinear; Got: u(%f,%f) and v(%f,%f)",
                    u.vx.v, u.vy.v, v.vx.v, v.vy.v);


    LX_Log::log("test: collinearity between u and w");

    if(collinear(u,w))
        LX_Log::log("SUCCESS - u and w are colinear");
    else
        LX_Log::log("FAILURE - expected: u and w must be colinear; Got: u(%f,%f) and w(%f,%f)",
                    u.vx.v, u.vy.v, w.vx.v, w.vy.v);

    LX_Log::log("test: collinearity between u and o");

    if(collinear(u,o))
        LX_Log::log("SUCCESS - u and o are colinear");
    else
        LX_Log::log("FAILURE - expected: u and o must be colinear; Got: u(%f,%f) and o(%f,%f)",
                    u.vx.v, u.vy.v, o.vx.v, o.vy.v);

    LX_Log::log("test: collinearity between u and t");

    if(!collinear(u,t))
        LX_Log::log("SUCCESS - u and t are colinear");
    else
        LX_Log::log("FAILURE - expected: u and t must be colinear; Got: u(%f,%f) and t(%f,%f)",
                    u.vx.v, u.vy.v, t.vx.v, t.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorLambda(void)
{
    LX_Log::log(" = TEST Vector, scalar multiplication = ");

    float lambda1 = 2.0f;
    float lambda2 = 0.0f;
    LX_Vector2D v{3.14f,1.59f};
    LX_Vector2D w{v.vx * lambda1,v.vy * lambda1};
    LX_Vector2D t{0.0f, 0.0f};

    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);

    v = v * lambda1;

    if(v == w)
        LX_Log::log("SUCCESS - Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    else
        LX_Log::log("FAILURE - expected: v(%f,%f); Got: v(%f,%f)", w.vx.v, w.vy.v,
                    v.vx.v, v.vy.v);

    v = v * lambda2;

    if(v == t)
        LX_Log::log("SUCCESS - Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    else
        LX_Log::log("FAILURE - expected: v(%f,%f); Got: v(%f,%f)", t.vx.v, t.vy.v,
                    v.vx.v, v.vy.v);

    // Test normalization
    LX_Log::log("Reset v");

    v = {3.0f,0.0f};
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("Normalize v");

    normalize(v);
    float n = vector_norm(v);

    if(n == 1.0f)
        LX_Log::log("SUCCESS - Vector2D v(%f,%f) normalized, norm: %f", v.vx.v, v.vy.v, n);
    else
        LX_Log::log("FAILURE - expected: v(%f,%f); Got: v(%f,%f)", t.vx.v, t.vy.v,
                    v.vx.v, v.vy.v);

    LX_Log::logWarning(LX_Log::LX_LOG_TEST,"The previous test may fail with some complex float values in the vector");
    LX_Log::logWarning(LX_Log::LX_LOG_TEST,"Try it with V(3.14,2.56)");

    LX_Log::log("Vector2D t(%f,%f)", t.vx.v, t.vy.v);
    LX_Log::log("Normalize t");

    normalize(t);   // t is a null vector

    if(t == t)
        LX_Log::log("SUCCESS - Vector2D t(%f,%f) normalized, norm: %f", v.vx.v, v.vy.v, n);
    else
        LX_Log::log("FAILURE - a zero vector must be normalized to 0");

    LX_Log::log(" = END TEST = ");
}

void displayPoly(LX_Polygon& poly)
{
    ostringstream os;
    os << "{";
    const unsigned long n = poly.numberOfEdges();
    for(unsigned int i = 0; i < n; i++)
    {
        os << "(" << (poly.getPoint(i)).x << ","
             << (poly.getPoint(i)).y << ")";
        if(i != n)
            os << ";";
    }
    os << "}";
    LX_Log::log("%s",os.str().c_str());
}
