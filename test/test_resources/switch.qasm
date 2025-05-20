OPENQASM 3.0;
include "stdgates.inc";
bit[1] c9;
int switch_dummy;
qubit[1] q9;
h q9[0];
c9[0] = measure q9[0];
switch_dummy = c9[0];
switch (switch_dummy) {
  case 0 {
    x q9[0];
  }
  case 1 {
    z q9[0];
  }
}
c9[0] = measure q9[0];
