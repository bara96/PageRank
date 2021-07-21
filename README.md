# PageRank
Pagerank project for Information Retrievial and Web Search, Ca' Foscari University of Venice

#Setup
##CMake Installation
This project is build with CMake to improve scalability between systems.  
Cmake keeps the project platform-independent in order to use it on different systems as well.

Download and install CMake form here <code> https://cmake.org/install/ </code>

##Project Build

###Step 1
After installing CMake, prompt with the following command into the project root:

<code>cmake -Bbuild -S.</code>  

This command will generate the buildsystem into the folder <code>build</code>.

###Step 2
Switch into the newly generated <code>build</code> folder and prompt the command:

<code>make all</code>

This command will build the application.

###Step 3
Run the project with the command:

<code>./PageRank</code>