#include <iostream>
#include <array>
#include <cstddef>
#include <cmath> 
#include <random>

template<std::size_t N, typename X, typename Y>
class Interpolant{
    private:
        std::array<X,N> x;
        std::array<Y,N> y;
        std::array<Y,N> diffs;
    public:
        Interpolant(const std::array<X, N>& x, const std::array<Y, N>& y): x(x), y(y)
        {
            std::array<Y, N> up;
            std::array<Y, N> down = y;
            for (std::size_t i = 0; i < N; i++)
            {
                diffs[i] = down[0];
                for (std::size_t j = 0; j < N - i; j++)
                    up[j] = (down[j+1] - down[j] ) / (x[j + i + 1] - x[j]);
                down = up;
                up = {};
            }
        };

        Interpolant(): x{}, y{} {};

        const std::array<X, N>& getX() const { return x; }
        const std::array<Y, N>& getY() const { return y; }
        const std::array<Y, N>& getD() const { return diffs; }

        Y operator()(const X &px) const{
            Y ans = 0;
            for (std::size_t i = 0; i < N; i++){
                X mult = 1;
                for (std::size_t j = 0; j < i; j++){
                    mult *= px - x[j];
                }
                ans += diffs[i] * mult;
            }

            return ans;
        }
        //void setGrid(const std::array<X, N>& a) { x = a; }
        //void setGrid(const std::array<Y, N>& a) { y = a; }
};

template<typename X, typename Y = X>
Y func0(const X &px){
    Y ans = std::exp(-0.1 * std::pow(px, 2)) * std::sin(px);
    return ans;
}

template<std::size_t N, typename Y>
void Noise(std::array<Y, N>& y, Y amp){
    static std::mt19937 rng(std::random_device{}());
    std::normal_distribution<Y> dist(0.0, amp);

    for (Y& y0: y)
        y0 += dist(rng);
}

int main() {
    constexpr std::size_t n = 8;
    double h = 0.0625;

    std::array<double, n> a;
    for (std::size_t i = 0; i < n; i++){ a[i] = h * ((int)i - (int)(n / 2)); }

    std::array<double, n> b;
    for (std::size_t i = 0; i < n; i++){ b[i] = func0(a[i]); }
    
    std::array<double, n> c;
    Interpolant<n, double, double> func(a, b);
    

    std::cout << "\nNodes X: \n[";
    for (std::size_t i = 0; i < n; i++){
        std::cout << a[i] << ", ";
    }        
    std::cout << "]\n";

    std::cout << "\nNodes Y: \n[";
    for (std::size_t i = 0; i < n; i++){
        std::cout << b[i] << ", ";
    }        
    std::cout << "]\n";

    Noise(a, h * .5);                                                      //чтобы точки не совпадали с изначальной сеткой
    std::cout << "\nTarget Nodes X: \n[";
    for (std::size_t i = 0; i < n; i++){
        std::cout << a[i] << ", ";
    }        
    std::cout << "]\n";

    for (std::size_t i = 0; i < n; i++){ c[i] = func(a[i]); }
    std::cout << "\nInterpolated in Target Nodes Y: \n[";
    for (std::size_t i = 0; i < n; i++){
        std::cout << c[i] << ", ";
    }        
    std::cout << "]\n";

    std::cout << "\nInterpolation error: \n[";
    for (std::size_t i = 0; i < n; i++){
        std::cout << std::abs(func0(a[i]) - c[i]) << ", ";
    }
    std::cout << "]\n";
    return 0;
}

// https://www.desmos.com/calculator/nfsr4ncsex?lang=ru