/*
======================================================
Author: Abhoy Kole
Created: 10th July, 2014
Last Modified: 19th December, 2022
Purpose: Reversible and Quantum GATE Instance Description
======================================================
*/
#include "qgate.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace qcore {

std::uint64_t QGate::gate_count = 0;

bool QGateCompare::operator()(const QGate &lhs, const QGate &rhs) {
    return lhs.getId() < rhs.getId();
}

QGate::QGate(const gate_t &gate_type, const size_t &gate_size, const TargetSet &targets) {
    if (controls.size() + targets.size() != gate_size) {
        throw QcoreException("[QGate] instantiation error msg: Gate size mismatch");
    }

    this->gate_id = ++gate_count;
    this->gate_type = gate_type;
    this->gate_size = gate_size;
    this->angles = RotationMap{};
    this->controls = QubitSet{};
    this->targets = targets;
    this->cbits = CbitSet{};
}

QGate::QGate(const gate_t &gate_type, const size_t &gate_size, const CbitSet &cbits, const TargetSet &targets) {
    if (controls.size() + targets.size() != gate_size) {
        throw QcoreException("[QGate] instantiation error msg: Gate size mismatch");
    }

    this->gate_id = ++gate_count;
    this->gate_type = gate_type;
    this->gate_size = gate_size;
    this->angles = RotationMap{};
    this->controls = QubitSet{};
    this->targets = targets;
    this->cbits = cbits;
}

QGate::QGate(const gate_t &gate_type, const size_t &gate_size, const RotationMap &angles, const TargetSet &targets) {
    if (controls.size() + targets.size() != gate_size) {
        throw QcoreException("[QGate] instantiation error msg: Gate size mismatch");
    }

    this->gate_id = ++gate_count;
    this->gate_type = gate_type;
    this->gate_size = gate_size;
    this->angles = angles;
    this->controls = QubitSet{};
    this->targets = targets;
    this->cbits = CbitSet{};
}

QGate::QGate(const gate_t &gate_type, const size_t &gate_size, const CbitSet &cbits, const RotationMap &angles, const TargetSet &targets) {
    if (controls.size() + targets.size() != gate_size) {
        throw QcoreException("[QGate] instantiation error msg: Gate size mismatch");
    }

    this->gate_id = ++gate_count;
    this->gate_type = gate_type;
    this->gate_size = gate_size;
    this->angles = angles;
    this->controls = QubitSet{};
    this->targets = targets;
    this->cbits = cbits;
}

QGate::QGate(const gate_t &gate_type, const size_t &gate_size, const ControlSet &controls, const TargetSet &targets) {
    if (controls.size() + targets.size() != gate_size) {
        throw QcoreException("[QGate] instantiation error msg: Gate size mismatch");
    }

    this->gate_id = ++gate_count;
    this->gate_type = gate_type;
    this->gate_size = gate_size;
    this->angles = RotationMap{};
    this->controls = controls;
    this->targets = targets;
    this->cbits = CbitSet{};
}

QGate::QGate(const gate_t &gate_type, const size_t &gate_size, const CbitSet &cbits, const ControlSet &controls, const TargetSet &targets) {
    if (controls.size() + targets.size() != gate_size) {
        throw QcoreException("[QGate] instantiation error msg: Gate size mismatch");
    }

    this->gate_id = ++gate_count;
    this->gate_type = gate_type;
    this->gate_size = gate_size;
    this->angles = RotationMap{};
    this->controls = controls;
    this->targets = targets;
    this->cbits = cbits;
}

QGate::QGate(const gate_t &gate_type, const size_t &gate_size, const RotationMap &angles, const ControlSet &controls, const TargetSet &targets) {
    if (controls.size() + targets.size() != gate_size) {
        throw QcoreException("[QGate] instantiation error msg: Gate size mismatch");
    }

    this->gate_id = ++gate_count;
    this->gate_type = gate_type;
    this->gate_size = gate_size;
    this->angles = angles;
    this->controls = controls;
    this->targets = targets;
    this->cbits = CbitSet{};
}

QGate::QGate(const gate_t &gate_type, const size_t &gate_size, const CbitSet &cbits, const RotationMap &angles, const ControlSet &controls, const TargetSet &targets) {
    if (controls.size() + targets.size() != gate_size) {
        throw QcoreException("[QGate] instantiation error msg: Gate size mismatch");
    }

    this->gate_id = ++gate_count;
    this->gate_type = gate_type;
    this->gate_size = gate_size;
    this->angles = angles;
    this->controls = controls;
    this->targets = targets;
    this->cbits = cbits;
}

// copy gate
QGate::QGate(const QGate &g) {
    this->gate_id = g.gate_id;
    this->gate_type = g.gate_type;
    this->gate_size = g.gate_size;
    this->angles = g.angles;
    this->controls = g.controls;
    this->targets = g.targets;
    this->cbits = g.cbits;
}

QGate &QGate::operator=(const QGate &g) {
    this->gate_id = g.gate_id;
    this->gate_type = g.gate_type;
    this->gate_size = g.gate_size;
    this->angles = g.angles;
    this->controls = g.controls;
    this->targets = g.targets;
    this->cbits = g.cbits;
    return *this;
}

std::string QGate::operator[](const FileFormat &format) {
    return this->toString(format);
}

std::string QGate::toString(const FileFormat &format) {
    if (format == FileFormat::OpenQASM) {
        return toOpenQASM();
    } else {
        throw QcoreException("[toString] format " + qcore::toString(format) + " not recognized");
    }
}

void QGate::updateBits(const ControlSet &controls, const TargetSet &targets) {
    this->controls = controls;
    this->targets = targets;
}

void QGate::updateBits(const CbitSet &cbits, const ControlSet &controls, const TargetSet &targets) {
    this->cbits = cbits;
    this->controls = controls;
    this->targets = targets;
}

void QGate::updateBits(const TargetSet &targets) {
    this->targets = targets;
}

void QGate::updateBits(const CbitSet &cbits, const TargetSet &targets) {
    this->cbits = cbits;
    this->targets = targets;
}

}  // namespace qcore
