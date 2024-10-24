#include "pchip.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    std::string inputfilename;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            inputfilename = argv[i + 1];
        }
    }

    if (inputfilename.empty()) {
        std::cerr << "Usage: " << argv[0] << " -i <inputfile>" << std::endl;
        return 1;
    }

    Initializer *init = new Initializer(inputfilename);
    PelletSolver *pelletsolver = new PelletSolver(init);

    // double z1 = 1.0;
    // double z2 = 1.5;
    // double z3 = 2.2;
    // double z4 = 3.1;
    // double z5 = 4.5;
    // double z6 = 5.0; 
    // double z7 = 7.0; 
    // double Tecoef, necoef;
    // pelletsolver->computePlasmaGradient(z1, Tecoef, necoef);
    // cout<<"x = "<<z1<<endl;
    // cout << "Te1: " << Tecoef*pelletsolver->Teinf << endl;
    // cout << "ne1: " << necoef*pelletsolver->neeff << endl;
    
    // pelletsolver->computePlasmaGradient(z2, Tecoef, necoef);
    // cout<<"x = "<<z2<<endl;
    // cout << "Te2: " << Tecoef*pelletsolver->Teinf << endl;
    // cout << "ne2: " << necoef*pelletsolver->neeff << endl;

    // pelletsolver->computePlasmaGradient(z3, Tecoef, necoef);
    // cout<<"x = "<<z3<<endl;
    // cout << "Te3: " << Tecoef*pelletsolver->Teinf << endl;
    // cout << "ne3: " << necoef*pelletsolver->neeff << endl;

    // pelletsolver->computePlasmaGradient(z4, Tecoef, necoef);
    // cout<<"x = "<<z4<<endl;
    // cout << "Te4: " << Tecoef*pelletsolver->Teinf << endl;
    // cout << "ne4: " << necoef*pelletsolver->neeff << endl;

    // pelletsolver->computePlasmaGradient(z5, Tecoef, necoef);
    // cout<<"x = "<<z5<<endl;
    // cout << "Te5: " << Tecoef*pelletsolver->Teinf << endl;
    // cout << "ne5: " << necoef*pelletsolver->neeff << endl;

    // pelletsolver->computePlasmaGradient(z6, Tecoef, necoef);
    // cout<<"x = "<<z6<<endl;
    // cout << "Te6: " << Tecoef*pelletsolver->Teinf << endl;
    // cout << "ne6: " << necoef*pelletsolver->neeff << endl;

    // pelletsolver->computePlasmaGradient(z7, Tecoef, necoef);
    // cout<<"x = "<<z7<<endl;
    // cout << "Te7: " << Tecoef*pelletsolver->Teinf << endl;
    // cout << "ne7: " << necoef*pelletsolver->neeff << endl;

    pelletsolver->evalPchip(1.489, 1.449, 100, "3output.txt");

    delete init;
    delete pelletsolver;

    return 0;
}