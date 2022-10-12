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
 *    ExifTagDump <filename>
 *       where <filename> is the name of the Exif file to read the Exif Tags
 *       from.
 */
 
 // The files we need to include...
#include "ExifImageFile.h"
#include <iomanip>

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
            // Get all the AppSeg 1 - "Exif" tags and output them
            cout << "App1 - \"Exif\" entries:" << endl;
            ExifPathsTags app1PathsTags ;
            inImageFile.getAllTags( 0xFFE1, "Exif", app1PathsTags ) ;

            ExifPathsTagsIter crntPathsTags = app1PathsTags.begin() ;
            ExifPathsTagsIter endPathsTags = app1PathsTags.end() ;
            while( crntPathsTags != endPathsTags )
            {
                ExifIFDPathIter crntPath = (*crntPathsTags).first.begin() ;
                ExifIFDPathIter endPath = (*crntPathsTags).first.end() ;
                while( crntPath != endPath )
                {
                    cout << "IFD: " << (*crntPath).first  ;
                    cout << "  Idx: " << (*crntPath).second << endl ;
                    crntPath++ ;
                }
         
                ExifTagsIter crnt = (*crntPathsTags).second.begin() ;
                ExifTagsIter end = (*crntPathsTags).second.end() ;
                
                cout << "Tag#\tType\tCount\tValue" << endl;
                while( crnt != end )
                {
                    ExifTagEntry* tag = *(crnt) ;
                    tag->print() ;
                    cout << endl ;
                    crnt++ ;
                }
                crntPathsTags++ ;
            }
            
            // Get all the AppSeg 3 - "Meta" tags and output them
            
            ExifPathsTags app3PathsTags ;
            inImageFile.getAllTags( 0xFFE3, "Meta", app3PathsTags ) ;

            crntPathsTags = app3PathsTags.begin() ;
            endPathsTags = app3PathsTags.end() ;
            if ( crntPathsTags != endPathsTags )
                cout << "\nApp3 - \"Meta\" entries:" << endl;
            while( crntPathsTags != endPathsTags )
            {
                ExifIFDPathIter crntPath = (*crntPathsTags).first.begin() ;
                ExifIFDPathIter endPath = (*crntPathsTags).first.end() ;
                while( crntPath != endPath )
                {
                    cout << "IFD: " << (*crntPath).first  ;
                    cout << "  Idx: " << (*crntPath).second << endl ;
                    crntPath++ ;
                }
         
                ExifTagsIter crnt = (*crntPathsTags).second.begin() ;
                ExifTagsIter end = (*crntPathsTags).second.end() ;
                
                cout << "Tag#\tType\tCount\tValue" << endl;
                while( crnt != end )
                {
                    ExifTagEntry* tag = *(crnt) ;
                    tag->print() ;
                    cout << endl ;
                    crnt++ ;
                }
                crntPathsTags++ ;
            }            

            //Now, recognition of any other app segments:
            // Get a vector with all the application segments in the file
            vector<ExifAppSegment*> appSegs = inImageFile.getAllAppSegs();
            
            // How many do we have?
            int numOfAppSegs = appSegs.size();
    
            cout << "\n\nNumber of Application Segments in " << filename <<
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
            
            
            // Now, lets output any COM marker data
            cout << endl << endl;
            ExifComMarkerList * comList = 
                     ( ExifComMarkerList * )inImageFile.getComData();
            const unsigned int comListSize = comList->size();
            for(unsigned int i = 0; i < comListSize; i++)
            {
                tsize_t dataSize;
                int j;
                ExifComMarker * marker = comList->getComMarker(i);
                const uint8 * comData = marker->getData(dataSize);
                cout << "COM Marker #" << i+1 << " Data" << endl;
                for (j = 0; j < dataSize; j++)
                    cout << setbase(16) << (unsigned short)comData[j] << " ";
                cout << endl;
                for (j = 0; j < dataSize; j++)
                    cout << comData[j];
                cout << endl << endl;
            }
            
            // And finally, let's output the SOF info
            ExifImageInfo info;
            inImageFile.getImageInfo(info);
            cout << "Image Information:\n";
            cout << "\twidth:\t\t" << info.width << endl;
            cout << "\theight:\t\t" << info.height << endl;
            cout << "\tchannels:\t" << info.numChannels << endl;
            cout << "\tbit depth:\t" << info.precision << endl;
           
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
