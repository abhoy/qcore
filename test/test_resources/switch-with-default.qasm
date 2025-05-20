OPENQASM 3.0;
include "stdgates.inc";
bit[3] c10;
int switch_dummy;
qubit[3] q10;
h q10[0];
h q10[1];
c10[0] = measure q10[0];
c10[1] = measure q10[1];
switch_dummy = c10;
switch (switch_dummy) {
  case 0, 3 {
    z q10[2];
  }
  case 1 {
    y q10[2];
  }
  default {
    x q10[2];
  }
}
c10[2] = measure q10[2];
