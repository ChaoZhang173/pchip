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
        //! initiazlie the linear interpolate function for plasma gradient
        void initLinearPlasmaGradient();
        //! initialize the parameters for pchip interpolation
        void initPchip(const vector<double>& x, const vector<double>& y, vector<double>& coef);
        //! initiazlie the parameters for linear interpolation
        void initLinear(const vector<double>& x, const vector<double>& y, vector<double>& coef);
        //! update the coefficients for pchip interpolation
        void updateCoeff(int interval);
        //! update the coefficients for linear interpolation
        void updateLinearCoeff(int interval);
        //! compute the plasma gradient
        void computePlasmaGradient(double const &f, double &Tecoef, double &necoef);
        //! compute the plasma gradient using linear interpolation
        void computeLinearPlasmaGradient(double const &f, double &Tecoef, double &necoef);
        //! find the index of y
        int findInterval(double& y);
        //! evaluate and write the interpolation 
        void evalPchip(double const &star, double const &end, int nums, const string& filename);
        //! evaluate and write the linear interpolation
        void evalLinear(double const &star, double const &end, int nums, const string& filename);

        string plasmafile;
        vector<double> plasmaPoints;
        vector<double> pchip_Tecoef;
        vector<double> pchip_necoef;
        vector<double> linear_Tecoef;
        vector<double> linear_necoef;
        vector<double> Te;
        vector<double> ne;
        int cachedInterval;
        double a_Te, b_Te, c_Te, d_Te;
        double a_ne, b_ne, c_ne, d_ne;
        double gradientAngle;
        double a_Te_linear;
        double a_ne_linear;

        double Teinf;
        double neinf, neeff;
};