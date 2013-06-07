DCFLDD_VERSION=1.3.4-1
DCFLDD_SOURCE = dcfldd-1.3.4-1.tar.gz
DCFLDD_SITE = http://prdownloads.sourceforge.net/dcfldd
DCFLDD_AUTORECONF = NO
DCFLDD_INSTALL_STAGING = NO
DCFLDD_INSTALL_TARGET = YES
DCFLDD_DEPENDENCIES = uclibc
$(eval $(autotools-package))
