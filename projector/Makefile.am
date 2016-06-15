####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = projector
projector_SOURCES = ProjUtil.cpp ProjectorException.cpp Projector.cpp ProjectionParams.cpp Main.cpp 
projector_LDADD   = -lProjectionIO -lProjection -lgctpc -lImageLib -lgeotiff -ltiff -lProjectionMesh  -lMathLib -lMiscUtils

SUBDIRS = docs 

EXTRA_DIST = DRect.h Main.cpp ProjectionParams.cpp ProjectionParams.h Projector.cpp Projector.h ProjectorException.cpp ProjectorException.h ProjUtil.h ProjUtil.cpp 

####### kdevelop will overwrite this part!!! (end)############
bin_PROGRAMS = projector

# set the include path for X, qt and KDE
INCLUDES= $(all_includes) @TIFF_INC@ @GEOTIFF_INC@ @IMAGE_INC@ @PROJ_INC@ @PROJMESH_INC@ @PROJIO_INC@ @GCTPC_INC@ @MATH_INC@

# the library search path.
projector_LDFLAGS = $(all_libraries) @TIFF_LIB@ @GEOTIFF_LIB@ @IMAGE_LIB@ @PROJ_LIB@ @PROJMESH_LIB@ @PROJIO_LIB@ @GCTPC_LIB@ @MATH_LIB@
