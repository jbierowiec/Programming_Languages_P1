#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

double radius(double Diameter) {
    return Diameter / 2;
}

double circumference(double Diameter) {
    return M_PI * Diameter;
}

double diameter(double Circumference) {
    return Circumference / M_PI;
}

double orbitalperiod(double Radius) {
    return sqrt(pow(Radius, 3.0));
}

double distancefromsun(double OrbitalPeriod) {
    return cbrt(pow((OrbitalPeriod / (2 * M_PI)), 2));
}

double volume(double Radius) {
    return ((4 * M_PI * pow(Radius, 3))/3);
}

struct Moon {
    string Name;
    double Diameter;
    double Circumference;
};

struct Planet {
    string Name;
    double DistanceFromSun;
    double OrbitalPeriod;
    double Diameter;
    double Circumference;
    vector<Moon> Moons;

    // Extra variables
    double Radius;
    double Volume;
};

struct Sun {
    string Name;
    double Diameter;
    double Circumference;
    vector<Planet> Planets;

    // Extra variables
    double Radius;
    double Volume;
};

void calculateDefaults(Planet& planet) {
    if (planet.Diameter == 0.00) {
        planet.Diameter = diameter(planet.Circumference);
    }

    if (planet.Radius == 0.00) {
        planet.Radius = radius(planet.Diameter);
    }

    if (planet.Circumference == 0.00) {
        planet.Circumference = circumference(planet.Diameter);
    }

    if (planet.OrbitalPeriod == 0.00) {
        planet.OrbitalPeriod = orbitalperiod(planet.DistanceFromSun);
    }

    if (planet.DistanceFromSun == 0.00) {
        planet.DistanceFromSun = distancefromsun(planet.OrbitalPeriod);
    }

    if (planet.Volume == 0.00) {
        planet.Volume = volume(planet.Radius);
    } 

    for (Moon& moon : planet.Moons) {
        if (moon.Diameter == 0.00) {
            moon.Diameter = diameter(moon.Circumference);
        }

        if (moon.Circumference == 0.00) {
            moon.Circumference = circumference(moon.Diameter);
        }
    }
}

void calculateDefaults(Moon& moon) {
    if (moon.Diameter == 0.0) {
        moon.Diameter = diameter(moon.Circumference);
    }

    if (moon.Circumference == 0.0) {
        moon.Circumference = circumference(moon.Diameter);
    }
}

void calculateDefaults(Sun& sun) {
    if (sun.Diameter == 0.0) {
        sun.Diameter = diameter(sun.Circumference);
    }

    if (sun.Radius == 0.00) {
        sun.Radius = radius(sun.Diameter);
    }

    if (sun.Circumference == 0.0) {
        sun.Circumference = circumference(sun.Diameter);
    }

    if (sun.Volume == 0.00) {
        sun.Volume = volume(sun.Radius);
    } 

    for (Planet& planet : sun.Planets) {
        calculateDefaults(planet);
    }
}

void displaySunInfo(const Sun& sun) {
    cout << sun.Name << "\n\n";
    cout << "Circumference: " << sun.Circumference << "\n";
    cout << "Diameter: " << sun.Diameter << "\n";
    cout << "Radius: " << sun.Radius << "\n";
    cout << "Volume: " << sun.Volume << "\n\n";
}

void displayPlanetInfo(const Planet& planet) {
    cout << planet.Name << "\n\n";
    cout << "Circumference: " << planet.Circumference << "\n";
    cout << "Diameter: " << planet.Diameter << "\n";
    cout << "Orbital Period: " << planet.OrbitalPeriod << "\n";
    cout << "Distance From Sun: " << planet.DistanceFromSun << "\n";
    cout << "Radius: " << planet.Radius << "\n";
    cout << "Volume: " << planet.Volume << "\n\n";
}

double sum_of_volumes(const vector<Planet>& planets) {
    double totalVolume = 0.0;
    for (const Planet& planet : planets) {
        totalVolume += planet.Volume;
    }
    return totalVolume;
}

bool isSunVolumeGreater(const vector<Planet>& planets, const Sun& sun) {
    double sumOfPlanetVolumes = sum_of_volumes(planets);
    return sun.Volume > sumOfPlanetVolumes;
}

int main()
{
    vector<Planet> planets = {
        { "Mecury", 0.39, 0.0, 0.0, 15329.0 },
        { "Venus", 0.72, 0.0, 12104.0, 0.0 },
        { "Earth", 1.0, 1.0, 12756.0, 40075.0, { { "Luna", 3474.0, 10917.0 } } },
        { "Mars", 1.52, 0.0, 0.0, 21344.0, { { "Phobos", 22.5, 0.0 }, { "Deimos", 0.0, 39.0 } } },
        { "Jupiter", 5.2, 0.0, 142984.0, 0.0, { { "Ganymede", 5268.0, 0.0 }, { "Calisto", 0.0, 4820.6 }, { "Io", 0.0, 3643.2 } } },
        { "Saturn", 9.54, 0.0, 120536.0, 0.0, {} },
        { "Uranus", 19.2, 0.0, 51118.0, 0.0 },
        { "Neptune", 30.06, 0.0, 49528.0, 0.0 }
    };

    cout << endl;
    cout << "Hello Solar System!\n\n";

    Sun sun{ "Sol", 1400000.0, 0.0, planets };

    calculateDefaults(sun);
    displaySunInfo(sun);

    for (Planet& planet : planets) {
        calculateDefaults(planet);
        displayPlanetInfo(planet);

        for (Moon& moon : planet.Moons) {
            calculateDefaults(moon);

            cout << "  " << moon.Name << "\n";
            cout << "  Circumference: " << moon.Circumference << "\n";
            cout << "  Diameter: " << moon.Diameter << "\n\n";
        }
    }

    if (isSunVolumeGreater(planets, sun)) {
        cout << "The sun's volume: " << sun.Volume << " is greater than the sum of volumes of all planets: " << sum_of_volumes(planets) << ".\n\n";
    } else {
        cout << "The sun's volume: " << sun.Volume << " is not greater than the sum of volumes of all planets: " << sum_of_volumes(planets) << ".\n\n";
    }

    return 0;
}
