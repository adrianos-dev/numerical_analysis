#include<iostream>
#include<string>
#include<fstream>
#include<vector>

int main(){

std::string header{ 
"#include<cmath>\n\
struct Unpack{\n\
double x;\n\
double y;\n\
double z;\n\
double q;\n\
double r;\n\
double s;\n\
double t;\n\
double u;\n\
double v;\n\
double w;\n\
Unpack(double a=0,double b=0,double c=0,double d=0,double e=0,double f=0,double g=0,double h=0,double i=0,\n\
double j=0):x(a),y(b),z(c),q(d),r(e),s(f),t(g),u(h),v(i),w(j){};};"
};

int vars;
int fil;
std::cout << "Enter number of variables: MAX 6" << std::endl;
std::cin >> vars;
std::cout << "Enter number of equations :MAX 6" << std::endl;
std::cin >> fil;
std::cout << std::endl;
double initial_value;
std::vector<double> initial_values(vars,0);

std::cout << "Enter initial guess points one by one" << std::endl;
for (int i=0;i<vars;++i){
 std::cin >> initial_value;
 initial_values[i]=initial_value;
};

double arr[10];
for (int i=0;i<vars;++i){arr[i]=initial_values[i];};
auto& [x0,y0,z0,q0,r0,s0,t0,u0,v0,w0] = arr; // only works with objects or arrays, vectors no.

std::vector<std::string> v;
std::ifstream ist("functions.txt");
std::string line;
std::ofstream ost("functions.hpp");
ost << header << '\n';

while(getline(ist,line)) v.push_back(line);

for (int i=0;i<vars;++i){
 std::string obj = "obj" + std::to_string(i);
 std::string f =  "f"    + std::to_string(i+1);
 std::string VAR = "double " + f + "(Unpack " + obj + "){auto [x,y,z,q,r,s,t,u,v,w] = "+ obj +
 ";double f_d =" + v[i] + ";return f_d;}";
 ost << VAR << std::endl;
 std::cout << std::endl;
}

// PART 2:  READ the main.template.dat to add lines about the functions.
std::vector<std::string> text;
std::ifstream is("main.template.dat");
std::string rows;
std::ofstream os("main.cpp");
std::vector<std::string> vec;
while(getline(is,rows)) vec.push_back(rows);

for (int i=0;i<40;++i){ os << vec[i] << std::endl;}; // write up to line 40
/// ####

for (int i=0;i<vars;++i){
std::string obj = "obj" + std::to_string(i+1);
std::string FUNC1 = "double (*func" + std::to_string(i+1) + ")" + "(Unpack " + obj + ");";
std::string FUNC2 = "func" + std::to_string(i+1) +"=f"+ std::to_string(i+1)+";";
os << FUNC1 << std::endl;
os << FUNC2 << std::endl;
}
os << "std::vector<double(*)(Unpack obj)> v;" << std::endl;
os << "funciones F(v); // call the CLASS funciones initialized with F(v);" << std::endl; 


for (int i=0;i<vars;++i){
 os << "F.add_f(func" + std::to_string(i+1) + ");" << std::endl;
}

os << "int fields    = " + std::to_string(fil)  + ";" << std::endl;
os << "int variables = " + std::to_string(vars) + ";" << std::endl;
os << "double xx= "      + std::to_string(x0)   + ";" << std::endl;
os << "double yy= "      + std::to_string(y0)   + ";" << std::endl;
os << "double zz= "      + std::to_string(z0)   + ";" << std::endl;
os << "double qq= "      + std::to_string(q0)   + ";" << std::endl;
os << "double rr= "      + std::to_string(r0)   + ";" << std::endl;
os << "double ss= "      + std::to_string(s0)   + ";" << std::endl;
os << "double tt= "      + std::to_string(t0)   + ";" << std::endl;
os << "double uu= "      + std::to_string(u0)   + ";" << std::endl;
os << "double vv= "      + std::to_string(v0)   + ";" << std::endl;
os << "double ww= "      + std::to_string(w0)   + ";" << std::endl;


for (int i=75;i<vec.size();++i){ os << vec[i] << std::endl;}; // print again from line 75 onwards.
/// ####

}
