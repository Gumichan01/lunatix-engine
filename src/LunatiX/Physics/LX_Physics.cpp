

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Physics.cpp
*	@brief The implementation of the physics library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <cmath>

#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Hitbox.hpp>
#include <LunatiX/LX_Polygon.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Error.hpp>


static const int RECT_SIDES = 4;   // The number of sides of a rectangle (AABB)


namespace LX_Physics{

/**
*	@fn unsigned int euclide_square_distance(const int x1, const int y1,
*                                                        const int x2, const int y2)
*
*	This function calculates the euclidean square distance between 2 coordinates
*
*	@param x1 The x location of the first point
*	@param y1 The y location of the first point
*	@param x2 The x location of the second point
*	@param y2 The y location of the second point
*
*	@return An integer value
*
*/
unsigned int euclide_square_distance(const int x1, const int y1,
                                                 const int x2, const int y2)
{
    return( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}


/**
*	@fn float euclide_distance(const int x1, const int y1,
*                                          const int x2, const int y2)
*
*	This function calculates the euclidean distance with accuracy
*
*	@param x1 The x location of the first point
*	@param y1 The y location of the first point
*	@param x2 The x location of the second point
*	@param y2 The y location of the second point
*
*	@return An float value
*
*/
float euclide_distance(const int x1, const int y1,
                                   const int x2, const int y2)
{
    return sqrt(euclide_square_distance(x1,y1,x2,y2));
}


/**
*	@fn unsigned int euclide_square_distance(const LX_Point& p1,
*                                                        const LX_Point& p2)
*
*	This function calculates the euclidean square distance
*
*	@param	p1 The first point
*	@param	p2 The second point
*
*	@return An integer value
*
*/
unsigned int euclide_square_distance(const LX_Point& p1,
                                                 const LX_Point& p2)
{
    return euclide_square_distance(p1.x,p1.y,p2.x,p2.y);
}


/**
*	@fn float euclide_distance(const LX_Point& p1, const LX_Point& p2)
*
*	This function calculates the euclidean distance with accuracy
*
*	@param p1 The first point
*	@param p2 The second point
*
*	@return An integer value
*
*/
float euclide_distance(const LX_Point& p1, const LX_Point& p2)
{
    return sqrt(euclide_square_distance(p1,p2));
}


/**
*	@fn bool collisionPointRect(const int x_pos, const int y_pos,
*                                           const LX_AABB& rect)
*
*	Check the collision between a point and an Axis Aligned Bouding Box (AABB)
*
*	@param x_pos The x position of the point
*	@param y_pos The y position of the point
*	@param rect The AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointRect(const int x_pos, const int y_pos, const LX_AABB& rect)
{

    if(x_pos <= rect.x || y_pos >= (rect.y + rect.h)
       || y_pos <= rect.y || x_pos >= (rect.x + rect.w))
    {
        return false;
    }

    return true;
}


/**
*	@fn bool collisionPointRect(const LX_Point& p,const LX_AABB& rect)
*
*	Check the collision between a point and an AABB
*
*	@param p The point
*	@param rect The AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointRect(const LX_Point& p,const LX_AABB& rect)
{
    return collisionPointRect(p.x,p.y,rect);
}


/**
*	@fn bool collisionPointCircle(const int x_pos, const int y_pos,
*                                               const LX_Circle& circle)
*
*	Check the collision between a point and a circle
*
*	@param x_pos The x position of the point
*	@param y_pos The y position of the point
*	@param circle The circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointCircle(const int x_pos, const int y_pos,
                                      const LX_Circle& circle)
{
    LX_Point tmp = {x_pos,y_pos};
    return collisionPointCircle(tmp,circle);
}


/**
*	@fn bool collisionPointCircle(const LX_Point& p, const LX_Circle& circle)
*
*	Check the collision between a point and a circle
*
*	@param p The point
*	@param circle The circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointCircle(const LX_Point& p, const LX_Circle& circle)
{
    return(euclide_square_distance(p,circle.center) <= (circle.square_radius));
}


/**
*	@fn bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2)
*
*	Check the collision between two Axis Aligned Bounding Box (AABB)
*
*	@param rect1 The first AABB
*	@param rect2 The second AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2)
{
    if((rect1.x >= (rect2.x + rect2.w)) || (rect1.y >= (rect2.y + rect2.h))
       || ((rect1.x + rect1.w) <= rect2.x) || ((rect1.y + rect1.h) <= rect2.y))
    {
        return false;
    }

    return true;
}


/**
*	@fn bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2)
*
*	Check the collision between two circles
*
*	@param circle1 The first circle
*	@param circle2 The second circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2)
{
    const unsigned int d = (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);

    return (euclide_square_distance(circle1.center,circle2.center) <= d);
}


/**
*	@fn bool collisionSegCircle(const LX_Circle& circle,
*                                           const LX_Point& A, const LX_Point& B)
*
*	Check the collision between a circle and the [AB] segment
*
*	@param circle The circle
*	@param A The first point of the segment
*	@param B The other point of the segment
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionSegCircle(const LX_Circle& circle,
                                    const LX_Point& A, const LX_Point& B)
{
    LX_Vector2D AB,AC,BC;
    LX_Point M;
    LX_Point O = circle.center;

    float scal,scal1,scal2;
    int sum;
    double t;
    double x,y;

    if(collisionPointCircle(A,circle) || collisionPointCircle(B,circle))
        return true;

    AB.vx = B.x - A.x;
    AB.vy = B.y - A.y;

    AC.vx = O.x - A.x;
    AC.vy = O.y - A.y;

    BC.vx = O.x - B.x;
    BC.vy = O.y - B.y;

    scal1 = scalar_product(AB,AC);
    // I use the opposite value of vx
    scal2 = ((-AB.vx) * BC.vx) + ((-AB.vy) * BC.vy);

    if(scal1 < 0 || scal2 < 0)
        return false;

    // Find the projection point of O
    scal = scalar_product(AB,AB);
    sum = static_cast<int>(scal);

    if(sum == 0)        // A and B are the same point
        return false;

    t = scal1/scal;

    x = A.x + (t*AB.vx);
    y = A.y + (t*AB.vy);

    M = {static_cast<int>(x), static_cast<int>(y)};     // M is the projection point of O

    return collisionPointCircle(M,circle);
}


/**
*	@fn bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect)
*
*	Check the collision between a circle and a AABB
*
*	@param circle The circle
*	@param rect The AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect)
{
    // Check if the center of the circle is completly into the AABB
    if(collisionPointRect(circle.center,rect))
        return true;

    LX_Point sides[RECT_SIDES][2];  //4 segments

    // 1st segment
    sides[0][0] = {rect.x , rect.y};
    sides[0][1] = {rect.x , rect.y + rect.h};

    // 2nd segment
    sides[1][0] = sides[0][1];
    sides[1][1] = {rect.x + rect.w , rect.y + rect.h};

    // 3rd segment
    sides[2][0] = sides[1][1];
    sides[2][1] = {rect.x + rect.w, rect.y};

    // 4th segment
    sides[3][0] = sides[2][1];
    sides[3][1] = sides[0][0];

    for(int i=0; i< RECT_SIDES ; i++)
    {
        if(collisionSegCircle(circle, sides[i][0], sides[i][1]))
            return true;
    }

    return false;
}


/**
*   @fn bool intersectSegLine(const LX_Point& A, const LX_Point& B,
*                                         const LX_Point& C, const LX_Point& D)
*
*   Test the intersection between a line and a segment
*
*   @param A the first point of the segment
*   @param B the second point of the segment
*   @param C the first point of the line
*   @param D the second point of the line
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*/
bool intersectSegLine(const LX_Point& A, const LX_Point& B,
                                   const LX_Point& C, const LX_Point& D)
{
    LX_Vector2D AC,AD,AB;
    long d;

    AB.vx = B.x - A.x;
    AB.vy = B.y - A.y;

    AC.vx = C.x - A.x;
    AC.vy = C.y - A.y;

    AD.vx = D.x - A.x;
    AD.vy = D.y - A.y;

    d = vector_product(AB,AD) * vector_product(AB,AC);

    return (d <= 0);
}


/**
*   @fn bool intersectSegment(const LX_Point& A, const LX_Point& B,
*                                         const LX_Point& C, const LX_Point& D)
*
*   Test the intersection between 2 segments
*
*   @param A the first point of the first segment
*   @param B the second point of the first segment
*   @param C the first point of the second segment
*   @param D the second point of the second segment
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*/
bool intersectSegment(const LX_Point& A, const LX_Point& B,
                                   const LX_Point& C, const LX_Point& D)
{
    return (intersectSegLine(A,B,C,D) && intersectSegLine(C,D,A,B));
}



/**
*   @fn bool collisionPointPoly(const LX_Point& P, const LX_Polygon& poly)
*
*   Test the collision between a point and a polygon
*
*   @param P The point to test
*   @param poly The polygon
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*/
bool collisionPointPoly(const LX_Point& P, const LX_Polygon& poly)
{
    int count = 0;
    LX_Point I;

    const int v = 10000;
    const unsigned int n = poly.numberOfEdges();

    I.x = v + rand()%100;
    I.y = v + rand()%100;

    for(unsigned int i = 0; i < n; i++)
    {
        if(i == n-1)
        {
            LX_Point p1 = poly.getPoint(0);
            LX_Point p2 = poly.getPoint(i);

            if(intersectSegment(P,I,p1,p2))
                count++;
        }
        else
        {
            LX_Point p3 = poly.getPoint(i+1);
            LX_Point p4 = poly.getPoint(i);

            if(intersectSegment(P,I,p3,p4))
                count++;
        }
    }

    return (count%2 == 1);
}


/**
*   @fn bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly)
*
*   Test the intersection between a circle and a polygon
*
*   @param C The circular hitbox
*   @param poly The polygon
*
*   @return TRUE if there is an collision, FALSE otherwise
*
*/
bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly)
{
    LX_Point A,B;
    const LX_Point P = C.center;

    if(collisionPointPoly(P,poly) == true)
        return true;

    const unsigned int n = poly.numberOfEdges();

    for(unsigned int i = 0; i < n; i++)
    {
        A = poly.getPoint(i);

        if(i == n-1)
            B = poly.getPoint(0);
        else
            B = poly.getPoint(i+1);

        if(collisionSegCircle(C,A,B) == true)
            return true;
    }

    return false;
}


/**
*   @fn bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly)
*
*   Test the intersection between an AABB and a polygon
*
*   @param rect The AABB
*   @param poly The polygon
*
*   @return TRUE if there is an collision, FALSE otherwise
*
*/
bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly)
{
    LX_Point A,B,C,D;
    LX_Point E,F;

    A = {rect.x,rect.y};
    B = {rect.x + rect.w,rect.y};
    C = {rect.x + rect.w,rect.y + rect.h};
    D = {rect.x,rect.y + rect.h};

    const unsigned int n = poly.numberOfEdges();

    for(unsigned int j = 0; j < n; j++)
    {
        E = poly.getPoint(j);

        if(j == n-1)
            F = poly.getPoint(0);
        else
            F = poly.getPoint(j+1);

        if(intersectSegment(A,B,E,F) || intersectSegment(B,C,E,F) ||
                intersectSegment(C,D,E,F) || intersectSegment(D,A,E,F))
            return true;

        if(collisionPointRect(E,rect))
            return true;
    }

    return(collisionPointPoly(A,poly) || collisionPointPoly(B,poly)
           || collisionPointPoly(C,poly) || collisionPointPoly(A,poly));
}


/**
*   @fn bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2)
*
*   Test the intersection between 2 polygons
*
*   @param poly1 The first polygon
*   @param poly2 The second polygon
*
*   @return TRUE if there is an collision, FALSE otherwise
*
*/
bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2)
{
    LX_Point A,B,C,D;
    const unsigned int polySize1 = poly1.numberOfEdges();
    const unsigned int polySize2 = poly2.numberOfEdges();

    for(unsigned int i = 0; i < polySize1; i++)
    {
        A = poly1.getPoint(i);

        if(i == polySize1-1)
            B = poly1.getPoint(0);
        else
            B = poly1.getPoint(i+1);

        for(unsigned int j = 0; j < polySize2; j++)
        {
            C = poly2.getPoint(j);

            if(j == polySize2-1)
                D = poly2.getPoint(0);
            else
                D = poly2.getPoint(j+1);

            if(intersectSegment(A,B,C,D))
                return true;
        }
    }

    LX_Point origin1 = poly1.getPoint(0);
    LX_Point origin2 = poly2.getPoint(0);

    return (collisionPointPoly(origin1,poly2)
            || collisionPointPoly(origin2,poly1));
}


/**
*   @fn void movePoint(LX_Point& P, const int vx, const int vy)
*
*   Move a point to a direction
*
*   @param P The point to move
*   @param vx The x direction
*   @param vy The y direction
*
*/
void movePoint(LX_Point& P, const int vx, const int vy)
{
    P.x += vx;
    P.y += vy;
}


/**
*   @fn void moveRect(LX_AABB& rect, const int vx, const int vy)
*
*   Move an AABB to a direction
*
*   @param rect The AABB to move
*   @param vx The x direction
*   @param vy The y direction
*
*/
void moveRect(LX_AABB& rect, const int vx, const int vy)
{
    rect.x += vx;
    rect.y += vy;
}


/**
*   @fn void moveCircle(LX_Circle *C, const int vx, const int vy)
*
*   Move the circle to a direction
*
*   @param C The circle to move
*   @param vx The x direction
*   @param vy The y direction
*
*/
void moveCircle(LX_Circle& C, const int vx, const int vy)
{
    movePoint(C.center,vx,vy);
}


/**
*   @fn void movePoly(LX_Polygon& poly, const int vx, const int vy)
*
*   Move the polygon to a direction
*
*   @param poly The polygon to move
*   @param vx The x direction
*   @param vy The y direction
*
*/
void movePoly(LX_Polygon& poly, const int vx, const int vy)
{
    poly.move(vx,vy);
}


/**
*   @fn void movePoint(LX_Point *P, const LX_Vector2D& v)
*
*   Move a point to a direction using the vector
*
*   @param P The point to move
*   @param v The vector that indicates the direction
*
*/
void movePoint(LX_Point& P, const LX_Vector2D& v)
{
    movePoint(P,v.vx,v.vy);
}


/**
*   @fn void moveRect(LX_AABB *rect, const LX_Vector2D& v)
*
*   Move an AABB to a direction using the vector
*
*   @param rect The AABB to move
*   @param v The vector that indicates the direction
*
*/
void moveRect(LX_AABB& rect, const LX_Vector2D& v)
{
    moveRect(rect,v.vx,v.vy);
}


/**
*   @fn void moveCircle(LX_Circle& C, const LX_Vector2D& v)
*
*   Move the circle to a direction using the vector
*
*   @param C The circle to move
*   @param v The vector that indicates the direction
*
*/
void moveCircle(LX_Circle& C, const LX_Vector2D& v)
{
    moveCircle(C,v.vx,v.vy);
}


/**
*   @fn void movePoly(LX_Polygon& poly, const LX_Vector2D& v)
*
*   Move the polygon to a direction using the vector
*
*   @param poly The polygon to move
*   @param v The vector that indicates the direction
*
*/
void movePoly(LX_Polygon& poly, const LX_Vector2D& v)
{
    poly.move(v);
}


/**
*   @fn void movePointTo(LX_Point& P, const int xpos, const int ypos)
*
*   Move a point to an absolute position
*
*   @param P The point to move
*   @param xpos The x position
*   @param ypos The y position
*
*/
void movePointTo(LX_Point& P, const int xpos, const int ypos)
{
    P = {xpos,ypos};
}


/**
*   @fn void moveRectTo(LX_AABB& rect, const int xpos, const int ypos)
*
*   Move an AABB to an absolute position
*
*   @param rect The AABB to move
*   @param xpos The x position
*   @param ypos The y position
*
*/
void moveRectTo(LX_AABB& rect, const int xpos, const int ypos)
{
    rect.x = xpos;
    rect.y = ypos;
}


/**
*   @fn void moveCircleTo(LX_Circle& C, const int xpos, const int ypos)
*
*   Move a circle to an absolute position
*
*   @param C The circle to move
*   @param xpos The x position
*   @param ypos The y position
*
*/
void moveCircleTo(LX_Circle& C, const int xpos, const int ypos)
{
    movePointTo(C.center,xpos,ypos);
}


/**
*   @fn void movePolyTo(LX_Polygon *poly, const int xpos, const int ypos)
*
*   Move a polygon to an absolute position
*
*   @param poly The polygon to move
*   @param xpos The x position
*   @param ypos The y position
*
*/
void movePolyTo(LX_Polygon& poly, const int xpos, const int ypos)
{
    poly.moveTo(xpos,ypos);
}


};

