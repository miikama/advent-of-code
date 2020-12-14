"""Setting up advent_of_code python package
with bindings for C++ processing code.

Takes inspiration from 
https://github.com/pybind/cmake_example/blob/master/setup.py

"""
import os
import sys
import subprocess

from setuptools import Extension, find_packages, setup
from setuptools.command.build_ext import build_ext


# A CMakeExtension needs a sourcedir instead of a file list.
class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        Extension.__init__(self, name, sources=[])

        # /path/to/advent_of_code
        self.sourcedir = os.path.abspath(sourcedir)

class CMakeBuild(build_ext):

    def build_extension(self, ext):
        """
        The paths are set to following:

            ext.name:           advent_processing
            ext.sourcedir:      /mnt/c/Users/Miika/Documents/ohjelmointi/advent-of-code            
            extdir:             /mnt/c/Users/Miika/Documents/ohjelmointi/advent-of-code/build/lib.linux-x86_64-3.6/
            self.build_temp:    build/temp.linux-x86_64-3.6

        """
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        # required for auto-detection of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cfg = "Debug" if self.debug else "Release"
        
        print(f"Got ext.name {ext.name}")
        print(f"Got ext.sourcedir {ext.sourcedir}")
        print(f"Got full path {self.get_ext_fullpath(ext.name)}")
        print(f"Got extdir {extdir}")        
        print(f"Got build_temp folder {self.build_temp}")        


        # Set Python_EXECUTABLE instead if you use PYBIND11_FINDPYTHON
        # EXAMPLE_VERSION_INFO shows you how to pass a value into the C++ code
        # from Python.
        cmake_args = [
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={}".format(extdir),
            "-DPYTHON_EXECUTABLE={}".format(sys.executable),
            "-DCMAKE_BUILD_TYPE={}".format(cfg),
        ]
        
        # CMake lets you override the generator - we need to check this.
        # Can be set with Conda-Build, for example.
        # cmake_generator = os.environ.get("CMAKE_GENERATOR", "")
        # Using Ninja-build since it a) is available as a wheel and b)
        # multithreads automatically. MSVC would require all variables be
        # exported for Ninja to pick it up, which is a little tricky to do.
        # Users can override the generator with CMAKE_GENERATOR in CMake
        # 3.15+.
        # if not cmake_generator:
        #     cmake_args += ["-GNinja"]

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(
            ["cmake", ext.sourcedir] + cmake_args, cwd=self.build_temp
        )
        subprocess.check_call(
            ["cmake", "--build", "."], cwd=self.build_temp
        )



with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    ext_modules=[CMakeExtension("advent_processing")],
    cmdclass = {"build_ext": CMakeBuild},
    zip_safe=False,
    name = "advent_of_code",
    author="Miika Mäkelä",
    author_email="makelanmiika@gmail.com",
    description="Advent of code stuff.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    packages=find_packages(where='src'),
    package_dir={'': 'src'},
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    extras_require= {
        'dev': [
            'pytest',
            'pylint',
            'yapf',
            'mypy',
        ]
    },
    entry_points = {
        'console_scripts': [
            'aoc=advent_of_code.processing:main'
        ]
    },
)
