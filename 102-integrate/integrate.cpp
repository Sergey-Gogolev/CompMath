#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstddef>
#include <cmath> 


template<typename X, typename Y>
class Integrator{
    private:
        std::vector<X> nodes;
        std::vector<X> weights;
        std::size_t N;
        std::size_t digits;

        template<typename Callable>
        Y subsum(Callable&& f, const X& a, const X& b){
            Y ans = 0;
            for (std::size_t i = 0; i < N; i++)
                ans += weights[i] * f((b + a) / 2 + (b - a) / 2 * nodes[i]);
            return (b - a) / 2 * ans;
        }

    public:
        Integrator(const std::string& filename){
            std::ifstream file(filename);
            if (!file.is_open())
                throw std::runtime_error("Cannot open file: " + filename);
            
            if (!(file >> N >> digits))
                throw std::runtime_error("Data reading error in file " + filename + " header");

            nodes.resize(N);
            weights.resize(N);

            for (std::size_t i = 0; i < N; i++)
                if (!(file >> nodes[i] >> weights[i]))
                    throw std::runtime_error("Data reading error in file " + filename + "(str " + std::to_string(i) + " )");
        }

        void PrintData() const{
            std::cout << "\nIntegrator Weights:";
            for (std::size_t i = 0; i < N; i++)
                std::cout << "\nNode #" << i << " " << nodes[i] << " --- " << weights[i];
        }

        template<typename Callable>
        Y operator()(Callable&& f, const X& a, const X& b, const X& h){
            X ai = a;
            Y ans = 0;
            while (ai + h < b){
                ans += subsum(f, ai, ai + h);
                ai += h;
            }
            ans += subsum(f, ai, b);
            return ans;
        }
};


int main(){
    try{
        Integrator<double, double> g("weights.txt");
        auto f = [](double x) {return std::pow(x, 5) - 2 * std::pow(x, 4) + 3 * std::pow(x, 3) - 4 * std::pow(x, 2) + 5 * x; };
        std::cout << "\nValue = " << g(f, -2, 2, 0.1s) << '\n';
    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        return 1;
    }
}