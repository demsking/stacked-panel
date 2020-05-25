# Generate the AUTHORS file
authors:
	git log --format="%aN <%ae>"                 	\
		| sort                                     	\
		| uniq -c                                  	\
		| sort -rn                                 	\
		| awk '$$1>=$THRESHOLD {$$1=""; print $$0}'	\
		| cut -d" " -f2-                           	\
		> AUTHORS

build/cpplint.py:
	mkdir -p build
	curl -sL https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py > $@
	chmod +x $@

cpplint: build/cpplint.py
	./build/cpplint.py --counting=detailed src/*.h src/**/*.h src/**/*.cpp

cppcheck:
	cppcheck src --quiet --error-exitcode=1 -I src \
    --enable=style,warning,performance,portability,information,missingInclude

cppcheck-report: cppcheck
	cppcheck src          \
    --quiet             \
    --enable=all        \
    -I src              \
    --xml 2> error.xml

cppcheck-htmlreport: cppcheck-report
	cppcheck-htmlreport            \
    --file=error.xml             \
    --report-dir=cppcheck-report \
    --source-dir=.

lint: cpplint cppcheck
