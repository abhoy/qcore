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
 *  @file   qasm3_parser_test.cpp
 *  @brief  Unit Test for QASM3 Parser
 *  @author Louis Krüger
 *  @date   19.05.2025
 ***********************************************************/

#include <iostream>
#include <filesystem>

#include <gtest/gtest.h>

#include "QCircuit.hpp"

std::ifstream open_test_resource(const std::string& filename) {
    std::filesystem::path path = std::filesystem::path(TEST_RESOURCES_DIR) / filename;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open test resource: " + path.string());
    }
    return file;
}


TEST(QASM3ParserTest, BasicTest) {
    auto qasm_file = open_test_resource("3_17_14.qasm");
    ASSERT_TRUE(qasm_file.is_open()) << "Error opening file!";

    qcore::QCircuit circuit;
    circuit.readQASM3(qasm_file);
    qasm_file.close();

    // Test the circuit
    std::string test_string = R"(OPENQASM 2.0;
include "qelib1.inc";

qreg q[3];
creg c[3];
cx q[0], q[1];
ccx q[2], q[1], q[0];
x q[2];
cx q[2], q[1];
cx q[0], q[2];
ccx q[2], q[1], q[0];)";
    ASSERT_EQ(circuit.toString(qcore::FileFormat::OpenQASM), test_string);
}

TEST(QASM3ParserTest, IfTest) {
    auto qasm_file = open_test_resource("if.qasm");
    ASSERT_TRUE(qasm_file.is_open()) << "Error opening file!";

    qcore::QCircuit circuit;
    circuit.readQASM3(qasm_file);
    qasm_file.close();
    std::cout << circuit.toString(qcore::FileFormat::OpenQASM) << std::endl;
}

