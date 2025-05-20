OPENQASM 3.0;
include "stdgates.inc";
bit[2] c12;
qubit[2] q12;
h q12[0];
h q12[1];
c12[0] = measure q12[0];
c12[1] = measure q12[1];
while (c12 == 3) {
  h q12[0];
  h q12[1];
  c12[0] = measure q12[0];
  c12[1] = measure q12[1];
}
