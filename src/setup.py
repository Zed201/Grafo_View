# usar o cython para compilar tudo numa umnico .so para ficar organizado
# colocar numa pasta build
from setuptools import setup, Extension
from Cython.Build import cythonize

ex_ = [
        Extension(
            name='lib',
            sources=['./py/lib.py'],
            extra_compile_args=['-I/cpp'],
           language='c++'
        )
]

setup(
    name='lib',
    ext_modules=cythonize(ex_),
    packages=['lib']
)
