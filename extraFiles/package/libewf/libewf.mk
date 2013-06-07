LIBEWF_VERSION=20130331
LIBEWF_SOURCE = libewf-experimental-20130331.tar.gz
LIBEWF_SITE = https://libewf.googlecode.com/files/
LIBEWF_AUTORECONF = NO
LIBEWF_INSTALL_STAGING = NO
LIBEWF_INSTALL_TARGET = YES
LIBEWF_DEPENDENCIES = uclibc
$(eval $(autotools-package))
