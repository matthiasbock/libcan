
include mingw.mk
include lib/pcan-basic.mk

$(TESTDIR)/test-pcan.exe: $(TESTDIR)/test-pcan.cpp $(LIBSRCS) $(PCANBASIC_DLL64)
	$(MINGW_CPP) $(MINGW_CPPFLAGS) -I$(PCANBASIC_INCDIR) $^ -o $@

test-pcan.exe: $(TESTDIR)/test-pcan.exe
