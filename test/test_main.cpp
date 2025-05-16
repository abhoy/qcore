//
// Created by lokr on 5/16/25.
//
#include <iostream>
#include "QCircuit.hpp"

int main() {

  // Test the readQASM function with the "test/3_17_14.qasm" file
  qcore::QCircuit circuit;
  std::ifstream qasm_file("test/3_17_14.qasm");
  if (!qasm_file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }
  circuit.readQASM3(qasm_file);
  qasm_file.close();
  // Test the writeQASM function
  std::ofstream output_file("test/output.qasm");
  if (!output_file.is_open()) {
    std::cerr << "Error opening output file!" << std::endl;
    return 1;
  }
  circuit.writeQASM3(output_file);
  output_file.close();

  std::cout << "Test Passed!\n";

  return 0;
}