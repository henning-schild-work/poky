SUMMARY = "A sophisticated Numeric Processing Package for Python"
SECTION = "devel/python"
LICENSE = "BSD-3-Clause & BSD-2-Clause & PSF & Apache-2.0 & BSD & MIT"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=1a32aba007a415aa8a1c708a0e2b86a1"

SRCNAME = "numpy"

SRC_URI = "https://github.com/${SRCNAME}/${SRCNAME}/releases/download/v${PV}/${SRCNAME}-${PV}.tar.gz \
           file://0001-Don-t-search-usr-and-so-on-for-libraries-by-default-.patch \
           file://0001-npy_cpu-Add-riscv-support.patch \
           ${CONFIGFILESURI} \
           file://0001-numpy-random-setup.py-remove-the-detection-of-x86-ta.patch \
           "
SRC_URI[md5sum] = "c48b2ad785f82cdfe28c907ce35e2a71"
SRC_URI[sha256sum] = "47b7b6145e7ba5918ce26be25999b6d4b35cf9fbfdf46b7da50090ffdb020445"

UPSTREAM_CHECK_URI = "https://github.com/numpy/numpy/releases"
UPSTREAM_CHECK_REGEX = "(?P<pver>\d+(\.\d+)+)\.tar"

# Needed for building with gcc 4.x from centos 7
CFLAGS_append_class-native = " -std=c99"

CONFIGFILESURI ?= ""

CONFIGFILESURI_aarch64 = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_arm = " \
    file://config.h \
    file://numpyconfig.h \
"
CONFIGFILESURI_armeb = " \
    file://config.h \
    file://numpyconfig.h \
"
CONFIGFILESURI_mipsarcho32el = " \
    file://config.h \
    file://numpyconfig.h \
"
CONFIGFILESURI_x86 = " \
    file://config.h \
    file://numpyconfig.h \
"
CONFIGFILESURI_x86-64 = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_mipsarcho32eb = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_powerpc = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_powerpc64 = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_mipsarchn64eb = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_mipsarchn64el = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_mipsarchn32eb = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_mipsarchn32el = " \
    file://config.h \
    file://_numpyconfig.h \
"
CONFIGFILESURI_riscv64 = " \
    file://config.h \
    file://_numpyconfig.h \
"

S = "${WORKDIR}/numpy-${PV}"

CLEANBROKEN = "1"

# Make the build fail and replace *config.h with proper one
# This is a ugly, ugly hack - Koen
do_compile_prepend_class-target() {
    ${STAGING_BINDIR_NATIVE}/${PYTHON_PN}-native/${PYTHON_PN} setup.py build ${DISTUTILS_BUILD_ARGS} || \
    true
    cp ${WORKDIR}/*config.h ${S}/build/$(ls ${S}/build | grep src)/numpy/core/include/numpy/
}

FILES_${PN}-staticdev += "${PYTHON_SITEPACKAGES_DIR}/numpy/core/lib/*.a"

# install what is needed for numpy.test()
RDEPENDS_${PN} = "${PYTHON_PN}-unittest \
                  ${PYTHON_PN}-difflib \
                  ${PYTHON_PN}-pprint \
                  ${PYTHON_PN}-pickle \
                  ${PYTHON_PN}-shell \
                  ${PYTHON_PN}-nose \
                  ${PYTHON_PN}-doctest \
                  ${PYTHON_PN}-datetime \
                  ${PYTHON_PN}-distutils \
                  ${PYTHON_PN}-misc \
                  ${PYTHON_PN}-mmap \
                  ${PYTHON_PN}-netclient \
                  ${PYTHON_PN}-numbers \
                  ${PYTHON_PN}-pydoc \
                  ${PYTHON_PN}-pkgutil \
                  ${PYTHON_PN}-email \
                  ${PYTHON_PN}-compression \
                  ${PYTHON_PN}-ctypes \
                  ${PYTHON_PN}-threading \
"

RDEPENDS_${PN}_class-native = ""

BBCLASSEXTEND = "native nativesdk"
