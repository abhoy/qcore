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
 *  @file   QGate.hpp
 *  @brief  Specification of Quantum Gate
 *  @author Abhoy Kole 
 *  @date   19.12.2022 
 ***********************************************************/

#pragma once

#include "Definition.hpp"
#include "GateType.hpp"

namespace qcore {

// To compare two gates from a circuit
struct QGateCompare {
    bool operator()(const QGate &lhs, const QGate &rhs);
};

/*
Type for Quantum Gate composing
    1. set of control qubits
    2. set of target qubits
    3. type of gate
    4. rotation angle, theta, phi, lambda
*/
class QGate {
   private:
    static std::uint64_t gate_count;
    gateid_t gate_id;
    gate_t gate_type;
    size_t gate_size;
    ControlSet controls{};
    TargetSet targets{};
    RotationMap angles{};
    CbitSet cbits{};
    is_classical flag;
    expression_t expression{};

   public:
    QGate(const QGate &);

    QGate &operator=(const QGate &);

    QGate(const gate_t &gate_type, const size_t &gate_size,
          const TargetSet &targets);

    QGate(const gate_t &gate_type, const size_t &gate_size,
          const CbitSet &cbits, const TargetSet &targets);

    QGate(const gate_t &gate_type, const size_t &gate_size,
          const RotationMap &angles, const TargetSet &targets);

    QGate(const gate_t &gate_type, const size_t &gate_size,
          const CbitSet &cbits, const RotationMap &angles, 
          const TargetSet &targets);

    QGate(const gate_t &gate_type, const size_t &gate_size,
          const ControlSet &controls, const TargetSet &targets);

    QGate(const gate_t &gate_type, const size_t &gate_size,
          const CbitSet &cbits, const ControlSet &controls, 
          const TargetSet &targets);

    QGate(const gate_t &gate_type, const size_t &gate_size,
          const RotationMap &angles, const ControlSet &controls,
          const TargetSet &targets);

    QGate(const gate_t &gate_type, const size_t &gate_size,
          const CbitSet &cbits, const RotationMap &angles, 
          const ControlSet &controls, const TargetSet &targets);

    std::string toOpenQASM();

    std::string toString(const FileFormat &format);

    std::string operator[](const FileFormat &format);

    inline void setIsClassical(const is_classical &flag) { this->flag = flag; }

    inline void setExpression(const expression_t &expression) {
        this->expression = expression;
    }

    inline gate_t getType() { return this->gate_type; }

    inline RotationMap &getAngle() { return this->angles; }

    inline gateid_t getId() const { return this->gate_id; }

    inline QubitSet &getControls() { return this->controls; }

    inline QubitSet &getTargets() { return this->targets; }

    inline CbitSet &getCbits() { return this->cbits; }

    inline is_classical &getIsClassical() { return this->flag; }

    inline expression_t &setExpression() { return this->expression; }

    void updateBits(const ControlSet &controls, const TargetSet &targets);

    void updateBits(const CbitSet &cbits, const ControlSet &controls,
                    const TargetSet &targets);

    void updateBits(const TargetSet &targets);

    void updateBits(const CbitSet &cbits, const TargetSet &targets);
};
}  // namespace qcore
