# dda
dda is a program to model deposition diffusion aggregation (DDA) with activated diffusion. The program uses the algorithm outline in Pablo Jensen's report (I don't have the reference available right now). Keeping track of cluster labels is done using my own version of the "improved cluster labeling scheme" outlined in chapter 7 of Giordano and Nakanishi's Computational Physics text.

The sources are located in the `src` directory, and should be pretty self explanatory and well commented. To learn more, start reading `main` and the associated functions.

The program can output the actual grid to show the grid morphology, but the primary purpose of the program is to write information about the island size distribution. This is done by simply counting the sizes of each island, and output these sizes to a file. I have written separate utilities to then take this output and convert it into meaningful size distribution data suitable for plotting by some external program such as gnuplot or matlab. 

`dda` itself is built by issuing the command `make` or `make bin/dda` in this directory, which builds the program and places the executable in the `bin` directory. The program is then run by issuing the command `bin/dda`. This will run the program and save the output files in the current working directory. You can alternatively move to another directory where you want the output files saved and issue the absolute pathname to the binary file to run the program and save the output to that directory. If I were to work with it much more I might change this behavior, and allow for a command line argument to specify the output file path, but that's how it works for now. The program also writes the density information at each time step to stdout. This can be redirected to a file to save the density information for plotting. Information about the parameters used is also included in this output, so it is nice to save this output to a file (i.e. issue the command `bin/dda > run.out`).

All configuration is done by editing the file `src/globals.h`. All of the parameters should be clear from their usage and the comments. The definitions of `D0`, `D`, and `D1` are a little confusing, as are the activation energies `E0` and `E1`. Reading Pablo Jensen's report and Amar and Family's papers might help clear this up. I would have to look back at them to be able to explain it well myself.

In its current state, the program writes output to text files, which makes for easy plotting but may be slowing things down quite a bit. One thing to look into is maybe writing the output to binary files, and modifying the `scale` program to read in the binary data as opposed to the text files.

20 JULY 2009
Added logical flags to make it easier to pick what information gets output to file. These flags are defined in the header file `src/globals.h`. Also in this latest version, I did some work to clean up some of the routines, and the lists are now linked together in some sort of logical fashion (at least to me) by incorporating them together in a `grid_point` data structure. Hopefully this makes things a little easier to read/understand.

That's about all I can think if now. Please feel free to contact me with any and all questions about the algorithm or the code itself.
