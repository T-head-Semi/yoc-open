# Compiler and flags
CXX = gcc
CXXFLAGS = -static -I./include -I./include/amrwb -I./src -lc -lm

# Source files
LIBSOURCE = \
    src/highpass_400hz_at_12k8.cpp \
    src/low_pass_filt_7k.cpp \
    src/interpolate_isp.cpp \
    src/isp_az.cpp \
    src/get_amr_wb_bits.cpp \
    src/isf_extrapolation.cpp \
    src/qpisf_2s.cpp \
    src/dec_alg_codebook.cpp \
    src/pvamrwbdecoder.cpp \
    src/synthesis_amr_wb.cpp \
    src/weight_amrwb_lpc.cpp \
    src/median5.cpp \
    src/qisf_ns.cpp \
    src/wb_syn_filt.cpp \
    src/q_gain2_tab.cpp \
    src/pit_shrp.cpp \
    src/highpass_50hz_at_12k8.cpp \
    src/qpisf_2s_tab.cpp \
    src/dec_acelp_4p_in_64.cpp \
    src/normalize_amr_wb.cpp \
    src/scale_signal.cpp \
    src/isp_isf.cpp \
    src/oversamp_12k8_to_16k.cpp \
    src/lagconceal.cpp \
    src/dec_acelp_2p_in_64.cpp \
    src/homing_amr_wb_dec.cpp \
    src/pvamrwb_math_op.cpp \
    src/phase_dispersion.cpp \
    src/mime_io.cpp \
    src/pred_lt4.cpp \
    src/preemph_amrwb_dec.cpp \
    src/qisf_ns_tab.cpp \
    src/voice_factor.cpp \
    src/dec_gain2_amr_wb.cpp \
    src/agc2_amr_wb.cpp \
    src/band_pass_6k_7k.cpp \
    src/deemphasis_32.cpp \
    src/dtx_decoder_amr_wb.cpp \
    src/noise_gen_amrwb.cpp \
    test/amrwb_test.cpp

# Object files
OBJECTS = $(LIBSOURCE:.cpp=.o)

# Executable target
TARGET = main_executable

# Installation path
INSTALL_PATH = $(DESTDIR)/usr/local

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -static $< -o $@

install: $(TARGET)
	mkdir -p $(INSTALL_PATH)/bin
	cp $(TARGET) $(INSTALL_PATH)/bin/

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all install clean