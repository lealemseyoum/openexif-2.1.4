/*
 * Copyright (c) 2000-2009, Eastman Kodak Company
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification,are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, 
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the 
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Eastman Kodak Company nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * Creation Date: 03/30/2003
 *
 * Original Author: 
 * Ricardo Rosario ricardo.rosario@kodak.com
 * 
 */
 
/*
 * Program Usage:
 *    AppSegDump <filename>
 *       where <filename> is the name of the Exif file to read the Application
 *       Segments from.
 */
  
// The files we need to include...
#include "ExifImageFile.h"

using namespace std;

// The main entry point.
int main(int argc, char *argv[])
{
    int return_value = 0;
    
    // Verify that we have one command-line argument. If we don't, show the
    // usage and exit.
    if (argc == 2)
    {
        char * filename = argv[1];
        
        // Create instance of ExifImageFile
        ExifImageFile inImageFile;
        
        // Open the file in read-only mode and verify that it succeeds
        if ( inImageFile.open( filename, "r" ) == EXIF_OK)
        {
            // Get a vector with all the application segments in the file
            vector<ExifAppSegment*> appSegs = inImageFile.getAllAppSegs();
            
            // How many do we have?
            int numOfAppSegs = appSegs.size();
    
            cout << "Number of Application Segments in " << filename <<
                ": " << numOfAppSegs << endl ;
            cout << "Marker\tLength\tIdent" << endl;
    
            // Loop through the application segments outputting their marker,
            // length and identifier.
            for ( int i = 0; i < numOfAppSegs; i++ )
            {
                cout << appSegs[i]->getAppSegmentMarker() << "\t";
                cout << appSegs[i]->getLength() << "\t";
                cout << appSegs[i]->getAppIdent() << endl;
            }

            // Close the file
            if( inImageFile.close() != EXIF_OK )
            {
                cout << "Error: Could not close" << filename << endl;
                return_value = 1;
            }   
        }
        else
        {
            cout << "Error: could not open " << filename <<
                " with ExifImageFile." << endl;
            return_value = 1;   
        }
    }
    else
    {
        cout << " Usage: " << argv[0] << " <filename>\n";
        return_value = 1;
    }
        
    // return the status
    return return_value;
}
