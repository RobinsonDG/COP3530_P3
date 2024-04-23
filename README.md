To run "Something Smells Phishy", create a dedicated folder.
This folder should included everything in the Github repository exactly how it is laid out.
Given you are on a Windows computer with MinGW-64 installed...
	Open cmd and navigate to the program's folder
	Enter "mingw32-make compile"
	Navigate to "output" folder and run project3.exe
	When finished, go back to cmd and enter "mingw32-make remove"
Otherwise, clone the Github repository into CLion, ensure all .cpp and .h files are included in CMakeLists.txt,
	and run through an IDE.