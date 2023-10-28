# ContourPlots  
C programs for generating contour plots  
During development of the Green's function method for simulating mass transport by microvessel networks, I have been unable to find suitable open-source C programs for generating contour plots. The following subroutines are designed to address this problem. Both subroutines plot contours of a function specified by numerical data on a rectangular grid, and generate PostScript output. In this version, contr_shade combines polygons with the same color before writing to the PostScript file. Also some new options have been added. This yields compact output files.    
- contr_lines.cpp - generates contour lines and labels with contour heights  
- contr_shade.cpp - generates contour lines with colored shading between contours and a color bar  
Input variables are:  
- m n nl: dimensions of array, no. of contour levels  
- scalefac: determines size of plot  
- xmin xmax ymin ymax: boundaries of box  
- cl(nl): array of contour levels  
- zv(m,n): array of heights  
Additional variables are defined within the subroutines and may need to be changed for specific applications.  
This code is free to use at your own risk. Feedback and/or acknowledgement are appreciated. Email secomb@u.arizona.edu.  
Note: This code makes use of nrutil.h and nrutil.cpp as placed in the public domain by Numerical Recipes http://numerical.recipes/. 
