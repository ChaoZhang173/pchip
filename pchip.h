#include <string>
#include <vector>

using namespace std;
class Initializer{
    public:
        Initializer(const string& inputfilename);

        void readInputfile(const string& inputfilename);
        string getPlasmaFile() const{return m_sPlasmafile;}
        double getAngle() const{return m_fAgnle;}
    private:
        double m_fAgnle;
        string m_sPlasmafile;
};

class PelletSolver{
    public:
        PelletSolver(Initializer* init);

        //! initialize the interpolate function for plasma gradient
        void initPlasmaGradient();
        //! initialize the parameters for pchip interpolation
        void initPchip(const vector<double>& x, const vector<double>& y, vector<double>& coef);
        //! update the coefficients for pchip interpolation
        void updateCoeff(int interval);
        //! compute the plasma gradient
        void computePlasmaGradient(double const &f, double &Tecoef, double &necoef);
        //! find the index of y
        int findInterval(double& y);

        string plasmafile;
        vector<double> plasmaPoints;
        vector<double> pchip_Tecoef;
        vector<double> pchip_necoef;
        int cachedInterval;
        double a_Te, b_Te, c_Te, d_Te;
        double a_ne, b_ne, c_ne, d_ne;
        double incidenceAngle;

        double Teinf;
        double neinf, neeff;
};