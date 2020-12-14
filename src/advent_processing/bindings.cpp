
#include <pybind11/pybind11.h>

#include "day.h"
#include "day1.h"
#include "day2.h"

namespace py = pybind11;

PYBIND11_MODULE(advent_processing, m) {
    m.doc() = "Processing interface for all days";
    
    py::class_<Day>(m, "Day")
        .def("process", &Day::process, pybind11::arg("input_file"));

    py::class_<Day1, Day>(m, "Day1")
        .def(py::init<>());

    py::class_<Day2, Day>(m, "Day2")
        .def(py::init<>());
};

