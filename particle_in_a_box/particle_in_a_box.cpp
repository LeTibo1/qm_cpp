#include <iostream>
#include <numbers>
#include <math.h>

// ====================================
//           - namespace -
// ====================================

using namespace std; 

namespace phys_const {
    const double h = 6.62607015e-34;
    const double h_bar = h/(2*M_PI);  
}
using namespace phys_const;

namespace units {
	const unordered_map<string, double> factors {
		{"J", 1.0},
		{"eV", 6.24181e18},
		{"kcal/mol", 1.44e20},
		{"kJ/mol", 6.02e20},
		{"cm-1", 5.03445e22},
		{"nm", 1.98644586e-16}
	};
	
	const vector<string> names {"J", "eV", "kcal/mol", "kJ/mol", "cm-1", "nm"};
}

// ====================================
//           - functions -
// ====================================


template<typename... Args>
void print(Args&&... args) {
	((cout << args), ...);
}

template <typename T>
double round_to(T a, int dec) {
	double mult = 1.0;
	for (int i = 0; i < dec; i++) {
		mult *= 10.0;
	}

	double scaled = a * mult;
	double rounded = round(scaled);

	return rounded / mult;
}

// ====================================
//           - Particle class -
// ====================================

class ParticleInABox {
    private:

		// functions
		double convert_unit(string unit) {
			auto it = units::factors.find(unit);
			if (it != units::factors.end()) {
				return it->second;
			}

			return 1.0;
		}
    	double calc_energy(double length, double mass, int n, string unit) {
			double energy;
        	energy = (pow((n * M_PI * h_bar),2)) / (2 * mass * pow(length,2));
			energy *= convert_unit(unit);
        	return energy;
    	}
		

		// variables with default values
    	double length = 10e-9;
    	double mass = 1.6735575*10e-27;   
    	double h_bar = h/(2*M_PI);
		int n = 1;
		string unit = "J";
    
    public:

		// set functions
		void set_length(double new_length) {
			length = new_length * 10e-9;
			print("New length is set to: ", round_to(new_length, 2), " nm\n");
		}
		void set_unit() {
			int choice;
			print("Select the number of the unit for the energy output:\n");
			for (int i = 0; i < units::names.size(); i++) {
				print(i, " ", units::names.at(i), "\n");
			}

			cin >> choice;
			unit = units::names.at(choice);
			print("Energy will be displayed in ", unit);
		}
		// get functions
		void get_energy(int n) {
			double energy = calc_energy(length, mass, n, unit);

			string grade = to_string(n) + "th";
			if (n == 1) {
				grade = "ground";
			} else if (n == 2) {
				grade = "2nd";
			} else if (n == 3) {
				grade = "3rd";
			}
			print("The energy of the ", grade, " state of the particle is: ", energy, unit, "\n");
		}
};

// ====================================
//           - main function -
// ====================================

int main() {
    double length;
    print("Length of the box in [nm]: ");
    cin >> length;
    ParticleInABox particle_1; 
    particle_1.set_length(length);
    particle_1.get_energy(2);
    return 0;
} 

