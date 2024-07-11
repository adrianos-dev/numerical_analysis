The idea of this code is to solve linear/non linear system of equations numerically using the Newton method, aka, linearization of the
F(X)=0 around X0 point by a first order Taylor approximation. F(x0) + F'(x0)(x-x0) = 0

It works for systems of n equations and n variables ( between 2 and 6). It is entirely written in C++.

The code has to sections, in the file 'functions.txt' the user writes each function line by line as F1(X)=0,F2(X)..etc using the cmath c++ library 
style. The variables are ordered so they must labelled as x,y,z,q,r,s in this order. In the folder /functions_examples
there are several examples of systems.
Compile as g++ -std=c++20 build_functions.cpp and run it on your terminal. It will then create the file 'functions.hpp'.

The second part is to compile the main as g++ -std=c++20 main.cpp and run it. It will use the guess point the user typed before and the functions written in 'functions.hpp' file to numerically try to solve the system.
