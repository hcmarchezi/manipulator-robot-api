TEMPLATE = subdirs

SUBDIRS += \
    tests \
    domain \
    persistence \
    utils 

persistence.depends = domain utils

tests.depends = domain persistence


