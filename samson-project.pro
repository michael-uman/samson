TEMPLATE = subdirs

SUBDIRS +=  samsonlib \
            qtSamson

qtSamson.depends = samsonlib
