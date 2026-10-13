#include <iostream>
#include <cmath>

int main(){
    double eps = std::pow(10,-6);
    
    for (unsigned i = 0; i < 50; i++){
        for (unsigned j = 1; j < 10; j++){

            std::cout << "\n";
            double e = 0.1 * j;
            double M = (double)i / 25 * M_PI;
            auto F = [e, M](double E){return E - e * std::sin(E) - M;};
            auto dF = [e, M](double E){return 1 - e * std::cos(E);};

            double E = M;
            double err = F(E);
            while (std::abs(err) > eps){
                E = E - F(E)/ dF(E);
                err = F(E);
            }
            std::cout << "\r{M, e} = {"<< M << "; " << e << "}\t    Value: " << E << ";\t Error: " << err;

        }
    }
    

    std::cout << "\n";
    return 0;
}