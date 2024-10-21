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

    double f1 = 1.0;
    double f2 = 1.5;
    double f3 = 2.2;
    double f4 = 3.1;
    double f5 = 4.5;
    double f6 = 5.0; 
    double f7 = 7.0; 
    double Tecoef, necoef;
    pelletsolver->computePlasmaGradient(f1, Tecoef, necoef);
    cout<<"x = "<<f1<<endl;
    cout << "Te1: " << Tecoef*pelletsolver->Teinf << endl;
    cout << "ne1: " << necoef*pelletsolver->neeff << endl;
    
    pelletsolver->computePlasmaGradient(f2, Tecoef, necoef);
    cout<<"x = "<<f2<<endl;
    cout << "Te2: " << Tecoef*pelletsolver->Teinf << endl;
    cout << "ne2: " << necoef*pelletsolver->neeff << endl;

    pelletsolver->computePlasmaGradient(f3, Tecoef, necoef);
    cout<<"x = "<<f3<<endl;
    cout << "Te3: " << Tecoef*pelletsolver->Teinf << endl;
    cout << "ne3: " << necoef*pelletsolver->neeff << endl;

    pelletsolver->computePlasmaGradient(f4, Tecoef, necoef);
    cout<<"x = "<<f4<<endl;
    cout << "Te4: " << Tecoef*pelletsolver->Teinf << endl;
    cout << "ne4: " << necoef*pelletsolver->neeff << endl;

    pelletsolver->computePlasmaGradient(f5, Tecoef, necoef);
    cout<<"x = "<<f5<<endl;
    cout << "Te5: " << Tecoef*pelletsolver->Teinf << endl;
    cout << "ne5: " << necoef*pelletsolver->neeff << endl;

    pelletsolver->computePlasmaGradient(f6, Tecoef, necoef);
    cout<<"x = "<<f6<<endl;
    cout << "Te6: " << Tecoef*pelletsolver->Teinf << endl;
    cout << "ne6: " << necoef*pelletsolver->neeff << endl;

    pelletsolver->computePlasmaGradient(f7, Tecoef, necoef);
    cout<<"x = "<<f7<<endl;
    cout << "Te7: " << Tecoef*pelletsolver->Teinf << endl;
    cout << "ne7: " << necoef*pelletsolver->neeff << endl;

    delete init;
    delete pelletsolver;

    return 0;
}