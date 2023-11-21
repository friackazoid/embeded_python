#include <pybind11/eval.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include <iostream>
#include <pybind11/pytypes.h>
#include <vector>


void example_1 () {

    std::cout << "======================= Example 1" << std::endl;

    pybind11::scoped_interpreter guard{};


    pybind11::dict locals;
    pybind11::exec(R"(
    import my_robot_function

    print("Hello from Python!")

    robot = my_robot_function.MyRobotFunction()
    robot.movej([1,2,3,4,5,6], 1.0, 2.0)

    )", pybind11::globals(), locals);
}

void example_2 () {
    std::cout << "====================== Example 2" << std::endl;

    pybind11::scoped_interpreter guard{};
    std::vector<std::string> script{
        "import my_robot_function",
        "print('Hello from Python!')",
        "robot = my_robot_function.MyRobotFunction()",
        "robot.movej([1,2,3,4,5,6], 1.0, 2.0)"
    };


    for (const auto &line : script) {
        try {
            std::cout << "Executing: " << line << std::endl;
            pybind11::eval<pybind11::eval_single_statement>(line);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            PyErr_Print();
        }
    }
}

void example_3 () {
    std::cout << "====================== Example 3" << std::endl;

    pybind11::scoped_interpreter guard{};
    std::vector<std::string> script{
        "import my_robot_function",
        "hi()",
        "print('Hello from Python!')",
        "robot = my_robot_function.MyRobotFunction()",
        "robot.movej([1,2,3,4,5,6], 1.0, 2.0)"
    };

    for (const auto &line : script) {
        try {
            pybind11::eval<pybind11::eval_single_statement>(line);
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << "In line: " << line << std::endl;
            PyErr_Print();
        }
    }
}

void example_4 () {

    std::cout << "======================= Example 4" << std::endl;

    try {

    pybind11::scoped_interpreter guard{};

    pybind11::dict g;
    //= pybind11::globals();
    g["__builtins__"]["print"]= pybind11::globals()["__builtins__"]["print"];
    pybind11::dict locals;

    try {
        pybind11::exec(R"(

            print("Hello from Python!")
            f = open("test.txt", "w")
        )", g, locals);
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        PyErr_Print();
    }
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        PyErr_Print();
    }
}


int main (int argc, char *argv[])
{

    try {
        example_1();
        example_2();
        example_3();
        // Doesn't work
        //example_4();
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "FIN!" << std::endl;
    return 0;
}
