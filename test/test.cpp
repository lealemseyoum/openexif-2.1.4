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
 * Creation Date: 07/14/2001
 *
 * Original Author: 
 * George Sotak george.sotak@kodak.com 
 *
 * Contributor(s): 
 * Ricardo Rosario ricardo.rosario@kodak.com
 * 
 */ 



#include "ExifImageDescUtils.h"
#include "ExifImageFile.h"
#include "ExifMisc.h"

// In-memory testing has been removed due to a bug in the standard IJG 
// toolkit w/r/t reading images in memory.  This bug has been fixed in 
// several Linux distributions of libjpeg.  Therefore, if you need to
// check your version, define TEST_IN_MEMORY_EXIF and the test will be
// run (but the output will not be in the GroundTrue file).
#ifdef TEST_IN_MEMORY_EXIF
#include <sys/mman.h>
#endif

using namespace std;

// Test reading a Thumbnail from an Exif file and writing it out to a new
// Jpeg file as the main image.
void testThumbnailRead( void )
{
    cout << "=================================================" << endl ;
    cout << "Trying to read thumbnail and write to new file..." << endl ;
    cout << "=================================================" << endl ;

    char inputFile[]= "Kodak_DC290.jpg" ;
    char outputFile[]= "copyThumb.jpg" ;

    ExifImageFile inImageFile ;
    ExifJpegImage outImageFile ;

    if( inImageFile.open( inputFile, "r" ) != EXIF_OK )
    {
        cout << "Error: could not open " << inputFile << endl;
        return;
    }
    if( outImageFile.open( outputFile, "w" ) != EXIF_OK )
    {
        cout << "Error: could not open " << outputFile << endl;
        return;
    }

    ExifImageDesc* tnBuf ;

    tnBuf = inImageFile.getThumbnail() ;

    ExifImageInfo imgInfo ;
    imgInfo.width = tnBuf->numberOfColumns ;
    imgInfo.height = tnBuf->numberOfRows ;
    imgInfo.numChannels = tnBuf->numberOfComponents ;
    
    outImageFile.setImageInfo( imgInfo ) ;

    ExifStatus status ;
    exif_uint32 nextLine ;
    exif_uint32 linesDone ;
    
    status = outImageFile.writeScanLines( *tnBuf, tnBuf->numberOfRows, nextLine, linesDone ) ;

   
    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << inputFile << endl;
    }
    if( outImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << outputFile << endl;
    }

    return ;
}


// Test opening a file for creation to verify it creates the correct default
// metadata.
void testDefaultMetadata( void )
{
    cout << "===========================" << endl ;
    cout << "Testing default metadata..." << endl ;
    cout << "===========================" << endl ;
    char outputFile[]= "copyDefaultMd.jpg" ;

    ExifImageFile outImageFile ;
    
    if( outImageFile.open( outputFile, "w" ) != EXIF_OK )
    {
        cout << "Error: could not open " << outputFile << endl;
        return;
    }
    if( outImageFile.close() != EXIF_OK )
    {
        cout << "Could not close  (expected! - because no image)" <<
            outputFile << endl;
    }

    return ;
}

// Test reading all metadata from one image and writing it out to another
void testMetadataReadWrite( void )
{
    cout << "=======================================" << endl ;
    cout << "Testing reading and writing metadata..." << endl ;
    cout << "=======================================" << endl ;

    char inputFile[]= "Kodak_DC290.jpg" ;
    char outputFile[]= "copyMd.jpg" ;

    ExifImageFile inImageFile ;
    ExifImageFile outImageFile ;

    if( inImageFile.open( inputFile, "r" ) != EXIF_OK )
    {
        cout << "Error: could not open " << inputFile << endl;
        return;
    }
    if( outImageFile.open( outputFile, "w" ) != EXIF_OK )
    {
        cout << "Error: could not open " << outputFile << endl;
        return;
    }

    ExifPathsTags pathsTags ;
    inImageFile.getAllTags( 0xFFE1, "Exif", pathsTags ) ;

    ExifPathsTagsIter crntPathsTags = pathsTags.begin() ;
    ExifPathsTagsIter endPathsTags = pathsTags.end() ;
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
        
        while( crnt != end )
        {
            ExifTagEntry* tag = *(crnt) ;
            tag->print() ;
            cout << endl ;
            crnt++ ;
        }
        crntPathsTags++ ;
    }

    outImageFile.setAllTags( 0xFFE1, "Exif", pathsTags ) ;

    // Copy the thumbnail need to create a whole new copy (deep copy)
    // of the ExifImageDesc because each file will clean up its own
    // and, therefore, cannot share the data.
    ExifImageDesc* tnBuf ;
    // tnBufCopy (below) will be deleted in outImageFile
    ExifImageDesc* tnBufCopy = new ExifImageDesc ; 
    tnBuf = inImageFile.getThumbnail() ;
    ExifImageInfo tnInfo ;
    tnInfo.width = tnBuf->numberOfColumns ;
    tnInfo.height = tnBuf->numberOfRows ;
    tnInfo.numChannels = tnBuf->numberOfComponents ;
    // Allocate mem for new image. This will be cleaned up in outImageFile
    exifAllocImageDesc( tnInfo, *tnBufCopy ); 
    exif_uint32 bufSize = tnInfo.width*tnInfo.height*tnInfo.numChannels ;
    uint8* imgData = tnBuf->components[0].theData ;
    uint8* imgDataCopy = tnBufCopy->components[0].theData ;
    for( exif_uint32 i = 0; i < bufSize; i++ )
    {
        imgDataCopy[i] = imgData[i] ; // Copy all the image data
    }
    outImageFile.setThumbnail( tnBufCopy, false ) ;

    ExifImageInfo imgInfo ;
    inImageFile.getImageInfo( imgInfo ) ;
    outImageFile.setImageInfo( imgInfo ) ;
    ExifImageDesc imageBuf ;

    exifAllocImageDesc( imgInfo, imageBuf ) ;

    ExifStatus status ;
    exif_uint32 nextLine ;
    exif_uint32 linesDone ;

    status = inImageFile.readScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    if( status != EXIF_OK )
    {
        cout << "Error: could not readScanLines from " << inputFile << endl;
        return;
    }

    status = outImageFile.writeScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    if( status != EXIF_OK )
    {
        cout << "Error: could not writeScanLines to " << outputFile << endl;
    }

    exifDeleteImageDesc( imageBuf );

    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << inputFile << endl;
    }
    if( outImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << outputFile << endl;
    }

    if( outImageFile.open( outputFile, "r" ) != EXIF_OK )
    {
        cout << "Error: could not open " << outputFile << endl;
    }

    pathsTags.clear() ;
    outImageFile.getAllTags( 0xFFE1, "Exif", pathsTags ) ;

    crntPathsTags = pathsTags.begin() ;
    endPathsTags = pathsTags.end() ;
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
        
        while( crnt != end )
        {
            ExifTagEntry* tag = *(crnt) ;
            tag->print() ;
            cout << endl ;
            crnt++ ;
        }
        crntPathsTags++ ;
    }

    char thumbFile[]= "copyThumb2.jpg" ;

    ExifJpegImage thumbImageFile ;
    
    if( thumbImageFile.open( thumbFile, "w" ) != EXIF_OK )
    {
        cout << "Error:: could not open " << thumbFile << endl;
        return;
    }

    tnBuf = outImageFile.getThumbnail() ;

    imgInfo.width = tnBuf->numberOfColumns ;
    imgInfo.height = tnBuf->numberOfRows ;
    imgInfo.numChannels = tnBuf->numberOfComponents ;
    
    thumbImageFile.setImageInfo( imgInfo ) ;

    
    status = thumbImageFile.writeScanLines( *tnBuf, tnBuf->numberOfRows, nextLine, linesDone ) ;
    if( status != EXIF_OK )
    {
        cout << "Error: could not writeScanLines to " << thumbFile << endl;
    }
   
    if( outImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << outputFile << endl;
    }
    if( thumbImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << thumbFile << endl;
    }
    
}

// Test reading image from one file and writing it to another.
void testImageReadWrite( void )
{
    cout << "====================================" << endl ;
    cout << "Testing reading and writing image..." << endl ;
    cout << "====================================" << endl ;
    char inputFile[]= "Kodak_DC4800.jpg" ;
    char outputFile[]= "copy.jpg" ;

    ExifJpegImage inImageFile ;
    ExifJpegImage outImageFile ;

    if( inImageFile.open( inputFile, "r" ) != EXIF_OK )
    {
        cout << "Error: could not open " << inputFile << endl;
        return;
    }
    if( outImageFile.open( outputFile, "w" ) != EXIF_OK )
    {
        cout << "Error: could not open " << outputFile << endl;
        return;
    }
    
    ExifImageInfo imgInfo ;
    inImageFile.getImageInfo( imgInfo ) ;
    outImageFile.setImageInfo( imgInfo ) ;
    
    ExifImageDesc imageBuf ;

    exifAllocImageDesc( imgInfo, imageBuf ) ;
    
    ExifStatus status ;
    exif_uint32 nextLine ;
    exif_uint32 linesDone ;

    status = inImageFile.readScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    cout << "Read from file status: " << status << " lines decompressed: " << linesDone << endl ;

    status = inImageFile.writeScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    cout << "Write to read only file should fail (result > 0): " << status << endl ;
    
    status = outImageFile.readScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    cout << "Read from write only file should fail (result > 0): " << status << endl ;
    
    status = outImageFile.writeScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    cout << "Write to file status: " << status << " lines compressed: " << linesDone << endl ;

    exifDeleteImageDesc( imageBuf ) ;
    
    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << inputFile << endl;
    }
    if( outImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << outputFile << endl;
    }
    
    return ;
}

#ifdef TEST_IN_MEMORY_EXIF
// Test reading image from one file and writing it to another.
void testImageReadWriteInMemory( void )
{
    cout << "==============================================" << endl ;
    cout << "Testing reading and writing image in memory..." << endl ;
    cout << "==============================================" << endl ;
    char inputFile[]= "KodakDC260.jpg" ;
    char outputFile[]= "copy2.jpg" ;

    int infile = open (inputFile,O_RDONLY);
    long fileSize = lseek(infile,0,SEEK_END);
    lseek(infile,0,SEEK_SET);
    void * infilemem = mmap(NULL,fileSize,PROT_READ,MAP_PRIVATE,infile,0);

    ExifJpegImage inImageFile ;
    ExifJpegImage outImageFile ;

    if( inImageFile.open( infilemem, fileSize, "r" ) != EXIF_OK )
    {
        cout << "Error: could not open " << inputFile << endl;
        return;
    }
    if( outImageFile.open( outputFile, "w" ) != EXIF_OK )
    {
        cout << "Error: could not open " << outputFile << endl;
        return;
    }
    
    ExifImageInfo imgInfo ;
    inImageFile.getImageInfo( imgInfo ) ;
    outImageFile.setImageInfo( imgInfo ) ;
    
    ExifImageDesc imageBuf ;

    exifAllocImageDesc( imgInfo, imageBuf ) ;
    
    ExifStatus status ;
    exif_uint32 nextLine ;
    exif_uint32 linesDone ;

    status = inImageFile.readScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    cout << "Read from file status: " << status << " lines decompressed: " << linesDone << endl ;

    status = inImageFile.writeScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    cout << "Write to read only file should fail (result > 0): " << status << endl ;
    
    status = outImageFile.readScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    cout << "Read from write only file should fail (result > 0): " << status << endl ;
    
    status = outImageFile.writeScanLines( imageBuf, imageBuf.numberOfRows, nextLine, linesDone ) ;
    cout << "Write to file status: " << status << " lines compressed: " << linesDone << endl ;

    exifDeleteImageDesc( imageBuf ) ;
    
    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << inputFile << endl;
    }
    if( outImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << outputFile << endl;
    }
    
    munmap(infilemem,fileSize);
    close(infile);
    return ;
}
#endif

// Test the ExifJpegImage::isJpegFile() method.
void testIsJpegFile()
{
    cout << "======================================" << endl ;
    cout << "Testing ExifJpegImage::isJpegFile()..." << endl ;
    cout << "======================================" << endl ;
    char dc220Exif[]     = "Kodak_DC220.jpg";
    char dc260Exif[]     = "KodakDC260.jpg";
    char dc290Exif[]     = "Kodak_DC290.jpg";
    char dc4800Exif[]    = "Kodak_DC4800.jpg";
    char mc3Exif[]       = "Kodak_MC3.jpg";
    char palmpixExif[]   = "Kodak_Palmpix.jpg";
    char pictureCDExif[] = "Kodak_PictureCD.jpg";
    char comSeg[]        = "DCP_0433_com.JPG";
    char jfif[]          = "JFIF.jpg";

    if( ExifJpegImage::isJpegFile( dc220Exif ) != EXIF_OK )
    {
        cout << "Error: " << dc220Exif << " not determined to be a Jpeg file." << endl;
    }
    if( ExifJpegImage::isJpegFile( dc260Exif ) != EXIF_OK )
    {
        cout << "Error: " << dc260Exif << " not determined to be a Jpeg file." << endl;
    }
    if( ExifJpegImage::isJpegFile( dc290Exif ) != EXIF_OK )
    {
        cout << "Error: " << dc290Exif << " not determined to be a Jpeg file." << endl;
    }
    if( ExifJpegImage::isJpegFile( dc4800Exif ) != EXIF_OK )
    {
        cout << "Error: " << dc4800Exif << " not determined to be a Jpeg file." << endl;
    }
    if( ExifJpegImage::isJpegFile( mc3Exif ) != EXIF_OK )
    {
        cout << "Error: " << mc3Exif << " not determined to be a Jpeg file." << endl;
    }
    if( ExifJpegImage::isJpegFile( palmpixExif ) != EXIF_OK )
    {
        cout << "Error: " << palmpixExif << " not determined to be a Jpeg file." << endl;
    }
    if( ExifJpegImage::isJpegFile( pictureCDExif ) != EXIF_OK )
    {
        cout << "Error: " << pictureCDExif << " not determined to be a Jpeg file." << endl;
    }
    if( ExifJpegImage::isJpegFile( comSeg ) != EXIF_OK )
    {
        cout << "Error: " << comSeg << " not determined to be a Jpeg file." << endl;
    }
    if( ExifJpegImage::isJpegFile( jfif ) != EXIF_OK )
    {
        cout << "Error: " << jfif << " not determined to be a Jpeg file." << endl;
    }

    ExifStatus status;
    ExifIO * exifio = ExifIO::open(status, dc220Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << dc220Exif << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << dc220Exif << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;

    exifio = ExifIO::open(status, dc260Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << dc260Exif << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << dc260Exif << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, dc290Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << dc290Exif << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << dc290Exif << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, dc4800Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << dc4800Exif << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << dc4800Exif << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, mc3Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << mc3Exif << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << mc3Exif << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, palmpixExif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << palmpixExif << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << palmpixExif << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, pictureCDExif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << pictureCDExif << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << pictureCDExif << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, comSeg, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << comSeg << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << comSeg << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, jfif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << jfif << " with ExifIO." << endl;    
    if( ExifJpegImage::isJpegFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << jfif << " not determined to be a Jpeg file." << endl;
    }
    exifio->close();
    delete exifio;

}

// Test the ExifImageFile::isExifFile() method.
void testIsExifFile()
{
    cout << "=====================================" << endl ;
    cout << "Testing ExifImageFile isExifFile()..." << endl ;
    cout << "=====================================" << endl ;
    char dc220Exif[]     = "Kodak_DC220.jpg";
    char dc260Exif[]     = "KodakDC260.jpg";
    char dc290Exif[]     = "Kodak_DC290.jpg";
    char dc4800Exif[]    = "Kodak_DC4800.jpg";
    char mc3Exif[]       = "Kodak_MC3.jpg";
    char palmpixExif[]   = "Kodak_Palmpix.jpg";
    char pictureCDExif[] = "Kodak_PictureCD.jpg";
    char comSeg[]        = "DCP_0433_com.JPG";
    char jfif[]          = "JFIF.jpg";

    if( ExifImageFile::isExifFile( dc220Exif ) != EXIF_OK )
    {
        cout << "Error: " << dc220Exif << " not determined to be an Exif file." << endl;
    }
    if( ExifImageFile::isExifFile( dc260Exif ) != EXIF_OK )
    {
        cout << "Error: " << dc260Exif << " not determined to be an Exif file." << endl;
    }
    if( ExifImageFile::isExifFile( dc290Exif ) != EXIF_OK )
    {
        cout << "Error: " << dc290Exif << " not determined to be an Exif file." << endl;
    }
    if( ExifImageFile::isExifFile( dc4800Exif ) != EXIF_OK )
    {
        cout << "Error: " << dc4800Exif << " not determined to be an Exif file." << endl;
    }
    if( ExifImageFile::isExifFile( mc3Exif ) != EXIF_OK )
    {
        cout << "Error: " << mc3Exif << " not determined to be an Exif file." << endl;
    }
    if( ExifImageFile::isExifFile( palmpixExif ) != EXIF_OK )
    {
        cout << "Error: " << palmpixExif << " not determined to be an Exif file." << endl;
    }
    if( ExifImageFile::isExifFile( pictureCDExif ) != EXIF_OK )
    {
        cout << "Error: " << pictureCDExif << " not determined to be an Exif file." << endl;
    }
    if( ExifImageFile::isExifFile( comSeg ) != EXIF_OK )
    {
        cout << "Error: " << comSeg << " not determined to be an Exif file." << endl;
    }
    if( ExifImageFile::isExifFile( jfif ) == EXIF_OK )
    {
        cout << "Error: " << jfif << " determined to be an Exif file." << endl;
    }

    ExifStatus status;
    ExifIO * exifio = ExifIO::open(status, dc220Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << dc220Exif << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << dc220Exif << " not determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;

    exifio = ExifIO::open(status, dc260Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << dc260Exif << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << dc260Exif << " not determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, dc290Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << dc290Exif << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << dc290Exif << " not determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, dc4800Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << dc4800Exif << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << dc4800Exif << " not determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, mc3Exif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << mc3Exif << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << mc3Exif << " not determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, palmpixExif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << palmpixExif << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << palmpixExif << " not determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, pictureCDExif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << pictureCDExif << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << pictureCDExif << " not determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, comSeg, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << comSeg << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) != EXIF_OK )
    {
        cout << "Error: " << comSeg << " not determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;


    exifio = ExifIO::open(status, jfif, "r");
    if ( status != EXIF_OK )
        cout << "Error: could not open " << jfif << " with ExifIO." << endl;    
    if( ExifImageFile::isExifFile( exifio ) == EXIF_OK )
    {
        cout << "Error: " << jfif << " determined to be an Exif file." << endl;
    }
    exifio->close();
    delete exifio;
}

// Used in testOpenVariousImages() to open and close the specified file
// in the specified mode using ExifImageFile.
void testExifImageFileOpen( char * inputFile, string mode )
{
    ExifImageFile inImageFile ;

    if ( inImageFile.open( inputFile, mode.c_str() ) != EXIF_OK)
    {
        cout << "Error: could not open " << inputFile << " with ExifImageFile." << endl;
        return;
    }

    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Could not close " << inputFile << endl;
    }
}

// Used in testOpenVariousImages() to open and close the specified file
// in the specified mode using ExifJpegImage.
void testExifJpegImageOpen( char * inputFile, string mode )
{
    ExifJpegImage inImageFile ;

    if ( inImageFile.open( inputFile, mode.c_str() ) == EXIF_ERROR)
    {
        cout << "Error: could not open " << inputFile << " with ExifJpegImage." << endl;
        return;
    }

    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << inputFile << endl;
    }
}

// Test opening and closing various images in various modes to make sure
// files do not get corrupted and that we handle all of them well.
void testOpenVariousImages()
{
    cout << "=============================================" << endl ;
    cout << "Trying to open images from various sources..." << endl ;
    cout << "=============================================" << endl ;

    char dc220Exif[]     = "Kodak_DC220.jpg";
    char dc260Exif[]     = "KodakDC260.jpg";
    char dc290Exif[]     = "Kodak_DC290.jpg";
    char dc4800Exif[]    = "Kodak_DC4800.jpg";
    char mc3Exif[]       = "Kodak_MC3.jpg";
    char palmpixExif[]   = "Kodak_Palmpix.jpg";
    char pictureCDExif[] = "Kodak_PictureCD.jpg";
    char comSeg[]        = "DCP_0433_com.JPG";
    char jfif[]          = "JFIF.jpg";
    
    char dc220Exif_copy[]     = "Kodak_DC220_copy.jpg";
    char dc260Exif_copy[]     = "KodakDC260_copy.jpg";
    char dc290Exif_copy[]     = "Kodak_DC290_copy.jpg";
    char dc4800Exif_copy[]    = "Kodak_DC4800_copy.jpg";
    char mc3Exif_copy[]       = "Kodak_MC3_copy.jpg";
    char palmpixExif_copy[]   = "Kodak_Palmpix_copy.jpg";
    char pictureCDExif_copy[] = "Kodak_PictureCD_copy.jpg";
    char comSeg_copy[]        = "DCP_0433_com_copy.JPG";
    char jfif_copy[]          = "JFIF_copy.jpg";

    ExifCopyFile( dc220Exif, dc220Exif_copy, true );
    ExifCopyFile( dc260Exif, dc260Exif_copy, true );
    ExifCopyFile( dc290Exif, dc290Exif_copy, true ); 
    ExifCopyFile( dc4800Exif, dc4800Exif_copy, true );
    ExifCopyFile( mc3Exif, mc3Exif_copy, true );
    ExifCopyFile( palmpixExif, palmpixExif_copy, true );
    ExifCopyFile( pictureCDExif, pictureCDExif_copy, true );
    ExifCopyFile( comSeg, comSeg_copy, true );
    ExifCopyFile( jfif, jfif_copy, true ); 


    //Open in readonly mode then close, open in readwrite mode then close, and
    //finally try to open again in readonly mode.
    const unsigned int modesTested = 4;
    string mode[modesTested];
    mode[0] = "r";
    mode[1] = "r+";
    mode[2] = "r";
    mode[3] = "r";

    for( unsigned int i = 0; i < modesTested; i++ )
    {
        testExifImageFileOpen( dc220Exif_copy, mode[i] );
        testExifImageFileOpen( dc260Exif_copy, mode[i] );
        testExifImageFileOpen( dc290Exif_copy, mode[i] ); 
        testExifImageFileOpen( dc4800Exif_copy, mode[i] ); 
        testExifImageFileOpen( mc3Exif_copy, mode[i] ); 
        testExifImageFileOpen( palmpixExif_copy, mode[i] );
        testExifImageFileOpen( pictureCDExif_copy, mode[i] );
        testExifImageFileOpen( comSeg_copy, mode[i] );
        testExifImageFileOpen( jfif_copy, mode[i] );
    
        testExifJpegImageOpen( dc220Exif_copy, mode[i] );
        testExifJpegImageOpen( dc260Exif_copy, mode[i] );
        testExifJpegImageOpen( dc290Exif_copy, mode[i] );
        testExifJpegImageOpen( dc4800Exif_copy, mode[i] ); 
        testExifJpegImageOpen( mc3Exif_copy, mode[i] );
        testExifJpegImageOpen( palmpixExif_copy, mode[i] );
        testExifJpegImageOpen( pictureCDExif_copy, mode[i] );
        testExifJpegImageOpen( comSeg_copy, mode[i] );
        testExifJpegImageOpen( jfif_copy, mode[i] );

  }
}

// Test the ExifImageFile::getImageInfo() method.
void testGetImageInfo()
{
    cout << "========================================" << endl ;
    cout << "Testing ExifImageFile::getImageInfo()..." << endl ;
    cout << "========================================" << endl ;

    char dc290Exif[]     = "Kodak_DC290.jpg";
    char dc4800Exif[]    = "Kodak_DC4800.jpg";

    ExifImageFile inImageFile ;

    if ( inImageFile.open( dc290Exif, "r" ) != EXIF_OK )
    {
        cout << "Error opening " << dc290Exif << " with ExifImageFile." << endl;
        return;
    }
    ExifImageInfo imageInfo;
    if ( inImageFile.getImageInfo(imageInfo) != EXIF_OK )
    {
        cout << "Error: unable to get image info from " << dc290Exif << endl;
    }
    else
    {
        cout << dc290Exif << ":" << endl;
        cout << "   width - " << imageInfo.width << endl;
        cout << "   height - " << imageInfo.height << endl;
        cout << "   numChannels - " << imageInfo.numChannels << endl;
        cout << "   precision - " << imageInfo.precision << endl;
        cout << "   colorSpace - " << imageInfo.colorSpace << endl;
    }
    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << dc290Exif << endl;
    }

    if ( inImageFile.open( dc4800Exif, "r" ) != EXIF_OK )
    {
        cout << "Error opening " << dc4800Exif << " with ExifImageFile." << endl;
        return;
    }

    if ( inImageFile.getImageInfo(imageInfo) != EXIF_OK )
    {
        cout << "Error: unable to get image info from " << dc4800Exif << endl;
    }
    else
    {
        cout << dc4800Exif << ":" << endl;
        cout << "   width - " << imageInfo.width << endl;
        cout << "   height - " << imageInfo.height << endl;
        cout << "   numChannels - " << imageInfo.numChannels << endl;
        cout << "   precision - " << imageInfo.precision << endl;
        cout << "   colorSpace - " << imageInfo.colorSpace << endl;
    }

    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: could not close " << dc4800Exif << endl;
    }
}

// Test opening an image file from memory.
void testOpenImageFromMemory()
{
    cout << "======================================" << endl ;
    cout << "Opening a ExifImageFile from memory..." << endl ;
    cout << "======================================" << endl ;
    
    const char * dc290Exif = "Kodak_DC290.jpg" ;
    ExifStatus status ;
    ExifIO* exifio = ExifIO::open( status, dc290Exif, "r" ) ;
    if ( exifio && status == EXIF_OK )
    {
        exif_uint32 size = exifio->ioHandler().size() ;
        uint8* inMemImage = new uint8[size] ;
        exifio->read( inMemImage, size ) ;
        
        ExifImageFile img ;
        if ( img.open( inMemImage, size, "r" ) != EXIF_OK )
        {
            cout << "Error opening image from memory in testOpenImageFromMemory"
                << endl ;
        }
        
        cout << "Tags found in the image: " << endl ;
        ExifPathsTags pathsTags ;
        img.getAllTags( 0xFFE1, "Exif", pathsTags ) ;
        ExifPathsTagsIter crntPathsTags = pathsTags.begin() ;
        ExifPathsTagsIter endPathsTags = pathsTags.end() ;
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
        
            while( crnt != end )
            {
                ExifTagEntry* tag = *(crnt) ;
                tag->print() ;
                cout << endl ;
                crnt++ ;
            }
            crntPathsTags++ ;
        }

        if ( img.close() != EXIF_OK )
        {
            cout << "Error: could not close in ExifImageFile in " <<
                "testOpenImageFromMemory()" << endl ;
        }
        
        delete[] inMemImage ;
        exifio->close() ;
        delete exifio ;
    }
    else
    {
        cout << "Error opening " << dc290Exif <<
            " in testOpenImageFromMemory()" << endl ;
    }
}

// Dump the info for all AppSegs in the file
void appSegDump( char * file )
{
    ExifImageFile inImageFile ;

    if ( inImageFile.open( file, "r" ) != EXIF_OK)
    {
        cout << "Error: could not open " << file << " with ExifImageFile." << endl;
        return;
    }

    vector<ExifAppSegment*> appSegs = inImageFile.getAllAppSegs();
    int numOfAppSegs = appSegs.size() ;
    
    cout << "Number of Application Segments in " << file << ": " << numOfAppSegs << endl ;
    cout << "Marker\tLength\tIdent" << endl;
    
    for ( int i = 0; i < numOfAppSegs; i++ )
    {
        cout << appSegs[i]->getAppSegmentMarker() << "\t";
        cout << appSegs[i]->getLength() << "\t";
        cout << appSegs[i]->getAppIdent() << endl;
    }


    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: Could not close " << file << endl;
    }   
}

// Test the ExifAppSegManager through calls to ExifImageFile.
void testAppSegManager()
{
    cout << "================================" << endl ;
    cout << "Testing the ExifAppSegManager..." << endl ;
    cout << "================================" << endl ;

    char dc220Exif[]     = "Kodak_DC220.jpg";
    char dc260Exif[]     = "KodakDC260.jpg";
    char dc290Exif[]     = "Kodak_DC290.jpg";
    char dc4800Exif[]    = "Kodak_DC4800.jpg";
    char mc3Exif[]       = "Kodak_MC3.jpg";
    char palmpixExif[]   = "Kodak_Palmpix.jpg";
    char pictureCDExif[] = "Kodak_PictureCD.jpg";
    char comSeg[]        = "DCP_0433_com.JPG";
    char jfif[]          = "JFIF.jpg";

    appSegDump( dc220Exif );
    appSegDump( dc260Exif );
    appSegDump( dc290Exif );
    appSegDump( dc4800Exif );
    appSegDump( mc3Exif );
    appSegDump( palmpixExif );
    appSegDump( pictureCDExif );
    appSegDump( comSeg );
    appSegDump( jfif );
}

// Test the App3 segment implementation
void testApp3Seg()
{
    cout << "==========================" << endl ;
    cout << "Testing the ExifApp3Seg..." << endl ;
    cout << "==========================" << endl ;

    char pictureCDExif[] = "Kodak_PictureCD.jpg";
    char comSeg[]        = "DCP_0433_com.JPG";
    
    // Create instance of ExifImageFile
    ExifImageFile inImageFile;
        
    // Open the file in read-only mode and verify that it succeeds
    if ( inImageFile.open( pictureCDExif, "r" ) == EXIF_OK)
    {
        cout << "App3 Entries in " << pictureCDExif << ":" << endl;
        // Get all the AppSeg 3 - "Meta" tags and output them
        ExifPathsTags pathsTags ;
        inImageFile.getAllTags( 0xFFE3, "Meta", pathsTags ) ;

        ExifPathsTagsIter crntPathsTags = pathsTags.begin() ;
        ExifPathsTagsIter endPathsTags = pathsTags.end() ;
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
        // Close the file
        if( inImageFile.close() != EXIF_OK )
        {
            cout << "Error: Could not close" << pictureCDExif << endl;
        }   
    }
    else
    {
        cout << "Error: could not open " << pictureCDExif <<
            " with ExifImageFile." << endl;
    }    
    
    // Open the file in read-only mode and verify that it succeeds
    if ( inImageFile.open( comSeg, "r" ) == EXIF_OK)
    {
        cout << "App3 Entries in " << comSeg << ":" << endl;
        // Get all the AppSeg 3 - "Meta" tags and output them
        ExifPathsTags pathsTags ;
        inImageFile.getAllTags( 0xFFE3, "Meta", pathsTags ) ;

        ExifPathsTagsIter crntPathsTags = pathsTags.begin() ;
        ExifPathsTagsIter endPathsTags = pathsTags.end() ;
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
        // Close the file
        if( inImageFile.close() != EXIF_OK )
        {
            cout << "Error: Could not close" << comSeg << endl;
        }   
    }
    else
    {
        cout << "Error: could not open " << comSeg <<
            " with ExifImageFile." << endl;
    }
}

void testGetHVSamplingFactors()
{
    cout << "======================================" << endl ;
    cout << "Test getting H and V sampling factors " << endl ;
    cout << "======================================" << endl ;

    char file[] = "KodakDC260.jpg";
     
    ExifImageFile inImageFile ;

    if ( inImageFile.open( file, "r" ) != EXIF_OK)
    {
        cout << "Error: could not open " << file << " with ExifImageFile." 
            << endl;

        return;
    }

    cout << "CompID\tH\tV" << endl;
    for (uint8 i = 0; i < 5; i++)
    {
        uint8 hFact = inImageFile.getHSamplingFactor(i);
        uint8 vFact = inImageFile.getVSamplingFactor(i);
        
        cout << (int)i << "\t" << (int)hFact << "\t" << (int)vFact <<endl;
    }
    
    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: Could not close " << file << endl;
    }      
    
}

void testRemoveMetadata()
{
    cout << "========================" << endl ;
    cout << "Testing removeMetdata() " << endl ;
    cout << "========================" << endl ;

    char file[] = "KodakDC260_copy.jpg";
     
    ExifImageFile inImageFile ;

    if ( inImageFile.open( file, "r+" ) != EXIF_OK)
    {
        cout << "Error: could not open " << file << " with ExifImageFile." 
            << endl;
        return;
    }
    
    ExifStatus status;
    ExifTagEntry* entry = new ExifTagEntryT<exif_uint32>(7777, EXIF_LONG, 1,
        1977);
    inImageFile.setGenericTag( *entry, EXIF_APP1_IFD0 );
    delete entry;

    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: Could not close " << file << endl;
        return;
    }
    
    if ( inImageFile.open( file, "r+" ) != EXIF_OK)
    {
        cout << "Error: could not open " << file << " with ExifImageFile." 
            << endl;
        return;
    }
    
    entry = inImageFile.getGenericTag(7777, EXIF_APP1_IFD0, status);
    if( entry==NULL )
    {
        cout << "Entry wasn't written to file correctly!!!" << endl;
        return;
    }
    
    inImageFile.removeGenericTag(7777, EXIF_APP1_IFD0);
    
    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: Could not close " << file << endl;
        return;
    }
    
    if ( inImageFile.open( file, "r" ) != EXIF_OK)
    {
        cout << "Error: could not open " << file << " with ExifImageFile." 
            << endl;
        return;
    }
    
    entry = inImageFile.getGenericTag(7777, EXIF_APP1_IFD0, status);
    if( entry!=NULL )
    {
        cout << "Entry wasn't removed from file correctly!!!" << endl;
        return;
    }
    
    if( inImageFile.close() != EXIF_OK )
    {
        cout << "Error: Could not close " << file << endl;
        return;
    } 
    
}

// Main
int main(int argc, char* argv[])
{
    //for ( int i = 0; i < 100; i++ )
    //{
#ifdef TEST_IN_MEMORY_EXIF
        testImageReadWriteInMemory();
#endif
        testOpenVariousImages();
        testImageReadWrite();
        testThumbnailRead();
        testDefaultMetadata();
        testMetadataReadWrite();

        testIsJpegFile();
        testIsExifFile();
        testGetImageInfo();
        
        testOpenImageFromMemory();
        
        testAppSegManager();
        
        testApp3Seg();
        
        testGetHVSamplingFactors();
        
        testRemoveMetadata();
        
        //cout << i << " " ;
    //}

    return 0;
}
