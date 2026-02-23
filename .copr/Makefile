.PHONY: srpm

SPEC := fio.spec
NAME := fio
VERSION := 3.50

srpm:
	dnf install -y git
	set -e && \
	TMPDIR=$$(mktemp -d) && \
	trap "rm -rf $$TMPDIR" EXIT && \
	cd $(CURDIR) && \
	git archive --prefix=$(NAME)-$(VERSION)/ HEAD | \
		gzip > $${TMPDIR}/$(NAME)-$(VERSION).tar.gz && \
	cp $(CURDIR)/$(SPEC) $${TMPDIR}/$(SPEC) && \
	rpmbuild -bs $${TMPDIR}/$(SPEC) \
		--define "_sourcedir $${TMPDIR}" \
		--define "_srcrpmdir $(outdir)"
