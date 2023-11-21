#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
#include <iostream>
#include <random>

class MyRobotFunction {
public:
    MyRobotFunction() {}
    ~MyRobotFunction() {}

    void movej(const std::vector<double> &joint_positions, double a, double b) {
        std::cout << "Moving joints to: ";
        for (double position : joint_positions) {
            std::cout << position << " ";
        }
        std::cout << " with acceleration " << a << " and blending " << b << std::endl;

    }

    int read_signal (const std::string &signal_name, std::vector<double> &signal_values) {

        std::mt19937 rng(std::random_device{}());

        // Define the distribution for integers between 1 and 10
        std::uniform_int_distribution<int> distribution(1, 10);

        // Generate a random number
        int random_number = distribution(rng);

        // Your implementation of the read_signal function goes here
        std::cout << "Reading signal[" << signal_name << "] = " << random_number << std::endl;
        return random_number;
    }
};


PYBIND11_MODULE(my_robot_function, m) {
    pybind11::class_<MyRobotFunction>(m, "MyRobotFunction")
        .def(pybind11::init<>())
        .def("movej", &MyRobotFunction::movej)
        .def("read_signal", &MyRobotFunction::read_signal);
}


