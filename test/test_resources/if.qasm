OPENQASM 3.0;
include "stdgates.inc";
bit[1] c;               // classical 1-bit register
qubit[1] q;             // 1-qubit register
h q[0];                 // h on first qubit.
c[0] = measure q[0];    // Measurement von erstem Qubit wird aufs klassische Bit geschrieben
if (c[0]) {             // Wenn das Bit 1 ist
  x q[0];               // wird ein x gate auf dem Qubit ausgeführt
}
c[0] = measure q[0];    // Qubit wird nochmal auf das klassische Bit gemessen.
                        // ->Programm gibt immer 0 aus.
