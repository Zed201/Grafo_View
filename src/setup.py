from setuptools import setup, Extension
from Cython.Build import cythonize

gra_module = [
    Extension(
        name='graph',
        sources=['./src/Grafo.cpp', './src/libpyMatriz.cpp'],
        language='c++'
    ),
    Extension(
        name='lib',
        sources=['./src/lib.py'],
        language='c'
    )
]

setup(
    name='lib',
    ext_modules=cythonize(gra_module),
)
