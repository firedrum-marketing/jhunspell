#
# Source level Makefile for JHunspell.
#
# NOTE: Define DESTDIR if you are not installing JHunspell
#       to its final directories. This is meant for the
#       purpose of packaging.
#
MAKE_PATH = ../../../..
include $(MAKE_PATH)/Make.def

# JNI specifications
JNI_LIB_NAME    =	JHunspell
JNI_SRC_FILES   =	Hunspell.java

JNI_LINK_LIBS   =	$(HUNSPELL_LIBS)

INCLUDES        =	$(JAVA_INCLUDES) $(HUNSPELL_INCLUDES)

CLEAN_LIST	=	$(JNI_LIB) $(LIB_DIR)/.libs

include $(MAKE_PATH)/Make.rules

extra-install::
	$(INSTALL) -d $(DESTDIR)$(libdir)
	$(LIBTOOL) --mode=install $(INSTALL) $(JNI_LIB) $(DESTDIR)$(libdir)
