void Switches_Process(void){
//------------------------------------------------------------------------------
  if (!(P4IN & SW1)){
    display_1 = "NCSU";
    posL1 = 3;
    display_2 = "WOLFPACK";
    posL2 = 1;
    display_3 = "ECE306";
    posL3 = 2;
    display_4 = "J Carlson";
    posL4 = 1;
  }
  if (!(P4IN & SW2)) {
    display_1 = "Embedded";
    posL1 = 1;
    display_2 = "Systems";
    posL2 = 2;
    display_3 = "Rock!";
    posL3 = 3;
    display_4 = "Go Pack!";
    posL4 = 1;
  }
//------------------------------------------------------------------------------
}