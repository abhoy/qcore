/*
 * This file is part of the core quantum library package.
 *
 * Developed for the Deutsches Forschungszentrum für Künstliche 
 * Intelligenz GmbH (DFKI), Cyber-Physical Systems Dept.
 *
 * This program is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation, either version 
 * 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public 
 * License along with this program. If not, see 
 * <https://www.gnu.org/licenses/>.
 */

/** 
 *  @file   QCircuit.hpp
 *  @brief  Specification of Quantum Circuit
 *  @author Abhoy Kole 
 *  @date   02.02.2022 
 ***********************************************************/

#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include "QGate.hpp"

namespace qcore {

void exchangeQubits(QubitSet& qubits, int i, int j);

class QCircuit {
   private:
    regsize_t qreg;
    regsize_t creg;
    QubitSet qubits;
    CbitSet cbits;
    size_t max_gate_size;
    QGateSet gates;

    QubitDepthMap depth;
    PropertiesMap properties;

   public:
    QCircuit();

    QCircuit(const QCircuit& ckt);

    QCircuit& operator=(const QCircuit& ckt);

    ~QCircuit();

    void init();

    void clone(const QCircuit& ckt);

    FileFormat readQCircuit(const std::string& filename);

    FileFormat writeQCircuit(const std::string& filename);

    void readQASM(std::istream& is);

    void writeQASM(std::ostream& os);

    std::string toString(const FileFormat& format);

    std::string operator[](const FileFormat& format);
    
    Qubit addQubit(Qubit& qubit);

    Cbit addCbit(Cbit& cbit);

    inline QGateSet& getGates() {
        return this->gates;
    }
    
    inline QubitSet& getQubits() {
        return this->qubits;
    }

    inline CbitSet& getCbits() {
        return this->cbits;
    }

    inline regsize_t& getQregSize() {
        return this->qreg;
    }

    inline regsize_t& getCregSize() {
        return this->creg;
    }

    inline size_t& getMaxGateSize() {
        return this->max_gate_size;
    }
    
    depth_t getDepth(); 
    
    inline PropertiesMap& getProperties() {
        return this->properties;
    }

    /*
    void readReal(std::istream& is);
    void addQGate(QGate&);

    void writeQCircuit(const std::string& filename, FileFormat format);
    void writeQASM(std::string, unsigned);
    void writeReal(std::string file);

    void displayQASM(std::ostream& os, unsigned size);
    void displayQisKit(std::ostream& os, unsigned size);
    
    MeasuredQubitMap getMeasures();
    void setGates(QGateSet& gates);
    void setQubits(QubitSet& qubits);
    void setMeasures(MeasuredQubitMap& measures);
    unsigned twoQubitGateCount();
    unsigned getCNOTDepth();
    unsigned maxCNOTDepth();
    void reduceCNOTDepth(QGate& g);
    unsigned twoQubitGateCount(unsigned pos);

    void addQGate(QGate&);
    void addQGate(QGate);
    void clear();*/
    friend void exchangeQubits(QubitSet& qubits, int i, int j);
};

}  // namespace qcore
