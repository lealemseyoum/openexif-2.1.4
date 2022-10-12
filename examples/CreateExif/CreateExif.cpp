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
 * Creation Date: 06/23/2003
 *
 * Original Author: 
 * Ricardo Rosario ricardo.rosario@kodak.com
 * 
 */
 
 /*
 * Program Usage:
 *    CreateExif <filename>
 *       where <filename> is the name of the Exif file we will create
 */
 
 // The files we need to include...
#include "ExifImageFile.h"
#include "ExifImageDescUtils.h"

using namespace std;

// Define the height and width of the image we are going to create
#define WIDTH   600
#define HEIGHT  400
#define THUMBWIDTH   60
#define THUMBHEIGHT  40

// Prototype for the function that will initialize all the pixels to form a
// checkerboard type pattern of red, green and blue boxes.
void initializePixels(char *buf);
void initializeThumbPixels(char *buf);

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
        ExifImageFile outImageFile;
        
        // Open the file in write (create) mode and verify that it succeeds
        if ( outImageFile.open( filename, "w" ) == EXIF_OK)
        {
            cout << "Creating new Exif image file " <<filename<< "..." << endl;

            // set the image information
            ExifImageInfo imgInfo;
            imgInfo.width = WIDTH;
            imgInfo.height = HEIGHT;
            outImageFile.setImageInfo( imgInfo ) ;

            // Create and allocate image buffer we will use to create and
            // initialize the pixel values
            ExifImageDesc imageBuf ;
            exifAllocImageDesc( imgInfo, imageBuf ) ;
    
            // initailize the pixels
            initializePixels( (char *)imageBuf.components[0].theData );
    
            // Compress the image to the file
            ExifStatus status ;
            exif_uint32 nextLine ;
            exif_uint32 linesDone ;
            status = outImageFile.writeScanLines( imageBuf,
                 imageBuf.numberOfRows, nextLine, linesDone ) ;
            if ( status != EXIF_OK )
            {
                cout << "Error during compression!" << endl;
                return_value = 1;
            }

            // Clean up the image buffer
            exifDeleteImageDesc( imageBuf ) ;
    
            // --- Set the thumbnail image ---
            ExifImageInfo thumbInfo;
            thumbInfo.height = THUMBHEIGHT;
            thumbInfo.width = THUMBWIDTH;
            
            ExifImageDesc* thumbBuf = new ExifImageDesc;
            exifAllocImageDesc(thumbInfo, *thumbBuf);
            initializeThumbPixels( (char *)thumbBuf->components[0].theData );
            
            // Set tags related to the thumbnail dimensions
            ExifTagEntry* entry = new ExifTagEntryT<exif_uint32>( 257, 
                EXIF_LONG, 1, THUMBHEIGHT );
            outImageFile.setGenericTag(*entry,EXIF_APP1_IFD1 );
            delete entry;
            
            entry = new ExifTagEntryT<exif_uint32>( 256, 
                EXIF_LONG, 1, THUMBWIDTH );
            outImageFile.setGenericTag(*entry,EXIF_APP1_IFD1);
            delete entry;
            
            outImageFile.setThumbnail(thumbBuf);
            // --- Finished setting the thumbnail ---
            
            // Close the file
            if( outImageFile.close() != EXIF_OK )
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

// This function initializes the pixels to form a checkerboard type pattern of
// red, green and blue boxes.
void initializePixels(char *buf)
{
    // Initialize the values in all of the pixels
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < (WIDTH * 3); j += 3)
        {
            // Set R, G, B values
            if (i % 300 < 100)
            {
                if (j % 900 < 300)
                {
                    // Set to RED
                    *(buf + i * WIDTH * 3 + j) = (char) 255;    //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 0;  //B
                }
                else if (j % 900 < 600)
                {
                    // Set to GREEN
                    *(buf + i * WIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 255;    //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 0;  //B
                }
                else
                {
                    // Set to BLUE
                    *(buf + i * WIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 255;    //B
                }
            }
            else if (i % 300 < 200)
            {
                if (j % 900 < 300)
                {
                    // Set to GREEN
                    *(buf + i * WIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 255;    //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 0;  //B
                }
                else if (j % 900 < 600)
                {
                    // Set to BLUE
                    *(buf + i * WIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 255;    //B
                }
                else
                {
                    // Set to RED
                    *(buf + i * WIDTH * 3 + j) = (char) 255;    //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 0;  //B
                }
            }
            else if (i % 300 < 300)
            {
                if (j % 900 < 300)
                {
                    // Set to BLUE
                    *(buf + i * WIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 255;    //B
                }
                else if (j % 900 < 600)
                {
                    // Set to RED
                    *(buf + i * WIDTH * 3 + j) = (char) 255;    //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 0;  //B
                }
                else
                {
                    // Set to GREEN
                    *(buf + i * WIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * WIDTH * 3 + j + 1) = (char) 255;    //G
                    *(buf + i * WIDTH * 3 + j + 2) = (char) 0;  //B
                }
            }
        }
    }
}

// This function initializes the pixels to form a checkerboard type pattern of
// red, green and blue boxes.
void initializeThumbPixels(char *buf)
{
    // Initialize the values in all of the pixels
    for (int i = 0; i < THUMBHEIGHT; i++)
    {
        for (int j = 0; j < (THUMBWIDTH * 3); j += 3)
        {
            // Set R, G, B values
            if (i % 30 < 10)
            {
                if (j % 90 < 30)
                {
                    // Set to RED
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 255;    //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 0;  //B
                }
                else if (j % 90 < 60)
                {
                    // Set to GREEN
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 255;    //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 0;  //B
                }
                else
                {
                    // Set to BLUE
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 255;    //B
                }
            }
            else if (i % 30 < 20)
            {
                if (j % 90 < 30)
                {
                    // Set to GREEN
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 255;    //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 0;  //B
                }
                else if (j % 90 < 60)
                {
                    // Set to BLUE
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 255;    //B
                }
                else
                {
                    // Set to RED
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 255;    //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 0;  //B
                }
            }
            else if (i % 30 < 30)
            {
                if (j % 90 < 30)
                {
                    // Set to BLUE
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 255;    //B
                }
                else if (j % 90 < 60)
                {
                    // Set to RED
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 255;    //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 0;  //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 0;  //B
                }
                else
                {
                    // Set to GREEN
                    *(buf + i * THUMBWIDTH * 3 + j) = (char) 0;  //R
                    *(buf + i * THUMBWIDTH * 3 + j + 1) = (char) 255;    //G
                    *(buf + i * THUMBWIDTH * 3 + j + 2) = (char) 0;  //B
                }
            }
        }
    }
}
