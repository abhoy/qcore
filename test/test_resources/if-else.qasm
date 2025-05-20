OPENQASM 3.0;
include "stdgates.inc";
bit[2] c7;
qubit[2] q7;
h q7[0];
c7[0] = measure q7[0];
if (c7[0]) {
  h q7[1];
} else {
  x q7[1];
}
c7[1] = measure q7[1];
