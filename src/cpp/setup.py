from setuptools import setup, Extension
from Cython.Build import cythonize

com_module = [
        Extension(
            name='graph',
            sources=['./Grafo.cpp', './libpyMatriz.cpp'],
            language='c++'
            )
]

setup(
        name='graph',
        ext_modules=cythonize(com_module),
        packages=['graph']
        )
