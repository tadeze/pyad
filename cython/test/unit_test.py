#!/usr/bin/env python

"""
multiply.pyx and c_multiply.c test code

designed to be run-able with py.test
"""
import pytest
import numpy as np
import multiply

def test_basic():
    a = np.arange(12, dtype=np.float64).reshape((3,4))
    b = a * 3
    multiply.multiply(a, 3)
    assert np.array_equal(a, b)

def test_wrong_dims():
    a = np.arange(12, dtype=np.float64).reshape((3,2,2))
    with pytest.raises(ValueError):
        multiply.multiply(a, 3)

def test_wrong_type():
    a = np.arange(12, dtype=np.float32).reshape((3,4))
    b = a * 3
    with pytest.raises(ValueError):
        multiply.multiply(a, 3)

def test_zero_dims():
    """
    this shoudln't crash!
    """
    a = np.ones( (3, 0), dtype=np.float64)
    b = a.copy()
    multiply.multiply(a, 3) # zero size, shouldn't do anything
    assert np.array_equal(a, b)
