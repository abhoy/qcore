OPENQASM 3.0;
include "stdgates.inc";
bit[1] c11;
qubit[1] q11;
for _ in [0:4] {
  x q11[0];
}
c11[0] = measure q11[0];
