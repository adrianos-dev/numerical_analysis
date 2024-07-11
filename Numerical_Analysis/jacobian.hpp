#include<iostream>
#include<vector>
#include<cmath>

using namespace :: std;

class funciones{

private:
 std::vector<double(*)(Unpack obj)> vek;
public:
 funciones(std::vector<double(*)(Unpack obj2)> v):vek(v){}; //constructor. 
 void add_f(double(*f)(Unpack obj2)){vek.push_back(f);};
  std::vector<double> evaluate_f(Unpack obj3){
  std::vector<double>F; // vector with F(f1,f2,...fn) values at x,y,z point.
  for (int i=0;i<vek.size();++i){F.push_back(vek[i](obj3));}
  return F;}

  std::vector<std::vector<double>> gradient(Unpack obj4,int variables){
     double dx,dy,dz,dq,dr,ds,dt,du,dv,dw;
     std::vector<std::vector<double>> return_gradient;
      auto [x,y,z,q,r,s,t,u,v,w] = obj4;
      double  h=1;
      for  (int j=0;j<vek.size();++j){ // loop through the vector vek 
       for (int i=0;i<5;++i){        // for each line in vek calculate de derivative.
         Unpack objx(x+h,y,z,q,r,s,t,u,v,w); dx = (vek[j](objx)   - vek[j](obj4))/h;
         Unpack objy(x,y+h,z,q,r,s,t,u,v,w); dy = (vek[j](objy)   - vek[j](obj4))/h;
         Unpack objz(x,y,z+h,q,r,s,t,u,v,w); dz = (vek[j](objz)   - vek[j](obj4))/h;
         Unpack objq(x,y,z,q+h,r,s,t,u,v,w); dq = (vek[j](objq)   - vek[j](obj4))/h;
         Unpack objr(x,y,z,q,r+h,s,t,u,v,w); dr = (vek[j](objr)   - vek[j](obj4))/h;
         Unpack objs(x,y,z,q,r,s+h,t,u,v,w); ds = (vek[j](objs)   - vek[j](obj4))/h;
         Unpack objt(x,y,z,q,r,s,t+h,u,v,w); dt = (vek[j](objt)   - vek[j](obj4))/h;
         Unpack obju(x,y,z,q,r,s,t,u+h,v,w); du = (vek[j](obju)   - vek[j](obj4))/h;
         Unpack objv(x,y,z,q,r,s,t,u,v+h,w); dv = (vek[j](objv)   - vek[j](obj4))/h;
         Unpack objw(x,y,z,q,r,s,t,u,v,w+h); dw = (vek[j](objw)   - vek[j](obj4))/h;
         h=h/10;
       }
       std::vector<double> v = {dx,dy,dz,dq,dr,ds,dt,du,dv,dw};
       v.erase(std::next(v.begin(), variables), std::next(v.begin(),v.size()));
       return_gradient.push_back(v);
       v.clear();
       //reinitialize these values.
       dx=dy=dz=dq=dr=ds=dt=du=dv=dw=0;
       h=1;
 }
 return return_gradient;};
};
