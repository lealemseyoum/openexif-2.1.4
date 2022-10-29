
# Store the source files into variables
set(OPENEXIF_JPEG_SRCS   	OpenExifJpeg/OpenExif_jcapimin.cpp  
                            OpenExifJpeg/OpenExif_jdapimin.cpp  
                            OpenExifJpeg/OpenExif_jdsample.cpp
                            OpenExifJpeg/OpenExif_jcapistd.cpp  
                            OpenExifJpeg/OpenExif_jdapistd.cpp  
                            OpenExifJpeg/OpenExif_jerror.cpp 
                            OpenExifJpeg/OpenExif_jccoefct.cpp  
                            OpenExifJpeg/OpenExif_jdatadst.cpp  
                            OpenExifJpeg/OpenExif_jfdctflt.cpp
                            OpenExifJpeg/OpenExif_jccolor.cpp   
                            OpenExifJpeg/OpenExif_jdatasrc.cpp  
                            OpenExifJpeg/OpenExif_jfdctfst.cpp
                            OpenExifJpeg/OpenExif_jcdctmgr.cpp
                            OpenExifJpeg/OpenExif_jdcoefct.cpp
                            OpenExifJpeg/OpenExif_jfdctint.cpp
                            OpenExifJpeg/OpenExif_jchuff.cpp
                            OpenExifJpeg/OpenExif_jdcolor.cpp
                            OpenExifJpeg/OpenExif_jidctflt.cpp
                            OpenExifJpeg/OpenExif_jcinit.cpp
                            OpenExifJpeg/OpenExif_jddctmgr.cpp
                            OpenExifJpeg/OpenExif_jidctfst.cpp
                            OpenExifJpeg/OpenExif_jcmainct.cpp
                            OpenExifJpeg/OpenExif_jdhuff.cpp
                            OpenExifJpeg/OpenExif_jidctint.cpp
                            OpenExifJpeg/OpenExif_jcmarker.cpp
                            OpenExifJpeg/OpenExif_jdinput.cpp
                            OpenExifJpeg/OpenExif_jidctred.cpp
                            OpenExifJpeg/OpenExif_jcmaster.cpp
                            OpenExifJpeg/OpenExif_jdmainct.cpp
                            OpenExifJpeg/OpenExif_jmemansi.cpp
                            OpenExifJpeg/OpenExif_jcomapi.cpp
                            OpenExifJpeg/OpenExif_jdmarker.cpp
                            OpenExifJpeg/OpenExif_jmemmgr.cpp
                            OpenExifJpeg/OpenExif_jcparam.cpp
                            OpenExifJpeg/OpenExif_jdmaster.cpp
                            OpenExifJpeg/OpenExif_jquant1.cpp
                            OpenExifJpeg/OpenExif_jcphuff.cpp
                            OpenExifJpeg/OpenExif_jdmerge.cpp
                            OpenExifJpeg/OpenExif_jquant2.cpp
                            OpenExifJpeg/OpenExif_jcprepct.cpp
                            OpenExifJpeg/OpenExif_jdphuff.cpp
                            OpenExifJpeg/OpenExif_jutils.cpp
                            OpenExifJpeg/OpenExif_jcsample.cpp
                            OpenExifJpeg/OpenExif_jdpostct.cpp)

set(OPENEXIF_SRCS           ExifApp0Seg.cpp
                            ExifAppSegManager.cpp
                            ExifAppSegment.cpp
                            ExifFileIO.cpp
                            ExifHuffmanTable.cpp
                            ExifIFD.cpp
                            ExifIJGWrapper.cpp
                            ExifIJGWriteFrame.cpp
                            ExifImageDescUtils.cpp
                            ExifImageFile.cpp
                            ExifImageFileRead.cpp
                            ExifImageFileWrite.cpp
                            ExifInternetIO.cpp
                            ExifIO.cpp
                            ExifJpegDataDst.cpp
                            ExifJpegDataSrc.cpp
                            ExifJpegImage.cpp
                            ExifMemoryIO.cpp
                            ExifMisc.cpp
                            ExifOpenFile.cpp
                            ExifRawAppSeg.cpp
                            ExifStripImage.cpp
                            ExifTiffAppSeg.cpp
                            ${OPENEXIF_JPEG_SRCS})

# Create library from sources
add_library(
    ${PROJECT_NAME} STATIC ${OPENEXIF_SRCS}
    )

# Specify where to find the header files at build and after installing
# Use generator expressions to avoid using source directory
target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/OpenExifJpeg/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/OpenExifJpeg>
) 

# Install targets
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    INCLUDES 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install header files or include directories
install(
    DIRECTORY ../src/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h*"
)

