/*
======================================================
Author: Abhoy Kole
Created: 10th July, 2014
Last Modified: 2nd February, 2022
Purpose: Reversible and Quantum Circuit Instance Description
======================================================
*/

#include "qcircuit.hpp"

namespace qcore {

depth_t QCircuit::getDepth() {
    depth_t max_depth = 0;
    for (auto d : this->depth) {
        if (d.second > max_depth) {
            max_depth = d.second;
        }
    }
    return max_depth;
}

std::string QCircuit::toString(const FileFormat& format) {
    if (format == FileFormat::OpenQASM) {
        auto os = std::ostringstream();
        this->writeQASM(os);
        return os.str();
    } else {
        throw QcoreException("[toString] format " + qcore::toString(format) + " not recognized");
    }
}

std::string QCircuit::operator[](const FileFormat& format) {
    return this->toString(format);
}

Qubit QCircuit::addQubit(Qubit& qubit) {
    this->qubits.push_back(qubit);
    return qubit;
}

Cbit QCircuit::addCbit(Cbit& cbit) {
    this->cbits.push_back(cbit);
    return cbit;
}

FileFormat QCircuit::writeQCircuit(const std::string& filename) {
    const std::size_t dot = filename.find_last_of('.');

    std::string extension = filename.substr(dot + 1);

    std::transform(extension.cbegin(), extension.cend(), extension.begin(), [](unsigned char ch) { return ::tolower(ch); });

    if (extension == "qasm") {
        auto ofs = std::ofstream(filename);
        
        if (!ofs.good()) {
            throw QcoreException("[writeQCircuit] unable to open file " + filename);
        }
        
        writeQASM(ofs);

        ofs.close();

        return FileFormat::OpenQASM;
    }

    /*
    else if (extension == "real") {
        readReal(filename, FileFormat::Real);
    }*/

    else {
        throw QcoreException("[readQCircuit] extension " + extension + " not recognized");
    }

}

FileFormat QCircuit::readQCircuit(const std::string& filename) {
    const std::size_t dot = filename.find_last_of('.');

    std::string extension = filename.substr(dot + 1);

    std::transform(extension.cbegin(), extension.cend(), extension.begin(), [](unsigned char ch) { return ::tolower(ch); });

    if (extension == "qasm") {
        auto ifs = std::ifstream(filename);

        if (!ifs.good()) {
            throw QcoreException("[readQCircuit] unable to open file " + filename);
        }

        readQASM(ifs);
        
        ifs.close();

        return FileFormat::OpenQASM;
    }

    /*
    else if (extension == "real") {
        readReal(filename, FileFormat::Real);
    }*/

    else {
        throw QcoreException("[readQCircuit] extension " + extension + " not recognized");
    }
}

QCircuit::~QCircuit() {}

QCircuit& QCircuit::operator=(const QCircuit& ckt) {
    clone(ckt);
    return *this;
}

QCircuit::QCircuit(const QCircuit& ckt) {
    clone(ckt);
}

QCircuit::QCircuit() {
    init();
}

void QCircuit::clone(const QCircuit& ckt) {
    init();

    this->qreg = ckt.qreg;
    this->qreg = ckt.creg;
    this->max_gate_size = ckt.max_gate_size;
    this->qubits = ckt.qubits;
    this->cbits = ckt.cbits;
    this->depth = ckt.depth;
    this->properties = ckt.properties;

    for (ConstantQGateIterator g = ckt.gates.begin(); g != ckt.gates.end(); ++g) {
        this->gates.push_back(QGatePtr(new QGate(**g)));
    }
}

void QCircuit::init() {
    this->qreg = 0;
    this->qreg = 0;
    this->max_gate_size = 0;
    this->qubits = QubitSet{};
    this->cbits = CbitSet{};
    this->gates = QGateSet{};
    this->depth = QubitDepthMap{};
    this->properties = PropertiesMap{};
}

/* Interchange the position of i-th qubit with j-th qubit*/
void exchangeQubits(QubitSet& qubits, int i, int j) {
    Qubit qubit = qubits[i];
    qubits[i] = qubits[j];
    qubits[j] = qubit;
}
}  // namespace qcore
