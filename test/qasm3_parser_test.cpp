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
#include "antlr4-runtime.h"
#include "qasm3Parser.h"
#include "qasm3Lexer.h"
#include "qasm3ParserBaseListener.h"
#include "tree/ParseTreeWalker.h"

using namespace antlr4;

class MyQASMListener : public qasm3ParserBaseListener {
public:
    void enterProgram(qasm3Parser::ProgramContext *ctx) override {
        std::cout << "Entering QASM3 program: " << ctx->getText() << std::endl;
    }
};

void writeParseTreeToFile(tree::ParseTree* tree, Parser* parser, const std::string& filename) {
    std::string string = tree::Trees::toStringTree(tree, parser, true);
    std::ofstream file(filename);
    file << string;
    file.close();
}

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

/*
TEST(QASM3ParserTest, IfTest) {
    auto qasm_file = open_test_resource("if.qasm");
    ASSERT_TRUE(qasm_file.is_open()) << "Error opening file!";

    qcore::QCircuit circuit;
    circuit.readQASM3(qasm_file);
    qasm_file.close();
    std::cout << circuit.toString(qcore::FileFormat::OpenQASM) << std::endl;
}*/

TEST(AntlrTest, BasicTest) {
    //std::string input = R"(OPENQASM 3.0;
//qubit q[2];
//h q[0];
//cx q[0], q[1];)";
    std::ifstream file = open_test_resource("if.qasm");

    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    ANTLRInputStream inputStream(input);
    qasm3Lexer lexer(&inputStream);
    CommonTokenStream tokens(&lexer);
    qasm3Parser parser(&tokens);

    // Start rule: usually 'program' in ANTLR grammars
    qasm3Parser::ProgramContext* tree = parser.program();

    writeParseTreeToFile(tree, &parser, std::string(TEST_RESOURCES_DIR) + "/output.txt");

    // Walk the tree with a listener
    MyQASMListener listener;
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

    // Optional: assert that parse tree is not null
    ASSERT_NE(tree, nullptr);
}