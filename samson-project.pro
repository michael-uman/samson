TEMPLATE = subdirs

SUBDIRS +=  samsonlib \
            qtSamson \
            qmlSamson

qtSamson.depends = samsonlib
qmlSamson.depends = samsonlib
