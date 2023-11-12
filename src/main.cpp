#include <Python.h>
#include <iostream>
#include <vector>

void movej(const std::vector<double>& joint_positions, double a, double b) {
    // Your implementation of the movej function goes here
    std::cout << "Moving joints to: ";
    for (double position : joint_positions) {
        std::cout << position << " ";
    }
    std::cout << " with acceleration " << a << " and blending " << b << std::endl;
}

static PyObject* movej_wrapper(PyObject* self, PyObject* args, PyObject* kwargs) {
    // Parse arguments and call the C++ movej function
    PyObject* joint_positions_obj;
    double a, b;

    static const char* keywords[] = {"joint_positions", "a", "b", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Odd", (char**)keywords, &joint_positions_obj, &a, &b)) {
        return NULL;
    }

    std::vector<double> joint_positions;

    if (PyList_Check(joint_positions_obj)) {
        Py_ssize_t size = PyList_Size(joint_positions_obj);
        for (Py_ssize_t i = 0; i < size; ++i) {
            PyObject* item = PyList_GetItem(joint_positions_obj, i);
            joint_positions.push_back(PyFloat_AsDouble(item));
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "joint_positions must be a list");
        return NULL;
    }

    movej(joint_positions, a, b);

    Py_RETURN_NONE;
}

static PyMethodDef module_methods[] = {
    {"movej", (PyCFunction)movej_wrapper, METH_VARARGS | METH_KEYWORDS, "Move joints"},
    {NULL, NULL, 0, NULL} // Sentinel
};


static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT,
    "robot_module", // Module name
    NULL, // Module docstring
    -1, // Module state
    module_methods
};

PyMODINIT_FUNC 
PyInit_robot_module(void) {
    return PyModule_Create(&module_def);
}


int main() {
 // Execute custom scripting language code
    const char* script = R"(
import robot_module
import random

c = random.randint(1, 10)

if c < 5:
    print("c is less than 5")
    print (c)
    robot_module.movej([0, 1.57, 0, 0, 0, 0], a=c, b=1)
else:
    print("c is greater than 5")
    print (c)
    robot_module.movej([0, 1.57, 0, 0, 0, 0], a=42, b=1)
)";

    if (PyImport_AppendInittab("robot_module", &PyInit_robot_module) == -1) {
        std::cout << "Failed to add robot_module to the interpreter's builtin modules" << std::endl;
        return 1;
    }

    Py_SetProgramName((wchar_t*)L"robot_module");

    // Initialize the Python interpreter
    Py_Initialize();

    PyObject *pmodule = PyImport_ImportModule("robot_module");

    PyRun_SimpleString(script);

    // Finalize the Python interpreter
    Py_Finalize();

    return 0;
}

