#include <iostream>
#include <cmath>

int main(){
    double eps = std::pow(10,-14);
    
    for (unsigned i = 0; i < 50; i++){
        for (unsigned j = 1; j < 10; j++){

            std::cout << "\n";
            double e = 0.1 * j;
            double M = (double)i / 25 * M_PI;
            
            double E = M;
            double err = - e * std::sin(E);
            while (std::abs(err) > eps){
                E = M + e * std::sin(E);
                err = E - e * std::sin(E) - M;
            }
            std::cout << "\r{M, e} = {"<< M << "; " << e << "}\t    Value: " << E << ";\t Error: " << err;

        }
    }
    

    std::cout << "\n";
    return 0;
}