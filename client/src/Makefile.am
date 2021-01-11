lib_LTLIBRARIES = libunifyfs.la
libunifyfsdir = $(includedir)

if HAVE_GOTCHA
lib_LTLIBRARIES += libunifyfs_gotcha.la
libunifyfs_gotchadir = $(includedir)
endif

if HAVE_FORTRAN
lib_LTLIBRARIES += libunifyfsf.la
endif

AM_CFLAGS = -Wall -Wno-strict-aliasing -Werror

include_HEADERS = unifyfs.h

if HAVE_FORTRAN
include_HEADERS += unifyfsf.h
endif

OPT_FLAGS =
OPT_LIBS =
OPT_SRCS =

if USE_PMIX
  OPT_FLAGS += -DUSE_PMIX
  OPT_LIBS += -lpmix
endif

if USE_PMI2
  OPT_FLAGS += -DUSE_PMI2
  OPT_LIBS += -lpmi2
endif

CLIENT_COMMON_CPPFLAGS = \
  -Wall -Werror \
  $(OPT_FLAGS) \
  -I$(top_builddir)/client \
  -I$(top_srcdir)/common/src

CLIENT_COMMON_CFLAGS = \
  -Wall -Werror \
  $(MPI_CFLAGS) \
  $(MARGO_CFLAGS)

CLIENT_COMMON_LDFLAGS = \
  -version-info $(LIBUNIFYFS_LT_VERSION) \
  $(MPI_CLDFLAGS) \
  $(MARGO_LDFLAGS)

CLIENT_COMMON_LIBADD = \
  $(OPT_LIBS) \
  $(MARGO_LIBS) \
  -lm -lrt -lcrypto -lpthread

BASE_SRCS = \
  $(OPT_SRCS) \
  ../../common/src/arraylist.h \
  ../../common/src/arraylist.c \
  ../../common/src/cm_enumerator.h \
  ../../common/src/cm_enumerator.c \
  ../../common/src/ini.h \
  ../../common/src/ini.c \
  ../../common/src/rm_enumerator.h \
  ../../common/src/rm_enumerator.c \
  ../../common/src/seg_tree.h \
  ../../common/src/seg_tree.c \
  ../../common/src/slotmap.h \
  ../../common/src/slotmap.c \
  ../../common/src/tinyexpr.h \
  ../../common/src/tinyexpr.c \
  ../../common/src/tree.h \
  ../../common/src/unifyfs_const.h \
  ../../common/src/unifyfs_configurator.h \
  ../../common/src/unifyfs_configurator.c \
  ../../common/src/unifyfs_keyval.h \
  ../../common/src/unifyfs_keyval.c \
  ../../common/src/unifyfs_log.h \
  ../../common/src/unifyfs_log.c \
  ../../common/src/unifyfs_logio.h \
  ../../common/src/unifyfs_logio.c \
  ../../common/src/unifyfs_meta.h \
  ../../common/src/unifyfs_meta.c \
  ../../common/src/unifyfs_misc.c \
  ../../common/src/unifyfs_misc.h \
  ../../common/src/unifyfs_rpc_util.h \
  ../../common/src/unifyfs_rpc_util.c \
  ../../common/src/unifyfs_rpc_types.h \
  ../../common/src/unifyfs_client_rpcs.h \
  ../../common/src/unifyfs_server_rpcs.h \
  ../../common/src/unifyfs_rc.h \
  ../../common/src/unifyfs_rc.c \
  ../../common/src/unifyfs_shm.h \
  ../../common/src/unifyfs_shm.c \
  ../../common/src/unifyfs-stack.h \
  ../../common/src/unifyfs-stack.c

CLIENT_COMMON_SOURCES = \
  $(BASE_SRCS) \
  client_read.c \
  client_read.h \
  margo_client.c \
  margo_client.h \
  unifyfs.c \
  unifyfs.h \
  unifyfs-dirops.h \
  unifyfs-dirops.c \
  unifyfs-fixed.c \
  unifyfs-fixed.h \
  unifyfs-internal.h \
  unifyfs-stdio.c \
  unifyfs-stdio.h \
  unifyfs-sysio.c \
  unifyfs-sysio.h \
  uthash.h \
  utlist.h

if USE_PMPI_WRAPPERS
CLIENT_COMMON_SOURCES += \
  pmpi_wrappers.c \
  pmpi_wrappers.h
endif

libunifyfs_la_SOURCES  = $(CLIENT_COMMON_SOURCES)
libunifyfs_la_CPPFLAGS = $(CLIENT_COMMON_CPPFLAGS)
libunifyfs_la_CFLAGS   = $(CLIENT_COMMON_CFLAGS)
libunifyfs_la_LDFLAGS  = $(CLIENT_COMMON_LDFLAGS)
libunifyfs_la_LIBADD   = $(CLIENT_COMMON_LIBADD)

if HAVE_GOTCHA

libunifyfs_gotcha_la_SOURCES  = $(CLIENT_COMMON_SOURCES) gotcha_map_unifyfs_list.c
libunifyfs_gotcha_la_CPPFLAGS = $(CLIENT_COMMON_CPPFLAGS) -DUNIFYFS_GOTCHA
libunifyfs_gotcha_la_CFLAGS   = $(CLIENT_COMMON_CFLAGS) $(GOTCHA_CFLAGS)
libunifyfs_gotcha_la_LDFLAGS  = $(CLIENT_COMMON_LDFLAGS) $(GOTCHA_LDFLAGS)
libunifyfs_gotcha_la_LIBADD   = $(CLIENT_COMMON_LIBADD) -lgotcha

endif

if HAVE_FORTRAN

libunifyfsf_la_SOURCES  = unifyfsf.c
libunifyfsf_la_CPPFLAGS = $(CLIENT_COMMON_CPPFLAGS)
libunifyfsf_la_CFLAGS   = $(AM_CFLAGS) $(CLIENT_COMMON_CFLAGS)
libunifyfsf_la_LIBADD   = libunifyfs_gotcha.la

endif
