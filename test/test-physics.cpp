

#include <cmath>

#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_Physics;


void test_euclide(void);
void test_collisionPointCircle(void);
void test_collisionPointRect(void);
void test_collision2Circle(void);
void test_collision2Rect(void);
void test_collisionRectCircle(void);


int main(int argc, char **argv)
{
    bool err = false;

    cout << " ==== Test Physics ==== " << endl;

    err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    test_euclide();
    test_collisionPointCircle();

    LX_Quit();

    cout << " ==== END Physics ==== " << endl;

    return EXIT_SUCCESS;
}


// Test the euclidean functions
void test_euclide(void)
{

    LX_Point A = {1,1};
    LX_Point B = {10,1};

    LX_Point C = {0,0};
    LX_Point D = {10,10};

    int d;

    d = euclide_square_distance(&A,&B);

    if(d != 81)
        cerr << "FAILURE - Bad square distance of AB - expected : 81; got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance of AB : " << d << endl;

    d = euclide_distance(&A,&B);

    if(d != 9)
        cerr << "FAILURE - Bad distance of AB - expected : 9; got : " << d << endl;
    else
        cout << "SUCCESS - Good distance of AB : " << d << endl;

    // Test CD

    d = euclide_square_distance(&C,&D);

    if(d != 200)
        cerr << "FAILURE - Bad square distance of CD - expected : 200; got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance of CD : " << d << endl;

    d = euclide_distance(&C,&D);

    if(d != ( (int) sqrt(200)) )
        cerr << "FAILURE - Bad distance of CD - expected : " << (int) sqrt(200) << "; got : " << d << endl;
    else
        cout << "SUCCESS - Good distance of CD : " << d << endl;

}


void test_collisionPointCircle(void)
{
    LX_Point A,B,C,D;
    LX_Circle c;

    bool d;

    c = {100,100,10,100};

    A = {100,100};
    B = {50,50};
    C = {105,105};
    D = {100,125};


    d = collision(A.x,A.y,&c);

    if(d != true)
        cerr << "FAILURE - expected : TRUE ; got : " << d << endl;
    else
        cout << "SUCCESS - collision point is the center : " << d << endl;

    d = collision(B.x,B.y,&c);

    if(d != false)
        cerr << "FAILURE - expected : FALSE; got : TRUE" << endl;
    else
        cout << "SUCCESS - collision point is the center"<< endl;

    d = collision(C.x,C.y,&c);

    if(d != true)
        cerr << "FAILURE - expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision point is the center " << endl;

    d = collision(D.x,D.y,&c);

    if(d != false)
        cerr << "FAILURE - expected : FALSE ; got : TRUE" << endl;
    else
        cout << "SUCCESS - collision point is the center "<< endl;
}

















