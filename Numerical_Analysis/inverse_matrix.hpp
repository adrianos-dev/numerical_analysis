#include<iostream>
#include<vector>
#include<numeric> // for the dot product.
#include<iomanip> 

typedef std::vector<std::vector<double>> multi_vector;
typedef std::vector<double> single_vector;
void ERROR(std::string s){throw runtime_error(s);};

void print_2_screen(std::vector<std::vector<double>> &permutate){
   std::vector<std::vector<double>>::iterator row;
   std::vector<double>::iterator column;
   for (row=permutate.begin();row!=permutate.end();++row){  
     for (column=row->begin();column!= row->end();++column){std::cout << *column << '\t';}
    std::cout << std::endl; 
   }
}

std::vector<std::vector<double>> read_from_column(multi_vector &v,int column,int variables,int fields){

 multi_vector I(fields,std::vector<double>(variables));
 std::vector<std::vector<double>>::iterator row;
 std::vector<double>::iterator col;
 int C;
 std::vector<double> col_vector; // add the values of a given column
  for (row=v.begin();row!=v.end();++row){
     col=row->begin() + column;
     col_vector.push_back(*col); 
  }
  if (col_vector[column]!=0 || column==(variables-1)){
    for (int j=0;j<variables;++j){
   row=I.begin() + j;
   *(row->begin() + j)=1;
    }
   return I;
  }; 
  if (col_vector[column]==0 && column!=(variables-1)){ 
   for (C=column;C<col_vector.size();++C){if (col_vector[C]!=0) break;}; // return first index i which has not 0 element.
   //for (double xx : col_vector){std::cout << " column! " << xx << '\t';};
    row=I.begin() + 0;
    *(row->begin() + C)=1;   
    int newc=0;
    for (int i=1;i<variables;++i){
       row=I.begin()+ i; 
     if (newc!=C){ *(row->begin() + newc)=1;++newc;};
     if (newc==C){++newc;};
    }
  }
   // now add 1's on the other rows from 2 to end.
  
return I;}

void write_to_column(multi_vector &v, std::vector<double> &linear_vector,int column){

 std::vector<std::vector<double>>::iterator row;
 std::vector<double>::iterator col;
 int i=0;
  for (row=v.begin();row!=v.end();++row){
     col=row->begin()+column;
     *col=linear_vector[i];
     ++i;
  }
 }

std::vector<double> new_column(std::vector<std::vector<double>> &A,int column){
 double x,y,z;
 std::vector<std::vector<double>>::iterator row;
 std::vector<double>::iterator col;
 std::vector<double> col_values;
 for (row=A.begin();row!=A.end();++row){
    col=row->begin() + column;
     col_values.push_back(*col);
 }
 for (int i=0;i<col_values.size();++i){
  if (i!=column){col_values[i]= -col_values[i]/col_values[column];}; 
  }
  col_values[column]= 1/col_values[column];
return col_values;}

// function multiply matrixes.
std::vector<std::vector<double>> mult_matrices(multi_vector &A,multi_vector &B,multi_vector &I,int variables){
 
 std::vector<std::vector<double>> matrix_m = I;
 std::vector<std::vector<double>>::iterator row;
 std::vector<double>::iterator col;
 std::vector<double> temp,col_values,new_rows;
 for (int column=0;column<A[0].size();++column){
 for (int i=0;i<variables;++i){
   temp = A[i]; // cada vector file de matriz A.
    for (row=B.begin();row!=B.end();++row){
      col=row->begin() + column;
      col_values.push_back(*col);
    }
    double dot_product = inner_product(temp.begin(),temp.end(),col_values.begin(),0.0);
    new_rows.push_back(dot_product);
 } 
 int j=0;
 for (row=matrix_m.begin();row!=matrix_m.end();++row){
  col = row->begin() + column;
  *col = new_rows[j];
  ++j;
 }
 new_rows.clear();
 col_values.clear();
 }
return matrix_m;}


// main function!

std::vector<std::vector<double>> inverse(std::vector<std::vector<double>> A,int variables,int fields){

 multi_vector I(fields,std::vector<double>(variables));
 std::vector<double> add_c(variables,0); // create a vector of size 'variables' al set to zero.
 for (int k=0;k<add_c.size();++k){
 add_c[k]=1;
 write_to_column(I,add_c,k); // create identity matrix I of size variables
 add_c[k]=0;
 }
 multi_vector E1=I; // copy identity into E1 and manipulate.
 multi_vector inv=I;
 single_vector var;
 multi_vector matrix_m;
 // IF matrix 'A' has a zero at the index of any column it will need permutation.
 matrix_m=A; // copy A first 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl; 
 //print_2_screen(A);
 for (int i=0;i<variables;++i){ 
  multi_vector P = read_from_column(matrix_m,i,variables,fields); // permutation if needed. 
  matrix_m=mult_matrices(P,matrix_m,I,variables); // permutates A if needed for first row.
  var = new_column(matrix_m,i);
  write_to_column(E1,var,i); // add var @column 0 .
  inv=mult_matrices(P,inv,I,variables);
  inv=mult_matrices(E1,inv,I,variables);
  matrix_m = mult_matrices(E1,matrix_m,I,variables);
  E1=I;
 }
 return inv;
 }
