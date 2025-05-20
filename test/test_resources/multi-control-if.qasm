OPENQASM 3.0;
include "stdgates.inc";
bit[3] c8;
qubit[3] q8;
h q8[0];
h q8[1];
c8[0] = measure q8[0];
c8[1] = measure q8[1];
if (c8 == 1) {
  x q8[2];
}
c8[2] = measure q8[2];
