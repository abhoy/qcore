/*
======================================================
Author: Abhoy Kole
Created: 18th February, 2023
Last Modified: 18th February, 2023
Purpose: Reversible and Quantum GATE Instance Description
======================================================
*/
#pragma once

#include <iostream>

#include "definition.hpp"

namespace qcore {

/*
Reversible and Quantum Gate Types:
Classical Gates:
    Pauli X, Controlled Pauli X (CX), Toffoli (CCX), Multiple Controlled Toffoli (MCX), SWAP
Phase Gates:
    Pauli Z, sqrt of Z (S), inverse of S (SDG), sqrt of S (T), inverse of T (TDG), Phase (P),
    Rotation around Z axix (RZ)
Non-unitory Gates:
    active reset(RESET), measurement (MESURE), classical controlled operation (IF), BARRIER
Hadamard Gate:
    H
Quantum Gates:
    Y, Rotation around X and Y axix (RX and RY), sqrt of X (SX), inverse of SX (SXDG),
    Rotation around XX axix (RXX), Rotation around ZZ axis (RZZ), Margolus gate (RCCX),
    Relative phase 3 controlled Toffoli gate (RC3X)
Special unitaries from IBM:
    U1, U2, U3 and U
*/

enum GateType : std::uint8_t {  // Gate Type
    NONE,
    // Standard operations
    I,
    X,
    CX,
    CCX,
    MCX,
    RX,
    CRX,
    RXX,
    RCCX,
    RC3X,
    V,
    CV,
    VDG,
    CVDG,
    SX,
    CSX,
    SXDG,
    CSXDG,
    Y,
    CY,
    RY,
    CRY,
    Z,
    CZ,
    S,
    CS,
    SDG,
    CSDG,
    T,
    CT,
    TDG,
    CTDG,
    P,
    CP,
    RZ,
    CRZ,
    RZZ,
    H,
    CH,
    U1,
    CU1,
    U2,
    CU2,
    U3,
    CU3,
    U,
    CU,
    PERES,
    PERESDG,
    SWAP,
    CSWAP,
    ISWAP,
    // Non-unitary operations
    RESET,
    MEASURE,
    IF,
    BARRIER,
    // Supported Gate Types
    TYPECOUNT
};

// Flag for classical control gate
using is_classical = bool;
using expression_t = std::string;

// Type for holding gate type
using gate_t = GateType;

// number of gates of each type
using PropertiesMap = std::map<gate_t, gcount_t>;
using PropertyIterator = PropertiesMap::iterator;
using ConstantPropertyIterator = PropertiesMap::const_iterator;

enum RotationType : std::uint8_t {  // Type of explicit rotations
    ROTATENONE,
    THETA,
    PHI,
    LAMBDA,
    GAMMA,
    ROTATIONCOUNT
};

// alias for rotation type
using rotation_t = RotationType;

// Collection for angle of rotation
using RotationMap = std::map<RotationType, angle_t>;

using RotationIterator = RotationMap::iterator;
using ConstantRotationIterator = RotationMap::const_iterator;

inline std::string toString(const rotation_t& rotationType) {
    switch (rotationType) {
        case RotationType::ROTATENONE:
            return "none";
        case RotationType::THETA:
            return "theta";
        case RotationType::PHI:
            return "phi";
        case RotationType::LAMBDA:
            return "lambda";
        case RotationType::GAMMA:
            return "gamma";
        default:
            throw std::invalid_argument("Invalid RotationType!");
    }
}

inline std::string toString(const gate_t& gateType) {
    switch (gateType) {
        case GateType::NONE:
            return "none";
        case GateType::I:
            return "id";
        case GateType::X:
            return "x";
        case GateType::CX:
            return "cx";
        case GateType::CCX:
            return "ccx";
        case GateType::MCX:
            return "mcx";
        case GateType::RX:
            return "rx";
        case GateType::CRX:
            return "crx";
        case GateType::RXX:
            return "rxx";
        case GateType::RCCX:
            return "rccx";
        case GateType::RC3X:
            return "rc3x";
        case GateType::V:
            return "v";
        case GateType::CV:
            return "cv";
        case GateType::VDG:
            return "vdg";
        case GateType::CVDG:
            return "cvdg";
        case GateType::SX:
            return "sx";
        case GateType::CSX:
            return "csx";
        case GateType::SXDG:
            return "sxdg";
        case GateType::CSXDG:
            return "csxdg";
        case GateType::Y:
            return "y";
        case GateType::CY:
            return "cy";
        case GateType::RY:
            return "ry";
        case GateType::CRY:
            return "cry";
        case GateType::Z:
            return "z";
        case GateType::CZ:
            return "cz";
        case GateType::S:
            return "s";
        case GateType::CS:
            return "cs";
        case GateType::SDG:
            return "sdg";
        case GateType::CSDG:
            return "csdg";
        case GateType::T:
            return "t";
        case GateType::CT:
            return "ct";
        case GateType::TDG:
            return "tdg";
        case GateType::CTDG:
            return "ctdg";
        case GateType::P:
            return "p";
        case GateType::CP:
            return "cp";
        case GateType::RZ:
            return "rz";
        case GateType::CRZ:
            return "crz";
        case GateType::RZZ:
            return "rzz";
        case GateType::H:
            return "h";
        case GateType::CH:
            return "ch";
        case GateType::U1:
            return "u1";
        case GateType::CU1:
            return "cu1";
        case GateType::U2:
            return "u2";
        case GateType::CU2:
            return "cu2";
        case GateType::U3:
            return "u3";
        case GateType::CU3:
            return "cu3";
        case GateType::U:
            return "u";
        case GateType::CU:
            return "cu";
        case GateType::PERES:
            return "peres";
        case GateType::PERESDG:
            return "peresdg";
        case GateType::SWAP:
            return "swap";
        case GateType::CSWAP:
            return "cswap";
        case GateType::ISWAP:
            return "iswap";
        case GateType::RESET:
            return "reset";
        case GateType::MEASURE:
            return "measure";
        case GateType::IF:
            return "if";
        case GateType::BARRIER:
            return "barrier";
        default:
            throw std::invalid_argument("Invalid OpType!");
    }
}

inline gate_t gateTypeFromString(const std::string& gateType) {
    if (gateType == "none" || gateType == "0") {
        return GateType::NONE;
    }
    if (gateType == "i" || gateType == "id" || gateType == "1") {
        return GateType::I;
    }
    if (gateType == "x" || gateType == "2") {
        return GateType::X;
    }
    if (gateType == "cx" || gateType == "cnot" || gateType == "3") {
        return GateType::CX;
    }
    if (gateType == "ccx" || gateType == "c2x" || gateType == "4") {
        return GateType::CCX;
    }
    if (gateType == "mcx" || gateType == "5") {
        return GateType::MCX;
    }
    if (gateType == "rx" || gateType == "6") {
        return GateType::RX;
    }
    if (gateType == "crx" || gateType == "7") {
        return GateType::CRX;
    }
    if (gateType == "rxx" || gateType == "8") {
        return GateType::RXX;
    }
    if (gateType == "rccx" || gateType == "9") {
        return GateType::RCCX;
    }
    if (gateType == "rc3x" || gateType == "10") {
        return GateType::RC3X;
    }
    if (gateType == "v" || gateType == "11") {
        return GateType::V;
    }
    if (gateType == "cv" || gateType == "12") {
        return GateType::CV;
    }
    if (gateType == "vdg" || gateType == "13") {
        return GateType::VDG;
    }
    if (gateType == "cvdg" || gateType == "14") {
        return GateType::CVDG;
    }
    if (gateType == "sx" || gateType == "15") {
        return GateType::SX;
    }
    if (gateType == "csx" || gateType == "16") {
        return GateType::CSX;
    }
    if (gateType == "sxdg" || gateType == "17") {
        return GateType::SXDG;
    }
    if (gateType == "csxdg" || gateType == "18") {
        return GateType::CSXDG;
    }
    if (gateType == "y" || gateType == "19") {
        return GateType::Y;
    }
    if (gateType == "cy" || gateType == "20") {
        return GateType::CY;
    }
    if (gateType == "ry" || gateType == "21") {
        return GateType::RY;
    }
    if (gateType == "cry" || gateType == "22") {
        return GateType::CRY;
    }
    if (gateType == "z" || gateType == "23") {
        return GateType::Z;
    }
    if (gateType == "cz" || gateType == "24") {
        return GateType::CZ;
    }
    if (gateType == "s" || gateType == "25") {
        return GateType::S;
    }
    if (gateType == "cs" || gateType == "26") {
        return GateType::CS;
    }
    if (gateType == "sdg" || gateType == "27") {
        return GateType::SDG;
    }
    if (gateType == "csdg" || gateType == "28") {
        return GateType::CSDG;
    }
    if (gateType == "t" || gateType == "29") {
        return GateType::T;
    }
    if (gateType == "ct" || gateType == "30") {
        return GateType::CT;
    }
    if (gateType == "tdg" || gateType == "31") {
        return GateType::TDG;
    }
    if (gateType == "ctdg" || gateType == "32") {
        return GateType::CTDG;
    }
    if (gateType == "p" || gateType == "33") {
        return GateType::P;
    }
    if (gateType == "cp" || gateType == "34") {
        return GateType::CP;
    }
    if (gateType == "rz" || gateType == "35") {
        return GateType::RZ;
    }
    if (gateType == "crz" || gateType == "36") {
        return GateType::CRZ;
    }
    if (gateType == "rzz" || gateType == "37") {
        return GateType::RZZ;
    }
    if (gateType == "h" || gateType == "38") {
        return GateType::H;
    }
    if (gateType == "ch" || gateType == "39") {
        return GateType::CH;
    }
    if (gateType == "u1" || gateType == "40") {
        return GateType::U1;
    }
    if (gateType == "cu1" || gateType == "41") {
        return GateType::CU1;
    }
    if (gateType == "u2" || gateType == "42") {
        return GateType::U2;
    }
    if (gateType == "cu2" || gateType == "43") {
        return GateType::CU2;
    }
    if (gateType == "u3" || gateType == "44") {
        return GateType::U3;
    }
    if (gateType == "cu3" || gateType == "45") {
        return GateType::CU3;
    }
    if (gateType == "u" || gateType == "46") {
        return GateType::U;
    }
    if (gateType == "cu" || gateType == "47") {
        return GateType::CU;
    }
    if (gateType == "peres" || gateType == "48") {
        return GateType::PERES;
    }
    if (gateType == "peresdg" || gateType == "49") {
        return GateType::PERESDG;
    }
    if (gateType == "swap" || gateType == "50") {
        return GateType::SWAP;
    }
    if (gateType == "cswap" || gateType == "51") {
        return GateType::CSWAP;
    }
    if (gateType == "iswap" || gateType == "52") {
        return GateType::ISWAP;
    }
    if (gateType == "reset" || gateType == "53") {
        return GateType::RESET;
    }
    if (gateType == "measure" || gateType == "54") {
        return GateType::MEASURE;
    }
    if (gateType == "if" || gateType == "55") {
        return GateType::IF;
    }
    if (gateType == "barrier" || gateType == "56") {
        return GateType::BARRIER;
    }
    throw std::invalid_argument("Unknown operation type: " + gateType);
}

inline std::istream& operator>>(std::istream& in, gate_t& gateType) {
    std::string token;
    in >> token;

    if (token.empty()) {
        in.setstate(std::istream::failbit);
        return in;
    }

    gateType = gateTypeFromString(token);
    return in;
}

inline std::ostream& operator<<(std::ostream& out, gate_t& gateType) {
    out << toString(gateType);
    return out;
}

}  // namespace qcore