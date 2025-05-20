OPENQASM 3.0;
include "stdgates.inc";
bit[1] c6;
qubit[1] q6;
h q6[0];
c6[0] = measure q6[0];
if (c6[0]) {
  x q6[0];
}
c6[0] = measure q6[0];
