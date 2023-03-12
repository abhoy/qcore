/*
======================================================
Author: Abhoy Kole
Created: 18th February, 2023
Last Modified: 18th February, 2023
Purpose: Reversible and Quantum GATE Instance Description
======================================================
*/
#pragma once

#include <bitset>
#include <cmath>
#include <cstdint>
#include <map>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

namespace qcore {

// Type for quantum bit
using Qubit = std::uint64_t;
using line_t = Qubit;  // for backward compitable

// register size
using regsize_t = std::uint64_t;

// Type for classical bit
using Cbit = std::uint32_t;

// Type for unique gate identifier
using gateid_t = std::uint64_t;

// Type for storing angle of rotation
using angle_t = std::string;

// Type for holding gate count
using gcount_t = std::uint64_t;

// Quantum bit Collection
using QubitSet = std::vector<Qubit>;
using ControlSet = QubitSet;
using TargetSet = QubitSet;

// Classical bit collection
using CbitSet = std::vector<Cbit>;

// forward declaration of quantum Gate
class QGate;
using QGatePtr = std::unique_ptr<QGate>;
using QGateSet = std::vector<std::unique_ptr<QGate>>;

// Quantum to Classical Mapping for Result
using MeasuredQubitMap = std::map<Qubit, Cbit>;

// qubit names
using QubitLabelMap = std::map<Qubit, std::string>;
using QubitIdMap = std::map<std::string, Qubit>;
using QIdMapElement = std::pair<std::string, Qubit>;

// cbit names
using CbitLabelMap = std::map<Cbit, std::string>;
using CbitIdMap = std::map<std::string, Cbit>;
using CIdMapElement = std::pair<std::string, Cbit>;

// per qubit gate depth
using depth_t = std::uint64_t;
using QubitDepthMap = std::map<line_t, depth_t>;

// Layout mapping
using PermutationMap = std::map<Qubit, Qubit>;

using QubitIterator = std::vector<Qubit>::iterator;
using CbitIterator = std::vector<Cbit>::iterator;
using ConstantQubitIterator = std::vector<Qubit>::const_iterator;
using ConstantCbitIterator = std::vector<Cbit>::const_iterator;
using QubitReverseIterator = std::vector<Qubit>::reverse_iterator;
using CbitReverseIterator = std::vector<Cbit>::reverse_iterator;
using QGateIterator = QGateSet::iterator;
using ConstantQGateIterator = QGateSet::const_iterator;
using QGateReverseIterator = QGateSet::reverse_iterator;
using MeasuredQubitIterator = MeasuredQubitMap::iterator;
using ConstantMeasuredQubitIterator = MeasuredQubitMap::const_iterator;
using QubitLabelIterator = QubitLabelMap::iterator;
using ConstantQubitLabelIterator = QubitLabelMap::const_iterator;
using QubitIdIterator = QubitIdMap::iterator;
using ConstantQubitIdIterator = QubitIdMap::const_iterator;
using CbitLabelIterator = CbitLabelMap::iterator;
using ConstantCbitLabelIterator = CbitLabelMap::const_iterator;
using CbitIdIterator = CbitIdMap::iterator;
using ConstantCbitIdIterator = CbitIdMap::const_iterator;
using QubitDepthIterator = QubitDepthMap::iterator;
using ConstantQubitDepthIterator = QubitDepthMap::const_iterator;
using PermutationIterator = PermutationMap::iterator;
using ConstantPermutationIterator = PermutationMap::const_iterator;

// floating-point type used throughout the library
using fp = double;

// PI	3.142857143
static constexpr fp PI = static_cast<fp>(3.141592653589793238462643383279502884197169399375105820974L);

class QcoreException : public std::invalid_argument {
    std::string msg;

   public:
    explicit QcoreException(std::string m) : std::invalid_argument("QCORE Exception"), msg(std::move(m)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return msg.c_str();
    }
};

// supported file formats
enum class FileFormat {
    Real,
    OpenQASM,
    FormatCount
};

using format_t = FileFormat;

using version_t = double;

inline std::string toString(const FileFormat &format) {
    switch (format) {
        case FileFormat::OpenQASM:
            return "OPENQASM";
        case FileFormat::Real:
            return "REAL";
        default:
            throw std::invalid_argument("Invalid RotationType!");
    }
}

inline std::string ltrim(const std::string &s) {
    return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

inline std::string rtrim(const std::string &s) {
    return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

inline double round_sig(double num, int sig) {
    return static_cast<double>(static_cast<int>(num * pow(10, sig))) / pow(10, sig);
}

}  // namespace qcore