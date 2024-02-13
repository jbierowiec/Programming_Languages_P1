import json
import math

class CelestialBody:
    def __init__(self, Name, Diameter=0, Circumference=0):
        self.name = Name
        self.diameter = Diameter
        self.circumference = Circumference
        self.radius = Diameter / 2 if Diameter else 0
        self.volume = (4/3) * math.pi * math.pow(self.radius, 3) if Diameter else 0


class Moon(CelestialBody):
    def __init__(self, Name, Diameter=0, Circumference=0):
        super().__init__(Name, Diameter, Circumference)

    def calculate_defaults(self):
        if not self.diameter:
            self.diameter = self.diameter_from_circumference()
        if not self.radius:
            self.radius = self.diameter / 2
        if not self.circumference:
            self.circumference = self.circumference_from_diameter()
        if not self.volume:
            self.volume = self.volume_from_radius()

    def diameter_from_circumference(self):
        return self.circumference / math.pi

    def circumference_from_diameter(self):
        return math.pi * self.diameter

    def volume_from_radius(self):
        return (4/3) * math.pi * math.pow(self.radius, 3)


class Planet(CelestialBody):
    def __init__(self, Name, DistanceFromSun=0, OrbitalPeriod=0, Diameter=0, Circumference=0, Moons=None):
        super().__init__(Name, Diameter, Circumference)
        self.distance_from_sun = DistanceFromSun
        self.orbital_period = OrbitalPeriod
        self.moons = [Moon(**moon) for moon in Moons] if Moons else []
        self.calculate_defaults()

    def calculate_defaults(self):
        if not self.diameter:
            self.diameter = self.diameter_from_circumference()
        if not self.radius:
            self.radius = self.diameter / 2
        if not self.circumference:
            self.circumference = self.circumference_from_diameter()
        if not self.orbital_period:
            self.orbital_period = self.orbital_period_from_distance()
        if not self.volume:
            self.volume = self.volume_from_radius()
        for moon in self.moons:
            moon.calculate_defaults()

    def diameter_from_circumference(self):
        return self.circumference / math.pi

    def circumference_from_diameter(self):
        return math.pi * self.diameter

    def orbital_period_from_distance(self):
        return math.sqrt(math.pow(self.distance_from_sun, 3))

    def volume_from_radius(self):
        return (4/3) * math.pi * math.pow(self.radius, 3)


class Sun(CelestialBody):
    def __init__(self, Name, Diameter=0, Planets=None):
        super().__init__(Name, Diameter)
        self.planets = [Planet(**planet) for planet in Planets] if Planets else []
        self.calculate_defaults()

    def calculate_defaults(self):
        if not self.diameter:
            self.diameter = self.diameter_from_circumference()
        if not self.radius:
            self.radius = self.diameter / 2
        if not self.circumference:
            self.circumference = math.pi * self.diameter  # No need for a separate method
        if not self.volume:
            self.volume = (4/3) * math.pi * math.pow(self.radius, 3)
        for planet in self.planets:
            planet.calculate_defaults()


def display_info(body):
    print(f"{body.name}\n")
    print(f"Circumference: {body.circumference}")
    print(f"Diameter: {body.diameter}")

    if isinstance(body, Planet):
        print(f"Distance From Sun: {body.distance_from_sun}")
        print(f"Orbital Period: {body.orbital_period}")

    print(f"Radius: {body.radius}")
    print(f"Volume: {body.volume}")

    print("\n")


def sum_of_volumes(planets):
    total_volume = sum(planet.volume for planet in planets)
    return total_volume


def is_sun_volume_greater(planets, sun):
    sum_of_planet_volumes = sum_of_volumes(planets)
    return sun.volume > sum_of_planet_volumes


# Read data from JSONPrettyPrint.txt
with open("JSONPlain.txt", "r") as file:
    solar_system_data = json.load(file)

# Create objects
sun = Sun(**solar_system_data)

# Display information
print("\nHello Solar System!\n")
display_info(sun)

for planet in sun.planets:
    display_info(planet)
    for moon in planet.moons:
        display_info(moon)

if is_sun_volume_greater(sun.planets, sun):
    print(f"The sun's volume: {sun.volume} is greater than the sum of volumes of all planets: {sum_of_volumes(sun.planets)}.\n")
else:
    print(f"The sun's volume: {sun.volume} is not greater than the sum of volumes of all planets: {sum_of_volumes(sun.planets)}.\n")
