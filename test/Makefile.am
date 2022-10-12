
AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = 	DCP_0433_com.JPG GroundTrue.txt JFIF.jpg \
		Kodak_DC220.jpg KodakDC260.jpg Kodak_DC290.jpg \
		Kodak_DC4800.jpg Kodak_MC3.jpg Kodak_Palmpix.jpg \
		Kodak_PictureCD.jpg
		   

TESTS_ENVIRONMENT 	= top_builddir=$(top_builddir)
TESTS			= exifTest

INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/OpenExifJpeg

noinst_PROGRAMS = exifTest

exifTest_SOURCES = test.cpp

exifTest_LDADD = $(top_srcdir)/src/libopenexif.la 

clean-compile:
	-rm -f $(OBJECTS)









