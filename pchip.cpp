#include "pchip.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

Initializer::Initializer(const string& inputfilename){
    readInputfile(inputfilename);
}

void Initializer::readInputfile(const string& inputfilename){
    ifstream ifs(inputfilename);

    vector<string> lines;
    string s;
    while(getline(ifs, s)){
        lines.push_back(s);
    }

    istringstream iss;
    size_t i = 0; // input file line number

    iss.str(lines[i++]);
    iss>>m_fAgnle;
    
    iss.clear();
    iss.str(lines[i++]);
    iss>>m_sPlasmafile;
}

PelletSolver::PelletSolver(Initializer* init){
    Teinf = 2000;
    neinf = 1e14;
    neeff = neinf;
    cachedInterval = -1;

    incidenceAngle = init->getAngle();
    plasmafile = init->getPlasmaFile();

    initPlasmaGradient();
}

void PelletSolver::initPlasmaGradient(){
    vector<double> Te;
    vector<double> ne;

    ifstream file(plasmafile);
    string line;

    if(!file.is_open()){
        cerr<<"Error: cannot open file "<<plasmafile<<endl;
        exit(1);
    }

    double r_val, Te_val, ne_val;
    while(getline(file, line)){
        istringstream iss(line);
        iss>>r_val>>Te_val>>ne_val;
        plasmaPoints.push_back(r_val);
        Te.push_back(Te_val);
        ne.push_back(ne_val);
    }
    file.close();

    // do pchip for Te, ne
    initPchip(plasmaPoints, Te, pchip_Tecoef);
    initPchip(plasmaPoints, ne, pchip_necoef);
}

void PelletSolver::initPchip(const vector<double>& x, const vector<double>& y, vector<double>& coef){
    int n = x.size();

    if(n < 2){
        cerr<<"Need at least 2 points for interpolation."<<endl;
        exit(1);
    }

    vector<double> h(n-1);
    vector<double> d(n-1);
    for(int i = 0; i < n-1; i++){
        h[i] = x[i+1] - x[i];
        d[i] = (y[i+1] - y[i]) / h[i];
    }

    // estimate the slopes
    vector<double> der(n);
    der[0] = d[0];
    der[n-1] = d[n-2];

    // // for debug 
    // cout<<" der[0] = "<<der[0]<<", d[0] = "<<d[0]<<endl;
    // cout<<" der[n-1] = "<<der[n-1]<<", d[n-2] = "<<d[n-2]<<endl;

    for (int i = 1; i < n-1; ++i){
        if (d[i-1]*d[i] > 0){
            der[i] = (2*h[i+1]*d[i-1] + 2*h[i]*d[i]) / (h[i+1] + h[i]);
        } else {
            der[i] = 0;
        }
    }

    // prevent oscillation
    for (int i = 0; i < n - 1; ++i){
        if (d[i] == 0){
            der[i] = 0;
            der[i+1] = 0;
        } else {
            double alpha = der[i] / d[i];
            double beta = der[i+1] / d[i];
            double sum = alpha*alpha + beta*beta;
            if (sum > 9){
                double tau = 3 / sqrt(sum);
                der[i] = tau * alpha * d[i];
                der[i+1] = tau * beta * d[i];
            }
        }
    }

    for (int i = 0; i < n - 1; ++i){
        double a = (der[i] + der[i+1] - 2*d[i]) / (h[i]*h[i]);
        double b = (3*d[i] - 2*der[i] - der[i+1]) / h[i];
        double c = der[i];
        double d = y[i];

        // // for debug 
        // if (i == 0){
        //     cout<<"a = "<<a<<", b = "<<b<<", c = "<<c<<", d = "<<d<<endl;
        // }

        coef.push_back(a);
        coef.push_back(b);
        coef.push_back(c);
        coef.push_back(d);
    }
}

void PelletSolver::computePlasmaGradient(double const &f, double &Tecoef, double &necoef){
    double y = f * incidenceAngle;
    int interval = findInterval(y);
    if(interval == -1){
        cerr<<"Error: cannot find the interval for f="<<f<<endl;
        exit(1);
    }

    // only update the coefficients when the interval changes
    if (interval != cachedInterval){
        updateCoeff(interval);
    }

    double dx = y - plasmaPoints[interval];

    // // for debug
    // cout<<"y = "<<y<<", dx = "<<dx<<endl;
    // cout<<"a_Te = "<<a_Te<<", b_Te = "<<b_Te<<", c_Te = "<<c_Te<<", d_Te = "<<d_Te<<endl;
    // cout<<"a_ne = "<<a_ne<<", b_ne = "<<b_ne<<", c_ne = "<<c_ne<<", d_ne = "<<d_ne<<endl;

    Tecoef = (a_Te*dx*dx*dx + b_Te*dx*dx + c_Te*dx + d_Te)/Teinf;
    necoef = (a_ne*dx*dx*dx + b_ne*dx*dx + c_ne*dx + d_ne)/neinf;
}

int PelletSolver::findInterval(double& y){
    int n = plasmaPoints.size();
    if(y < plasmaPoints[0] || y > plasmaPoints[n-1]){
        return -1;
    }

    for (int i = 0; i < n-1; ++i){
        if (y >= plasmaPoints[i] && y <= plasmaPoints[i+1]){
            return i;
        }
    }

    return -1;
}

void PelletSolver::updateCoeff(int interval){
    a_Te = pchip_Tecoef[4*interval];
    b_Te = pchip_Tecoef[4*interval+1];
    c_Te = pchip_Tecoef[4*interval+2];
    d_Te = pchip_Tecoef[4*interval+3];

    a_ne = pchip_necoef[4*interval];
    b_ne = pchip_necoef[4*interval+1];
    c_ne = pchip_necoef[4*interval+2];
    d_ne = pchip_necoef[4*interval+3];

    cachedInterval = interval;
}