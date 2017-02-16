#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "point.h"

//! Class to input coordinates from text file
template<unsigned Tdim> class Mesh {

public:
    //!  Constructor
    Mesh();

    //! Read file
    void readfile();

    //!Output contents of vector to check right data included
    void outputcoords();

private:

    //!Total number of vertices
    double nvertices;
    //! coordinates used in incoordvector
    double xcoord,ycoord,zcoord;
    //! Vertices id
    unsigned vertn;

    //!Array to store vertices coordinates
    std::array<double, Tdim> verticesarray;

    //!coordinate and id container
    std::vector<std::unique_ptr<Point<Tdim>>> vertices_;
};
