OpenSim Forward Dynamics How To (Tensegrity Knee):
1) Load in Tensegrity_Knee_REV_3 into OpenSim
2) Go into the coordiantes window and clamp the hip and knee coordinates (to the right of the lock icon). This ensures that nothing will move the coordiante outside of its range of motion. For the hip it is between -50 and 50 degrees and for the knee it's between 0 and -140 degrees.
3) Engage the Forward Dynamics tool
4) Under the main settings tab, in the Controls section select the Tensegrity_Knee_Forward_Default_Controls.xml file
5) In the Initial State section, select the Tensegrity_Knee_Default_States.sto file
6) Click the far right icon on the Controls section row (to open the Excitation Editor)
7) Select the muscles you wish to excite
8) In the Excitation Editor, right click on the graphs and select "Add control point to excitation"
9) Do this for every muscle you wish to excite
10) Click save and properly name the file (this will be file that contains the set of excitations at the various times that you want for your simulation)
11) In the in Controls section, navigate to the file you just saved and select it
12) Check the "Solve for equilibrium for actuator states" box
13) Set the duration of simulation you want in the Time area
14) Set the name of the output files you will be creating
15) hit run