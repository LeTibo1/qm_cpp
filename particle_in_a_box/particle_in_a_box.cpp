#include <iostream>
#include <numbers>
#include <math.h>
using namespace std; 

namespace phys_const {
    const double h = 6.626e-34;
    const double h_bar = h/(2*M_PI);  
}
using namespace phys_const;

class ParticleInABox {
    private:

    float length;
    float mass = 1,6735575*10e-27;   
    float h_bar = h/(2*M_PI);
    
    public:

    float energie(float length) {
        int n = 1;
        float mass = 9.109e-31; 
        return (pow(n,2)*pow(M_PI,2)*pow(h_bar,2))/(2*mass*pow(length,2));
    }
};

int main() {
    float length;
    cout << "gib länge der Box:" << "\n";
    cin >> length;
    ParticleInABox partile_1; 
    float energies = partile_1.energie(length);
    cout << energies << "super sache\n"; 
    return 0;
} 

