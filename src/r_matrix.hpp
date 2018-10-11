//
// Created by tadeze on 10/10/18.
//

#ifndef OSU_IFOREST_R_MATRIX_HPP
#define OSU_IFOREST_R_MATRIX_HPP

#include "Eigen/Dense"
#include "Eigen/Core"
#include <set>
#include <iostream>
#include <fstream>
#include<vector>
#include <random>
#include <memory>

#define PRINT(X) std::cout << #X << ":\n" << X << std::endl << std::endl

using DoubleMatrix = Eigen::MatrixXd;
using DoubleRow = Eigen::VectorXd;

/**
 * @brief  Gives a new shape to an array without changing its data.
 *         This function is based on numpy.reshape
 *         see: https://docs.scipy.org/doc/numpy/reference/generated/numpy.reshape.html
 *
 * @param x input matrix
 * @param r the number of row elements
 * @param c the number of collum elements
 *
 * @return The new shape matrix
 */
inline DoubleMatrix reshape(
        DoubleMatrix &x,
        uint32_t r,
        uint32_t c
) {

    Eigen::Map<DoubleMatrix> rx(x.data(), r, c);

    return rx;
}


/**
 * @brief Detemine if matrix is diagonal
 *        if matrix is not square, return false
 *
 *        It is inspired by MATLAB isdiag function.
 *        see: https://www.mathworks.com/help/matlab/ref/isdiag.html
 *
 * @param x input matrix
 *
 * @return matrix is diagonal (true) or not (false)
 */
inline bool isdiag(const DoubleMatrix &x) {

    if (x.cols() != x.rows()) {
        return false;//not square matrix
    }

    DoubleMatrix t = x.diagonal().asDiagonal();
    // PRINT(t);

    // std::cout<<std::abs((t-x).sum())<<std::endl;
    if (std::abs((t - x).sum()) >= 0.00001) {
        return false;
    }

    return true;

}


/**
 * @brief Stack matrix in sequence vertically
 *        imspired by numpy.vstack
 *        https://docs.scipy.org/doc/numpy/reference/generated/numpy.vstack.html
 *
 * @param m1 first matrix
 * @param m2 second matrix
 *
 * @return stacked matrix
 */
inline DoubleMatrix rbind(
        const DoubleMatrix &m1,
        const DoubleMatrix &m2
) {

    if (m1.rows() == 0) {
        return m2;
    } else if (m2.rows() == 0) {
        return m1;
    }

    uint32_t ncol = m1.cols();
    if (ncol == 0) {
        ncol = m2.cols();
    }

    DoubleMatrix rm(m1.rows() + m2.rows(), ncol);
    rm << m1, m2;

    return rm;
}


/**
 * @brief Stack matrix in sequence horizontally
 *        imspired by numpy.hstack
 *        https://docs.scipy.org/doc/numpy/reference/generated/numpy.hstack.html
 *
 * @param m1 first matrix
 * @param m2 second matrix
 *
 * @return stacked matrix
 */
inline DoubleMatrix cbind(
        const DoubleMatrix &m1,
        const DoubleMatrix &m2
) {

    if (m1.cols() == 0) {
        return m2;
    } else if (m2.cols() == 0) {
        return m1;
    }

    uint32_t nrow = m1.rows();
    if (nrow == 0) {
        nrow = m2.rows();
    }

    DoubleMatrix rm(nrow, m1.cols() + m2.cols());
    rm << m1, m2;

    return rm;
}


/**
 * @brief Create a block diagonal matrix from provided matrices
 *        3 input version
 *        inspired scipy.linalg.block_diag
 *        https://docs.scipy.org/doc/scipy-0.14.0/reference/generated/scipy.linalg.block_diag.html
 *
 * @param m1 first matrix
 * @param m2 second matrix
 *
 * @return Created a block diagonal matrix
 */
inline DoubleMatrix block_diag(
        const DoubleMatrix &m1,
        const DoubleMatrix &m2) {

    uint32_t m1r = m1.rows();
    uint32_t m1c = m1.cols();
    uint32_t m2r = m2.rows();
    uint32_t m2c = m2.cols();

    DoubleMatrix mf = DoubleMatrix::Zero(m1r + m2r, m1c + m2c);
    mf.block(0, 0, m1r, m1c) = m1;
    mf.block(m1r, m1c, m2r, m2c) = m2;

    return mf;
}

/**
 * @brief Create a block diagonal matrix from provided matrices
 *        3 input version
 *
 * @param m1 first matrix
 * @param m2 second matrix
 * @param m3 third matrix
 *
 * @return Created a block diagonal matrix
 */
inline DoubleMatrix block_diag(
        const DoubleMatrix &m1,
        const DoubleMatrix &m2,
        const DoubleMatrix &m3) {

    uint32_t m1r = m1.rows();
    uint32_t m1c = m1.cols();
    uint32_t m2r = m2.rows();
    uint32_t m2c = m2.cols();
    uint32_t m3r = m3.rows();
    uint32_t m3c = m3.cols();

    DoubleMatrix bdm = DoubleMatrix::Zero(m1r + m2r + m3r, m1c + m2c + m3c);
    bdm.block(0, 0, m1r, m1c) = m1;
    bdm.block(m1r, m1c, m2r, m2c) = m2;
    bdm.block(m1r + m2r, m1c + m2c, m3r, m3c) = m3;

    return bdm;
}


/**
 * @brief Compute the Kronecker product
 *        A composite array made of blocks of the second array scaled by the first
 *        Inspired numpy.kron
 *        see: https://docs.scipy.org/doc/numpy/reference/generated/numpy.kron.html
 *
 * @param m1 first matrix
 * @param m2 second matrix
 *
 * @return A result of the Kronecker product
 */
inline DoubleMatrix kron(
        const DoubleMatrix &m1,
        const DoubleMatrix &m2) {

    uint32_t m1r = m1.rows();
    uint32_t m1c = m1.cols();
    uint32_t m2r = m2.rows();
    uint32_t m2c = m2.cols();


    DoubleMatrix m3(m1r * m2r, m1c * m2c);
    // PRINT(m3);


    for (int i = 0; i < m1r; i++) {
        for (int j = 0; j < m1c; j++) {
            m3.block(i * m2r, j * m2c, m2r, m2c) = m1(i, j) * m2;
        }
    }

    return m3;
}

/**
 *  Read  matrix data from disk into Eign Matrix
 * @tparam M Eigen matrix type
 * @param path : string  path to the file location
 * @param header : bool if true header is expected
 * @param delimiter : char delimiter for the file. default csv ','
 * @param skiprows : int rows to skip
 * @param usecols : list of columns to use. Default use all columns.
 * @return M type matrix.
 */
template<typename M>
M load_csv(const std::string &path, bool header = true, char delimiter = ',', int skiprows = 0,
           std::set<int> &usecols = nullptr) {
    std::ifstream indata;
    indata.open(path);
    std::string line;
    std::vector<double> values;
    uint rows = 0;

    if (header)
        std::getline(indata, line);
    for (int i = 0; i < skiprows; i++)
        std::getline(indata, line);
    auto isinusecols = [&usecols](int cols) {
        if (usecols.empty()) return true;
        return std::find(usecols.begin(), usecols.end(), cols) != usecols.end();
    };

    while (std::getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        uint cols = 0;

        while (std::getline(lineStream, cell, delimiter)) {
            if (isinusecols(cols))
                values.push_back(std::stod(cell));
            ++cols;
        }
        ++rows;
    }

    return Eigen::Map<const Eigen::Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, Eigen::RowMajor>>(
            values.data(), rows, values.size() / rows);
}

inline Eigen::MatrixXd loadtxt(const std::string &file_name, bool header = true, char delimiter = ',',
                               int skiprow = 0) {
    std::set<int> usecols;
    return load_csv<DoubleMatrix>(file_name, header, delimiter, skiprow, usecols);
}

/**
 *  Save matrix data to disk
 * @param matrix MatrixXd type
 * @param file_name path to save to disk
 * @param headers  if provided save with given header file.
 * @param delimiter delimiter default ','
 */
inline void savetxt(DoubleMatrix &matrix, const std::string &file_name, std::set<std::string> headers,
                    std::string delimiter = ",") {
    std::ofstream file(file_name.c_str());
    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, delimiter, "\n");

    if (file.is_open()) {
        if (!headers.empty()) {
            for (auto col : headers)
                file << col << delimiter;
            file << "\n";
        }
        file << matrix.format(CSVFormat);
    }


}


// Slicing matrix data.
inline DoubleMatrix random_rotation(int n) {
    std::default_random_engine eng;
    std::normal_distribution<double> distribution(0.0, 1.0);
    DoubleMatrix A(n, n);

    const Eigen::VectorXd ones(Eigen::VectorXd::Ones(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A(i, j) = distribution(eng);


    const Eigen::HouseholderQR<DoubleMatrix> qr(A);
    const DoubleMatrix Q = qr.householderQ();
    DoubleMatrix M = Q * (qr.matrixQR().diagonal().array() < 0).select(-ones, ones).asDiagonal();
    if (M.determinant() < 0)
        for (int i = 0; i < n; i++)
            M(i, 0) = -M(i, 0);
    return M;

}

inline double min(const DoubleMatrix &doublematrix) {
    return doublematrix.minCoeff();
}

inline double max(const DoubleMatrix &doublematrix) {
    return doublematrix.maxCoeff();
}


struct DoubleFrame {
private:
    long nrow, ncol;
    std::set<std::string> cols;
public:
    DoubleMatrix data;

    //DoubleMatrix data;
    virtual ~DoubleFrame() {};

    DoubleFrame(DoubleMatrix &matrix, std::set<std::string> &cols) {
        data = matrix;
        cols = cols;
    }

    DoubleFrame(DoubleMatrix &matrix) {
        data = matrix;
    }

    DoubleFrame() {};

    //DoubleMatrix data(){ return data}
    inline void set_data(DoubleMatrix &data) {
        nrow = data.rows();
        ncol = data.cols();
    }

    long nrows() { return nrow; }

    long ncols() { return ncol; }
//
//   DoubleRow & operator[] (int i) {
//        DoubleRow row = data->row(i);
//        return row;
//    }

//    double & operator()(const unsigned& row, const unsigned& col){
//        return data(row, col);
//    }




};

inline DoubleMatrix vect_to_matrix(std::vector<std::vector<double> > vect_matrix) {
    DoubleMatrix mat(vect_matrix.size(), vect_matrix[0].size());
    for (int i = 0; i < (int) vect_matrix.size(); i++)
        mat.row(i) = Eigen::VectorXd::Map(&vect_matrix[i][0], (int) vect_matrix[i].size());
    return mat;
};

#endif //OSU_IFOREST_RSTYLE_EIGEN_HPP
