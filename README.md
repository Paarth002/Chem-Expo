# Chem-Expo

### CS-352: Computer Graphics and Visualisation Course Project
### Under Prof. Somnath Dey, IIT Indore
### Team Members: Parth Bhore (200001015), Khushi Verma (200001036), Sanskar Verma (200001069).

Chem-Expo explores the possibility of demonstrating fully-animated real-life chemical reactions while integrating them with the fundamental concepts of Computer Graphics and Visualization paradigm. In our project, we have worked with two popular reactions of chemistry, namely – formation of sulfuric acid (H2O + SO3 -> H2SO4 ) and bromination of methyl-cyclopentane ( methyl-cyclopentane + HBr -> bromo-methyl-cyclopentane ). 

### Demo Video Link - https://drive.google.com/file/d/1OsBBYy-6fkQGbtQrVuszhREi3YWLnnlO/view?usp=sharing

We can install OpenGL using:

```
$ sudo apt-get update
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

To install SOIL library, simply run the command:

```
$ sudo apt-get install libsoil-dev
```

Further steps to run the files: (let’s take the example of H2SO4.cpp, exactly similar steps and functionalities are there for cyclopentane.cpp, just the name changed)   
```
$ g++ H2SO4.cpp -o H2SO4 -lGL -lGLU -lglut -lm -lSOIL
$ ./H2SO4
```

That’s it! You will see the reaction window in OpenGL pop-up, with the reaction in place.

#### Key controls to play around with the reaction:
*	Use Keys: W/A (to translate along x-axis), S/D(to translate along y-axis), 5/8(to translate along z-axis).
*	Use Mouse: Hold Middle Button and Drag to Zoom In / Zoom Out.
*	Use Mouse: Hold Left Button and Drag to Rotate Axis
*	Press Enter to Start/Pause animation for the reaction.
*	Press Space to Start/Pause rotation of individual molecules about their centers.
*	Press P to Change Projection types.
*	Press C to Change Camera positions.
*	Press L to Change Lighting Effects.
*	Press M to Toggle display of Legend.
*	Press R to Reset animation from the beginning.
*	Press + to Add/Remove display of Axes of the coordinate system.
*	Press – to Highlight the colors of molecules.
*	Press Esc to Close Window.


