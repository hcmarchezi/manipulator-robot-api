TEMPLATE = subdirs

SUBDIRS += \
    application \
    tests \
    domain \
    persistence \
    utils

persistence.depends = domain utils

tests.depends = domain persistence

application.depends = domain persistence

