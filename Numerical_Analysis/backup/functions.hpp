#include<cmath>
struct Unpack{
double x;
double y;
double z;
double q;
double r;
double s;
double t;
double u;
double v;
double w;
Unpack(double a=0,double b=0,double c=0,double d=0,double e=0,double f=0,double g=0,double h=0,double i=0,
double j=0):x(a),y(b),z(c),q(d),r(e),s(f),t(g),u(h),v(i),w(j){};};
double f1(Unpack obj0){auto [x,y,z,q,r,s,t,u,v,w] = obj0;double f_d =3*z + y + 2*x + 2;return f_d;}
double f2(Unpack obj1){auto [x,y,z,q,r,s,t,u,v,w] = obj1;double f_d =-y -z + x + 3;return f_d;}
double f3(Unpack obj2){auto [x,y,z,q,r,s,t,u,v,w] = obj2;double f_d =pow(x,2) + pow(y,3) + z - 5;return f_d;}
