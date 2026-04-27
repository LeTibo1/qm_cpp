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
	((cout << args), ..., (cout << "\n"));
}

void err_msg(string message) {
	print("Error: ", message);
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
			print("New length is set to: ", round_to(new_length, 2), " nm");
		}
		void set_unit() {
			int choice;
			print("Select the number of the unit for the energy output:");
			for (int i = 0; i < units::names.size(); i++) {
				print(" ", i, " - ", units::names.at(i));
			}

			cout << "Your Input: ";
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
			print("The energy of the ", grade, " state of the particle is: ", energy, unit);
		}
};

// ====================================
//           - print functions -
// ====================================

void print_starting_menu() {
	vector<string> menu {
		"--------------------------------",
		"Choose an option:",
		" 1 - 'create a new particle'",
		" 2 - 'interact with particle'",
		" 3 - 'delete particle'",
		" 4 - 'exit program'",
	};

	for (int i = 0; i < menu.size(); i++) {
		print(menu.at(i));
	}
}

void print_particle_menu() {
	vector<string> menu {
		"--------------------------------",
		"Choose an option:",
		" 0 - 'back to main menu'",
		" 1 - 'set length of the box'",
		" 2 - 'set unit of the energy'",
		" 3 - 'get energy of a given state'",
	};

	for (int i = 0; i < menu.size(); i++) {
		print(menu.at(i));
	}
}

void particle_menu(ParticleInABox& particle) {
	while (true) {
		print_particle_menu();
		int choice;
		cout << "Your choice: ";
		cin >> choice;

		if (choice == 0) {
			break;
		} else if (choice == 1) {
			double length;
			cout << "Enter length of the box in [nm]: ";
			cin >> length;
			particle.set_length(length);
		} else if (choice == 2) {
			particle.set_unit();
		} else if (choice == 3) {
			int n;
			cout << "Enter number of state: ";
			cin >> n;
			particle.get_energy(n);
		}
	}
}
    
// ====================================
//           - main function -
// ====================================

int main() {
	print("WELCOME TO THE PARTICLE IN A BOX PROGRAM ;)");
	bool is_created = false;
	// unique lässt nur ein Objekt gleichzeitig zu.
	// schlecht, falls man programm erweitern will
	// um mehrere Objekte zu erlauben
	unique_ptr<ParticleInABox> particle;
	void particle_menu(ParticleInABox& particle);
	while (true) {
		int choice;
		print_starting_menu();
		cout << "Your choice: ";
		cin >> choice;

		if (choice == 1) {
			particle = make_unique<ParticleInABox>();
			print("A new particle has been created in the box");
			is_created = true;
		} else if (choice == 2) {
			if (is_created) {
				particle_menu(*particle);
			} else {err_msg("Particle has not been created yet. First create a particle");}
		} else if (choice == 3) {
			if (!is_created) {err_msg("Particle has not been created yet. First create a particle");}
			is_created = false;
			particle.reset();
		} else if (choice == 4) {break;}
	}

	return 0;
} 

