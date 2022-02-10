# Generated automatically from Makefile.in by configure.
########################################################## USING QT
##### If using Qt, uncomment these five lines
# GRAPH_FLAGS = -DUSEQT -DQT_THREAD_SUPPORT -I$(QTDIR)/include $(QUI_CFLAGS)
# GRAPH_LIBS = -L$(QTDIR)/lib $(QUI_LIBS) $(QT_LIB_EXTRAS)
# GRAPH_OBJS = $(GRAPH_OBJS_QT)
# GRAPH_SRC = $(GRAPH_SRC_QT)
# CCOMPILER = c++

##### Qt on UNIX/Linux: uncomment the next two lines:
ELECTRIC_TARGET = electric-target-unix
QT_LIB_EXTRAS = -lqt-mt -lX11

##### Qt on Macintosh: uncomment the next two lines (for Qt Evaluation, change "-lqt" to "-lqt-mt"):
# ELECTRIC_TARGET = electric-target-mac
# QT_LIB_EXTRAS = -prebind -framework Carbon -lqt -lz -framework Quicktime

##### Using ".ui" forms on Qt
QUI_LIBS = -lqui
QUI_CFLAGS = -DUSEQUI

########################################################### USING MOTIF
##### If using Motif (or OpenMotif/Lesstif), uncomment these five lines
GRAPH_FLAGS = 
GRAPH_LIBS = -lXm  -lXt  -lXext -lX11
GRAPH_OBJS = $(GRAPH_OBJS_XT)
GRAPH_SRC = $(GRAPH_SRC_XT)
CCOMPILER = gcc

##### For the general-purpose X facility, uncomment this line
XPOWER = -DANYDEPTH
##### For the alternate X facility, uncomment this line
# XPOWER =

##### For the T1lib TrueType, uncomment these two lines and set them to the proper location
# TRUETYPE_LIBS = /usr/local/lib/libt1.a
# TRUETYPECFLAGS = -DTRUETYPE -I/usr/local/include
###########################################################


########################################################### IRSIM SIMULATOR
##### If building with the IRSIM simulator, uncomment these three lines
# SIMIRSIM_OBJS = $(IRSIM_OBJS)
# SIMIRSIM_SRC = $(IRSIM_SRC)
# SIMIRSIM_CFLAGS = -DFORCEIRSIMTOOL $(FSDB_CFLAGS)

##### If building with the FSDB writer, uncomment these three lines
# FSDB_DIR = /usr/local/debussy/fsdb
# FSDB_LIBS += -L$(FSDB_DIR)/LINUX/ -lnffw
# FSDB_CFLAGS = -DFORCEFSDB -I$(FSDB_DIR)

###########################################################


########################################################### LISP INTERPRETER
##### If building with a LISP interpreter, uncomment these three lines
# LANGLISP_OBJS= $(ELK_OBJS)
# LANGLISP_SRC = $(ELK_SRC)
# LANGLISPCFLAGS = -DFORCELISP=1 -Isrc/elk
###########################################################


########################################################### TCL INTERPRETER
##### If building with a TCL interpreter, uncomment these two lines
# LANGTCLCFLAGS =  -DFORCETCL=1
# LANGTCLLIBS = -ltcl
###########################################################


########################################################### JAVA INTERPRETER
##### If building with a JAVA interpreter, uncomment this line and one of the following sets:
# LANGJAVACLASS = lib/java/COM/staticfreesoft.com/Electric.class lib/java/romgen.class

##### If building with a JAVA interpreter 1.3 on Linux, uncomment these four lines
# LANGJAVA_DIR = /usr/java/jdk1.3
# LANGJAVA_BIN = /usr/java/jdk1.3/bin
# LANGJAVACFLAGS = -DFORCEJAVA=1 -I$(LANGJAVA_DIR)/include -I$(LANGJAVA_DIR)/include/linux
# LANGJAVALIBS = -L$(LANGJAVA_DIR)/jre/lib/i386/classic -L$(LANGJAVA_DIR)/jre/lib/i386/native_threads -ljvm -lhpi

##### If building with a JAVA interpreter 1.4 on Linux, uncomment these four lines
# LANGJAVA_DIR = /usr/java/j2sdk1.4.1_01
# LANGJAVA_BIN = $(LANGJAVA_DIR)/bin
# LANGJAVACFLAGS = -DFORCEJAVA=1 -I$(LANGJAVA_DIR)/include -I$(LANGJAVA_DIR)/include/linux
# LANGJAVALIBS = -L$(LANGJAVA_DIR)/jre/lib/i386/client -ljvm

##### If building with a JAVA interpreter on Solaris, uncomment these four lines
# LANGJAVA_DIR = /usr/j2se
# LANGJAVA_BIN = /usr/j2se/bin
# LANGJAVACFLAGS = -DFORCEJAVA=1 -I$(LANGJAVA_DIR)/include -I$(LANGJAVA_DIR)/include/solaris
# LANGJAVALIBS = -L$(LANGJAVA_DIR)/jre/lib/sparc -L$(LANGJAVA_DIR)/jre/lib/sparc/native_threads -ljvm -lthread

##### If building with a JAVA interpreter on Macintosh OS 10, uncomment these four lines
# LANGJAVA_DIR = /System/Library/Frameworks/JavaVM.framework
# LANGJAVA_BIN = /usr/bin
# LANGJAVACFLAGS = -DFORCEJAVA=1 -I$(LANGJAVA_DIR)/Versions/1.3.1/Headers
# LANGJAVALIBS = $(LANGJAVA_DIR)/JavaVM /System/Library/Frameworks/Carbon.framework/Carbon
###########################################################


########################################################### ONLY AT SUN
##### If building with the Sun logical effort module, comment the next and uncomment the following two lines:
LETOOL = logeffort
# LETOOL = logeffortsun
# LETOOLJAVA = lib/java/COM/staticfreesoft.com/LogicalEffort.class

##### if building with Sun extras, uncomment these three lines
# SUN_OBJS = src/misc/logeffortsun2.o src/net/netanalyze.o src/misc/dbmirrortool.o src/tec/tecepic7s.o src/tec/tecziptronics.o
# SUN_SRC  = src/misc/logeffortsun2.cpp src/net/netanalyze.c src/misc/dbmirrortool.cpp src/tec/tecepic7s.c src/tec/tecziptronics.c
# SUNCFLAGS = -DFORCESUNTOOLS=1 -DEPROGRAMNAME="\"Son of Electric\""

##### If building with CADENCE SKILL module, uncomment these three lines
# CADENCE_OBJS = src/io/ioskillo.o
# CADENCE_SRC  = src/io/ioskillo.c
# CADENCECFLAGS = -DFORCECADENCE=1

##### if building with the database mirror tool, uncomment the next line:
# JARLOC = lib/java/dbmirror.jar
JAVA_MIRRORFILES = \
	ArcInst.java \
	ArcProto.java \
	Cell.java \
	ClassReloader.java \
	CmdLine.java \
	Connection.java \
	ELabel.java \
	Electric.java \
	ElectricObject.java \
	Export.java \
	Geometric.java \
	HierarchyEnumerator.java \
	InstPicker.java \
	JNetwork.java \
	JoseLogicalEffort.java \
	Layer.java \
	Library.java \
	NccOptions.java \
	Networkable.java \
	NodeInst.java \
	NodeProto.java \
	Notification.java \
	NotificationBoard.java \
	NotificationEvent.java \
	NotificationListener.java \
	Poly.java \
	PortFilter.java \
	PortInst.java \
	PortProto.java \
	PrimitiveNode.java \
	PrimitivePort.java \
	RectShape.java \
	SanityAnswer.java \
	ShapeProxy.java \
	SizeOffset.java \
	Slicer.java \
	Technology.java \
	Tool.java \
	VarCode.java \
	VarContext.java \
	View.java \
	WindowPart.java
JAVA_SRCS = $(JAVA_MIRRORFILES:%=src/java/com/sun/dbmirror/%)
JAVA_OBJS = $(JAVA_SRCS:%.java=%.class)
###########################################################


########################################################### MISCELLANEOUS EXTRAS
##### If building with Internationalization, uncomment this line
# INTERNATIONALCFLAGS = -DINTERNATIONAL

##### If building with Unicode text, uncomment this line
# UNICODECFLAGS = -D_UNICODE

##### If building with 64-bit integers on ULTRASparcII, uncomment this line
# ARCHFLAGS = -xtarget=ultra2 -xarch=v9a

##### If building with 64-bit integers on ULTRASparcIII, uncomment this line
# ARCHFLAGS = -xtarget=ultra3 -xarch=v9b

##### If using the Sun Forte C compiler, uncomment this line
# FORTECFLAGS = -compat

##### If optimizing, uncomment this line (modify optimizations to taste)
# OPTIMIZE = -O3

##### If debugging, uncomment this line (modify debug options to taste)
# DEBUG = -g3

##### This is the name of the executable
PROGNAME = electric

##### These are your compilers:
CPPCOMPILER = c++
JAVACOMPILER = $(LANGJAVA_BIN)/javac
JAVAFLAGS = -classpath src/java/:lib/java/bsh-1.2b3.jar
###########################################################


.KEEP_STATE:
.SCCS_GET:
.SUFFIXES:
.SUFFIXES: .c .cpp .o .java .class

# implicit rule for compilation
.c.o:
	$(CCOMPILER) $(CFLAGS) -c $< -o $@
.cpp.o:
	$(CPPCOMPILER) $(CFLAGS) -c $< -o $@
.java.class:
	$(JAVACOMPILER) $(JAVAFLAGS) $<

##### THE OBJECT MODULES:

CONS_OBJS = \
    src/cons/conlay.o \
    src/cons/conlin.o \
    src/cons/conlingtt.o \
    src/cons/conlinprs.o \
    src/cons/conlinttg.o \
    src/cons/contable.o

DB_OBJS = \
    src/db/aidtable.o \
    src/db/data.o \
    src/db/dbchange.o \
    src/db/dbcontour.o \
    src/db/dbcontrol.o \
    src/db/dbcreate.o \
    src/db/dberror.o \
    src/db/dbgeom.o \
    src/db/dblang.o \
    src/db/dblangelk.o \
    src/db/dblangjava.o \
    src/db/dblangtcl.o \
    src/db/dblibrary.o \
    src/db/dbmath.o \
    src/db/dbmemory.o \
    src/db/dbmerge.o \
    src/db/dbmult.o \
    src/db/dbnoproto.o \
    src/db/dbtech.o \
    src/db/dbtechi.o \
    src/db/dbtext.o \
    src/db/dbvars.o

DRC_OBJS = \
    src/drc/drc.o \
    src/drc/drcbatch.o \
    src/drc/drcflat.o \
    src/drc/drcquick.o

ELK_OBJS = \
    src/elk/elkautoload.o \
    src/elk/elkbignum.o \
    src/elk/elkbool.o \
    src/elk/elkchar.o \
    src/elk/elkcont.o \
    src/elk/elkcstring.o \
    src/elk/elkdebug.o \
    src/elk/elkdump.o \
    src/elk/elkenv.o \
    src/elk/elkerror.o \
    src/elk/elkexception.o \
    src/elk/elkfeature.o \
    src/elk/elkheap.o \
    src/elk/elkio.o \
    src/elk/elklist.o \
    src/elk/elkload.o \
    src/elk/elkmain.o \
    src/elk/elkmalloc.o \
    src/elk/elkmath.o \
    src/elk/elkonfork.o \
    src/elk/elkprim.o \
    src/elk/elkprint.o \
    src/elk/elkproc.o \
    src/elk/elkpromise.o \
    src/elk/elkread.o \
    src/elk/elkspecial.o \
    src/elk/elkstab.o \
    src/elk/elkstkmem.o \
    src/elk/elkstring.o \
    src/elk/elksymbol.o \
    src/elk/elkterminate.o \
    src/elk/elktype.o \
    src/elk/elkvector.o

GRAPH_OBJS_XT = \
    src/graph/graphcommon.o \
    src/graph/graphunixx11.o

GRAPH_OBJS_QT = \
    src/graph/graphcommon.o \
    src/graph/graphqt.o \
    src/graph/graphqtdlg.o \
    src/graph/graphqtdraw.o \
    src/graph/moc_graphqt.o \
    src/graph/moc_graphqtdlg.o

IO_OBJS = \
    src/io/io.o \
    src/io/iobinaryi.o \
    src/io/iobinaryo.o \
    src/io/iocifin.o \
    src/io/iocifout.o \
    src/io/iocifpars.o \
    src/io/iodefi.o \
    src/io/iodxf.o \
    src/io/ioecado.o \
    src/io/ioeagleo.o \
    src/io/ioedifi.o \
    src/io/ioedifo.o \
    src/io/iogdsi.o \
    src/io/iogdso.o \
    src/io/iohpglout.o \
    src/io/iolefi.o \
    src/io/iolefo.o \
    src/io/iolout.o \
    src/io/iopadso.o \
    src/io/iopsout.o \
    src/io/iopsoutcolor.o \
    src/io/iosdfi.o \
    src/io/iosuei.o \
    src/io/iotexti.o \
    src/io/iotexto.o \
    src/io/iovhdl.o

IRSIM_OBJS = src/irsim/irsimanalyzer.o \
    src/irsim/irsimbinsim.o \
    src/irsim/irsimconfig.o \
    src/irsim/irsimconn_list.o \
    src/irsim/irsimeval.o \
    src/irsim/irsimfaultsim.o \
    src/irsim/irsimhist.o \
    src/irsim/irsimhist_io.o \
    src/irsim/irsimincsim.o \
    src/irsim/irsimmem.o \
    src/irsim/irsimnetupdate.o \
    src/irsim/irsimnetwork.o \
    src/irsim/irsimnewrstep.o \
    src/irsim/irsimnsubrs.o \
    src/irsim/irsimparallel.o \
    src/irsim/irsimrsim.o \
    src/irsim/irsimsched.o \
    src/irsim/irsimsim.o \
    src/irsim/irsimsstep.o \
    src/irsim/irsimstack.o \
    src/irsim/irsimsubckt.o \
    src/irsim/irsimtpos.o

MISC_OBJS = \
    src/misc/compact.o \
    src/misc/compensate.o \
    src/misc/erc.o \
    src/misc/ercantenna.o \
    src/misc/$(LETOOL).o \
    src/misc/projecttool.o

NET_OBJS = \
    src/net/netdiff.o \
    src/net/netextract.o \
    src/net/netflat.o \
    src/net/network.o

PLA_OBJS = \
    src/pla/pla.o \
    src/pla/placdecode.o \
    src/pla/placio.o \
    src/pla/placngrid.o \
    src/pla/placpgrid.o \
    src/pla/placpla.o \
    src/pla/placutils.o \
    src/pla/planfacets.o \
    src/pla/planopt.o \
    src/pla/planprog1.o \
    src/pla/planprog2.o

ROUT_OBJS = \
    src/rout/rout.o \
    src/rout/routauto.o \
    src/rout/routmaze.o \
    src/rout/routmimic.o \
    src/rout/routriver.o

SC_OBJS = \
    src/sc/sc1.o \
    src/sc/sc1command.o \
    src/sc/sc1component.o \
    src/sc/sc1connect.o \
    src/sc/sc1delete.o \
    src/sc/sc1electric.o \
    src/sc/sc1err.o \
    src/sc/sc1extract.o \
    src/sc/sc1interface.o \
    src/sc/sc1maker.o \
    src/sc/sc1place.o \
    src/sc/sc1route.o \
    src/sc/sc1sim.o

SIM_OBJS = \
    src/sim/sim.o \
    src/sim/simals.o \
    src/sim/simalscom.o \
    src/sim/simalsflat.o \
    src/sim/simalsgraph.o \
    src/sim/simalssim.o \
    src/sim/simalsuser.o \
    src/sim/simfasthenry.o \
    src/sim/simirsim.o \
    src/sim/simmaxwell.o \
    src/sim/simmossim.o \
    src/sim/simpal.o \
    src/sim/simsilos.o \
    src/sim/simsim.o \
    src/sim/simspice.o \
    src/sim/simspicerun.o \
    src/sim/simtexsim.o \
    src/sim/simverilog.o \
    src/sim/simwindow.o
    
TEC_OBJS = \
    src/tec/tecart.o \
    src/tec/tecbicmos.o \
    src/tec/tecbipolar.o \
    src/tec/teccmos.o \
    src/tec/teccmosdodn.o \
    src/tec/tecefido.o \
    src/tec/tecfpga.o \
    src/tec/tecgem.o \
    src/tec/tecgen.o \
    src/tec/tecmocmos.o \
    src/tec/tecmocmosold.o \
    src/tec/tecmocmossub.o \
    src/tec/tecnmos.o \
    src/tec/tecpcb.o \
    src/tec/tecrcmos.o \
    src/tec/tecschem.o \
    src/tec/tectable.o

USR_OBJS = \
    src/usr/usr.o \
    src/usr/usrarc.o \
    src/usr/usrcheck.o \
    src/usr/usrcom.o \
    src/usr/usrcomab.o \
    src/usr/usrcomcd.o \
    src/usr/usrcomek.o \
    src/usr/usrcomln.o \
    src/usr/usrcomoq.o \
    src/usr/usrcomrs.o \
    src/usr/usrcomtv.o \
    src/usr/usrcomwz.o \
    src/usr/usrctech.o \
    src/usr/usrdiacom.o \
    src/usr/usrdiaedit.o \
    src/usr/usrdisp.o \
    src/usr/usreditemacs.o \
    src/usr/usreditpac.o \
    src/usr/usredtecc.o \
    src/usr/usredtecg.o \
    src/usr/usredtecp.o \
    src/usr/usrgraph.o \
    src/usr/usrhigh.o \
    src/usr/usrmenu.o \
    src/usr/usrmisc.o \
    src/usr/usrnet.o \
    src/usr/usrparse.o \
    src/usr/usrstatus.o \
    src/usr/usrterminal.o \
    src/usr/usrtrack.o \
    src/usr/usrtranslate.o \
    src/usr/usrwindow.o

VHDL_OBJS = \
    src/vhdl/vhdl.o \
    src/vhdl/vhdlexpr.o \
    src/vhdl/vhdlnetlisp.o \
    src/vhdl/vhdlparser.o \
    src/vhdl/vhdlals.o \
    src/vhdl/vhdlquisc.o \
    src/vhdl/vhdlsemantic.o \
    src/vhdl/vhdlsilos.o

EXTRA_OBJS = $(LANGLISP_OBJS) $(SIMIRSIM_OBJS) $(CADENCE_OBJS) $(SUN_OBJS)

CORE_OBJS = \
    $(CONS_OBJS) \
    $(DB_OBJS) \
    $(DRC_OBJS) \
    $(GRAPH_OBJS) \
    $(IO_OBJS) \
    $(MISC_OBJS) \
    $(NET_OBJS) \
    $(PLA_OBJS) \
    $(ROUT_OBJS) \
    $(SC_OBJS) \
    $(SIM_OBJS) \
    $(TEC_OBJS) \
    $(USR_OBJS) \
    $(VHDL_OBJS) \
    $(EXTRA_OBJS)

##### THE SOURCE MODULES:

CONS_SRC = \
    src/cons/conlay.cpp \
    src/cons/conlin.cpp \
    src/cons/conlingtt.cpp \
    src/cons/conlinprs.cpp \
    src/cons/conlinttg.cpp \
    src/cons/contable.cpp

DB_SRC = \
    src/db/aidtable.c \
    src/db/data.c \
    src/db/dbchange.c \
    src/db/dbcontour.c \
    src/db/dbcontrol.c \
    src/db/dbcreate.c \
    src/db/dberror.c \
    src/db/dbgeom.c \
    src/db/dblang.c \
    src/db/dblangelk.c \
    src/db/dblangjava.cpp \
    src/db/dblangtcl.c \
    src/db/dblibrary.c \
    src/db/dbmath.c \
    src/db/dbmemory.c \
    src/db/dbmerge.c \
    src/db/dbmult.c \
    src/db/dbnoproto.c \
    src/db/dbtech.c \
    src/db/dbtechi.c \
    src/db/dbtext.c \
    src/db/dbvars.c

DRC_SRC = \
    src/drc/drc.c \
    src/drc/drcbatch.c \
    src/drc/drcflat.cpp \
    src/drc/drcquick.c

ELK_SRC = \
    src/elk/elkautoload.c \
    src/elk/elkbignum.c \
    src/elk/elkbool.c \
    src/elk/elkchar.c \
    src/elk/elkcont.c \
    src/elk/elkcstring.c \
    src/elk/elkdebug.c \
    src/elk/elkdump.c \
    src/elk/elkenv.c \
    src/elk/elkerror.c \
    src/elk/elkexception.c \
    src/elk/elkfeature.c \
    src/elk/elkheap.c \
    src/elk/elkio.c \
    src/elk/elklist.c \
    src/elk/elkload.c \
    src/elk/elkmain.c \
    src/elk/elkmalloc.c \
    src/elk/elkmath.c \
    src/elk/elkonfork.c \
    src/elk/elkprim.c \
    src/elk/elkprint.c \
    src/elk/elkproc.c \
    src/elk/elkpromise.c \
    src/elk/elkread.c \
    src/elk/elkspecial.c \
    src/elk/elkstab.c \
    src/elk/elkstkmem.c \
    src/elk/elkstring.c \
    src/elk/elksymbol.c \
    src/elk/elkterminate.c \
    src/elk/elktype.c \
    src/elk/elkvector.c

GRAPH_SRC_XT = \
    src/graph/graphcommon.cpp \
    src/graph/graphunixx11.c

GRAPH_SRC_QT = \
    src/graph/graphcommon.cpp \
    src/graph/graphqt.cpp \
    src/graph/graphqtdlg.cpp \
    src/graph/graphqtdraw.cpp

GRAPH_SRC_OTHERS = \
    src/graph/graphpccode.cpp \
    src/graph/graphpc.cpp \
    src/graph/graphmac.c \
    src/graph/graphmacX.c

IO_SRC = \
    src/io/io.c \
    src/io/iobinaryi.c \
    src/io/iobinaryo.c \
    src/io/iocifin.c \
    src/io/iocifout.c \
    src/io/iocifpars.c \
    src/io/iodefi.c \
    src/io/iodxf.c \
    src/io/ioecado.c \
    src/io/ioeagleo.c \
    src/io/ioedifi.c \
    src/io/ioedifo.c \
    src/io/iogdsi.c \
    src/io/iogdso.c \
    src/io/iohpglout.c \
    src/io/iolefi.c \
    src/io/iolefo.c \
    src/io/iolout.c \
    src/io/iopadso.c \
    src/io/iopsout.cpp \
    src/io/iopsoutcolor.cpp \
    src/io/iosdfi.c \
    src/io/iosuei.c \
    src/io/iotexti.c \
    src/io/iotexto.c \
    src/io/iovhdl.c

IRSIM_SRC = src/irsim/irsimanalyzer.c \
    src/irsim/irsimbinsim.c \
    src/irsim/irsimconfig.c \
    src/irsim/irsimconn_list.c \
    src/irsim/irsimeval.c \
    src/irsim/irsimfaultsim.c \
    src/irsim/irsimhist.c \
    src/irsim/irsimhist_io.c \
    src/irsim/irsimincsim.c \
    src/irsim/irsimmem.c \
    src/irsim/irsimnetupdate.c \
    src/irsim/irsimnetwork.c \
    src/irsim/irsimnewrstep.c \
    src/irsim/irsimnsubrs.c \
    src/irsim/irsimparallel.c \
    src/irsim/irsimrsim.c \
    src/irsim/irsimsched.c \
    src/irsim/irsimsim.c \
    src/irsim/irsimsstep.c \
    src/irsim/irsimstack.c \
    src/irsim/irsimsubckt.c \
    src/irsim/irsimtpos.c

MISC_SRC = \
    src/misc/compact.c \
    src/misc/compensate.c \
    src/misc/erc.c \
    src/misc/ercantenna.c \
    src/misc/$(LETOOL).cpp \
    src/misc/projecttool.c

NET_SRC = \
    src/net/netdiff.cpp \
    src/net/netextract.c \
    src/net/netflat.c \
    src/net/network.cpp

PLA_SRC = \
    src/pla/pla.c \
    src/pla/placdecode.c \
    src/pla/placio.c \
    src/pla/placngrid.c \
    src/pla/placpgrid.c \
    src/pla/placpla.c \
    src/pla/placutils.c \
    src/pla/planfacets.c \
    src/pla/planopt.c \
    src/pla/planprog1.c \
    src/pla/planprog2.c

ROUT_SRC = \
    src/rout/rout.c \
    src/rout/routauto.c \
    src/rout/routmaze.c \
    src/rout/routmimic.c \
    src/rout/routriver.c

SC_SRC = \
    src/sc/sc1.c \
    src/sc/sc1command.c \
    src/sc/sc1component.c \
    src/sc/sc1connect.c \
    src/sc/sc1delete.c \
    src/sc/sc1electric.c \
    src/sc/sc1err.c \
    src/sc/sc1extract.c \
    src/sc/sc1interface.c \
    src/sc/sc1maker.c \
    src/sc/sc1place.c \
    src/sc/sc1route.c \
    src/sc/sc1sim.c

SIM_SRC = \
    src/sim/sim.cpp \
    src/sim/simals.c \
    src/sim/simalscom.c \
    src/sim/simalsflat.c \
    src/sim/simalsgraph.c \
    src/sim/simalssim.c \
    src/sim/simalsuser.c \
    src/sim/simfasthenry.cpp \
    src/sim/simirsim.c \
    src/sim/simmaxwell.c \
    src/sim/simmossim.c \
    src/sim/simpal.c \
    src/sim/simsilos.c \
    src/sim/simsim.cpp \
    src/sim/simspice.cpp \
    src/sim/simspicerun.cpp \
    src/sim/simtexsim.c \
    src/sim/simverilog.c \
    src/sim/simwindow.c

TEC_SRC = \
    src/tec/tecart.c \
    src/tec/tecbicmos.c \
    src/tec/tecbipolar.c \
    src/tec/teccmos.c \
    src/tec/teccmosdodn.c \
    src/tec/tecefido.c \
    src/tec/tecfpga.c \
    src/tec/tecgem.c \
    src/tec/tecgen.c \
    src/tec/tecmocmos.c \
    src/tec/tecmocmosold.c \
    src/tec/tecmocmossub.c \
    src/tec/tecnmos.c \
    src/tec/tecpcb.c \
    src/tec/tecrcmos.c \
    src/tec/tecschem.c \
    src/tec/tectable.c

USR_SRC = \
    src/usr/usr.c \
    src/usr/usrarc.c \
    src/usr/usrcheck.c \
    src/usr/usrcom.c \
    src/usr/usrcomab.c \
    src/usr/usrcomcd.c \
    src/usr/usrcomek.c \
    src/usr/usrcomln.c \
    src/usr/usrcomoq.c \
    src/usr/usrcomrs.c \
    src/usr/usrcomtv.c \
    src/usr/usrcomwz.c \
    src/usr/usrctech.c \
    src/usr/usrdiacom.cpp \
    src/usr/usrdiaedit.cpp \
    src/usr/usrdisp.c \
    src/usr/usreditemacs.c \
    src/usr/usreditpac.c \
    src/usr/usredtecc.c \
    src/usr/usredtecg.c \
    src/usr/usredtecp.c \
    src/usr/usrgraph.c \
    src/usr/usrhigh.c \
    src/usr/usrmenu.c \
    src/usr/usrmisc.c \
    src/usr/usrnet.c \
    src/usr/usrparse.c \
    src/usr/usrstatus.c \
    src/usr/usrterminal.c \
    src/usr/usrtrack.c \
    src/usr/usrtranslate.c \
    src/usr/usrwindow.c

VHDL_SRC = \
    src/vhdl/vhdl.c \
    src/vhdl/vhdlexpr.c \
    src/vhdl/vhdlnetlisp.c \
    src/vhdl/vhdlparser.c \
    src/vhdl/vhdlals.c \
    src/vhdl/vhdlquisc.c \
    src/vhdl/vhdlsemantic.c \
    src/vhdl/vhdlsilos.c

EXTRA_SRC = $(LANGLISP_SRC) $(SIMIRSIM_SRC) $(CADENCE_SRC) $(SUN_SRC)

CORE_SRC = \
    $(CONS_SRC) \
    $(DB_SRC) \
    $(DRC_SRC) \
    $(GRAPH_SRC) \
    $(IO_SRC) \
    $(MISC_SRC) \
    $(NET_SRC) \
    $(PLA_SRC) \
    $(ROUT_SRC) \
    $(SC_SRC) \
    $(SIM_SRC) \
    $(TEC_SRC) \
    $(USR_SRC) \
    $(VHDL_SRC) \
    $(EXTRA_SRC)

##### COMMANDS:

BUILDOPTS = $(DEBUG) $(ARCHFLAGS) 
BUILDDIR = obj
HDS = src/include
CFLAGS = $(OPTIMIZE) $(DEBUG) $(GRAPH_FLAGS) $(ARCHFLAGS) $(FORTECFLAGS) -I$(HDS) \
    $(LANGLISPCFLAGS) $(LANGTCLCFLAGS) $(LANGJAVACFLAGS) $(SIMIRSIM_CFLAGS) \
    $(CADENCECFLAGS) $(SUNCFLAGS) $(INTERNATIONALCFLAGS) $(UNICODECFLAGS) 
XCFLAGS = $(CFLAGS) $(XPOWER) $(TRUETYPECFLAGS) $(QT_CFLAGS)
LIBS =  -lSM -lICE  $(TRUETYPE_LIBS) $(FSDB_LIBS) $(GRAPH_LIBS) -lm  \
    $(LANGTCLLIBS) $(LANGJAVALIBS)  -lpthread
FIND = find
INSTALL = install
DESTDIR =
prefix = /usr/local
exec_prefix = ${prefix}

all: $(ELECTRIC_TARGET) $(JARLOC) $(LANGJAVACLASS) $(LETOOLJAVA)

# the target of the build (UNIX)
electric-target-unix: $(CORE_OBJS)
	$(CPPCOMPILER) $(BUILDOPTS) -o $(PROGNAME) $(CORE_OBJS) $(LIBS)

# the target of the build (Mac)
electric-target-mac: electric.app electric.app/Contents electric.app/Contents/MacOS \
    electric.app/Contents/Resources electric.app/Contents/Resources/electric.icns \
    electric.app/Contents/PkgInfo electric.app/Contents/Info.plist electric.app/Contents/MacOS/electric
electric.app:
	mkdir electric.app
electric.app/Contents:
	mkdir electric.app/Contents
electric.app/Contents/MacOS:
	mkdir electric.app/Contents/MacOS
electric.app/Contents/Resources:
	mkdir electric.app/Contents/Resources
electric.app/Contents/MacOS/electric: $(CORE_OBJS)
	$(CCOMPILER) $(BUILDOPTS) -o electric.app/Contents/MacOS/electric $(CORE_OBJS) $(LIBS)
electric.app/Contents/PkgInfo:
	@rm -f electric.app/Contents/PkgInfo
	echo "APPLElec" >electric.app/Contents/PkgInfo
electric.app/Contents/Info.plist:
	@rm -f electric.app/Contents/Info.plist
	cp src/graph/graphmac.plist electric.app/Contents/Info.plist
electric.app/Contents/Resources/electric.icns:
	cp src/graph/graphmac.icns electric.app/Contents/Resources/electric.icns

# for lint
lint: $(CORE_SRC)
	lint -v $(XCFLAGS) $(BUILDOPTS) $(CORE_SRC)

lclint: $(CORE_SRC)
	lclint \
        +posixlib \
        -mustfree \
        -branchstate \
        -globstate \
        -fixedformalarray \
        -shiftsigned \
        -compdef \
        -compmempass \
        -usereleased \
        -realcompare \
        -mayaliasunique \
        -misscase \
        -evalorder \
        -imptype \
        -castfcnptr \
        -uniondef \
        -aliasunique \
        +ignoresigns \
        +ignorequals \
        +charintliteral \
        +charindex \
        +longintegral \
        +matchanyintegral \
        +longunsignedintegral \
        -kepttrans \
        -temptrans \
        -ownedtrans \
        -freshtrans \
        -onlytrans \
        -statictrans \
        -observertrans \
        -dependenttrans \
        -unqualifiedtrans \
        -nullret \
        -nullstate \
        -nullpass \
        -booltype Boolean \
        $(XCFLAGS) $(BUILDOPTS) $(CORE_SRC)

# for internationalization
xgettext:
	xgettext --c++ --keyword=_ --keyword=N_ $(CORE_SRC) $(GRAPH_SRC_OTHERS) lib/evemenus.mac

clean:
	rm -f $(PROGNAME)
	rm -f src/cons/*.o
	rm -f src/db/*.o
	rm -f src/drc/*.o
	rm -f src/elk/*.o
	rm -f src/graph/*.o
	rm -f src/graph/moc_*.cpp
	rm -f src/io/*.o
	rm -f src/irsim/*.o
	rm -f src/misc/*.o
	rm -f src/net/*.o
	rm -f src/pla/*.o
	rm -f src/rout/*.o
	rm -f src/sc/*.o
	rm -f src/sim/*.o
	rm -f src/tec/*.o
	rm -f src/usr/*.o
	rm -f src/vhdl/*.o

distclean: clean
	rm -f Makefile config.cache config.log config.status
	rm -f $(HDS)/defines.h examples/samples.elib
	rm -f *~ "#"*"#"
	rm -f examples/*~ examples/"#"*"#"
	rm -f examples/pla/*~ examples/pla/"#"*"#"
	rm -f lib/*~ lib/"#"*"#"
	rm -f html/*~ html/"#"*"#"
	rm -f html/manual/*~ html/manual/"#"*"#"
	rm -f html/manual/text/*~ html/manual/text/"#"*"#"
	rm -f html/manual/images/*~ html/manual/images/"#"*"#"
	rm -f src/*~ src/"#"*"#"
	rm -f src/cons/*~ src/cons/"#"*"#"
	rm -f src/db/*~ src/db/"#"*"#"
	rm -f src/drc/*~ src/drc/"#"*"#"
	rm -f src/elk/*~ src/elk/"#"*"#"
	rm -f src/graph/*~ src/graph/"#"*"#"
	rm -f src/include/*~ src/include/"#"*"#"
	rm -f src/io/*~ src/io/"#"*"#"
	rm -f src/misc/*~ src/misc/"#"*"#"
	rm -f src/net/*~ src/net/"#"*"#"
	rm -f src/pla/*~ src/pla/"#"*"#"
	rm -f src/rout/*~ src/rout/"#"*"#"
	rm -f src/sc/*~ src/sc/"#"*"#"
	rm -f src/sim/*~ src/sim/"#"*"#"
	rm -f src/tec/*~ src/tec/"#"*"#"
	rm -f src/usr/*~ src/usr/"#"*"#"
	rm -f src/vhdl/*~ src/vhdl/"#"*"#"

install: all
	$(INSTALL) -d -m755 ${exec_prefix}/bin $(DESTDIR)${prefix}/share/electric/lib
	$(INSTALL) -m755 $(PROGNAME) $(DESTDIR)${exec_prefix}/bin/$(PROGNAME)
	$(INSTALL) -m644 lib/.cadrc $(DESTDIR)${prefix}/share/electric/lib
	@(cd lib ; \
	for d in `$(FIND) . -type d -print`; do \
	  $(INSTALL) -d -m755 $(DESTDIR)${prefix}/share/electric/lib/$$d ; \
	  (cd $$d ; \
	  for f in `$(FIND) . -type f -maxdepth 1 -print`; do \
	    $(INSTALL) -m644 $$f $(DESTDIR)${prefix}/share/electric/lib/$$d/$$f ; \
	  done ) ; \
	done ) ; 

install.html:
	$(INSTALL) -d -m755 $(DESTDIR)${prefix}/share/electric/doc/html
	@(cd html/manual ; \
	$(INSTALL) -m644 index.html $(DESTDIR)${prefix}/share/electric/doc/html ; \
	for d in `$(FIND) . -type d -print`; do \
	  $(INSTALL) -d -m755 $(DESTDIR)${prefix}/share/electric/doc/html/$$d ; \
	  (cd $$d ; \
	  for f in `$(FIND) . -type f -maxdepth 1 -print`; do \
	    $(INSTALL) -m644 $$f $(DESTDIR)${prefix}/share/electric/doc/html/$$d/$$f ; \
	  done ) ; \
	done ) ; 

$(prefix)/$(PROGNAME):
	mkdir $(prefix)/$(PROGNAME)
$(prefix)/$(PROGNAME)/lib:
	mkdir $(prefix)/$(PROGNAME)/lib

uninstall:
	rm -f ${exec_prefix}/bin/$(PROGNAME)
	rm -rf ${prefix}/share/electric/lib
	rm -rf ${prefix}/share/electric/doc

depend:
	grep '^\#[ ]*include' `ls -1 src/*/*.c src/*/*.cpp` | \
	grep -v '<' | \
	sed -e 's/:[^"]*"\([^"]*\)".*/: \1/' \
	    -e 's/^\(.*\)\.c: /\1.o: \1.c /' \
	    -e 's/^\(.*\)\.cpp: /\1.o: \1.cpp /' \
	    -e 's/ \([a-z0-9]*\)\.h/ \$$(HDS)\/\1.h/' | \
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
	        else rec = rec " " $$3 } END { print rec } ' | \
	sort > makedep

# special dependencies (manually generated)

$(HDS)/config.h: $(HDS)/defines.h
$(HDS)/global.h: $(HDS)/config.h
src/elk/elkkernel.h: src/elk/elkconfig.h src/elk/elkfuncproto.h \
	src/elk/elkparam.h src/elk/elkobject.h src/elk/elkintern.h \
	src/elk/elkextern.h src/elk/elkmisc.h src/elk/elkexception.h \
	src/elk/elkgc.h src/elk/elktype.h src/elk/elkstkmem.h \
	src/elk/elkcstring.h src/elk/elkcompat.h
src/graph/graphunixx11.o: src/graph/graphunixx11.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/eio.h $(HDS)/usrtrack.h $(HDS)/edialogs.h $(HDS)/config.h
	$(CCOMPILER) $(XCFLAGS) -c src/graph/graphunixx11.c -o $@

src/graph/graphqt.o: src/graph/graphqt.cpp $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/edialogs.h src/graph/graphqt.h $(HDS)/dblang.h
src/graph/graphqtdlg.o: src/graph/graphqtdlg.cpp $(HDS)/global.h src/graph/graphqtdlg.h $(HDS)/edialogs.h
src/graph/graphqtdraw.o: src/graph/graphqtdraw.cpp $(HDS)/global.h src/graph/graphqt.h $(HDS)/egraphics.h
src/graph/moc_graphqt.cpp: src/graph/graphqt.h $(HDS)/global.h
	moc src/graph/graphqt.h -o $@ 
src/graph/moc_graphqtdlg.cpp: src/graph/graphqtdlg.h $(HDS)/global.h
	moc src/graph/graphqtdlg.h -o $@ 
$(JARLOC): $(JAVA_OBJS)
	(cd src/java; jar -cf ../../$(JARLOC) com/sun/dbmirror/*.class)
lib/java/romgen.class: lib/java/romgen.java
	cd lib/java; $(JAVACOMPILER) romgen.java
lib/java/COM/staticfreesoft.com/Electric.class: lib/java/COM/staticfreesoft/Electric.java
	cd lib/java/COM/staticfreesoft; $(JAVACOMPILER) Electric.java
lib/java/COM/staticfreesoft.com/LogicalEffort.class: lib/java/COM/staticfreesoft/LogicalEffort.java
	cd lib/java/COM/staticfreesoft; $(JAVACOMPILER) LogicalEffort.java

# dependencies (automatically generated from "make depend")

src/cons/conlay.o: src/cons/conlay.cpp $(HDS)/global.h $(HDS)/conlay.h $(HDS)/database.h $(HDS)/usr.h
src/cons/conlin.o: src/cons/conlin.cpp $(HDS)/global.h $(HDS)/database.h $(HDS)/conlin.h
src/cons/conlingtt.o: src/cons/conlingtt.cpp $(HDS)/global.h $(HDS)/conlin.h
src/cons/conlinprs.o: src/cons/conlinprs.cpp $(HDS)/global.h $(HDS)/conlin.h
src/cons/conlinttg.o: src/cons/conlinttg.cpp $(HDS)/global.h $(HDS)/database.h $(HDS)/conlin.h
src/cons/contable.o: src/cons/contable.cpp $(HDS)/global.h $(HDS)/conlay.h $(HDS)/conlin.h
src/db/aidtable.o: src/db/aidtable.c $(HDS)/global.h $(HDS)/network.h $(HDS)/compact.h $(HDS)/compensate.h $(HDS)/drc.h $(HDS)/eio.h $(HDS)/logeffort.h $(HDS)/network.h $(HDS)/pla.h $(HDS)/rout.h $(HDS)/sc1.h $(HDS)/sim.h $(HDS)/usr.h $(HDS)/vhdl.h
src/db/data.o: src/db/data.c $(HDS)/global.h
src/db/dbchange.o: src/db/dbchange.c $(HDS)/global.h $(HDS)/database.h $(HDS)/edialogs.h $(HDS)/sim.h $(HDS)/usr.h
src/db/dbcontour.o: src/db/dbcontour.c $(HDS)/global.h $(HDS)/dbcontour.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/eio.h
src/db/dbcontrol.o: src/db/dbcontrol.c $(HDS)/global.h $(HDS)/database.h $(HDS)/tech.h $(HDS)/edialogs.h $(HDS)/usr.h
src/db/dbcreate.o: src/db/dbcreate.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/database.h
src/db/dberror.o: src/db/dberror.c $(HDS)/global.h $(HDS)/database.h $(HDS)/usr.h
src/db/dbgeom.o: src/db/dbgeom.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/tecart.h
src/db/dblang.o: src/db/dblang.c $(HDS)/global.h $(HDS)/database.h $(HDS)/dblang.h
src/db/dblangelk.o: src/db/dblangelk.c $(HDS)/config.h $(HDS)/global.h $(HDS)/dblang.h
src/db/dblangjava.o: src/db/dblangjava.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/dblang.h $(HDS)/usr.h
src/db/dblangmm.o: src/db/dblangmm.c $(HDS)/config.h $(HDS)/global.h $(HDS)/dblang.h
src/db/dblangtcl.o: src/db/dblangtcl.c $(HDS)/config.h $(HDS)/global.h $(HDS)/dblang.h $(HDS)/database.h
src/db/dblibrary.o: src/db/dblibrary.c $(HDS)/global.h $(HDS)/database.h $(HDS)/network.h
src/db/dbmath.o: src/db/dbmath.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/usr.h $(HDS)/drc.h
src/db/dbmemory.o: src/db/dbmemory.c $(HDS)/global.h $(HDS)/database.h
src/db/dbmerge.o: src/db/dbmerge.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/tecart.h $(HDS)/tecgen.h
src/db/dbmult.o: src/db/dbmult.c $(HDS)/global.h $(HDS)/database.h
src/db/dbnoproto.o: src/db/dbnoproto.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/network.h
src/db/dbtech.o: src/db/dbtech.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/tecschem.h $(HDS)/tecmocmos.h $(HDS)/drc.h $(HDS)/efunction.h
src/db/dbtechi.o: src/db/dbtechi.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecmocmos.h $(HDS)/efunction.h $(HDS)/usr.h
src/db/dbtext.o: src/db/dbtext.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/tecgen.h $(HDS)/network.h
src/db/dbvars.o: src/db/dbvars.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/erc.h $(HDS)/rout.h $(HDS)/network.h $(HDS)/logeffort.h $(HDS)/sim.h $(HDS)/simirsim.h $(HDS)/eio.h $(HDS)/tecart.h $(HDS)/tecmocmos.h $(HDS)/tecmocmossub.h $(HDS)/tecschem.h
src/drc/drc.o: src/drc/drc.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/drc.h $(HDS)/efunction.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/usrdiacom.h
src/drc/drcbatch.o: src/drc/drcbatch.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/drc.h $(HDS)/database.h $(HDS)/tech.h $(HDS)/egraphics.h $(HDS)/usr.h
src/drc/drcflat.o: src/drc/drcflat.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/drc.h $(HDS)/efunction.h $(HDS)/egraphics.h
src/drc/drcquick.o: src/drc/drcquick.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/drc.h $(HDS)/efunction.h $(HDS)/usr.h
src/elk/elkautoload.o: src/elk/elkautoload.c src/elk/elkkernel.h
src/elk/elkbignum.o: src/elk/elkbignum.c src/elk/elkkernel.h
src/elk/elkbool.o: src/elk/elkbool.c src/elk/elkkernel.h
src/elk/elkchar.o: src/elk/elkchar.c src/elk/elkkernel.h
src/elk/elkcont.o: src/elk/elkcont.c src/elk/elkkernel.h
src/elk/elkcstring.o: src/elk/elkcstring.c src/elk/elkkernel.h
src/elk/elkdebug.o: src/elk/elkdebug.c src/elk/elkkernel.h
src/elk/elkdump.o: src/elk/elkdump.c src/elk/elkkernel.h
src/elk/elkenv.o: src/elk/elkenv.c src/elk/elkkernel.h
src/elk/elkerror.o: src/elk/elkerror.c $(HDS)/global.h src/elk/elkkernel.h
src/elk/elkexception.o: src/elk/elkexception.c src/elk/elkkernel.h
src/elk/elkfeature.o: src/elk/elkfeature.c src/elk/elkkernel.h
src/elk/elkheap.o: src/elk/elkheap.c $(HDS)/global.h src/elk/elkkernel.h src/elk/elkheap-sc.c
src/elk/elkio.o: src/elk/elkio.c src/elk/elkkernel.h
src/elk/elklist.o: src/elk/elklist.c src/elk/elkkernel.h
src/elk/elkload.o: src/elk/elkload.c src/elk/elkkernel.h
src/elk/elkmain.o: src/elk/elkmain.c $(HDS)/global.h src/elk/elkkernel.h
src/elk/elkmalloc.o: src/elk/elkmalloc.c src/elk/elkkernel.h
src/elk/elkmath.o: src/elk/elkmath.c src/elk/elkkernel.h
src/elk/elkonfork.o: src/elk/elkonfork.c src/elk/elkkernel.h
src/elk/elkprim.o: src/elk/elkprim.c src/elk/elkkernel.h
src/elk/elkprint.o: src/elk/elkprint.c src/elk/elkkernel.h
src/elk/elkproc.o: src/elk/elkproc.c src/elk/elkkernel.h
src/elk/elkpromise.o: src/elk/elkpromise.c src/elk/elkkernel.h
src/elk/elkread.o: src/elk/elkread.c $(HDS)/global.h src/elk/elkkernel.h
src/elk/elkspecial.o: src/elk/elkspecial.c src/elk/elkkernel.h
src/elk/elkstab.o: src/elk/elkstab.c src/elk/elkkernel.h
src/elk/elkstkmem.o: src/elk/elkstkmem.c src/elk/elkkernel.h
src/elk/elkstring.o: src/elk/elkstring.c src/elk/elkkernel.h
src/elk/elksymbol.o: src/elk/elksymbol.c src/elk/elkkernel.h
src/elk/elkterminate.o: src/elk/elkterminate.c src/elk/elkkernel.h
src/elk/elktype.o: src/elk/elktype.c src/elk/elkkernel.h
src/elk/elkvector.o: src/elk/elkvector.c src/elk/elkkernel.h
src/graph/graphcommon.o: src/graph/graphcommon.cpp $(HDS)/global.h $(HDS)/edialogs.h $(HDS)/egraphics.h $(HDS)/usr.h
src/io/io.o: src/io/io.c $(HDS)/global.h $(HDS)/database.h $(HDS)/conlay.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/dbcontour.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/network.h $(HDS)/usredtec.h $(HDS)/edialogs.h $(HDS)/tecart.h $(HDS)/tecschem.h $(HDS)/tecgen.h $(HDS)/tecmocmos.h
src/io/iobinaryi.o: src/io/iobinaryi.c $(HDS)/global.h $(HDS)/database.h $(HDS)/eio.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/tecschem.h $(HDS)/tecmocmos.h $(HDS)/tecmocmossub.h $(HDS)/edialogs.h $(HDS)/usr.h
src/io/iobinaryo.o: src/io/iobinaryo.c $(HDS)/global.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/edialogs.h
src/io/iocifin.o: src/io/iocifin.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/iocifpars.h $(HDS)/edialogs.h
src/io/iocifout.o: src/io/iocifout.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/tecgen.h $(HDS)/edialogs.h $(HDS)/efunction.h
src/io/iocifpars.o: src/io/iocifpars.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h $(HDS)/iocifpars.h $(HDS)/edialogs.h
src/io/iodefi.o: src/io/iodefi.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/iolefdef.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/eio.h $(HDS)/usr.h
src/io/iodxf.o: src/io/iodxf.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/database.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/edialogs.h
src/io/ioecado.o: src/io/ioecado.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h
src/io/ioeagleo.o: src/io/ioeagleo.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h
src/io/ioedifi.o: src/io/ioedifi.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/database.h $(HDS)/edialogs.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/tecschem.h $(HDS)/eio.h $(HDS)/network.h $(HDS)/usr.h
src/io/ioedifo.o: src/io/ioedifo.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/eio.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/network.h $(HDS)/usr.h $(HDS)/edialogs.h
src/io/iogdsi.o: src/io/iogdsi.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/database.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/iogdsi.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/edialogs.h
src/io/iogdso.o: src/io/iogdso.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/dbcontour.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/edialogs.h
src/io/iohpglout.o: src/io/iohpglout.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/eio.h
src/io/iolefi.o: src/io/iolefi.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/iolefdef.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/eio.h $(HDS)/usr.h
src/io/iolefo.o: src/io/iolefo.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/efunction.h
src/io/iolout.o: src/io/iolout.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h $(HDS)/efunction.h
src/io/iopadso.o: src/io/iopadso.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h
src/io/iopsout.o: src/io/iopsout.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/edialogs.h
src/io/iopsoutcolor.o: src/io/iopsoutcolor.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/eio.h $(HDS)/usr.h
src/io/ioquickdraw.o: src/io/ioquickdraw.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/efunction.h
src/io/iosdfi.o: src/io/iosdfi.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/database.h $(HDS)/edialogs.h $(HDS)/eio.h $(HDS)/usr.h
src/io/ioskillo.o: src/io/ioskillo.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/efunction.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/edialogs.h $(HDS)/egraphics.h
src/io/iosuei.o: src/io/iosuei.c $(HDS)/global.h $(HDS)/edialogs.h $(HDS)/egraphics.h $(HDS)/eio.h $(HDS)/tech.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/network.h $(HDS)/usr.h
src/io/iotexti.o: src/io/iotexti.c $(HDS)/global.h $(HDS)/database.h $(HDS)/eio.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/tecmocmos.h $(HDS)/tecmocmossub.h $(HDS)/edialogs.h
src/io/iotexto.o: src/io/iotexto.c $(HDS)/global.h $(HDS)/eio.h
src/io/iovhdl.o: src/io/iovhdl.c $(HDS)/config.h $(HDS)/global.h $(HDS)/eio.h $(HDS)/edialogs.h
src/irsim/irsimanalyzer.o: src/irsim/irsimanalyzer.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/simirsim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h $(HDS)/usr.h $(HDS)/network.h
src/irsim/irsimbinsim.o: src/irsim/irsimbinsim.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimnet_macros.h
src/irsim/irsimconfig.o: src/irsim/irsimconfig.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimconn_list.o: src/irsim/irsimconn_list.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimnet_macros.h
src/irsim/irsimeval.o: src/irsim/irsimeval.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimfaultsim.o: src/irsim/irsimfaultsim.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimnet_macros.h
src/irsim/irsimhist.o: src/irsim/irsimhist.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimhist_io.o: src/irsim/irsimhist_io.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimincsim.o: src/irsim/irsimincsim.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimmem.o: src/irsim/irsimmem.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimnetupdate.o: src/irsim/irsimnetupdate.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimnet_macros.h
src/irsim/irsimnetwork.o: src/irsim/irsimnetwork.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimnewrstep.o: src/irsim/irsimnewrstep.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimspiketbl.h
src/irsim/irsimnsubrs.o: src/irsim/irsimnsubrs.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimparallel.o: src/irsim/irsimparallel.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimnet_macros.h
src/irsim/irsimrsim.o: src/irsim/irsimrsim.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimnet_macros.h
src/irsim/irsimsched.o: src/irsim/irsimsched.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/irsim/irsimsim.o: src/irsim/irsimsim.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimnet_macros.h
src/irsim/irsimsstep.o: src/irsim/irsimsstep.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimstables.h
src/irsim/irsimstack.o: src/irsim/irsimstack.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimnet_macros.h
src/irsim/irsimsubckt.o: src/irsim/irsimsubckt.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h src/irsim/irsimsubckt.h
src/irsim/irsimtpos.o: src/irsim/irsimtpos.c $(HDS)/config.h $(HDS)/global.h src/irsim/irsimnet.h src/irsim/irsimglobals.h
src/misc/compact.o: src/misc/compact.c $(HDS)/config.h $(HDS)/global.h $(HDS)/compact.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/conlay.h
src/misc/compensate.o: src/misc/compensate.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/dbcontour.h $(HDS)/edialogs.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/usr.h $(HDS)/compensate.h
src/misc/dbmirrortool.o: src/misc/dbmirrortool.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/usr.h $(HDS)/dbmirrortool.h
src/misc/erc.o: src/misc/erc.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/erc.h $(HDS)/usr.h $(HDS)/edialogs.h
src/misc/ercantenna.o: src/misc/ercantenna.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/erc.h
src/misc/logeffort.o: src/misc/logeffort.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/logeffort.h $(HDS)/network.h $(HDS)/usr.h
src/misc/logeffortsun.o: src/misc/logeffortsun.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/database.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/logeffort.h $(HDS)/network.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/tecschem.h $(HDS)/dblang.h
src/misc/logeffortsun2.o: src/misc/logeffortsun2.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h
src/misc/projecttool.o: src/misc/projecttool.c $(HDS)/config.h $(HDS)/global.h $(HDS)/projecttool.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/usrdiacom.h $(HDS)/tecgen.h
src/net/netanalyze.o: src/net/netanalyze.c $(HDS)/config.h $(HDS)/global.h $(HDS)/network.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/tecschem.h $(HDS)/usr.h
src/net/netdiff.o: src/net/netdiff.cpp $(HDS)/global.h $(HDS)/network.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/tecschem.h $(HDS)/usr.h
src/net/netextract.o: src/net/netextract.c $(HDS)/global.h $(HDS)/network.h $(HDS)/efunction.h $(HDS)/usr.h $(HDS)/tecgen.h
src/net/netflat.o: src/net/netflat.c $(HDS)/network.h $(HDS)/global.h $(HDS)/network.h $(HDS)/efunction.h $(HDS)/tecschem.h
src/net/network.o: src/net/network.cpp $(HDS)/global.h $(HDS)/network.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/sim.h $(HDS)/tecschem.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/usrdiacom.h
src/pla/pla.o: src/pla/pla.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/planmos.h
src/pla/placdecode.o: src/pla/placdecode.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/placmos.h
src/pla/placio.o: src/pla/placio.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/placmos.h
src/pla/placngrid.o: src/pla/placngrid.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/placmos.h
src/pla/placpgrid.o: src/pla/placpgrid.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/placmos.h
src/pla/placpla.o: src/pla/placpla.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/placmos.h
src/pla/placutils.o: src/pla/placutils.c $(HDS)/config.h $(HDS)/global.h $(HDS)/placmos.h $(HDS)/pla.h $(HDS)/tecgen.h $(HDS)/usr.h
src/pla/planfacets.o: src/pla/planfacets.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/planmos.h
src/pla/planopt.o: src/pla/planopt.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/planmos.h
src/pla/planprog1.o: src/pla/planprog1.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/planmos.h
src/pla/planprog2.o: src/pla/planprog2.c $(HDS)/config.h $(HDS)/global.h $(HDS)/pla.h $(HDS)/planmos.h
src/rout/rout.o: src/rout/rout.c $(HDS)/config.h $(HDS)/global.h $(HDS)/rout.h $(HDS)/usr.h $(HDS)/tecschem.h $(HDS)/tecgen.h $(HDS)/edialogs.h $(HDS)/efunction.h
src/rout/routauto.o: src/rout/routauto.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/tecgen.h $(HDS)/rout.h $(HDS)/usr.h
src/rout/routmaze.o: src/rout/routmaze.c $(HDS)/config.h $(HDS)/global.h $(HDS)/database.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/tecgen.h $(HDS)/rout.h
src/rout/routmimic.o: src/rout/routmimic.c $(HDS)/config.h $(HDS)/global.h $(HDS)/rout.h $(HDS)/usr.h $(HDS)/edialogs.h
src/rout/routriver.o: src/rout/routriver.c $(HDS)/config.h $(HDS)/global.h $(HDS)/rout.h $(HDS)/tecgen.h
src/sc/sc1.o: src/sc/sc1.c $(HDS)/config.h $(HDS)/global.h $(HDS)/usrdiacom.h $(HDS)/sc1.h $(HDS)/sim.h
src/sc/sc1command.o: src/sc/sc1command.c $(HDS)/config.h $(HDS)/global.h
src/sc/sc1component.o: src/sc/sc1component.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sc/sc1connect.o: src/sc/sc1connect.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sc/sc1delete.o: src/sc/sc1delete.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sc/sc1electric.o: src/sc/sc1electric.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/sc1.h $(HDS)/usr.h
src/sc/sc1err.o: src/sc/sc1err.c $(HDS)/config.h $(HDS)/global.h
src/sc/sc1extract.o: src/sc/sc1extract.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sc/sc1interface.o: src/sc/sc1interface.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sc/sc1maker.o: src/sc/sc1maker.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sc/sc1place.o: src/sc/sc1place.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sc/sc1route.o: src/sc/sc1route.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sc/sc1sim.o: src/sc/sc1sim.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sc1.h
src/sim/sim.o: src/sim/sim.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/sim.h $(HDS)/simals.h $(HDS)/simirsim.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/usr.h
src/sim/simals.o: src/sim/simals.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/simals.h
src/sim/simalscom.o: src/sim/simalscom.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/simals.h $(HDS)/usrdiacom.h
src/sim/simalsflat.o: src/sim/simalsflat.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/simals.h
src/sim/simalsgraph.o: src/sim/simalsgraph.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/simals.h $(HDS)/usr.h $(HDS)/network.h $(HDS)/edialogs.h
src/sim/simalssim.o: src/sim/simalssim.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/simals.h
src/sim/simalsuser.o: src/sim/simalsuser.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/simals.h
src/sim/simfasthenry.o: src/sim/simfasthenry.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/usr.h $(HDS)/edialogs.h
src/sim/simirsim.o: src/sim/simirsim.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/simirsim.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/network.h $(HDS)/usr.h $(HDS)/tecschem.h
src/sim/simmaxwell.o: src/sim/simmaxwell.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/sim.h $(HDS)/usr.h
src/sim/simmossim.o: src/sim/simmossim.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/sim.h $(HDS)/tecschem.h
src/sim/simpal.o: src/sim/simpal.c $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/efunction.h $(HDS)/network.h
src/sim/simsilos.o: src/sim/simsilos.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/sim.h $(HDS)/usr.h $(HDS)/tecschem.h
src/sim/simsim.o: src/sim/simsim.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/efunction.h $(HDS)/usr.h $(HDS)/tecschem.h
src/sim/simspice.o: src/sim/simspice.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/eio.h $(HDS)/usr.h $(HDS)/network.h $(HDS)/efunction.h $(HDS)/tecgen.h $(HDS)/tecschem.h
src/sim/simspicerun.o: src/sim/simspicerun.cpp $(HDS)/config.h $(HDS)/global.h $(HDS)/sim.h $(HDS)/efunction.h $(HDS)/usr.h $(HDS)/edialogs.h
src/sim/simtexsim.o: src/sim/simtexsim.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/sim.h $(HDS)/tecschem.h
src/sim/simverilog.o: src/sim/simverilog.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/sim.h $(HDS)/network.h $(HDS)/usr.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/edialogs.h
src/sim/simwindow.o: src/sim/simwindow.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/efunction.h $(HDS)/network.h $(HDS)/sim.h $(HDS)/simals.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/tecart.h $(HDS)/usr.h $(HDS)/usrtrack.h
src/tec/tecart.o: src/tec/tecart.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecart.h $(HDS)/efunction.h
src/tec/tecbicmos.o: src/tec/tecbicmos.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/efunction.h
src/tec/tecbipolar.o: src/tec/tecbipolar.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/efunction.h
src/tec/teccmos.o: src/tec/teccmos.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/efunction.h
src/tec/teccmosdodn.o: src/tec/teccmosdodn.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/teccmosdodn.h $(HDS)/efunction.h
src/tec/tecefido.o: src/tec/tecefido.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/efunction.h
src/tec/tecfpga.o: src/tec/tecfpga.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecfpga.h $(HDS)/tecgen.h $(HDS)/efunction.h $(HDS)/usr.h $(HDS)/edialogs.h $(HDS)/network.h
src/tec/tecgem.o: src/tec/tecgem.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecgem.h $(HDS)/efunction.h
src/tec/tecgen.o: src/tec/tecgen.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/efunction.h $(HDS)/tecgen.h $(HDS)/tecart.h
src/tec/tecmocmos.o: src/tec/tecmocmos.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecmocmos.h $(HDS)/efunction.h $(HDS)/drc.h
src/tec/tecmocmosold.o: src/tec/tecmocmosold.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecmocmosold.h $(HDS)/efunction.h
src/tec/tecmocmossub.o: src/tec/tecmocmossub.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/drc.h $(HDS)/tecmocmossub.h $(HDS)/efunction.h
src/tec/tecmocmos2.o: src/tec/tecmocmos2.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/efunction.h
src/tec/tecnmos.o: src/tec/tecnmos.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/efunction.h
src/tec/tecpcb.o: src/tec/tecpcb.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/efunction.h
src/tec/tecrcmos.o: src/tec/tecrcmos.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecrcmos.h $(HDS)/efunction.h
src/tec/tecschem.o: src/tec/tecschem.c $(HDS)/global.h $(HDS)/database.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecschem.h $(HDS)/efunction.h $(HDS)/usr.h $(HDS)/network.h
src/tec/tectable.o: src/tec/tectable.c $(HDS)/global.h $(HDS)/tecart.h $(HDS)/teccmosdodn.h $(HDS)/tecgem.h $(HDS)/tecgen.h $(HDS)/tecmocmos.h $(HDS)/tecmocmosold.h $(HDS)/tecmocmossub.h $(HDS)/tecrcmos.h $(HDS)/tecschem.h $(HDS)/tecfpga.h
src/tec/tecziptronics.o: src/tec/tecziptronics.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h  $(HDS)/efunction.h
src/tec/tecepic7s.o: src/tec/tecepic7s.c $(HDS)/config.h $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/tech.h  $(HDS)/efunction.h
src/usr/usr.o: src/usr/usr.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/tech.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/usrdiacom.h $(HDS)/sim.h $(HDS)/tecgen.h $(HDS)/tecschem.h
src/usr/usrarc.o: src/usr/usrarc.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/efunction.h $(HDS)/tecschem.h $(HDS)/tecgen.h
src/usr/usrcheck.o: src/usr/usrcheck.c $(HDS)/global.h $(HDS)/database.h $(HDS)/efunction.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/usr.h $(HDS)/network.h $(HDS)/sim.h
src/usr/usrcom.o: src/usr/usrcom.c $(HDS)/global.h $(HDS)/efunction.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/usredtec.h $(HDS)/tecart.h
src/usr/usrcomab.o: src/usr/usrcomab.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/usrtrack.h
src/usr/usrcomcd.o: src/usr/usrcomcd.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/database.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/tecschem.h $(HDS)/efunction.h $(HDS)/usrdiacom.h
src/usr/usrcomek.o: src/usr/usrcomek.c $(HDS)/global.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/usrdiacom.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/sim.h $(HDS)/network.h
src/usr/usrcomln.o: src/usr/usrcomln.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/conlay.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/sim.h
src/usr/usrcomoq.o: src/usr/usrcomoq.c $(HDS)/global.h $(HDS)/usr.h $(HDS)/egraphics.h $(HDS)/sim.h
src/usr/usrcomrs.o: src/usr/usrcomrs.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/efunction.h $(HDS)/conlay.h $(HDS)/tecgen.h $(HDS)/usrdiacom.h
src/usr/usrcomtv.o: src/usr/usrcomtv.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/tecgen.h $(HDS)/efunction.h
src/usr/usrcomwz.o: src/usr/usrcomwz.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/efunction.h
src/usr/usrctech.o: src/usr/usrctech.c $(HDS)/global.h $(HDS)/efunction.h $(HDS)/egraphics.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/usredtec.h
src/usr/usrdiacom.o: src/usr/usrdiacom.cpp $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/network.h $(HDS)/usrdiacom.h $(HDS)/usrtrack.h $(HDS)/efunction.h $(HDS)/tecart.h $(HDS)/tecschem.h $(HDS)/tecgen.h $(HDS)/tecmocmos.h $(HDS)/tecmocmossub.h $(HDS)/usredtec.h $(HDS)/eio.h $(HDS)/sim.h $(HDS)/edialogs.h $(HDS)/conlay.h
src/usr/usrdiaedit.o: src/usr/usrdiaedit.cpp $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/usrtrack.h
src/usr/usrdisp.o: src/usr/usrdisp.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/tech.h $(HDS)/tecgen.h
src/usr/usreditemacs.o: src/usr/usreditemacs.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/usreditemacs.h
src/usr/usreditpac.o: src/usr/usreditpac.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/usreditpac.h $(HDS)/usrtrack.h $(HDS)/edialogs.h
src/usr/usredtecc.o: src/usr/usredtecc.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/usredtec.h $(HDS)/usrdiacom.h
src/usr/usredtecg.o: src/usr/usredtecg.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/usredtec.h
src/usr/usredtecp.o: src/usr/usredtecp.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/usredtec.h
src/usr/usrgraph.o: src/usr/usrgraph.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/tecgen.h $(HDS)/tecart.h
src/usr/usrhigh.o: src/usr/usrhigh.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecart.h
src/usr/usrmenu.o: src/usr/usrmenu.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/efunction.h $(HDS)/tecart.h $(HDS)/tecschem.h
src/usr/usrmisc.o: src/usr/usrmisc.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/usreditemacs.h $(HDS)/usreditpac.h $(HDS)/usrtrack.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/sim.h
src/usr/usrnet.o: src/usr/usrnet.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/usrdiacom.h $(HDS)/database.h $(HDS)/conlay.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/tech.h $(HDS)/tecgen.h $(HDS)/tecart.h $(HDS)/tecschem.h $(HDS)/sim.h
src/usr/usrparse.o: src/usr/usrparse.c $(HDS)/global.h $(HDS)/usr.h $(HDS)/usrdiacom.h $(HDS)/edialogs.h
src/usr/usrstatus.o: src/usr/usrstatus.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/drc.h $(HDS)/network.h $(HDS)/efunction.h $(HDS)/edialogs.h $(HDS)/tecgen.h $(HDS)/tecschem.h $(HDS)/usrdiacom.h
src/usr/usrterminal.o: src/usr/usrterminal.c $(HDS)/global.h $(HDS)/usr.h $(HDS)/edialogs.h
src/usr/usrtrack.o: src/usr/usrtrack.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/efunction.h $(HDS)/tecart.h $(HDS)/tecgen.h $(HDS)/sim.h
src/usr/usrtranslate.o: src/usr/usrtranslate.c $(HDS)/global.h $(HDS)/edialogs.h $(HDS)/usr.h $(HDS)/usrdiacom.h
src/usr/usrwindow.o: src/usr/usrwindow.c $(HDS)/global.h $(HDS)/egraphics.h $(HDS)/efunction.h $(HDS)/usr.h $(HDS)/usrtrack.h $(HDS)/tecgen.h
src/vhdl/vhdl.o: src/vhdl/vhdl.c $(HDS)/config.h $(HDS)/global.h $(HDS)/efunction.h $(HDS)/vhdl.h $(HDS)/sim.h $(HDS)/eio.h $(HDS)/network.h $(HDS)/tecschem.h $(HDS)/edialogs.h
src/vhdl/vhdlals.o: src/vhdl/vhdlals.c $(HDS)/config.h $(HDS)/global.h $(HDS)/vhdl.h $(HDS)/usr.h
src/vhdl/vhdlexpr.o: src/vhdl/vhdlexpr.c $(HDS)/config.h $(HDS)/global.h $(HDS)/vhdl.h
src/vhdl/vhdlnetlisp.o: src/vhdl/vhdlnetlisp.c $(HDS)/config.h $(HDS)/global.h $(HDS)/vhdl.h $(HDS)/usr.h
src/vhdl/vhdlparser.o: src/vhdl/vhdlparser.c $(HDS)/config.h $(HDS)/global.h $(HDS)/vhdl.h
src/vhdl/vhdlquisc.o: src/vhdl/vhdlquisc.c $(HDS)/config.h $(HDS)/global.h $(HDS)/vhdl.h $(HDS)/sc1.h $(HDS)/usr.h
src/vhdl/vhdlsemantic.o: src/vhdl/vhdlsemantic.c $(HDS)/config.h $(HDS)/global.h $(HDS)/vhdl.h
src/vhdl/vhdlsilos.o: src/vhdl/vhdlsilos.c $(HDS)/config.h $(HDS)/global.h $(HDS)/vhdl.h $(HDS)/usr.h