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
 *  @file   Clifford_T.cpp
 *  @brief  Instance Description for Quantum Gate Decomposition using Clifford+T Gates
 *  @author Abhoy Kole
 *  @date   04.05.2025
 ***********************************************************/

#include "decompose/Clifford_T.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace qcore {

QCircuit &decompose_CCX_Clifford_T(Qubit &c1, Qubit &c2, Qubit &t, bool inverse) {
    auto qc = QCircuit{};
    qc.setQubits({c1, c2, t});
    if (inverse == false) {
        qc.addQGate(QGate(GateType::H, 1, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {c1}));
        qc.addQGate(QGate(GateType::TDG, 1, {c2}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){t}, {c1}));
        qc.addQGate(QGate(GateType::T, 1, {c1}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
        qc.addQGate(QGate(GateType::T, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {c1}));
        qc.addQGate(QGate(GateType::TDG, 1, {c1}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){t}, {c1}));
        qc.addQGate(QGate(GateType::T, 1, {c1}));
        qc.addQGate(QGate(GateType::TDG, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {c1}));
        qc.addQGate(QGate(GateType::H, 1, {t}));
    } else {
        qc.addQGate(QGate(GateType::H, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {c1}));
        qc.addQGate(QGate(GateType::T, 1, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {c1}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){t}, {c1}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
        qc.addQGate(QGate(GateType::T, 1, {c1}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {c1}));
        qc.addQGate(QGate(GateType::TDG, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {c1}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){t}, {c1}));
        qc.addQGate(QGate(GateType::T, 1, {c2}));
        qc.addQGate(QGate(GateType::T, 1, {c1}));
        qc.addQGate(QGate(GateType::H, 1, {t}));
    }

    return qc;
}

QCircuit &decompose_RCCX_Clifford_T(Qubit &c1, Qubit &c2, Qubit &t) {
    auto qc = QCircuit{};
    qc.setQubits({c1, c2, t});

    qc.addQGate(QGate(GateType::H, 1, {t}));
    qc.addQGate(QGate(GateType::T, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
    qc.addQGate(QGate(GateType::TDG, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
    qc.addQGate(QGate(GateType::T, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
    qc.addQGate(QGate(GateType::TDG, 1, {t}));
    qc.addQGate(QGate(GateType::H, 1, {t}));

    return qc;
}

QCircuit &decompose_SRCCX_Clifford_T(Qubit &c1, Qubit &c2, Qubit &t, bool inverse) {
    auto qc = QCircuit{};
    qc.setQubits({c1, c2, t});
    if (inverse == false) {
        qc.addQGate(QGate(GateType::H, 1, {t}));
        qc.addQGate(QGate(GateType::T, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
    } else {
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
        qc.addQGate(QGate(GateType::T, 1, {t}));
        qc.addQGate(QGate(GateType::H, 1, {t}));
    }

    return qc;
}

QCircuit &decompose_SSRCCX_Clifford_T(Qubit &c1, Qubit &c2, Qubit &t, bool inverse) {
    auto qc = QCircuit{};
    qc.setQubits({c1, c2, t});
    if (inverse == false) {
        qc.addQGate(QGate(GateType::H, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){t}, {c2}));
        qc.addQGate(QGate(GateType::TDG, 1, {c2}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {c2}));
        qc.addQGate(QGate(GateType::T, 1, {c2}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){t}, {c2}));
        qc.addQGate(QGate(GateType::TDG, 1, {c2}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {c2}));
        qc.addQGate(QGate(GateType::T, 1, {c2}));
    } else {
        qc.addQGate(QGate(GateType::T, 1, {c2}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {c2}));
        qc.addQGate(QGate(GateType::TDG, 1, {c2}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){t}, {c2}));
        qc.addQGate(QGate(GateType::T, 1, {c2}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {c2}));
        qc.addQGate(QGate(GateType::TDG, 1, {c2}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){t}, {c2}));
        qc.addQGate(QGate(GateType::H, 1, {t}));
    }

    return qc;
}

QCircuit &decompose_RC3X_Clifford_T(Qubit &c1, Qubit &c2, Qubit &c3, Qubit &t) {
    auto qc = QCircuit{};
    qc.setQubits({c1, c2, c3, t});

    qc.addQGate(QGate(GateType::H, 1, {t}));
    qc.addQGate(QGate(GateType::T, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c3}, {t}));
    qc.addQGate(QGate(GateType::TDG, 1, {t}));
    qc.addQGate(QGate(GateType::H, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
    qc.addQGate(QGate(GateType::T, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
    qc.addQGate(QGate(GateType::TDG, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
    qc.addQGate(QGate(GateType::T, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
    qc.addQGate(QGate(GateType::TDG, 1, {t}));
    qc.addQGate(QGate(GateType::H, 1, {t}));
    qc.addQGate(QGate(GateType::T, 1, {t}));
    qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c3}, {t}));
    qc.addQGate(QGate(GateType::TDG, 1, {t}));
    qc.addQGate(QGate(GateType::H, 1, {t}));

    return qc;
}

QCircuit &decompose_SRC3X_Clifford_T(Qubit &c1, Qubit &c2, Qubit &c3, Qubit &t, bool inverse) {
    auto qc = QCircuit{};
    qc.setQubits({c1, c2, c3, t});

    if (inverse == false) {
        qc.addQGate(QGate(GateType::H, 1, {t}));
        qc.addQGate(QGate(GateType::T, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c3}, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {t}));
        qc.addQGate(QGate(GateType::H, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
        qc.addQGate(QGate(GateType::T, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
    } else {
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
        qc.addQGate(QGate(GateType::T, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c2}, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c1}, {t}));
        qc.addQGate(QGate(GateType::H, 1, {t}));
        qc.addQGate(QGate(GateType::T, 1, {t}));
        qc.addQGate(QGate(GateType::CX, 2, (ControlSet){c3}, {t}));
        qc.addQGate(QGate(GateType::TDG, 1, {t}));
        qc.addQGate(QGate(GateType::H, 1, {t}));
    }

    return qc;
}

QCircuit &decompose_MCT_Clifford_T(QubitSet &controls, Qubit target, QubitSet &dirty, QubitSet &clean, bool inverse) {
    auto qc = QCircuit{};

    if (controls.size() == 2) {
        qc = decompose_CCX_Clifford_T(controls[0], controls[1], target);
    } else {
        qcore::regsize_t ancilla_need = ((controls.size() - 2) / 2) + ((controls.size() - 2) % 2);
        if (clean.size() + dirty.size() < ancilla_need) {
            throw QcoreException("[decompose_MCT_Clifford_T] decomposition error msg: ancilla required (" + std::to_string(ancilla_need) + ") is higher than available (" + std::to_string(clean.size() + dirty.size()) + ").");
        }

        qc.setQubits(mergeQubits({controls, {target}, dirty, clean}));
        
        //decompose using clean ancilla 
        auto controls_covered = 0;
        auto p_caq = clean[0];
        for (auto & caq: clean){
            if (controls.size() == 3 && controls_covered == 0){
                qc.addQCircuit(decompose_RCCX_Clifford_T(controls[0], controls[1], caq));
                controls_covered += 2; 
            }
            else if (controls.size() > 3 && controls_covered == 0){
                qc.addQCircuit(decompose_RC3X_Clifford_T(controls[0], controls[1], controls[2], caq));
                controls_covered += 3;
            }
            else if ((controls.size() - controls_covered) == 2) {
                qc.addQCircuit(decompose_RCCX_Clifford_T(p_caq, controls[controls_covered], caq));
                controls_covered += 1;
            }
            else if ((controls.size() - controls_covered) > 2) {
                qc.addQCircuit(decompose_RC3X_Clifford_T(p_caq, controls[controls_covered], controls[controls_covered + 1], caq));
                controls_covered += 2;
            }
            
            p_caq = caq;
            
            if ((controls.size() - controls_covered) == 1){
                break;
            }
        }
        auto qc_temp = qc; 
        //decompose using dirty ancilla
        if ((controls.size() - controls_covered) > 1){
            for (auto &daq: dirty){

            }
        }
        else{
            qc.addQCircuit(decompose_CCX_Clifford_T(p_caq, controls[controls_covered], target));
        }
        qc.addQCircuit(qc_temp.inverse());
    }
}

}  // namespace qcore