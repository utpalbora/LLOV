#!/bin/bash

if python -c 'import pkgutil; exit(not pkgutil.find_loader("lit"))'; then
    echo 'lit found'
    lit -sv --param llov_site_config=./test/lit.site.cfg ./test
else
    echo 'Please install lit with'
    echo "pip install lit --user"
    exit 1
fi
