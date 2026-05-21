#include <iostream>
#include <cmath>
using namespace std;

const double g = 9.81;

// Convert degrees to radians
double degToRad(double theta_deg) 
{
    return theta_deg * (M_PI / 180.0);
}

double calculateTimeOfFlight(double v, double theta_rad) 
{
    double vy = v * sin(theta_rad);
    return (2.0 * vy) / g;
}

double calculateMaxHeight(double v, double theta_rad) 
{
    double vy = v * sin(theta_rad);
    return pow(vy, 2) / (2.0 * g);
}

double calculateRange(double v, double theta_rad) 
{
    double vx = v * cos(theta_rad);
    double t_flight = calculateTimeOfFlight(v, theta_rad);
    return vx * t_flight;
}

double calculateYAtX(double v, double theta_rad, double x) 
{
    double numerator = g * pow(x, 2);
    double denominator = 2.0 * pow(v, 2) * pow(cos(theta_rad), 2);
    return (x * tan(theta_rad)) - (numerator / denominator);
}

int main() 
{
    double v, theta_deg, x;

    cout << "Enter initial speed v (m/s): ";
    cin >> v;

    if (v < 0)
    {
        cout << "Error: Initial speed cannot be negative!" << endl;
        return 1;
    }

    cout << "Enter launch angle theta (degrees): ";
    cin >> theta_deg;

    cout << "Enter a target horizontal distance x (m) to find its vertical position y: ";
    cin >> x;
    cout << "--------------------------------------------------" << endl;

    // Convert angle to radians once before passing to other functions
    double theta_rad = degToRad(theta_deg);

    cout << "Trajectory Simulation Results:" << endl;
    cout << "(a) Time of flight:      " << calculateTimeOfFlight(v, theta_rad) << " s" << endl;
    cout << "(b) Maximum height:     " << calculateMaxHeight(v, theta_rad) << " m" << endl;
    cout << "(c) Horizontal range:   " << calculateRange(v, theta_rad) << " m" << endl;
    cout << "(d) Vertical position y at x=" << x << "m is: " << calculateYAtX(v, theta_rad, x) << " m" << endl;

    return 0;
}