#include<iostream>
#include<vector>
#include<cmath>
#include"functions.hpp"
#include"jacobian.hpp"
#include"inverse_matrix.hpp"

// print to the screen.
void error(string s){ throw runtime_error(s);};
void print_to_screen(std::vector<std::vector<double>> &gradient){
   std::vector<std::vector<double>>::iterator row;
   std::vector<double>::iterator column;
   for (row=gradient.begin();row!=gradient.end();++row){  
     for (column=row->begin();column!= row->end();++column){std::cout << *column << '\t';}
    std::cout << std::endl; 
   }
}

std::vector<double> calc_new_point(std::vector<std::vector<double>> &gradient_inv,std::vector<double> initial_point,
std::vector<double> F_0)
{ std::vector<double> new_points;
  for (int i=0;i<F_0.size();++i){
    std::vector<double> temp = gradient_inv[i]; // each row vector of A 
    double dot_product = inner_product(temp.begin(),temp.end(),F_0.begin(),0.0);
    new_points.push_back(dot_product);
    new_points[i]=initial_point[i] + new_points[i];
  }   
return new_points;
};

// Solve a non linear system equation with the NEWTON method.


using namespace :: std;
int main(){




/// ####
double (*func1)(Unpack obj1);
func1=f1;
double (*func2)(Unpack obj2);
func2=f2;
double (*func3)(Unpack obj3);
func3=f3;
double (*func4)(Unpack obj4);
func4=f4;
std::vector<double(*)(Unpack obj)> v;
funciones F(v); // call the CLASS funciones initialized with F(v);
F.add_f(func1);
F.add_f(func2);
F.add_f(func3);
F.add_f(func4);
int fields    = 4;
int variables = 4;
double xx= 4.000000;
double yy= 2.100000;
double zz= 0.100000;
double qq= 4.0300000;
double rr= 0.000000;
double ss= 0.000000;
double tt= 0.000000;
double uu= 0.000000;
double vv= 0.000000;
double ww= 0.000000;

std::vector<double> new_point;
std::vector<std::vector<double>> gradient;
for (int i=0;i<100;++i){
 
 Unpack point(xx,yy,zz,qq,rr,ss,tt,uu,vv,ww);
 gradient = F.gradient(point,variables);
 std::vector<double> initial_point={xx,yy,zz,qq,rr,ss,tt,uu,vv,ww};
 std::vector<double> F_0=F.evaluate_f(point);
 for_each(F_0.begin(),F_0.end(),[](double& n){n=-n;}); // change sign of whole vector.
 std::vector<std::vector<double>> gradient_inv = inverse(gradient,fields,variables);
 print_to_screen(gradient_inv);
 std::cout << " " << std::endl;
 new_point = calc_new_point(gradient_inv,initial_point,F_0);
 xx = new_point[0];
 yy = new_point[1];
 zz = new_point[2];
 qq = new_point[3];
 rr = new_point[4];
 ss = new_point[5];
 tt = new_point[6];
 uu = new_point[7];
 vv = new_point[8];
 ww = new_point[9];
}
std::vector<double>::iterator it;
std::cout << " x,y,z ... points " << std::endl;
for (it=new_point.begin();it!=new_point.end();++it){std::cout << *it << '\t';};
}
