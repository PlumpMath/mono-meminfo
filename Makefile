all: perm clean swig mono run

perm:
	chmod +x ./util/*.sh

clean: perm
	./util/clean.sh

mono: perm
	./util/mono.sh

run: perm
	./util/run.sh

swig: perm
	./util/swig.sh
